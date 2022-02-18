# Aleksandr Verevkin (xverev00)

CC = gcc
FLAGS = -std=gnu99 -Werror -Wall -Wextra -lm
MAIN_FILE = hinfosvc.c
COMPILE = -o hinfosvc

all:
	$(CC) $(FLAGS) $(MAIN_FILE) $(COMPILE)
	