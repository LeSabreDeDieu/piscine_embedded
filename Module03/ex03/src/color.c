/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayfallahgabsi <sayfallahgabsi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:01:48 by sayfallahga       #+#    #+#             */
/*   Updated: 2025/03/07 13:02:00 by sayfallahga      ###   ########.fr       */
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

void correctGlobal(uint8_t *r, uint8_t *g, uint8_t *b) {
    uint8_t max_value = *r;
    if (*g > max_value) max_value = *g;
    if (*b > max_value) max_value = *b;

    uint16_t facteur = (255U * 255U) / max_value;
    
    *r = (*r * facteur) / 255;
    *g = (*g * facteur) / 255;
    *b = (*b * facteur) / 255;
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b) {

	correctGlobal(&r, &g, &b);

	if (r == 0) DDRD |= ~R;
    else OCR0B = r;
	if (g == 0) DDRD |= ~G;
	else OCR0A = g;
	if (b == 0) DDRD |= ~B;
    else OCR2B = b;
}