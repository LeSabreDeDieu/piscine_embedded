/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 16:27:53 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/14 16:28:51 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void SPI_MasterInit ( void ) {
	/* Set MOSI and SCK output, all others input */
	DDRB = (1 << DD3) | (1 << DD5) | (1 << PB2);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}
void SPI_MasterTransmit ( char cData ) {
	/* Start transmission */
	SPDR = cData;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
}

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
		_delay_ms(1000);
		on_LED(7, 0, 255, 0);
		_delay_ms(1000);
		on_LED(7, 0, 0, 255);

		_delay_ms(1000);

		on_LED(7, 255, 255, 0);
		_delay_ms(1000);
		on_LED(7, 0, 255, 255);
		_delay_ms(1000);
		on_LED(7, 255, 0, 255);
		_delay_ms(1000);

		on_LED(7, 255, 255, 255);
		_delay_ms(1000);
	}
}