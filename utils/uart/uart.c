/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uart.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:00:39 by sayfallahga       #+#    #+#             */
/*   Updated: 2025/03/13 09:59:14 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "uart.h"
#include <stdio.h>

void uart_init ( void ) {
    UBRR0H = (unsigned char)((int)MYUBBR >> 8);
    UBRR0L = (unsigned char) MYUBBR;
    UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
}

void uart_init_r ( void ) {
    uart_init();
	UCSR0B |= (1 << RXEN0) | (1 << RXCIE0);
    SREG |= (1 << SREG_I);
}

void uart_init_w ( void ) {
    uart_init();
	UCSR0B |= (1 << TXEN0);
}

void uart_init_rw ( void ) {
    uart_init();
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0) | (1 << RXCIE0);
    SREG |= (1 << SREG_I);
}

char uart_rx ( void ) {
	while ( !(UCSR0A & (1<<RXC0)) );
	return UDR0;
}

char read_char ( void ) {
    return (uart_rx());
}

void uart_tx ( const char data ) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void uart_printchar ( const char c ) {
    uart_tx(c);
}

void uart_printstr ( const char* str ) {
	while (*str) uart_tx(*str++);
}

void print_uint ( const uint32_t value ) {
    char *buffer = "";
    sprintf(buffer, "%zu", value);
    uart_printstr(buffer);
}

void print_int ( const int value ) {
    char *buffer = "";
    sprintf(buffer, "%d", value);
    uart_printstr(buffer);
}

void print_float ( const float value ) {
    char *buffer = "";
    sprintf(buffer, "%f", value);
    uart_printstr(buffer);
}

void print_hexa ( const uint32_t value, uint8_t uppercase ) {
    char *buffer = "";
    if (uppercase) sprintf(buffer, "%X", value);
    else sprintf(buffer, "%x", value);
    uart_printstr(buffer);
}

void println_uint ( const uint32_t value ) {
    print_uint(value);
    uart_printstr("\n\r");
}

void println_int ( const int value ) {
    print_int(value);
    uart_printstr("\n\r");
}

void println_float ( const float value ) {
    print_float(value);
    uart_printstr("\n\r");
}

void println_hexa ( const uint32_t value, uint8_t uppercase ) {
    char *buffer = "";
    if (uppercase) sprintf(buffer, "%X", value);
    else sprintf(buffer, "%x", value);
    uart_printstr(buffer);
}