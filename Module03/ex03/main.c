/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 10:03:42 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/06 17:34:51 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define R 	(1 << PD5)
#define G 	(1 << PD6)
#define B	(1 << PD3)
#define SET_RGB_LED (DDRD |= R | G | B)

#define BAUD 115200UL
#define MYUBBR ((float)(F_CPU) / (16UL * BAUD)) - 1

unsigned int round_ubbr() {
    if (MYUBBR >= 0)
        return (unsigned int)(MYUBBR + 0.5f);
    else
        return (unsigned int)(MYUBBR - 0.5f);
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b) {
    OCR0B = r;
	OCR0A = g;
    OCR2B = b;
}

int is_alpha( char c ) { return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')); }
int is_lowercase( char c ) { return c >= 'a' && c <= 'z'; }

int is_in_tab(char c, char *tab) {
	char *tmp = tab;
	
	while (*tmp) {
		if (c == *tmp) return 1;
	}
	return 0;
}

int is_all_hex(char *str) {
	char *char_auth = "0123456789ABCDEF#";
	char *tmp = str;

	while (*tmp) {
		if (!is_in_tab(*tmp, char_auth)) {
			return 0;
		}
	}
	return 1;
}

int hex2int(char ch)
{
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    if (ch >= 'A' && ch <= 'F')
        return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f')
        return ch - 'a' + 10;
    return -1;
}

void uart_tx ( char data ) {
	while ( !(UCSR0A & (1<<UDRE0)) );
	UDR0 = data;
}

char uart_rx(void) {
	while ( !(UCSR0A & (1<<RXC0)) );
	return UDR0;
}

void uart_init ( unsigned int ubrr ) {
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	
	UCSR0B |= (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);
	UCSR0C |= (1<<UCSZ00) | (1<<UCSZ01);
}

ISR(USART_RX_vect) {
	char c;
	char RGB[7] = {0};

	uint8_t i = 0;
	do {
		while (i < 7) {
			c = uart_rx();
			uart_tx(c);
			if (is_alpha(c)) {
				if (is_lowercase(c)) c -= 32;
			}
			RGB[i] = c;
		}
	} while (RGB[0] != '#' && is_all_hex(RGB));

	int red = hex2int(RGB[1]) + 16 * (RGB[2]);
	int green = hex2int(RGB[3]) + 16 * (RGB[4]);
	int blue = hex2int(RGB[5]) + 16 * (RGB[6]);
	
	set_rgb(red, green, blue);
}

int main(void) {
	SET_RGB_LED;
	uart_init(round_ubbr());
	while (1);
}
