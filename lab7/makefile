comp1: sort.o qs.o stack.o insertion_sort.o
	gcc ex1.c sort.o qs.o stack.o insertion_sort.o -o ex1.out

run1: comp1
	./ex1.out

comp2: sort.o qs.o stack.o insertion_sort.o
	gcc ex2.c sort.o qs.o stack.o insertion_sort.o -o ex2.out

run2: comp2
	./ex2.out 100000 output.txt

sort.o: sort.c
	gcc -c sort.c

stack.o: stack.c
	gcc -c stack.c

qs.o: qs.c
	gcc -c qs.c

insertion_sort.o: insertion_sort.c
	gcc -c insertion_sort.c
