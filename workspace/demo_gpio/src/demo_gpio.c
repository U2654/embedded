// See LICENSE for license details.

#include <stdio.h>
#include <stdlib.h>
#include "platform.h"
#include <string.h>
#include "plic/plic_driver.h"
#include "encoding.h"
#include <unistd.h>
#include "stdatomic.h"

#define HAS_BOARD_BUTTONS
#define BUTTON_0_OFFSET 0
#define BUTTON_1_OFFSET 1
#define BUTTON_2_OFFSET 2

#define INT_DEVICE_BUTTON_0 (INT_GPIO_BASE + BUTTON_0_OFFSET)
#define INT_DEVICE_BUTTON_1 (INT_GPIO_BASE + BUTTON_1_OFFSET)
#define INT_DEVICE_BUTTON_2 (INT_GPIO_BASE + BUTTON_2_OFFSET)

extern void trap_entry();

void reset_demo (void);

// Structures for registering different interrupt handlers
// for different parts of the application.
typedef void (*function_ptr_t) (void);

void no_interrupt_handler (void) {};

// irq handlers
function_ptr_t g_ext_interrupt_handlers[PLIC_NUM_INTERRUPTS];

// Instance data for the PLIC.
plic_instance_t g_plic;


/*Entry Point for PLIC Interrupt Handler*/
void handle_m_ext_interrupt(){
  plic_source int_num  = PLIC_claim_interrupt(&g_plic);
  if ((int_num >=1 ) && (int_num < PLIC_NUM_INTERRUPTS)) {
    g_ext_interrupt_handlers[int_num]();
  }
  else {
    exit(1 + (uintptr_t) int_num);
  }
  PLIC_complete_interrupt(&g_plic, int_num);
}


/*Entry Point for Machine Timer Interrupt Handler*/
void handle_m_time_interrupt(){

  clear_csr(mie, MIP_MTIP);

  // Reset the timer for 3s in the future.
  // This also clears the existing timer interrupt.

  volatile uint64_t * mtime       = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIME);
  volatile uint64_t * mtimecmp    = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIMECMP);
  uint64_t now = *mtime;
  uint64_t then = now + RTC_FREQ;
  *mtimecmp = then;

  // read the current value of the LEDS and invert them.
  uint32_t leds = GPIO_REG(GPIO_OUTPUT_VAL);

  GPIO_REG(GPIO_OUTPUT_VAL) ^= ((0x1 << RED_LED_OFFSET)   |
				(0x1 << GREEN_LED_OFFSET) |
				(0x1 << BLUE_LED_OFFSET));

  // Re-enable the timer interrupt.
  set_csr(mie, MIP_MTIP);

}


#ifdef HAS_BOARD_BUTTONS
void button_0_handler(void) {
  // Red LED on
  GPIO_REG(GPIO_OUTPUT_VAL) |= (0x1 << RED_LED_OFFSET);

  // Clear the GPIO Pending interrupt by writing 1.
  GPIO_REG(GPIO_RISE_IP) = (0x1 << BUTTON_0_OFFSET);

};

void button_1_handler(void) {
  // Green LED On
  GPIO_REG(GPIO_OUTPUT_VAL) |= (1 << GREEN_LED_OFFSET);

  // Clear the GPIO Pending interrupt by writing 1.
  GPIO_REG(GPIO_RISE_IP) = (0x1 << BUTTON_1_OFFSET);

};


void button_2_handler(void) {
  // Blue LED On
  GPIO_REG(GPIO_OUTPUT_VAL) |= (1 << BLUE_LED_OFFSET);

  GPIO_REG(GPIO_RISE_IP) = (0x1 << BUTTON_2_OFFSET);

};
#endif

