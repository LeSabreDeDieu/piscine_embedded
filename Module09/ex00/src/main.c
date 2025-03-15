/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:59:56 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/15 13:38:00 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#define SET_LED(D9,D10,D11,STATE) ((STATE) ? \
								   (0xFF & ~(D9 << 3) & ~(D10 << 2) & ~(D11 << 1)) : \
								   (0xFF | (D9 << 3) | (D10 << 2) | (D11 << 1)))

void pca9555_init() {
	i2c_start((SLAVE_ADDR << 1) | 0);
	i2c_write(0x06);  // Registre Configuration Port 0
	i2c_write(0x00);  // Tout en sortie
	i2c_write(0x00);  // Tout en sortie pour Port 1
	i2c_stop();
}

void pca9555_write(uint8_t port0, uint8_t port1) {
	i2c_start((SLAVE_ADDR << 1) | 0);
	i2c_write(0x02);  // Registre Output Port 0
	i2c_write(port0);
	i2c_write(port1);
	i2c_stop();
}

int main(void) {
	i2c_init();
	pca9555_init();

	while (1) {
		pca9555_write(SET_LED(1, 0, 0, 1), 0x00);
		_delay_ms(500);
		pca9555_write(SET_LED(1, 0, 0, 0), 0x00);
		_delay_ms(500);
	}
}
