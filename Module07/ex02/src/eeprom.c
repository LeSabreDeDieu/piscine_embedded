/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eeprom.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:19:02 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/14 14:26:56 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>

#define EEPROM_SIZE 1024  		// Taille totale de l'EEPROM
#define SIZE_KVD 36				// Size key-value-delimiter

#define STA 0x02
#define MID	0x1F
#define END 0x03

static char rx_buffer_addr[4] = {0};
static char rx_buffer_data[4] = {0};

uint16_t EEPROM_read(unsigned int uiAddress) {
	/* Wait for completion of previous write */
	while(EECR & (1 << EEPE));

	/* Set up address register */
	EEAR = uiAddress;

	/* Start eeprom read by writing EERE */
	EECR |= (1 << EERE);

	/* Return data from Data Register */
	return EEDR;
}

void EEPROM_write(unsigned int uiAddress, uint8_t data) {
	uint8_t SREG_copy;

	/* Wait for completion of previous write */
	while(EECR & (1 << EEPE));
	while(SPMCSR & (1 << SELFPRGEN));

	// Save status of register SREG
	SREG_copy = SREG;

	// Set interrupt to 0
	SREG |= ~(1 << SREG_I);
	
	/* Set up address register */
	EEAR = uiAddress;

	/* Set up data register */
	EEDR = data;

	/* Set up EEMPE && EEPE to wait 4 cycles */
	EECR |= (1 << EEMPE);
	EECR |= (1 << EEPE);

	SREG = SREG_copy;
}

void print_mem (const uint8_t *str) {
	int i = 0;

	while (i < 16) {
		if (str[i] >= 0x20 && str[i] <= 0x7E) uart_printchar(str[i]);
		else uart_printchar('.');
		i++;
	}
}

void print_mem_addr (const unsigned int address) {
	char buffer[1024] = {0};
    sprintf(buffer, "%04x%04x", 0, address);
    uart_printstr(buffer);
}

void eeprom_hexdump( unsigned int uiAddress ) {
	uint8_t buff[17] = {0};
	
	for (uint16_t addr = 0; addr < EEPROM_SIZE; addr += 16) {
		// Afficher l'adresse en hexadécimal
        print_mem_addr(addr);
		uart_printchar(' ');

		for (uint8_t i = 0; i < 16; i++) {
			buff[i] = EEPROM_read(addr + i);

			if (buff[i] == 0xFF || buff[i] == 0x00) uart_printstr("\033[38;5;247m");
			if (addr + i == uiAddress) uart_printstr("\033[38;5;196m");
			if (addr == 0xFFFF) uart_printstr("\033[0m");
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

unsigned int	ft_atohex(const char *str)
{
	unsigned int	num = 0;

	// Ignorer les espaces blancs et gérer le préfixe "0x" ou "0X"
	while (*str && (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\r' || *str == '\f' || *str == '\v'))
		++str;
	if ((*str == '0' && (str[1] == 'x' || str[1] == 'X')))
		str += 2;  // Si la chaîne commence par "0x" ou "0X", on saute ces deux caractères

	// Conversion des caractères hexadécimaux
	while (*str)
	{
		num *= 16;  // Décalage pour la position hexadécimale
		if (*str >= '0' && *str <= '9')
			num += *str - '0';  // Conversion des chiffres 0-9
		else if (*str >= 'a' && *str <= 'f')
			num += *str - 'a' + 10;  // Conversion des lettres a-f
		else if (*str >= 'A' && *str <= 'F')
			num += *str - 'A' + 10;  // Conversion des lettres A-F
		else
			return 0xFFFF;
		++str;
	}

	return num;
}

void eeprom_write ( void ) {
	uint16_t addr;
	uint16_t data;
	
	uart_printstr("\n\rAddress : ");
	get_input(rx_buffer_addr, 4);
	addr = ft_atohex(rx_buffer_addr);
	if ((uint32_t)addr >= 0x3FF) {
		uart_printstr("ERROR : Address doesn't exist !\n\r");
		return ;
	}

	uart_printstr("\n\rData : ");
	get_input(rx_buffer_data, 4);
	data = ft_atohex(rx_buffer_data);
	if (data > 0xFF) {
		uart_printstr("ERROR : Data too big !\n\r");
		return ;
	}

	uint16_t tmp = EEPROM_read(addr & 0xFFF);
	if ((uint8_t)tmp == (data & 0xFF)) {
		uart_printstr("\n\rERROR : Data ");
		print_hexa(data & 0xFF, 0);
		uart_printstr(" on address ");
		print_mem_addr(addr & 0xFFF);
		uart_printstr(" already exist !\n\rTry another one on data or address\n\n\r");
		return ;
	}
	EEPROM_write(addr & 0xFFF, data & 0xFF);
	eeprom_hexdump(addr & 0xFFF);
}

#include <stdio.h>

uint16_t find_key(const char *str) {
    for (uint16_t addr = 0; addr < EEPROM_SIZE; addr += SIZE_KVD) {

        if (EEPROM_read(addr) == STA) {
            uint16_t key_addr = addr + 1;
            uint8_t i = 0;
            char c;

            while (1) {
                c = EEPROM_read(key_addr + i);
                if (c == END) break;

                if ((uint8_t)str[i] != c)	break;
                i++;
            }

            // Vérifier si la clé complète est trouvée
            if (str[i] == 0 && c == END)
                return key_addr;  // Retourne l'adresse de la clé
        }
    }
    return 0xFFFF; // Retourne une adresse invalide si la clé n'est pas trouvée
}


void find_in_EEPROM ( const char *str ) {
	uint16_t addr = find_key(str);
	char buff[17];

	if (addr == 0xFFFF) {
		uart_printstr("Empty\n\r");
		return ;
	}
	addr += 17;
	for (uint16_t i = 0; i < 16; i++) {
		if (EEPROM_read(addr + i) == END) {
			buff[i] = 0;
			break;
		}
		buff[i] = EEPROM_read(addr + i);
	}
	uart_printchar('"');
	uart_printstr(buff);
	uart_printstr("\"\n\r");
	return ;
}

void write_str_on_EEPROM (unsigned int uiAddress, char *str) {
	int i = 0;
	while (*str) {
		EEPROM_write(uiAddress + i, *str);
		i++;
		str++;
	};
	EEPROM_write(uiAddress + i, END);
}

void write_on_EEPROM (char *key, char *value) {
	uint16_t addr = 0;
	if (find_key(key) != 0xFFFF) {
		uart_printstr("already exists\n\r");
		return ;
	}
	for (addr = 0; addr < EEPROM_SIZE; addr += SIZE_KVD) {
		if (EEPROM_read(addr) != STA) {
			EEPROM_write(addr, STA);
			write_str_on_EEPROM(addr + 1, key);
			EEPROM_write(addr + 18, STA);
			write_str_on_EEPROM(addr + 19, value);
			print_uint(addr);
			uart_println();
			break;
		}
	}
	if (addr == EEPROM_SIZE)
		uart_printstr("No space left !\n\r");
}

void forget_key_EEPROM ( char *key ) {
	uint16_t addr = find_key(key);
	if (addr == 0xFFFF) {
		uart_printstr("Key not found\n\r");
		return ;
	}
	EEPROM_write(find_key(key) - 1, 0xFF);
	uart_printstr("Done\n\r");
}