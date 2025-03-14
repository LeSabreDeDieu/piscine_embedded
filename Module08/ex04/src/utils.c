/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 17:32:36 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/14 17:32:58 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int is_in_tab(char c, char *tab) {
	while (*tab) {
		if (c == *tab) return 1;
		tab++;
	}
	return 0;
}

int is_all_hex(char *str) {
	char *char_auth = "0123456789ABCDEFabcdef";
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
