LIBS=-lm
LDFLAGS=
CPPFLAGS=
CFLAGS=-O3 -g -Wall

all:	abt simple

abt:	abt.o vatr.o sofv.o tofv.o vofs.o traject.o drop.o atmos.o
	cc -o  $@ $> -lm

simple:	simple.o vatr.o sofv.o tofv.o vofs.o traject.o drop.o atmos.o
	cc -o ${LDFLAGS} $@ $> ${LIBS}


.c.o:
	cc ${CPPFLAGS} ${CFLAGS} -c $< 

simple.o: simple.c dragfun.h atmos.h ballistics_prototypes.h g1.h g7.h
	cc ${CPPFLAGS} ${CFLAGS} -c simple.c

abt.o: abt.c dragfun.h atmos.h ballistics_prototypes.h g1.h g7.h
	cc ${CPPFLAGS} ${CFLAGS} -c abt.c

vatr.o: vatr.c dragfun.h
vofs.o: vofs.c dragfun.h
sofv.o: sofv.c dragfun.h
tofv.o: tofv.c dragfun.h
traject.o: traject.c dragfun.h
drop.o: drop.c 
atmos.o: atmos.c

clean:
	rm -f *.o abt simple
