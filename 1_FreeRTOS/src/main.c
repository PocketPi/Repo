/* Standard includes. */
#include <stdint.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "timers.h"


#include "stm32f4xx.h"

/* The period of the example software timer, specified in milliseconds, and
converted to ticks using the portTICK_RATE_MS constant. */
#define mainSOFTWARE_TIMER_PERIOD_MS		( 500 / portTICK_RATE_MS )

/*-----------------------------------------------------------*/
static void vLedTimerCallback( xTimerHandle xTimer );

static void init_hw(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;

  /* Enable the GPIO_LED Clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);

  /* Configure the GPIO_LED pin */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOG, &GPIO_InitStructure);

}

int main(void)
{
	xTimerHandle xLedTimer = NULL;

	init_hw();

	xLedTimer = xTimerCreate( 	( const signed char * ) "LEDTimer", /* A text name, purely to help debugging. */
								mainSOFTWARE_TIMER_PERIOD_MS,					/* The timer period, in this case 1000ms (1s). */
								pdTRUE,											/* This is a periodic timer, so xAutoReload is set to pdTRUE. */
								( void * ) 0,									/* The ID is not used, so can be set to anything. */
								vLedTimerCallback							/* The-DUSE_STM32F429I_DISCO callback function that switches the LED off. */
							);

	xTimerStart( xLedTimer, 0 );

	/* Start the tasks and timer running. */
	vTaskStartScheduler();

	for( ;; );
}
/*-----------------------------------------------------------*/

static void vLedTimerCallback( xTimerHandle xTimer )
{
	GPIOG->ODR ^= GPIO_Pin_13;
}

