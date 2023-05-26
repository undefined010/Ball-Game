cxx = gcc src/* -o out/main -O1 -Wall -std=c99 -Wno-missing-braces -L ./lib/ -I ./include/  -lraylib 

all:
	$(cxx)

clear_all:
	rm out/*
	@echo "removing output files"