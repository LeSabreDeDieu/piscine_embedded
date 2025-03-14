/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:16:10 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/14 17:40:51 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
#define MAIN_H

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "uart.h"
#include "spi.h"

void set_LED_state(uint8_t led_index, uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue);
void on_LED ( void );

int hex2int(char ch);
int is_all_hex(char *str);
void get_input (char *buffer, uint8_t size);

#endif // !MAIN_H