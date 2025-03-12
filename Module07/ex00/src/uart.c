/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uart.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:00:39 by sayfallahga       #+#    #+#             */
/*   Updated: 2025/03/12 08:53:23 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "uart.h"

void uart_tx(char data) {
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

void uart_init( void ) {
	UBRR0H = (unsigned char)((int)MYUBBR >> 8);
	UBRR0L = (unsigned char) MYUBBR;
	
	UCSR0B |= (1 << TXEN0);
	UCSR0C |= (1 << UCSZ00) | (1 << UCSZ01);
}

void uart_printstr(const char* str) {
	while (*str) uart_tx(*str++);
}

void print_hex(uint16_t value) {
    char hex_str[5];  								// Format "FFFF\0"
    hex_str[0] = "0123456789abcdef"[(value >> 12) & 0x0F];  // Partie haute-haute
    hex_str[1] = "0123456789abcdef"[(value >> 8) & 0x0F];   // Partie haute-basse
    hex_str[2] = "0123456789abcdef"[(value >> 4) & 0x0F];   // Partie basse-haute
    hex_str[3] = "0123456789abcdef"[value & 0x0F];          // Partie basse-basse
    hex_str[4] = '\0';  									// Fin de chaîne
    uart_printstr(hex_str);
}

char* uint16toa(uint16_t value) {
    static char str[6];  // Maximum length for uint16_t (65535) + null terminator
    char *ptr = str + sizeof(str) - 1;
    *ptr = '\0';

    // Convert integer to string
    do {
        *--ptr = (value % 10) + '0';
        value /= 10;
    } while (value);

    return ptr;
}

void print_hex_value(char c) {
	print_hex(c);
	uart_printstr(" ");
}
