/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:31:59 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/13 17:29:20 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <string.h>

void cli( void ) {
	char input[7];
	char key[33];
	char value[33];

	get_input(input, 6);
	if (strncmp(input, "READ", 4) == 0) {
		uart_printstr("Key : ");
		get_input(key, 33);
		find_in_EEPROM(input);
	}
	else if (strncmp(input, "WRITE", 5) == 0) {
		uart_printstr("Key : ");
		get_input(key, 33);
		uart_printstr("\n\rValue : ");
		get_input(value, 33);
		write_on_EEPROM(key, value);
	}
	else if (strncmp(input, "FORGET", 6) == 0) {
	}
	else if (strncmp(input, "PRINT", 5) == 0) {
		eeprom_hexdump(0xFFFF);
	}
	else {
		uart_printstr("Command inconnu\n\r");
	}
} 

int main( void )
{
	uart_init_rw();

    while (1) {
		uart_printstr("EEPROM> ");
		cli();
	};
}
