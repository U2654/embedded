#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "platform.h"

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

/* See https://www.freertos.org/Using-FreeRTOS-on-RISC-V.html */
#define configMTIME_BASE_ADDRESS 	( ( CLINT_CTRL_ADDR ) + 0xBFF8UL )
#define configMTIMECMP_BASE_ADDRESS ( ( CLINT_CTRL_ADDR ) + 0x4000UL )

#define configUSE_PREEMPTION			1
#define configUSE_IDLE_HOOK				0
#define configUSE_TICK_HOOK				0
#define configCPU_CLOCK_HZ				( 32768 )
#define configTICK_RATE_HZ				( ( TickType_t )  100)
#define configMAX_PRIORITIES			( 7 )
#define configMINIMAL_STACK_SIZE		( ( unsigned short ) 105 )
#define configTOTAL_HEAP_SIZE			( ( size_t ) 14500 )
#define configMAX_TASK_NAME_LEN			( 16 )
#define configUSE_TRACE_FACILITY		0
#define configUSE_16_BIT_TICKS			0
#define configIDLE_SHOULD_YIELD			0
#define configUSE_MUTEXES				1
#define configQUEUE_REGISTRY_SIZE		8
#define configCHECK_FOR_STACK_OVERFLOW	0
#define configUSE_RECURSIVE_MUTEXES		1
#define configUSE_MALLOC_FAILED_HOOK	0
#define configUSE_APPLICATION_TASK_TAG	0
#define configUSE_COUNTING_SEMAPHORES	1
#define configGENERATE_RUN_TIME_STATS	0
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 1

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 			0
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

/* Software timer definitions. */
#define configUSE_TIMERS				1
#define configTIMER_TASK_PRIORITY		( configMAX_PRIORITIES - 1 )
#define configTIMER_QUEUE_LENGTH		6
#define configTIMER_TASK_STACK_DEPTH	( 110 )

/* Task priorities.  Allow these to be overridden. */
#ifndef uartPRIMARY_PRIORITY
	#define uartPRIMARY_PRIORITY		( configMAX_PRIORITIES - 3 )
#endif

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet		1
#define INCLUDE_uxTaskPriorityGet		1
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	1
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay				1
#define INCLUDE_eTaskGetState			1
#define INCLUDE_xTimerPendFunctionCall	1
#define INCLUDE_xTaskAbortDelay				1
#define INCLUDE_xTaskGetHandle				1
#define INCLUDE_xSemaphoreGetMutexHolder	1

/* Normal assert() semantics without relying on the provision of an assert.h
header file. */
void vAssertCalled( void );
//#define configASSERT( x ) if( ( x ) == 0 ) vAssertCalled()

/* Overwrite some of the stack sizes allocated to various test and demo tasks.
Like all task stack sizes, the value is the number of words, not bytes. */
#define bktBLOCK_TIME_TASK_STACK_SIZE 100
#define notifyNOTIFIED_TASK_STACK_SIZE 110
#define priSUSPENDED_RX_TASK_STACK_SIZE 90
#define tmrTIMER_TEST_TASK_STACK_SIZE 100
#define ebRENDESVOUS_TEST_TASK_STACK_SIZE 100
#define ebEVENT_GROUP_SET_BITS_TEST_TASK_STACK_SIZE 115
#define genqMUTEX_TEST_TASK_STACK_SIZE 90
#define recmuRECURSIVE_MUTEX_TEST_TASK_STACK_SIZE 110

#endif /* FREERTOS_CONFIG_H */
