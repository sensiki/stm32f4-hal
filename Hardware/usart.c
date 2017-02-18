#include "usart.h"

void usart_init(ring_buffer *rb)
{
	rb_init(rb, USART_RX_BUF_SIZE, rx_buf);

	UART_Handler.Instance = USART1;
	UART_Handler.Init.BaudRate = 115200;
	UART_Handler.Init.WordLength = UART_WORDLENGTH_8B; 
	UART_Handler.Init.StopBits = UART_STOPBITS_1;	 
	UART_Handler.Init.Parity = UART_PARITY_NONE;
	UART_Handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	UART_Handler.Init.Mode = UART_MODE_TX_RX;		   
	HAL_UART_Init(&UART_Handler);				
}

void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{
	GPIO_InitTypeDef GPIO_Initure;

	if(huart->Instance == USART1) {
		__HAL_RCC_GPIOA_CLK_ENABLE();			
		__HAL_RCC_USART1_CLK_ENABLE();			

		GPIO_Initure.Pin = GPIO_PIN_9;			
		GPIO_Initure.Mode = GPIO_MODE_AF_PP;		
		GPIO_Initure.Pull = GPIO_PULLUP;		
		GPIO_Initure.Speed = GPIO_SPEED_FAST;		
		GPIO_Initure.Alternate = GPIO_AF7_USART1;	
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	

		GPIO_Initure.Pin = GPIO_PIN_10;			
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   

		HAL_NVIC_EnableIRQ(USART1_IRQn);		
		HAL_NVIC_SetPriority(USART1_IRQn, 3, 3);
	}
}

uint32_t usart_tx(const uint8_t *buf, uint32_t len) {
	uint32_t txed = 0;

	HAL_UART_Transmit(&UART_Handler, (u8 *)buf[txed++], len, 1000);
	while(__HAL_UART_GET_FLAG(&UART_Handler, UART_FLAG_TC) != SET);	

	return txed;
}

uint32_t usart_rx(ring_buffer *rb, uint8_t *buf, uint32_t len) {
	uint32 rxed = 0;
	while (usart_data_available(rb) && rxed < len) {
		*buf++ = usart_getc(rb);
		rxed++;
	}   
	return rxed;
}

void usart_putudec(ring_buffer *rb, uint32_t val) {
	char digits[12];
	int i = 0;

	do {
		digits[i++] = val % 10 + '0';
		val /= 10;
	} while (val > 0);

	while (--i >= 0) {
		usart_putc(digits[i]);
	}
}


void USART1_IRQHandler(void)                	
{ 
	uint32_t timeout = 0;

	HAL_UART_IRQHandler(&UART_Handler);

	timeout = 0;
	while (HAL_UART_GetState(&UART_Handler) != HAL_UART_STATE_READY){
		timeout++;
		if(timeout > HAL_MAX_DELAY) break;		
	}

	timeout = 0;
	while(HAL_UART_Receive_IT(&UART_Handler, (u8 *)rx_buffer, RXBUFFERSIZE) == HAL_OK){

		rb_push_insert(rb, rx_buffer[0]);
	}
} 



