CC := gcc
CFLAGS := -Wall -g
SYNTREE_OBJS := char_buf.o tokenizer.o  util.o list.o syntree.o struct_analyzer.o cogen_env.o cogen_label.o cogen_fun.o cogen_stmt.o

all: cogen

cogen: $(SYNTREE_OBJS) cogen_main.o
	$(CC) -o $@ $^

clean:
	rm -f $(SYNTREE_OBJS) cogen_main.o