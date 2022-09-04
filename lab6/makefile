comp3a: merge_sort_rec.o merge.o
	gcc 3a.c merge_sort_rec.o merge.o -o 3a.out

run3a: comp3a
	./3a.out

comp3b: merge_sort_rec.o merge.o
	gcc 3b.c merge_sort_rec.o merge.o -o 3b.out

run3b: comp3b
	./3b.out

merge_sort_rec.o: merge_sort_rec.c
	gcc -c merge_sort_rec.c

merge_sort_itr.o: merge_sort_itr.c
	gcc -c merge_sort_itr.c

merge.o: merge.c
	gcc -c merge.c
