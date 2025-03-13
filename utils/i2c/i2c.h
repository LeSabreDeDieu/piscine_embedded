/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i2c.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:59:32 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/13 10:15:32 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file i2c.h
 * @brief I2C communication utility functions and definitions.
 *
 * This header file contains the function declarations and macro definitions
 * for initializing and using the I2C (Inter-Integrated Circuit) communication
 * protocol.
 */

#ifndef I2C_H
#define I2C_H

#include <util/twi.h>

#define SCL 100000 /** I2C clock frequency in Hz */
#define PRESCALER 0 /** I2C prescaler value */
#define SLAVE_ADDR 0x38 /** I2C slave address */

/**
 * @brief Initializes the I2C communication.
 *
 * This function sets up the I2C communication by configuring the clock frequency
 * and prescaler.
 */
void i2c_init(void);

/**
 * @brief Reads a byte from the I2C bus.
 *
 * @return The byte read from the I2C bus.
 */
uint8_t i2c_read(void);

/**
 * @brief Writes a byte to the I2C bus.
 *
 * @param byte The byte to be written to the I2C bus.
 */
void i2c_write(uint8_t byte);

/**
 * @brief Sends a start condition and the slave address on the I2C bus.
 *
 * @param address The address of the I2C slave device.
 */
void i2c_start(uint8_t address);

/**
 * @brief Sends a stop condition on the I2C bus.
 */
void i2c_stop(void);

#endif // !I2C_H