/* FreeRTOS.org includes. */
#include "FreeRTOS.h"
#include "task.h"

/*-----------------------------------------------------------*/

void vPrintString( const char * pcString )
{
const uint32_t ulTxFifoFullBit = 0x80000000UL;

	while( *pcString != 0x00 )
	{
		while( ( UART0_REG( UART_REG_TXFIFO ) & ulTxFifoFullBit ) != 0UL );
		UART0_REG( UART_REG_TXFIFO ) = *pcString;
		pcString++;
	}
}
/*-----------------------------------------------------------*/

/* The task functions. */
void vContinuousProcessingTask( void *pvParameters );
void vPeriodicTask( void *pvParameters );

/* Define the strings that will be passed in as the task parameters.  These are
defined const and off the stack to ensure they remain valid when the tasks are
executing. */
const char *pcTextForTask1 = "Continuous task 1\n";
const char *pcTextForTask2 = "Continuous task 2\n";
const char *pcTextForPeriodicTask = "Periodic task\n";

/*-----------------------------------------------------------*/

int main( void )
{
	/* Create two instances of the continuous processing task, both at priority	1. */
	xTaskCreate( vContinuousProcessingTask, "Task 1", 1000, (void*)pcTextForTask1, 1, NULL );
	xTaskCreate( vContinuousProcessingTask, "Task 2", 1000, (void*)pcTextForTask2, 1, NULL );

	/* Create one instance of the periodic task at priority 2. */
	xTaskCreate( vPeriodicTask, "Task 3", 1000, (void*)pcTextForPeriodicTask, 2, NULL );

	/* Start the scheduler to start the tasks executing. */
	vTaskStartScheduler();

	/* The following line should never be reached because vTaskStartScheduler()
	will only return if there was not enough FreeRTOS heap memory available to
	create the Idle and (if configured) Timer tasks.  Heap management, and
	techniques for trapping heap exhaustion, are described in the book text. */
	for( ;; );
	return 0;
}
/*-----------------------------------------------------------*/

void vContinuousProcessingTask( void *pvParameters )
{
	unsigned long i = 0;
	char *pcTaskName;

	/* The string to print out is passed in via the parameter.  Cast this to a
	character pointer. */
	pcTaskName = ( char * ) pvParameters;

	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
		// In time slice only print every ms
		volatile uint64_t *now = (volatile uint64_t*)(CLINT_CTRL_ADDR + CLINT_MTIME);
		volatile uint64_t then = *now + (RTC_FREQ / 1000);

		/* Print out the name of this task.  This task just does this repeatedly
		without ever blocking or delaying. */
		vPrintString( pcTaskName );

		// Wait.
		while (*now < then){}
	}
}

/*-----------------------------------------------------------*/

void vPeriodicTask( void *pvParameters )
{
	TickType_t xLastWakeTime;
	const TickType_t xDelay20ms = pdMS_TO_TICKS( 20 );

	/* The xLastWakeTime variable needs to be initialized with the current tick
	count.  Note that this is the only time we access this variable.  From this
	point on xLastWakeTime is managed automatically by the vTaskDelayUntil()
	API function. */
	xLastWakeTime = xTaskGetTickCount();

	/* As per most tasks, this task is implemented in an infinite loop. */
	for( ;; )
	{
		/* Print out the name of this task. */
		vPrintString(pcTextForPeriodicTask);

		/* We want this task to execute exactly every 20 milliseconds. */
		vTaskDelayUntil( &xLastWakeTime, xDelay20ms );
	}
}
