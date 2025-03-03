# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 10:04:44 by sgabsi            #+#    #+#              #
#    Updated: 2025/03/03 11:51:35 by sgabsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################
##  VARIABLES  ##
#################

MCU = ATmega328P
F_CPU = 16000000UL
PORT = /dev/ttyUSB0
BAUD = 115200

# Output
NAME = main.hex

# Directories
SRCDIR = .
INCDIR = .
BINDIR = bin

SRC_FILES = main.c
SRC := $(addprefix $(SRCDIR)/, $(SRC_FILES))

BIN	:= $(SRC:$(SRCDIR)/%.c=$(BINDIR)/%.bin)

# Compiler
CC = avr-gcc
COBJ = avr-objcopy
DUDE = avrdude
CFLAGS = -Wall -Wextra -Werror -Wshadow

OPTIONS = -I $(INCDIR) -DF_CPU=$(F_CPU)


# Progress bar
COUNT						=	1
TOTAL_FILES					=	$(shell find $(SRCDIR) -type f -name "*.c" | wc -l)

# Colors
RED							=	\033[0;31m
GREEN						=	\033[0;32m
YELLOW						=	\033[0;33m
NC							=	\033[0m
KL							=	\033[K

#################
##  TARGETS    ##
#################

all: hex flash

hex: $(BIN)
	@$(COBJ) -O ihex $^ $(NAME)

$(BINDIR)/%.bin: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(OPTIONS) -c $< -o $@
	@printf "$(NC)\rCompiling files: [%-50s] %3d%% (%d/%d) %s$(KL)" \
		"$(shell printf '=%.0s' $$(seq 1 $$(($(COUNT) * 50 / $(TOTAL_FILES)))))" \
		$$(($(COUNT) * 100 / $(TOTAL_FILES))) \
		$(COUNT) \
		$(TOTAL_FILES) \
		$<
	$(eval COUNT=$(shell echo $$(($(COUNT)+1))))

flash:
	@$(DUDE) -p $(MCU) -P $(PORT) -c arduino -b $(BAUD) -U flash:w:$(NAME)

clean:
	@rm -rf $(BINDIR)
	@rm -rf $(NAME)

re: clean all

.PHONY: all hex flash clean re  