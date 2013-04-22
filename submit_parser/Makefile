CC := gcc
CFLAGS := -Wall -g
SYNTREE_OBJS := util.o list.o syntree.o struct_analyzer.o tokenizer.o char_buf.o

all: parser

parser: $(SYNTREE_OBJS) parser_main.o
	$(CC) -o $@ $^

clean:
	rm -f $(SYNTREE_OBJS) parser_main.o

