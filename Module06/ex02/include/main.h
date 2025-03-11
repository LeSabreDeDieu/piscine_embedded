/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 10:49:59 by sgabsi            #+#    #+#             */
/*   Updated: 2025/03/11 17:24:12 by sgabsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
#define MAIN_H

#include <util/delay.h>

#include "uart.h"
#include "i2c.h"

void init_aht20 ( void );
void read_aht20 ( void );

#endif // !MAIN_H
