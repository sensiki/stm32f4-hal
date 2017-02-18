#ifndef _USART_H_
#define _USART_H_

#include "sys.h"

#ifdef __cplusplus
extern "C"{
#endif

#include "ring_buffer.h"

#ifndef USART_RX_BUF_SIZE
#define USART_RX_BUF_SIZE 	64
#endif

#define RXBUFFERSIZE	1

UART_HandleTypeDef UART_Handler;

uint8_t rx_buf[USART_RX_BUF_SIZE];
uint8_t rxbuf;

struct ring_buffer *rb;

void usart_init(ring_buffer *rb);

uint32_t usart_tx(const uint8_t *buf, uint32_t len);
uint32_t usart_rx(ring_buffer *rb, uint8_t *buf, uint32_t len);
void usart_putudec(ring_buffer *rb, uint32_t val);

static inline void usart_putc(uint8_t byte) {
	while (!usart_tx(&byte, 1))
		;
}

static inline void usart_putstr(ring_buffer *rb, const char* str) {
	uint32_t i = 0;
	while (str[i] != '\0') {
		usart_putc(str[i++]);
	}
}

static inline uint8_t usart_getc(ring_buffer *rb) {
	return rb_remove(rb);
}

static inline uint32_t usart_data_available(ring_buffer *rb) {
	return rb_full_count(rb);
}

static inline void usart_reset_rx(ring_buffer *rb) {
	rb_reset(rb);
}

#ifdef __cplusplus
} // extern "C"
#endif

#endif //_USART_H_