void reset_demo (){

  // Disable the machine & timer interrupts until setup is done.

  clear_csr(mie, MIP_MEIP);
  clear_csr(mie, MIP_MTIP);

  for (int ii = 0; ii < PLIC_NUM_INTERRUPTS; ii ++){
    g_ext_interrupt_handlers[ii] = no_interrupt_handler;
  }

#ifdef HAS_BOARD_BUTTONS
  g_ext_interrupt_handlers[INT_DEVICE_BUTTON_0] = button_0_handler;
  g_ext_interrupt_handlers[INT_DEVICE_BUTTON_1] = button_1_handler;
  g_ext_interrupt_handlers[INT_DEVICE_BUTTON_2] = button_2_handler;

  // Have to enable the interrupt both at the GPIO level,
  // and at the PLIC level.
  PLIC_enable_interrupt (&g_plic, INT_DEVICE_BUTTON_0);
  PLIC_enable_interrupt (&g_plic, INT_DEVICE_BUTTON_1);
  PLIC_enable_interrupt (&g_plic, INT_DEVICE_BUTTON_2);

  // Priority must be set > 0 to trigger the interrupt.
  PLIC_set_priority(&g_plic, INT_DEVICE_BUTTON_0, 1);
  PLIC_set_priority(&g_plic, INT_DEVICE_BUTTON_1, 1);
  PLIC_set_priority(&g_plic, INT_DEVICE_BUTTON_2, 1);

  GPIO_REG(GPIO_RISE_IE) |= (1 << BUTTON_0_OFFSET);
  GPIO_REG(GPIO_RISE_IE) |= (1 << BUTTON_1_OFFSET);
  GPIO_REG(GPIO_RISE_IE) |= (1 << BUTTON_2_OFFSET);

#endif

    // Set the machine timer to go off in 3 seconds.
    // The
    volatile uint64_t * mtime       = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIME);
    volatile uint64_t * mtimecmp    = (uint64_t*) (CLINT_CTRL_ADDR + CLINT_MTIMECMP);
    uint64_t now = *mtime;
    uint64_t then = now + 2*RTC_FREQ/4;
    *mtimecmp = then;

    // Enable the Machine-External bit in MIE
    set_csr(mie, MIP_MEIP);

    // Enable the Machine-Timer bit in MIE
//    set_csr(mie, MIP_MTIP);

    // Enable interrupts in general.
    set_csr(mstatus, MSTATUS_MIE);
}

int main(int argc, char **argv)
{
  // set everything up
  write_csr(mtvec, &trap_entry);

  // Set up the GPIOs such that the LED GPIO
  // can be used as both Inputs and Outputs.

#ifdef HAS_BOARD_BUTTONS
  GPIO_REG(GPIO_OUTPUT_EN)  &= ~((0x1 << BUTTON_0_OFFSET) | (0x1 << BUTTON_1_OFFSET) | (0x1 << BUTTON_2_OFFSET));
  GPIO_REG(GPIO_PULLUP_EN)  &= ~((0x1 << BUTTON_0_OFFSET) | (0x1 << BUTTON_1_OFFSET) | (0x1 << BUTTON_2_OFFSET));
  GPIO_REG(GPIO_INPUT_EN)   |=  ((0x1 << BUTTON_0_OFFSET) | (0x1 << BUTTON_1_OFFSET) | (0x1 << BUTTON_2_OFFSET));
#endif

  GPIO_REG(GPIO_INPUT_EN)    &= ~((0x1<< RED_LED_OFFSET) | (0x1<< GREEN_LED_OFFSET) | (0x1 << BLUE_LED_OFFSET)) ;
  GPIO_REG(GPIO_OUTPUT_EN)   |=  ((0x1<< RED_LED_OFFSET)| (0x1<< GREEN_LED_OFFSET) | (0x1 << BLUE_LED_OFFSET)) ;
  GPIO_REG(GPIO_OUTPUT_VAL)  |=   (0x1 << BLUE_LED_OFFSET) ;
  GPIO_REG(GPIO_OUTPUT_VAL)  &=  ~((0x1<< RED_LED_OFFSET) | (0x1<< GREEN_LED_OFFSET)) ;

  PLIC_init(&g_plic,
	    PLIC_CTRL_ADDR,
	    PLIC_NUM_INTERRUPTS,
	    PLIC_NUM_PRIORITIES);

  reset_demo();

  while (1){
	 asm ("wfi");
  }

  return 0;

}
