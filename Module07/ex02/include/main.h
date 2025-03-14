/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:30:02 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/14 10:07:40 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
#define MAIN_H

#include <avr/io.h>
#include <avr/eeprom.h>

#include "uart.h"

void get_input (char *buffer, uint8_t size);

void write_on_EEPROM (char *key, char *value);
void find_in_EEPROM ( const char *str );
void forget_key_EEPROM ( char *key );

void eeprom_hexdump( unsigned int uiAddress );
void eeprom_write ( void );

#endif // !MAIN_H