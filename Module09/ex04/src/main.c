/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 12:59:56 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/15 15:56:56 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#define ZERO	0b00111111
#define ONE		0b00000110
#define TWO		0b01011011
#define THREE	0b01001111	
#define FOUR	0b01100110
#define FIVE	0b01101101
#define SIX		0b01111101
#define SEVEN	0b00000111
#define EIGHT	0b01111111
#define NINE	0b01101111

void pca9555_init() {
	i2c_start((SLAVE_ADDR << 1) | 0);
	i2c_write(0x06);  // Configuration des directions des ports
	i2c_write(0x00);  // Port 0 en sortie
	i2c_write(0x00);  // Port 1 en sortie
	i2c_stop();
}

void pca9555_write(uint8_t port0, uint8_t port1) {
	i2c_start((SLAVE_ADDR << 1) | 0);
	i2c_write(0x02);  // Sélection du registre Output Port 0
	i2c_write(port0);
	i2c_write(port1);
	i2c_stop();
}

int main(void) {
	i2c_init();
	pca9555_init();

	while (1) {
		pca9555_write(0xFF, 0x00);  // Éteindre l'afficheur
		_delay_us(100);  // Petit délai pour éviter les segments fantômes

		pca9555_write(0x7F, TWO);  // Affichage du chiffre "2"
		_delay_ms(0.2);

		pca9555_write(0xFF, 0x00);  // Éteindre l'afficheur
		_delay_us(100);

		pca9555_write(0xBF, FOUR);  // Affichage du chiffre "4"
		_delay_ms(0.2);
	}
}
