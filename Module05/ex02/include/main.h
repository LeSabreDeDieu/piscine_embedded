/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:35:25 by sayfallahga       #+#    #+#             */
/*   Updated: 2025/03/10 12:53:40 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
#define MAIN_H

#define BAUD 115200UL
#define MYUBBR ((float)(F_CPU) / (16UL * BAUD)) - 1

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned int round_ubbr();
void print_hex(uint8_t value);
char* uint16toa(uint16_t value);
void uart_init(unsigned int ubrr);
void uart_printstr(const char* str);

#endif // !MAIN_H