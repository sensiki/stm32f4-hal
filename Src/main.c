#include "sys.h"
#include "delay.h"
#include "led.h"
#include "usart.h"

int main(void)
{
	//char str = 'c';
	//char str[] = "kevin serial!";
    HAL_Init();                     
    Stm32_Clock_Init(360,25,2,8);   
    delay_init(180);                
	usart_init(rb);
    LED_Init();                       
    while(1)
    {
		while(!usart_data_available(rb))
			;
		usart_putc(usart_getc(rb));

		LED0 = !LED0;
		delay_ms(500);
    }
}
 
