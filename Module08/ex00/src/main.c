/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:15:51 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/14 16:27:12 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void APA102_sendPixel(uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue) {
    SPI_MasterTransmit(0b11100000 | (brightness & 0b00011111)); // 3 bits "1" + luminosité (5 bits)
    SPI_MasterTransmit(blue);  // Couleur Bleu
    SPI_MasterTransmit(green); // Couleur Vert
    SPI_MasterTransmit(red);   // Couleur Rouge
}

void on_LED (uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue) {
	for (int i = 0; i < 4; i++) {
        SPI_MasterTransmit(0x00);
    }

    // Envoyer la couleur à chaque LED
    APA102_sendPixel(brightness, red, green, blue);

    // End Frame (au moins numLEDs/2 bits à 1)
    SPI_MasterTransmit(0xFF);
}

int main( void )
{
	SPI_MasterInit();
	while (1) { 
		on_LED(7, 255, 0, 0);
	}
}
