SDIR = srcs/
HDIR = includes/
BDIR = bin/

TARGET = got
SRCS = $(SDIR)main.c	\
       $(SDIR)got.c
OBJS = $(SRCS:$(SDIR)%.c=$(BDIR)%.o)
HEADS = $(HDIR)got.h

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3

all: $(TARGET)

re: fclean all

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(TARGET)

$(TARGET): $(OBJS) $(HEADS)
	$(CC) $(CFLAGS) -I $(HDIR) $(OBJS) -o $(TARGET)

$(BDIR)%.o: $(SDIR)%.c $(HEADS)
	$(CC) $(CFLAGS) -I $(HDIR) -c $< -o $@

.PHONY: clean fclean all
