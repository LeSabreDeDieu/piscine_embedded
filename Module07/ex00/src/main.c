/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:31:59 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/13 11:18:25 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <stdio.h>

#define EEPROM_SIZE 1024  		// Taille totale de l'EEPROM

uint16_t EEPROM_read(unsigned int uiAddress)
{
	/* Wait for completion of previous write */
	while(EECR & (1 << EEPE));
	/* Set up address register */
	EEAR = uiAddress;
	/* Start eeprom read by writing EERE */
	EECR |= (1 << EERE);
	/* Return data from Data Register */
	return EEDR;
}

void print_mem (const uint8_t *str) {
	while (*str) {
		if (*str >= 32 && *str <= 126) uart_printchar(*str);
		else uart_printchar('.');
		str++;
	}
}

void print_mem_addr (const unsigned int address) {
	char buffer[1024] = {0};
    sprintf(buffer, "%04x%04x", 0, address);
    uart_printstr(buffer);
}

void eeprom_hexdump( void ) {
	uint8_t buff[17] = {0};
	for (uint32_t addr = 0; addr < EEPROM_SIZE; addr += 16) {
		// Afficher l'adresse en hexadécimal
        print_mem_addr(addr);
		uart_printchar(' ');

		for (uint8_t i = 0; i < 16; i++) {
			buff[i] = EEPROM_read(addr + i);

			if (buff[i] == 0xFF || buff[i] == 0x00) {
				uart_printstr("\033[38;5;247m");
			}

			print_hexa(buff[i], 0);
			
			if (i != 7) uart_printchar(' ');
			else uart_printstr("  ");
			
			uart_printstr("\033[0m");
        }
		uart_printstr("|");
		print_mem(buff);
		uart_printstr("|");
		uart_println();
	}
}

int main( void )
{
	uart_init_w();

	uart_printstr("EEPROM Hexdump:\n\r");
    eeprom_hexdump();

    while (1);
}
