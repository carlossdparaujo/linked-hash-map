
edit : linkedhashmap.o testrunner.o 
	gcc linkedhashmap.o testRunner.o linkedhashmaptest.c -o linkedhashmaptest

linkedhashmap.o : linkedhashmap.c
	gcc -c linkedhashmap.c
testrunner.o : CUnitForAndo/src/testRunner.c
	gcc -c CUnitForAndo/src/testRunner.c

clean : 
	rm linkedhashmap.o testRunner.o  linkedhashmaptest
