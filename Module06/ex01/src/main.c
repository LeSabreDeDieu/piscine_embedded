/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 11:18:27 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/11 15:20:55 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

uint8_t status = 0;

void print_hex_value(char c) {
	print_hex(c);
	uart_printstr(" ");
}

void read_aht20 ( void ) {   
	i2c_start(AHT20_ADDR << 1);
	i2c_write(0xAC); // Commande de mesure
	i2c_write(0x33);
	i2c_write(0x00);
	i2c_stop();
	
    _delay_ms(80); // Attente recommandée

	do {
		i2c_start(AHT20_ADDR << 1);
		i2c_write(0x71);
		status = i2c_read();
		i2c_stop();
	} while (!(status));
    
    i2c_start((AHT20_ADDR << 1) | 1);
    for (uint8_t i = 0; i < 7; i++) {
        print_hex_value(i2c_read());
    }
    i2c_stop();
}

int main(void) {
	uart_init();
    i2c_init(); // Initialisation du module I2C

	_delay_ms(40);
	
	i2c_start(AHT20_ADDR << 1);
	i2c_write(0x71);
	status = i2c_read();
	i2c_stop();
	
	if ((status & (1 << 3)) == 1)
	{
		i2c_start(AHT20_ADDR << 1);
		i2c_write(0xBE); // Commande de mesure
		i2c_write(0x08);
		i2c_write(0x00);
		i2c_stop();
		_delay_ms(10);
	}

    while (1) {
		uart_printstr("\b\rData received : ");
        read_aht20();
		uart_printstr("\n\r");
    }
	
}