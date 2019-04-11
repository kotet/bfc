CC := gcc
CFLAGS := -Wall -Wextra

bfc:

test: bfc
	./test.sh

clean:
	$(RM) bfc tmp*