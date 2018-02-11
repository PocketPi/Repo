/* Standard includes. */
#include <stdint.h>
#include <stdio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "timers.h"


#include "stm32f4xx.h"

/* The period of the example software timer, specified in milliseconds, and
converted to ticks using the portTICK_RATE_MS constant. */
#define mainSOFTWARE_TIMER_PERIOD_MS        ( 100 / portTICK_RATE_MS )

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

    xLedTimer = xTimerCreate(   ( const   char * ) "LEDTimer",
                                mainSOFTWARE_TIMER_PERIOD_MS,
                                pdTRUE,
                                ( void * ) 0,
                                vLedTimerCallback
                            );

    xTimerStart( xLedTimer, 0 );

    printf("test\n");

    /* Start the tasks and timer running. */
    vTaskStartScheduler();

    for( ;; );
}
/*-----------------------------------------------------------*/

static void vLedTimerCallback( xTimerHandle xTimer )
{
    (void)xTimer;
    GPIOG->ODR ^= GPIO_Pin_13;
}

