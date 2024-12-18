CC = gcc
CFLAGS = -Wall -g


SRCS = main.c creature.c item.c save_load.c
OBJS = $(SRCS:.c=.o)


EXEC = ultrakill


all: $(EXEC)


$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(EXEC)


%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS) $(EXEC)

.PHONY: all clean