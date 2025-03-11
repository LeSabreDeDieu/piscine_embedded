/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i2c.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:59:32 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/11 13:38:55 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef I2C_H
#define I2C_H

#include <avr/io.h>
#include <util/twi.h>

#include "uart.h"

void i2c_init( void );
void i2c_start( void );
void i2c_stop( void );

#endif // !I2C_H