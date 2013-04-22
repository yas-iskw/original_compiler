CC=gcc
CFLAGS=-Wall -g
OBJS=tokenizer.o tokenizer_main.o char_buf.o

tokenizer : $(OBJS)
	gcc -o $@ $(OBJS)

clean :
	rm -f $(OBJS)