#include <stdio.h>
#include <stdlib.h>

#ifndef CREDIT_CARD
#define CREDIT_CARD

typedef struct credit_card {
	long long unsigned int cardNumber;
	char bankCode[5];
	char expiryDate[7];
	char firstName[5];
	char lastName[5];
} * CreditCard;

struct records {
	CreditCard* arr;
	int n;
};

#endif
