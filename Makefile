all:	abt simple

abt:	abt.o vatr.o sofv.o tofv.o vofs.o traject.o drop.o atmos.o
	cc -o  $@ $> -lm

simple:	simple.o vatr.o sofv.o tofv.o vofs.o traject.o drop.o atmos.o
	cc -o  $@ $> -lm


.c.o:
	cc -c $< 

simple.o: simple.c dragfun.h
	cc -c -DUSE_G7 simple.c

abt.o: abt.c dragfun.h
	cc -c -DUSE_G7 abt.c

vatr.o: vatr.c dragfun.h
vofs.o: vofs.c dragfun.h
sofv.o: sofv.c dragfun.h
tofv.o: tofv.c dragfun.h
traject.o: traject.c dragfun.h
drop.o: drop.c 
atmos.o: atmos.c
