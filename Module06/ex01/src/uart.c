/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uart.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:00:39 by sayfallahga       #+#    #+#             */
/*   Updated: 2025/03/11 15:19:38 by sgabsi           ###   ########.fr       */
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

void print_hex(uint8_t value) {
    char hex_str[3];  								// Format "0xff\0"
    hex_str[0] = "0123456789ABCDEF"[value >> 4];  	// Partie haute
    hex_str[1] = "0123456789ABCDEF"[value & 0x0F];  // Partie basse
    hex_str[2] = '\0';  							// Fin de chaîne
    uart_printstr(hex_str);
}