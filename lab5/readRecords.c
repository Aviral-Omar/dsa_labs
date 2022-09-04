#include "readRecords.h"

struct records readData(FILE* fp, int size)
{
	int n = 10;
	CreditCard* arr = (CreditCard*)malloc(n * sizeof(CreditCard));
	int j = 0;
	for (int k = 0; k < (double)size / 100000; k++) {
		while (1) {
			fgetc(fp);
			if (feof(fp)) {
				break;
			}
			if (j == n) {
				n *= 10;
				arr = (CreditCard*)realloc(arr, n * sizeof(CreditCard));
			}
			CreditCard cc = (CreditCard)malloc(sizeof(struct credit_card));
			fscanf(fp, "%llu", &cc->cardNumber);
			fgetc(fp);
			for (int i = 0; i < 5; i++) {
				cc->bankCode[i] = fgetc(fp);
			}
			fgetc(fp);
			for (int i = 0; i < 7; i++) {
				cc->expiryDate[i] = fgetc(fp);
			}
			fgetc(fp);
			for (int i = 0; i < 5; i++) {
				cc->firstName[i] = fgetc(fp);
			}
			fgetc(fp);
			for (int i = 0; i < 5; i++) {
				cc->lastName[i] = fgetc(fp);
			}
			fgetc(fp);
			fgetc(fp);
			arr[j] = cc;
			j++;
		}
		fseek(fp, 0, SEEK_SET);
	}
	fclose(fp);
	struct records r;
	r.arr = arr;
	r.n = n;
	return r;
}
