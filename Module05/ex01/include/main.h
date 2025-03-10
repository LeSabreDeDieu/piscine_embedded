/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayfallahgabsi <sayfallahgabsi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:35:25 by sayfallahga       #+#    #+#             */
/*   Updated: 2025/03/07 15:38:29 by sayfallahga      ###   ########.fr       */
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
void uart_init(unsigned int ubrr);
void uart_printstr(const char* str);

#endif // !MAIN_H