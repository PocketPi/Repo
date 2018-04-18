/* Standard includes. */
#include <stdint.h>
#include <stdio.h>

/* Kernel includes. */
#include "FreeRTOS.h"
#include "timers.h"

#include "led.h"
#include "usart.h"
#include "shell.h"

/* The period of the example software timer, specified in milliseconds, and
converted to ticks using the portTICK_RATE_MS constant. */
#define mainSOFTWARE_TIMER_PERIOD_MS        ( 1000 / portTICK_RATE_MS )

/*-----------------------------------------------------------*/
static void vLedTimerCallback( xTimerHandle xTimer );

int main(void)
{
    xTimerHandle xLedTimer = NULL;

    setup_LED();
    setup_usart();

    const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
    my_printf("%s", CLEAR_SCREEN_ANSI);

    my_printf("Simple Embedded Shell - Build Time: %s\r\n", __TIME__);

    xTaskCreate(shell_task, "shell task", 1024, NULL, tskIDLE_PRIORITY, NULL);


    xLedTimer = xTimerCreate(   ( const char * ) "LEDTimer",
                                mainSOFTWARE_TIMER_PERIOD_MS,
                                pdTRUE,
                                ( void * ) 0,
                                vLedTimerCallback
                            );

    xTimerStart( xLedTimer, 0 );

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

