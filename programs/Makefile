SOURCE1		= chef
SOURCE2		= saladmaker
CC		    = gcc
ARGS        = -n 10 -m 0.4
ARGSS       = -t1 1 -t2 5 -s 491580 -i 2
OUT1		= chef
OUT2		= saladmaker
INCLUDE = ../include
MODULES = ../modules
MISC    = ../misc
LDFLAGS = 

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -Wall  -g  -lpthread -I$(INCLUDE)

# Αρχεία .o
OBJS1 = $(SOURCE1).o $(MODULES)/help_funcs.o $(MODULES)/chef_help.o $(MODULES)/shared_memory.o
OBJS2 = $(SOURCE2).o $(MODULES)/help_funcs.o $(MODULES)/saladmaker_help.o

all: $(OUT1) $(OUT2)

$(OUT1): $(OBJS1)
	$(CC) $(OBJS1) -o $(OUT1) $(CFLAGS)

$(OUT2): $(OBJS2)
	$(CC) $(OBJS2) -o $(OUT2) $(CFLAGS)

run: $(OUT1)
	./$(OUT1) $(ARGS)

runn: $(OUT2)
	./$(OUT2) $(ARGSS)

valgrind: $(OUT1)
	valgrind --leak-check=full ./$(OUT1) $(ARGS)

valgrindd: $(OUT2)
	valgrind --leak-check=full ./$(OUT2) $(ARGSS)


clean:	
	rm -f $(OUT1) $(OUT2) $(OBJS1) $(OBJS2) \
	rm -r $(MISC)/*
