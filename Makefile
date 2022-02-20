# Aleksandr Verevkin (xverev00)

CC = gcc
FLAGS = -std=gnu99 -lm #-Werror -Wall -Wextra
MAIN_FILE = hinfosvc.c
COMPILE = -o hinfosvc

all:
	$(CC) $(FLAGS) $(MAIN_FILE) $(COMPILE)
	
