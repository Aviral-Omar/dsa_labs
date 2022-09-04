#include <sys/time.h>
#include "insertionSort.h"
#include "readRecords.h"


struct records readingTimeTest(int size, FILE* fp);
void insertionTest(struct records r, FILE* fp);
