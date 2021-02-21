#
# FILE			: makefile
# PROJECT		: Assignment 01 - Getting to Know the Linux Development Environment
# PROGRAMMER		: Filipe Brito (7843808) & Zandrin Joseph ()
# FIRST VERSION	: 21/FEB/2021
# DESCRIPTION		: This file will construct the final executable by compiling the 
#	sources and linking the object files.
#

# =======================================================
#                       encodeInput
# =======================================================
# FINAL BINARY TARGET
./bin/encodeInput: ./obj/main.o ./obj/middleman.o ./obj/encoder.o
	cc ./obj/main.o ./obj/middleman.o ./obj/encoder.o -o ./bin/encodeInput
#
# =======================================================
#                       Dependencies
# =======================================================
./obj/main.o: ./src/main.c
	cc -c ./src/main.c -o ./obj/main.o

./obj/middleman.o: ./src/middleman.c
	cc -c ./src/middleman.c -o ./obj/middleman.o

./obj/encoder.o: ./src/encoder.c
	cc -c ./src/encoder.c -o ./obj/encoder.o

#
# =======================================================
# Other targets
# =======================================================
all: ./bin/encodeInput

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
