all: solution libsolution.so

libsolution.so: libsolution.c
	gcc -ggdb -shared -fPIC -o libsolution.so libsolution.c

solution: solution.c
	gcc -ggdb -Wl,--no-as-needed,-ldl,-rpath,. -o solution solution.c
clean:
	-rm solution
	-rm *.o
