/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i2c.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:00:17 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/11 13:51:38 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "i2c.h"

#define SCL 100000

void i2c_init ( void ) {
	TWSR = 0;            										// Set prescaler to 1
	TWBR = ((F_CPU / SCL) - 16) / (2 * (1 << (TWSR & 0x03)));	// Set the TW
	TWCR = (1 << TWEN);  										// Enable TWI
}

void i2c_write ( uint8_t byte ) {
	TWDR = byte;  												// Load data into TWDR register
	TWCR = (1 << TWEN) | (1 << TWINT);  						// Start transmission
	while (!(TWCR & (1 << TWINT)));  							// Wait for transmission to complete
}

uint8_t i2c_read ( void ) {
	TWCR = (1 << TWEN) | (1 << TWINT) | (1 << TWEA); 			// Lire avec ACK
	while (!(TWCR & (1 << TWINT)));					
	return TWDR; 									
}

void i2c_start ( uint8_t address ) {
	TWCR = (1 << TWEN) | (1 << TWSTA) | (1 << TWINT);  			// Send start condition
	while (!(TWCR & (1 << TWINT)));  							// Wait for start condition to be transmitted

	i2c_write(address);  										// Write address with write flag
}

void i2c_stop ( void )  {
	TWCR = (1 << TWEN) | (1 << TWSTO) | (1 << TWINT);  			// Send stop condition
	while (TWCR & (1 << TWSTO));								// Wait for stop condition to be transmitted
}