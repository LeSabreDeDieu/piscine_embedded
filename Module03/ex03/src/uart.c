/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uart.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayfallahgabsi <sayfallahgabsi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:00:39 by sayfallahga       #+#    #+#             */
/*   Updated: 2025/03/07 13:00:54 by sayfallahga      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void uart_tx(char data) {
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

char uart_rx(void) {
	while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

void uart_init(unsigned int ubrr) {
	UBRR0H = (unsigned char)(ubrr >> 8);
	UBRR0L = (unsigned char)ubrr;
	
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
}

void uart_printstr(const char* str) {
	while (*str) uart_tx(*str++);
}

ISR(USART_RX_vect) {
	char c;
	char RGB[8] = {0};
	uint8_t i = 0;
	
	while (i < 7) {
		c = uart_rx();
		uart_tx(c);
		
		if (c == '\b' || c == 127) { 
			if (i > 0) {
				uart_printstr("\b \b"); 
				i--; 
			}
			continue; 
		}
		
		RGB[i] = c;
		i++;
	}
	RGB[i] = 0;
	
	if (RGB[0] != '#' || !is_all_hex(RGB)) {
		uart_printstr("\n\rInvalid color format! Use #RRGGBB\n\r");
		return;
	}
	
	int red   = 16 * hex2int(RGB[1]) + hex2int(RGB[2]);
	int green = 16 * hex2int(RGB[3]) + hex2int(RGB[4]);
	int blue  = 16 * hex2int(RGB[5]) + hex2int(RGB[6]);
	
	SET_RGB_LED;
	set_rgb(red, green, blue);
	_delay_ms(1000);
	uart_printstr("\n\r");
}