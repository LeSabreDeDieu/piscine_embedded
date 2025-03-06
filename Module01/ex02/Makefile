# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sgabsi <sgabsi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/03 10:04:44 by sgabsi            #+#    #+#              #
#    Updated: 2025/03/06 13:53:55 by sgabsi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################
##  VARIABLES  ##
#################

MCU = atmega328p
F_CPU = 16000000UL
PORT = /dev/ttyUSB0
BAUD = 115200

# Dossiers
SRCDIR = .
OBJDIR = obj
BINDIR = bin

# Output files
BIN_NAME = $(BINDIR)/main.bin
HEX_NAME = main.hex

# Liste des fichiers sources
SRC_FILES = main.c
SRC = $(addprefix $(SRCDIR)/, $(SRC_FILES))

# Liste des fichiers objets
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Compilateurs et options
CC = avr-gcc
COBJ = avr-objcopy
DUDE = avrdude

CFLAGS = -Wall -Wextra -Werror -Wshadow -Os
OPTIONS = -DF_CPU=$(F_CPU) -mmcu=$(MCU)

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

hex: $(HEX_NAME)

$(HEX_NAME): $(BIN_NAME)
	@echo "\033[0;32mGenerating main.hex from main.bin...\033[0m"
	@$(COBJ) -O ihex $< $@

$(BIN_NAME): $(OBJ)
	@mkdir -p $(BINDIR)
	@echo "\033[0;32mLinking all object files into main.bin...\033[0m"
	@$(CC) $(CFLAGS) $(OPTIONS) -o $@ $^
	@rm -fr $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@$(CC) $(CFLAGS) $(OPTIONS) -c $< -o $@
	@printf "$(NC)\rCompiling files: [%-50s] %3d%% (%d/%d) %s$(KL)" \
		"$(shell printf '=%.0s' $$(seq 1 $$(($(COUNT) * 50 / $(TOTAL_FILES)))))" \
		$$(($(COUNT) * 100 / $(TOTAL_FILES))) \
		$(COUNT) \
		$(TOTAL_FILES) \
		$<
	$(eval COUNT=$(shell echo $$(($(COUNT)+1))))
	@printf "\n"

flash: $(HEX_NAME)
	@echo "\033[0;33mFlashing $(HEX_NAME) to microcontroller...\033[0m"
	@$(DUDE) -p $(MCU) -P $(PORT) -c arduino -b $(BAUD) -U flash:w:$(HEX_NAME)

clean:
	@echo "\033[0;31mCleaning up...\033[0m"
	@rm -rf $(BINDIR)
	@rm -rf $(HEX_NAME)

re: clean all

.PHONY: all hex flash clean re
