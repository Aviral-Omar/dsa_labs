compileAll : readRecords.o insertionSort.o measureTimeAndSpace.o
	gcc exer.c readRecords.o insertionSort.o measureTimeAndSpace.o -o lab5

readRecords.o : readRecords.c readRecords.h
	gcc -c readRecords.c

insertionSort.o : insertionSort.c insertionSort.h
	gcc -c insertionSort.c

measureTimeAndSpace.o : measureTimeAndSpace.c measureTimeAndSpace.h
	gcc -c measureTimeAndSpace.c
