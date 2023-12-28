ifdef _DEBUG_
DEBUG += -D_DEBUG_
endif

all: solution test

solution: solution.c
	gcc -ggdb $(DEBUG) -o solution solution.c
test: test.c
	gcc -ggdb $(DEBUG) -o test test.c
clean:
	-rm solution
	-rm test
	-rm *.o
