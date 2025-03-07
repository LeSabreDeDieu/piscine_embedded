/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sayfallahgabsi <sayfallahgabsi@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 12:58:26 by sayfallahga       #+#    #+#             */
/*   Updated: 2025/03/07 13:02:31 by sayfallahga      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int is_alpha(char c) { return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')); }
int is_lowercase(char c) { return c >= 'a' && c <= 'z'; }

int is_in_tab(char c, char *tab) {
	while (*tab) {
		if (c == *tab) return 1;
		tab++;
	}
	return 0;
}

int is_all_hex(char *str) {
	char *char_auth = "0123456789ABCDEFabcdef";
	if (str[0] != '#') return 0;
	for (int i = 1; str[i]; i++) {  
		if (!is_in_tab(str[i], char_auth)) return 0;
	}
	return 1;
}

int hex2int(char ch) {
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    if (ch >= 'A' && ch <= 'F')
        return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f')
        return ch - 'a' + 10;
    return -1;
}

unsigned int round_ubbr() {
    if (MYUBBR >= 0)
        return (unsigned int)(MYUBBR + 0.5f);
    else
        return (unsigned int)(MYUBBR - 0.5f);
}