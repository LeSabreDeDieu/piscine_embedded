/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aht20.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 15:32:58 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/13 10:16:30 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdlib.h>

#define SLAVE_ADDR 0x38 // Adresse I2C du capteur AHT20

static uint8_t status = 0;

void init_aht20(void) {
    _delay_ms(40);
    
    i2c_start(SLAVE_ADDR << 1);
    i2c_write(0x71);
    status = i2c_read();
    i2c_stop();
    
    if (status & (1 << 3)) {
        i2c_start(SLAVE_ADDR << 1);
        i2c_write(0xBE);
        i2c_write(0x08);
        i2c_write(0x00);
        i2c_stop();
        _delay_ms(10);
    }
}

float hexa_to_temp(uint32_t temperature) {
    return ((temperature / 1048576.0) * 200.0) - 50.0;
}

float hexa_to_pourcent(uint32_t humidity) {
    return (humidity / 1048576.0) * 100.0;
}

void read_aht20(void) {
    uint8_t data[6] = {0};
    float temp_sum = 0.0;
    float humidity_sum = 0.0;
    
    for (uint8_t j = 0; j < 3; j++) {
        i2c_start(SLAVE_ADDR << 1);
        i2c_write(0xAC);
        i2c_write(0x33);
        i2c_write(0x00);
        i2c_stop();
        
        _delay_ms(80);

        do {
            i2c_start(SLAVE_ADDR << 1);
            i2c_write(0x71);
            status = i2c_read();
            i2c_stop();
            _delay_ms(5);
        } while ((status & 0x80));
        
        i2c_start((SLAVE_ADDR << 1) | 1);
        for (uint8_t i = 0; i < 6; i++) {
            data[i] = i2c_read();
        }
        i2c_stop();
        
        uint32_t humidity_raw = ((uint32_t)data[1] << 12) | ((uint32_t)data[2] << 4) | (data[3] >> 4);
        uint32_t temperature_raw = ((uint32_t)(data[3] & 0x0F) << 16) | ((uint32_t)data[4] << 8) | data[5];
        
        humidity_sum += hexa_to_pourcent(humidity_raw);
        temp_sum += hexa_to_temp(temperature_raw);
    }
    
    float humidity_avg = humidity_sum / 3.0;
    float temperature_avg = temp_sum / 3.0;
    
    char buffer[10];
    uart_printstr("\b\rTemperature : ");
    dtostrf(temperature_avg, 6, 2, buffer);
    uart_printstr(buffer);
    uart_printstr("°C, Humidite : ");
    dtostrf(humidity_avg, 6, 2, buffer);
    uart_printstr(buffer);
    uart_printstr("%\n\r");
}