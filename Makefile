CC = gcc
OPTIONS = -g -Wall -ansi -pedantic
EXECUTABLE = main
# Ne pas modifier ci-dessous
SOURCE = $(wildcard *.c)
OBJETS = $(SOURCE:.c=.o)
all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJETS)
	$(CC) $(OPTIONS) $(OBJETS) -o $(EXECUTABLE)

%.o: %.c
	$(CC) $(OPTIONS) -MMD -c $<

clean:
	rm -vf *.o *.d

-include *.d


