CFLAGS   += -std=c99 -g -O2 -Wall -Wextra -Wpedantic
CPPFLAGS += -D_POSIX_VERSION=200112L
LDLIBS    = -lm

test: avg.o test.o

clean:
	$(RM) avg.o test.o test
