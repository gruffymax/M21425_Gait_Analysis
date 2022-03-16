all: gait_func.o
	gcc -g main.c gait_func.o -o test -lm

gait_func.o: gait_func.c
	gcc -c -g gait_func.c -lm

.PHONY: clean
clean:
	rm -f *.o
	rm -f test
