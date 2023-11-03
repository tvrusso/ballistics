LIBS=-lm
LDFLAGS=
CPPFLAGS=
CFLAGS=-O3 -g -Wall
BASIC_OBJS=vatr.o sofv.o tofv.o vofs.o traject.o drop.o atmos.o

all:	abt simple

abt:	abt.o ${BASIC_OBJS} 
	$(CC) -o  $@ abt.o ${BASIC_OBJS} -lm

simple:	simple.o ${BASIC_OBJS}
	$(CC) -o ${LDFLAGS} $@ simple.o ${BASIC_OBJS} ${LIBS}


.c.o:
	$(CC) ${CPPFLAGS} ${CFLAGS} -c $< 

simple.o: simple.c dragfun.h atmos.h ballistics_prototypes.h g1.h g7.h
	$(CC) ${CPPFLAGS} ${CFLAGS} -c simple.c

abt.o: abt.c dragfun.h atmos.h ballistics_prototypes.h g1.h g7.h
	$(CC) ${CPPFLAGS} ${CFLAGS} -c abt.c

vatr.o: vatr.c dragfun.h
vofs.o: vofs.c dragfun.h
sofv.o: sofv.c dragfun.h
tofv.o: tofv.c dragfun.h
traject.o: traject.c dragfun.h
drop.o: drop.c 
atmos.o: atmos.c

clean:
	rm -f *.o abt simple
