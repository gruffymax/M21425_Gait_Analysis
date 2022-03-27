LINK_TARGET := testgait

LIBS := -lunity \
		-lm

INCS := -L. \
	-I.

SRCS := gait_func_testharness.c \
	main.c \


OBJS :=  $(SRCS:.c=.o)

CFLAGS := -g3 \
	-Wall \
	-c

LDFLAGS := -g3

all: $(LINK_TARGET) 

$(LINK_TARGET): $(OBJS)
	gcc $(LDFLAGS) $(INCS) -o $@ $^ $(LIBS)

%.o: %.c
	gcc $(CFLAGS) $(INCS) -o $@ $^ 

.PHONY: clean
clean:
	rm -f *.o
	rm -f testgait
