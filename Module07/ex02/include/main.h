/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:30:02 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/13 17:19:09 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
#define MAIN_H

#include <avr/io.h>
#include <avr/eeprom.h>

#include "uart.h"

void get_input (char *buffer, uint8_t size);
void find_in_EEPROM ( const char *str );
void write_on_EEPROM (char *key, char *value);

void eeprom_hexdump( unsigned int uiAddress );
void eeprom_write ( void );

void void_flash();

#endif // !MAIN_H