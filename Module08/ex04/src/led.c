/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   led.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:18:04 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/14 17:18:11 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

typedef struct RGB_LED
{
    uint8_t brightness;
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}   RGB_LED;


RGB_LED LED_STATE[3] = {0};

void APA102_sendPixel(uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue) {
    SPI_MasterTransmit(0b11100000 | (brightness & 0b00011111)); // 3 bits "1" + luminosité (5 bits)
    SPI_MasterTransmit(blue);  // Couleur Bleu
    SPI_MasterTransmit(green); // Couleur Vert
    SPI_MasterTransmit(red);   // Couleur Rouge
}

void on_LED ( void ) {
	for (int i = 0; i < 4; i++) {
        SPI_MasterTransmit(0x00);
    }

    // Envoyer la couleur à chaque LED
    for (uint8_t i = 0; i < 3; i++) {
        APA102_sendPixel( LED_STATE[i].brightness,
                          LED_STATE[i].red,
                          LED_STATE[i].green,
                          LED_STATE[i].blue );
    }

    // End Frame (au moins numLEDs/2 bits à 1)
    SPI_MasterTransmit(0xFF);
    SPI_MasterTransmit(0xFF);
}

void set_LED_state(uint8_t led_index, uint8_t brightness, uint8_t red, uint8_t green, uint8_t blue) {
    if (led_index < 3) {
        LED_STATE[led_index].brightness = brightness;
        LED_STATE[led_index].red = red;
        LED_STATE[led_index].green = green;
        LED_STATE[led_index].blue = blue;
    }
}
