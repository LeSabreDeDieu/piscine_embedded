/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i2c.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:00:17 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/11 12:16:42 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "i2c.h"

#define SCL 100000

void i2c_init(void) {
	TWSR = 0;            										// Set prescaler to 1
	TWBR = ((F_CPU / SCL) - 16) / (2 * (1 << (TWSR & 0x03)));	// Set the TW
	TWCR = (1 << TWEN);  										// Enable TWI
}

void i2c_write(uint8_t byte) {
	TWDR = byte;  												// Load data into TWDR register
	TWCR = (1 << TWEN) | (1 << TWINT);  						// Start transmission

	while (!(TWCR & (1 << TWINT)));  							// Wait for transmission to complete
}

void i2c_start(void) {
	uint8_t start_status = 0;
	uint8_t addr_status = 0;

	TWCR = (1 << TWEN) | (1 << TWSTA) | (1 << TWINT);  			// Send start condition
	while (!(TWCR & (1 << TWINT)));  							// Wait for start condition to be transmitted

	start_status = TWSR & 0xF8;									// get status of slave

	i2c_write((0x38 << 1));  									// Write address with write flag
	
	addr_status = TWSR & 0xF8;									// get status of slave

	uart_printstr("\b\rStatus received : ");
	print_hex(start_status);
	uart_printstr(", ");
	print_hex(addr_status);
	uart_printstr("\r\n");
}

void i2c_stop(void) {
	TWCR = (1 << TWEN) | (1 << TWSTO) | (1 << TWINT);  			// Send stop condition
	while (TWCR & (1 << TWSTO));								// Wait for stop condition to be transmitted
}