#include "sys.h"
#include "delay.h"
#include "led.h"
#include "usart.h"

int main(void)
{
	//char str = 'c';
	char str[] = "kevin serial!";
    HAL_Init();                     
    Stm32_Clock_Init(360,25,2,8);   
    delay_init(180);                
	usart_init(rb);
    LED_Init();                       
    while(1)
    {
		HAL_UART_Transmit(&UART_Handler, (uint8_t *)str, 13, 1000);
		while(__HAL_UART_GET_FLAG(&UART_Handler, UART_FLAG_TC) != SET);	
		//usart_putstr(rb, str);
		//usart_putc(str);
		LED0 = !LED0;
		delay_ms(500);
    }
}
 
