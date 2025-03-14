/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 15:15:51 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/14 19:15:09 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <string.h>

uint32_t overflow = 0;

void ready( void ) {
	set_LED_state(0, 0, 0, 0, 0);
	set_LED_state(1, 0, 0, 0, 0);
	set_LED_state(2, 0, 0, 0, 0);
    on_LED();
}

void init_timer() {
	ready();
	
	TCCR0A = (1 << WGM00) | (1 << WGM01);
    TIMSK0 = (1 << TOIE0);
}

void wheel(uint8_t pos) {
	pos = 255 - pos;

	if (pos < 85) {
        set_LED_state(0, 7, 255 - pos * 3, 0, pos * 3);
        set_LED_state(1, 7, 255 - pos * 3, 0, pos * 3);
        set_LED_state(2, 7, 255 - pos * 3, 0, pos * 3);
	} 
	else if (pos < 170) {
		pos = pos - 85;
        set_LED_state(0, 7, 0, pos * 3, 255 - pos * 3);
        set_LED_state(1, 7, 0, pos * 3, 255 - pos * 3);
        set_LED_state(2, 7, 0, pos * 3, 255 - pos * 3);
        
	} 
	else {
		pos = pos - 170;
        set_LED_state(0, 7, pos * 3, 255 - pos * 3, 0);
        set_LED_state(1, 7, pos * 3, 255 - pos * 3, 0);
        set_LED_state(2, 7, pos * 3, 255 - pos * 3, 0);
	}
    on_LED();
}

ISR(TIMER0_OVF_vect) {
    wheel(overflow++);
    on_LED();
}

int main( void )
{
    char RGB[12] = {0};
    uint8_t red, green, blue, LED;

	SPI_MasterInit();
    uart_init_rw();
    init_timer();
    sei();

    uart_printstr("Enter a color with this patern : #RRGGBBDX :\n\r#");
	while (1) {
        get_input(RGB, 12);
        if (((strlen(RGB) < 8) || 
            (!is_all_hex(RGB) || RGB[6] != 'D' || !(RGB[7] >= '6' && RGB[7] <= '8'))) && 
            strcmp(RGB, "FULLRAINBOW") != 0) {
            uart_printstr("\n\rInvalid color format! Use #RRGGBBDX\n\r#");
            continue ;
        }

        TCCR0B &= ~((1 << CS00) | (1 << CS02));

        if (!strcmp(RGB, "FULLRAINBOW")) {
            TCCR0B |= (1 << CS00) | (1 << CS02);
        } else {
            red   = 16 * hex2int(RGB[0]) + hex2int(RGB[1]);
            green = 16 * hex2int(RGB[2]) + hex2int(RGB[3]);
            blue  = 16 * hex2int(RGB[4]) + hex2int(RGB[5]);
            LED   = (RGB[7] - '0') - 6;
            println_uint(LED);
            uart_printstr("Color set to : ");
            uart_printstr(RGB);
            uart_printstr("\n\r");
            set_LED_state(LED, 7, red, green, blue);
            on_LED();
        }
        _delay_ms(1000);
        uart_printstr("Enter a color with this patern : #RRGGBBDX :\n\r#");
    };
}
