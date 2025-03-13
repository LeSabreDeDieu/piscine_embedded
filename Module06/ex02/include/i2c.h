/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i2c.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:59:32 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/13 10:16:07 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I2C_H
#define I2C_H

#include <avr/io.h>
#include <util/twi.h>

#include "uart.h"

#define SLAVE_ADDR 0x38

void i2c_init( void );
void i2c_stop( void );
uint8_t i2c_read( void );
void i2c_write ( uint8_t byte );
void i2c_start( uint8_t address );

#endif // !I2C_H