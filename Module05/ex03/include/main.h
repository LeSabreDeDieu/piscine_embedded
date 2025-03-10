/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:35:25 by sayfallahga       #+#    #+#             */
/*   Updated: 2025/03/10 14:12:18 by sgabsi           ###   ########.fr       */
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
char* uint32toa(uint32_t value);
void uart_init(unsigned int ubrr);
void uart_printstr(const char* str);
uint16_t convert_to_celsius(uint16_t adc_value);

#endif // !MAIN_H