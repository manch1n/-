LIB=
CFLAGS=std=c++17 -O2
OBJECTS=common.o ceasar.o playfair.o hill.o

benchmark:${OBJECTS}
	g++ ${CFLAGS} -o benchmark ${OBJECTS}
common.o:
	g++ ${CFLAGS} -c common.h
ceasar.o:common.h
	g++ ${CFLAGS} -c ceasar.h
playfair.o:common.h
	g++ ${CFLAGS} -c playfair.h
hill.o:common.h
	g++ ${CFLAGS} -c hill.h

.PHONY:clean
clean:
	rm -rf *.o benchmark
