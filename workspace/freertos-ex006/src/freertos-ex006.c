/* FreeRTOS.org includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "wrap.h"

/*-----------------------------------------------------------*/

/* The task functions. */
void vTask1( void *pvParameters );
void vTask2( void *pvParameters );
void vTask3( void *pvParameters );

const char *pcTextForTask1 = "Task 1\n";
const char *pcTextForTask2 = "Task 2\n";
const char *pcTextForTask3 = "Task 3\n";

/*-----------------------------------------------------------*/
int main( void )
{
	/* _init for uart printf */
	_init();
	/* three tasks with different priorities */
	xTaskCreate( vTask1, "Task 1", 1000, (void*)pcTextForTask1, 2, NULL );
	xTaskCreate( vTask2, "Task 2", 1000, (void*)pcTextForTask2, 1, NULL );
	xTaskCreate( vTask3, "Task 3", 1000, (void*)pcTextForTask3, 1, NULL );

	/* start scheduler */
	vTaskStartScheduler();

	for( ;; );
	return 0;
}

/*-----------------------------------------------------------*/
void vTask1( void *pvParameters )
{
	TickType_t xLastWakeTime;
	const TickType_t xDelay = pdMS_TO_TICKS( 1000 );

	xLastWakeTime = xTaskGetTickCount();

	for( ;; )
	{
		printf(pcTextForTask1);
		/* periodic */
		vTaskDelayUntil( &xLastWakeTime, xDelay );
	}
}

/*-----------------------------------------------------------*/
void vTask2( void *pvParameters )
{
	for( ;; )
	{
		printf(pcTextForTask2);
	}
}

/*-----------------------------------------------------------*/
void vTask3( void *pvParameters )
{
	for( ;; )
	{
		printf(pcTextForTask3);
	}
}
