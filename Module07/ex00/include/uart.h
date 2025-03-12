/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uart.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:52:06 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/12 08:52:53 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UART_H
#define UART_H

#include <avr/io.h>

#define BAUD 115200UL
#define MYUBBR (((float)(F_CPU) / (16UL * BAUD)) - 0.5)

void uart_init( void );
void uart_tx( char data );
void print_hex(uint16_t value);
void uart_printstr( const char* str );
void print_hex_value(char c);
char* uint16toa(uint16_t value);

#endif // !UART_H