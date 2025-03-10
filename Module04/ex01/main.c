/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 13:20:03 by sayfallahga       #+#    #+#             */
/*   Updated: 2025/03/10 13:04:31 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <avr/interrupt.h>

#define LOOP while(1);
#define DELAY 2

volatile uint8_t direction = 1;
volatile uint8_t duty_cycle = 0;
volatile uint8_t delay_cycle = 0;

void init_TIMER0( void ) {
	// init Timer0 to CTC mode and set the prescaler to 64
	TCCR0A = (1<<WGM01);
	TCCR0B = (1<<CS01) | (1<<CS00);

	OCR0A 	= 249; // (F_CPU / (PRESCALER * Freq voulu)) - 1 => (16000000 / (64 * 1000(1ms))) - 1
	
	// Set the interrupt
	TIMSK0 |= (1 << OCIE0A);
}

void init_TIMER1( void ) {
	// init Timer1 to fast PWM mode and set the prescaler to 1024 and link to PD1
	TCCR1A |= (1 << WGM11) | (1 << COM1A1); 
	TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS10);

	ICR1 	= (int)(F_CPU / 100) - 1;
	
	OCR1A 	= 0;
}

ISR (TIMER0_COMPA_vect) {
	delay_cycle++;
	if (delay_cycle >= DELAY)
	{
		delay_cycle = 0;
		if (direction) {
			duty_cycle++;
			if (duty_cycle >= 255) direction = 0;
		} else {
			duty_cycle--;
			if (duty_cycle == 0) direction = 1;
		}
		OCR1A = ((uint32_t)ICR1 * duty_cycle) / 255;
	}
}

int main( void ) {
	
	DDRB |= (1 << DDB1);

	init_TIMER0();
	init_TIMER1();
	sei();

	LOOP;
}
