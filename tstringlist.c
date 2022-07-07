#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include "tstringlist.h"
	
	
	
	
	
	
#define list_max 10
TStringList a[10];

	
	
//--------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
	
	
	
	
	for (s64 n = 0; n < list_max; n++) {
		if (TStringListCreate(&a[n]) != 0) { printf("ERROR: CREATE\n"); exit(1); }
	}
	
	
	a[0].ListSetLength(&a[0], 10);
	for (int n = 0; n < 10; n++) {
		a[0].StringSet(&a[0], n, "Hello TStringList");
	}

	if (a[0].StringCheck(&a[0], 5) == 0) {
		printf("StringSet:%s\n", a[0].TStringList[5]);
	}

	if (a[0].StringCheck(&a[0], 0) == 0) {
		printf("%s\n", a[0].TStringList[0]);
	}
	
	if (a[6].StringCheck(&a[6], 5) == 0) {
		printf("%s\n", a[6].TStringList[5]);
	}
	
	a[0].StringAdd(&a[0], 0, "aaaaaaaaaaaaaaaax");
	if (a[0].StringCheck(&a[0], 0) == 0) {
		printf("StringAdd:%s\n", a[0].TStringList[0]);
	}
	
	a[0].StringAdd(&a[0], 0, "bbbbbbbbbbbbbbbbx");
	if (a[0].StringCheck(&a[0], 0) == 0) {
		printf("StringAdd:%s\n", a[0].TStringList[0]);
	}
	
	a[0].StringAdd(&a[0], 0, a[0].TStringList[0]);
	a[0].StringAdd(&a[0], 0, a[0].TStringList[0]);
	a[0].StringAdd(&a[0], 0, a[0].TStringList[0]);
	a[0].StringAdd(&a[0], 0, a[0].TStringList[0]);
	if (a[0].StringCheck(&a[0], 0) == 0) {
		printf("StringAdd:%s\n", a[0].TStringList[0]);
	}
	
	/* liste einen weniger */
	a[0].ListDel(&a[0], 5);
	if (a[0].StringCheck(&a[0], 5) == 0) {
		printf("ListDel:%s\n", a[0].TStringList[5]);
	}
	
	
	a[0].StringAdd(&a[0], 5, "bbbbbbbbbbbbbbbbx");
	if (a[0].StringCheck(&a[0], 5) == 0) {
		printf("StringAdd:%s\n", a[0].TStringList[5]);
	}

	a[0].StringSet(&a[0], 5, "z");
	if (a[0].StringCheck(&a[0], 5) == 0) {
		printf("StringSet:%s\n", a[0].TStringList[5]);
	}

	a[0].StringAdd(&a[0], 5, "12345678900x");
	if (a[0].StringCheck(&a[0], 5) == 0) {
		printf("StringAdd:%s\n", a[0].TStringList[5]);
	}

	a[0].StringReplace(&a[0], 5, 0, "Yabc");
	if (a[0].StringCheck(&a[0], 5) == 0) {
		printf("StringReplace:%s\n", a[0].TStringList[5]);
	}

	printf("%lld\n", a[0].StringDel(&a[0], 5, 10, 2));
	if (a[0].StringCheck(&a[0], 5) == 0) {
		printf("StringDel:%s\n", a[0].TStringList[5]);
	}


	a[0].StringAdd(&a[0], 5, "1234567890");
	if (a[0].StringCheck(&a[0], 5) == 0) {
		printf("StringAdd:%s\n", a[0].TStringList[5]);
	}

	a[0].StringInsert(&a[0], 5, 2, "abcde");
	if (a[0].StringCheck(&a[0], 5) == 0) {
		printf("StringInsert:%s\n", a[0].TStringList[5]);
	}

	printf("%lld\n", a[0].StringInsert(&a[0], 5, 1, "zyx"));
	if (a[0].StringCheck(&a[0], 5) == 0) {
		printf("StringInsert:%s\n\n\n", a[0].TStringList[5]);
	}
	

printf("key");
getchar();
	a[0].ListSort(&a[0]);
	for (int n = 0; n < 10; n++) {
		if (a[0].StringCheck(&a[0], n) == 0) {
			printf("%s\n\n", a[0].TStringList[n]);
		}
	}

printf("key");
getchar();
	a[0].ListDel(&a[0], 7);
	/* liste einen weniger */
	printf("list delete one line\n");
	a[0].ListSort(&a[0]);
	for (int n = 0; n < 10; n++) {
		if (a[0].StringCheck(&a[0], n) == 0) {
			printf("%s\n\n", a[0].TStringList[n]);
		}
	}

printf("key");
getchar();
	a[0].ListAdd(&a[0], "new string");

	printf("list new line:\n");
	a[0].ListSort(&a[0]);
	for (int n = 0; n < 10; n++) {
		if (a[0].StringCheck(&a[0], n) == 0) {
			printf("%s\n\n", a[0].TStringList[n]);
		}
	}

	printf("COUNT: %lld\n", a[0].TStringListCount);
	
	printf("Index found: %lld\n", a[0].ListIndex(&a[0], "new string"));

printf("key");
getchar();
	char *TEXT;
	a[0].ListText(&a[0], &TEXT);
	printf("%s", TEXT);
	free(TEXT);

	for(s64 n = 0; n < 100000000; n++) {
			a[5].ListAdd(&a[5], "TEXT 0");
	}

	printf("init: %lld\n", a[5].TStringListCount);

	a[5].StringSet(&a[5], 99999999, "hello julia" );
	printf("Index found: %lld\n", a[5].ListIndex(&a[5], "hello julia"));














}