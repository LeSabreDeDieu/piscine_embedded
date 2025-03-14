/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:31:59 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/14 10:07:54 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"
#include <string.h>
#include <stdio.h>

#define MAX_LEN 32

typedef struct s_parsed {
    char command[MAX_LEN];
    char key[MAX_LEN];
    char value[MAX_LEN];
} t_parsed;

t_parsed parse_line(const char *line) {
    t_parsed parsed = {"", "", ""};
    char buffer[MAX_LEN * 3]; // Assurez-vous d'avoir assez de place pour la ligne complète
    strncpy(buffer, line, sizeof(buffer) - 1);
    buffer[sizeof(buffer) - 1] = '\0';
    
    char *p = buffer;
    char *start;
    
    // Extraire la commande
    while (*p == ' ') p++; // Ignorer les espaces initiaux
    start = p;
    while (*p && *p != ' ') p++;
    if (p > start) {
        size_t len = p - start;
        if (len >= MAX_LEN) len = MAX_LEN - 1;
        strncpy(parsed.command, start, len);
        parsed.command[len] = '\0';
    }
    if (*p) p++;
    
    // Extraire la clé si présente
    while (*p == ' ') p++;
    if (*p == '"') {
        start = ++p;
        while (*p && *p != '"') p++;
        if (*p == '"') {
            size_t len = p - start;
            if (len >= MAX_LEN) len = MAX_LEN - 1;
            strncpy(parsed.key, start, len);
            parsed.key[len] = '\0';
            p++;
        }
    }
    
    // Extraire la valeur si présente
    while (*p == ' ') p++;
    if (*p == '"') {
        start = ++p;
        while (*p && *p != '"') p++;
        if (*p == '"') {
            size_t len = p - start;
            if (len >= MAX_LEN) len = MAX_LEN - 1;
            strncpy(parsed.value, start, len);
            parsed.value[len] = '\0';
        }
    }
    
    return parsed;
}

void cli( void ) {
	char input[255];
	t_parsed parse_cmd;

	get_input(input, 255);

	parse_cmd = parse_line(input);

	if (strncmp(parse_cmd.command, "READ", 4) == 0) {
		if (parse_cmd.key[0] == 0) {
			uart_printstr("Key is missing\n\r");
			return;
		}
		find_in_EEPROM(parse_cmd.key);
	}
	else if (strncmp(parse_cmd.command, "WRITE", 5) == 0) {
		if (parse_cmd.key[0] == 0 || parse_cmd.value[0] == 0) {
			uart_printstr("Key or value is missing\n\r");
			return;
		}
		write_on_EEPROM(parse_cmd.key, parse_cmd.value);
	}
	else if (strncmp(parse_cmd.command, "FORGET", 6) == 0) {
		if (parse_cmd.key[0] == 0) {
			uart_printstr("Key is missing\n\r");
			return;
		}
		forget_key_EEPROM(parse_cmd.key);
	}
	else if (strncmp(parse_cmd.command, "PRINT", 5) == 0) {
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
