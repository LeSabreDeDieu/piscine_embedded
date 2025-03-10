/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:01:48 by sayfallahga       #+#    #+#             */
/*   Updated: 2025/03/08 13:54:04 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void pwm_init(void) {
    TCCR0A |= (1 << WGM00) | (1 << WGM01);
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1);
    TCCR0B |= (1 << CS01);

    TCCR2A |= (1 << WGM20) | (1 << WGM21); 
    TCCR2A |= (1 << COM2B1);
    TCCR2B |= (1 << CS21);
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b) {
    DDRD &= ~(R | G | B);

	if (r != 0) {
        DDRD |= R;
        OCR0B = r;
    }
	if (g != 0) {
        DDRD |= G;
        OCR0A = g;
    }
	if (b != 0) {
        DDRD |= B;
        OCR2B = b;
    }
}