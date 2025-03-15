/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:59:56 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/15 15:02:31 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#define SET_LED(D9,D10,D11,STATE) ((STATE) ? \
								   (0xFF & ~((D9 << 3) | (D10 << 2) | (D11 << 1))) : \
								   (0xFF | ((D9 << 3) | (D10 << 2) | (D11 << 1))))

void pca9555_init() {
	i2c_start((SLAVE_ADDR << 1) | 0);
	i2c_write(0x06);
	i2c_write(0x01);
	i2c_stop();
}

void pca9555_write(uint8_t port0) {
	i2c_start((SLAVE_ADDR << 1) | 0);
	i2c_write(0x02);
	i2c_write(port0);
	i2c_stop();
}

uint16_t pca9555_read() {
	uint8_t port0;

	i2c_start((SLAVE_ADDR << 1) | 0);
	i2c_write(0x00);
	i2c_start((SLAVE_ADDR << 1) | 1);
	port0 = i2c_read_nack();
	i2c_stop();

	return port0;
}

int main(void) {
	i2c_init();
	pca9555_init();
	uint8_t val = 0;
	uint16_t data;

	uint8_t flag = 0;
	while (1) {
		uint8_t read = pca9555_read();
		pca9555_write(SET_LED(1, 1, 1, 0));
		if (!(read & 0x01) && flag == 0) {  
			// Si SW pressé, incrémente val
			val++;
			flag = 1;
			_delay_ms(20);
		}
		if ((read & 0x01) && flag == 1) flag = 0;

		// Afficher `val` sur les LEDs
		data = ~((0xFF & ~((1 << 1) | (1 << 2) | (1 << 3))) | ((val & 7) << 1) | 1);
		pca9555_write(data);
	}
}

// 0000 0000
