# Aleksandr Verevkin (xverev00)

CC = gcc
FLAGS = -std=gnu99
MAIN_FILE = hinfosvc.c
COMPILE = -o hinfosvc
ZIP = xverev00.zip

.PHONY: all pack clean

all:
	$(CC) $(FLAGS) $(MAIN_FILE) $(COMPILE)

pack:
	zip $(ZIP) $(MAIN_FILE) Makefile Readme.md

clean:
	rm -rf hinfosvc $(ZIP) 
