/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayfallahgabsi <sayfallahgabsi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:59:04 by sayfallahga       #+#    #+#             */
/*   Updated: 2025/03/07 13:08:49 by sayfallahga      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
#define MAIN_H

#define R 	(1 << PD5)
#define G 	(1 << PD6)
#define B	(1 << PD3)
#define SET_RGB_LED (DDRD |= R | G | B)

#define BAUD 115200UL
#define MYUBBR ((float)(F_CPU) / (16UL * BAUD)) - 1

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void pwm_init(void);
void uart_init(unsigned int ubrr);
void set_rgb(uint8_t r, uint8_t g, uint8_t b);

// UTILS
int is_alpha(char c);
int is_lowercase(char c);
int is_all_hex(char *str);
int hex2int(char ch);
unsigned int round_ubbr();

#endif // !MAIN_H