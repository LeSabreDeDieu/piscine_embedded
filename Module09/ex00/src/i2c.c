/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i2c.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:00:17 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/13 10:10:33 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "i2c.h"

void i2c_init ( void ) {
	TWSR = PRESCALER;
	TWBR = ((F_CPU / SCL) - 16) / (2 * (1 << (TWSR & 0x03)));
}

void i2c_write ( uint8_t byte ) {
	TWDR = byte;
	TWCR = (1 << TWEN) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));
}

uint8_t i2c_read ( void ) {
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA);
	while (!(TWCR & (1 << TWINT)));					
	return TWDR; 									
}

void i2c_start ( uint8_t address ) {
	TWCR = (1 << TWEN) | (1 << TWSTA) | (1 << TWINT);
	while (!(TWCR & (1 << TWINT)));

	i2c_write(address);
}

void i2c_stop ( void )  {
	TWCR = (1 << TWEN) | (1 << TWSTO) | (1 << TWINT);
	while (TWCR & (1 << TWSTO));
}
