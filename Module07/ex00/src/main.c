/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:31:59 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/12 09:38:13 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

#define EEPROM_SIZE 1024  		// Taille totale de l'EEPROM

uint16_t EEPROM_read(unsigned int uiAddress)
{
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE));
	/* Set up address register */
	EEAR = uiAddress;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from Data Register */
	return EEDR;
}

void eeprom_hexdump( void ) {
	for (uint32_t addr = 0; addr < EEPROM_SIZE; addr += 16) {
		// Afficher l'adresse en hexadécimal
        print_hex((addr >> 8) & 0xFF);
        print_hex(addr & 0xFF);
		uart_tx(' ');

		for (uint8_t i = 0; i < 8; i++) {
			const uint16_t const_addr = (addr + i);
			uint16_t data = EEPROM_read(const_addr) << 8;
			data |= EEPROM_read(const_addr);
			print_hex(data);
			uart_tx(' ');
        }
		uart_printstr("\n\r");
	}
}

int main( void )
{
	uart_init();

	uart_printstr("EEPROM Hexdump:\n\r");
    eeprom_hexdump();

    while (1);
}
