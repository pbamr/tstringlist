#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include "tstringlist.h"
#include "ansistring.h"
#include "pbmath.h"
	
	
	
	
	
	
#define list_max 10
TStringList a[10];

	
	
//--------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
	
	
	
	
	for (s64 n = 0; n < list_max; n++) {
		if (TStringListCreate(&a[n]) != 0) { printf("ERROR: CREATE\n"); exit(1); }
	}
	
	
	a[0].ListSetLength(&a[0], 10);
	a[0].StringSet(&a[0], 0, "Hallo TStringList 0 0,");
	a[0].StringSet(&a[0], 5, "Hallo TStringList 0 5,");
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
		printf("StringInsert:%s\n", a[0].TStringList[5]);
	}



}