/*
 * Copyright (c) 2022/05/18, 2022.07.06, Peter Boettcher, Germany/NRW, Muelheim Ruhr
 * Urheber: 2022/05/18, 2022.07.6,  Peter Boettcher, Germany/NRW, Muelheim Ruhr

   Permission is hereby granted, free of charge, to any person obtaining 
   a copy of this software and associated documentation files (the “Software”),
   to deal in the Software without restriction, including without limitation
   the rights to use, copy, modify, merge, publish, distribute, sublicense,
   and/or sell copies of the Software, and to permit persons to whom the
   Software is furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be included
   in all copies or substantial portions of the Software.

   The Software is provided “as is”, without warranty of any kind, express
   or implied, including but not limited to the warranties of merchantability,
   fitness for a particular purpose and noninfringement. In no event shall the
   authors or copyright holders be liable for any claim, damages or other
   liability, whether in an action of contract, tort or otherwise, arising from,
   out of or in connection with the software or the use or other dealings in the
   Software.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include "tstringlist.h"


typedef signed long long int s64;
typedef unsigned long long int u64;



int TryStrToInt64 (char *STRING_NUMBER, s64 *NUMBER, int ZAHLEN_SYSTEM) {

	char *ERROR;

	if (strlen(STRING_NUMBER) == 0) return (-1);

	*NUMBER = strtoll(STRING_NUMBER, &ERROR, ZAHLEN_SYSTEM);
	if (strlen(ERROR) != 0) return (-1);

	if (*NUMBER == 9223372036854775807) {
		if (strncmp(STRING_NUMBER, "9223372036854775807", 19) != 0) return(-1);
		else return(0);
	}

	/* Warning gcc: -922337203685477588 */
	if (*NUMBER + 1 == -9223372036854775807) {
		if (strncmp(STRING_NUMBER, "-9223372036854775808", 20) != 0) return(-1);
		else return(0);
	}

	return(0);
}






#define list_max 9000000
TStringList a[list_max];
TStringList b;






//--------------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	s64 NUMBER;
	char	*line;
	size_t	line_length = 0;
	ssize_t	line_size = 0;

	printf("INIT b State: %lld\n", ListInitState(&b, 0, sizeof(TStringList), sizeof(b)));
	if (TStringListCreate(&b, 0, sizeof(TStringList), sizeof(b)) != 0) { printf("ERROR: CREATE\n"); /* exit(-1); */ }
	printf("INIT b State: %lld\n", ListInitState(&b, 0, sizeof(TStringList), sizeof(b)));


	printf("NUMBER: ");
	line_size = getline(&line, &line_length, stdin);
	TryStrToInt64 (line, &NUMBER, 10);


	printf("INIT State: %lld\n", ListInitState(&a[NUMBER], NUMBER, sizeof(TStringList), sizeof(a)));
	//memory Error if NUMBER > list_max. DO NOT USE!
	printf("INIT State: %lld\n", a[NUMBER].INIT);

	for (s64 n = 0; n < list_max; n++) {
		if (TStringListCreate(&a[n], n, sizeof(TStringList), sizeof(a)) != 0) { printf("ERROR: CREATE\n"); /* exit(-1); */ }
	}

	printf("INIT State: %lld\n", ListInitState(&a[NUMBER], NUMBER, sizeof(TStringList), sizeof(a)));
	//memory Error if NUMBER > list_max.  DO NOT USE!
	printf("INIT State: %lld\n", a[NUMBER].INIT);

	printf("listfree a: %d\n", ListFree(&a[10000-1], 10000-1, sizeof(TStringList), sizeof(a)));
	printf("listfree b: %d\n", ListFree(&b, 1, sizeof(TStringList), sizeof(b)));

	if (TStringListCreate(&b, 1, sizeof(TStringList), sizeof(b)) != 0) { printf("ERROR: CREATE\n"); /* exit(-1); */ }
	printf("listfree b: %d\n", ListFree(&b, 0, sizeof(TStringList), sizeof(b)));

	printf("INIT aaa: %lld\n", ListInitState(&a[100000], 100000,sizeof(TStringList), sizeof(a)));
	printf("INIT aaa: %lld\n", ListInitState(&a[NUMBER], NUMBER, sizeof(TStringList), sizeof(a)));



printf("key");
getchar();

	printf("ELEMENTS: %lld\n", ListCount(&a[0], 0, sizeof(TStringList), sizeof(a)));
	ListSetLength(&a[0], 0, sizeof(TStringList), sizeof(a), 10);
	printf("ELEMENTs: %lld\n", ListCount(&a[0], 0, sizeof(TStringList), sizeof(a)));

	for (int n = 0; n < 10; n++) {
		StringSet(&a[0], 0, sizeof(TStringList), sizeof(a), n, "Hello TStringList");
	}

	if (StringCheck(&a[0], 0, sizeof(TStringList), sizeof(a),5) == 0) {
		printf("StringSet:%s\n", a[0].TStringList[5]);
	}

	if (StringCheck(&a[0],0, sizeof(TStringList), sizeof(a), 0) == 0) {
		printf("%s\n", a[0].TStringList[0]);
	}

	if (StringCheck(&a[6], 0, sizeof(TStringList), sizeof(a),5) == 0) {
		printf("%s\n", a[6].TStringList[5]);
	}

	StringAdd(&a[0], 0, sizeof(TStringList), sizeof(a),0, "aaaaaaaaaaaaaaaax");
	if (StringCheck(&a[0], 0, sizeof(TStringList), sizeof(a),0) == 0) {
		printf("StringAdd:%s\n", a[0].TStringList[0]);
	}

	StringAdd(&a[0],0, sizeof(TStringList), sizeof(a), 0, "bbbbbbbbbbbbbbbbx");
	if (StringCheck(&a[0], 0, sizeof(TStringList), sizeof(a),0) == 0) {
		printf("StringAdd:%s\n", a[0].TStringList[0]);
	}

	StringAdd(&a[0], 0, sizeof(TStringList), sizeof(a),0, a[0].TStringList[0]);
	StringAdd(&a[0], 0, sizeof(TStringList), sizeof(a),0, a[0].TStringList[0]);
	StringAdd(&a[0], 0, sizeof(TStringList), sizeof(a),0, a[0].TStringList[0]);
	StringAdd(&a[0], 0, sizeof(TStringList), sizeof(a),0, a[0].TStringList[0]);
	if (StringCheck(&a[0], 0, sizeof(TStringList), sizeof(a),0) == 0) {
		printf("StringAdd:%s\n", a[0].TStringList[0]);
	}

	/* liste einen weniger */
	ListDel(&a[0], 0, sizeof(TStringList), sizeof(a), 5);
	if (StringCheck(&a[0], 0, sizeof(TStringList), sizeof(a),5) == 0) {
		printf("ListDel:%s\n", a[0].TStringList[5]);
	}


	StringAdd(&a[0], 0, sizeof(TStringList), sizeof(a), 5, "bbbbbbbbbbbbbbbbx");
	if (StringCheck(&a[0], 0, sizeof(TStringList), sizeof(a), 5) == 0) {
		printf("StringAdd:%s\n", a[0].TStringList[5]);
	}

	StringSet(&a[0], 0, sizeof(TStringList), sizeof(a), 5, "z");
	if (StringCheck(&a[0], 0, sizeof(TStringList), sizeof(a), 5) == 0) {
		printf("StringSet:%s\n", a[0].TStringList[5]);
	}

	StringAdd(&a[0], 0, sizeof(TStringList), sizeof(a),5, "12345678900x");
	if (StringCheck(&a[0], 0, sizeof(TStringList), sizeof(a),5) == 0) {
		printf("StringAdd:%s\n", a[0].TStringList[5]);
	}

	StringReplace(&a[0], 0, sizeof(TStringList), sizeof(a),5, 0, "Yabc");
	if (StringCheck(&a[0],0, sizeof(TStringList), sizeof(a), 5) == 0) {
		printf("StringReplace:%s\n", a[0].TStringList[5]);
	}

	printf("%lld\n", StringDel(&a[0], 0, sizeof(TStringList), sizeof(a),5, 10, 2));
	if (StringCheck(&a[0], 0, sizeof(TStringList), sizeof(a), 5) == 0) {
		printf("StringDel:%s\n", a[0].TStringList[5]);
	}


	StringAdd(&a[0], 0, sizeof(TStringList), sizeof(a),5, "1234567890");
	if (StringCheck(&a[0], 0, sizeof(TStringList), sizeof(a),5) == 0) {
		printf("StringAdd:%s\n", a[0].TStringList[5]);
	}

	StringInsert(&a[0], 0, sizeof(TStringList), sizeof(a),5, 2, "abcde");
	if (StringCheck(&a[0], 0, sizeof(TStringList), sizeof(a),5) == 0) {
		printf("StringInsert:%s\n", a[0].TStringList[5]);
	}

	printf("%lld\n", StringInsert(&a[0], 0, sizeof(TStringList), sizeof(a),5, 1, "zyx"));
	if (StringCheck(&a[0], 0, sizeof(TStringList), sizeof(a),5) == 0) {
		printf("StringInsert:%s\n\n\n", a[0].TStringList[5]);
	}


printf("key");
getchar();
	ListSort(&a[0],0, sizeof(TStringList), sizeof(a));
	for (int n = 0; n < 10; n++) {
		if (StringCheck(&a[0], 0, sizeof(TStringList), sizeof(a),n) == 0) {
			printf("%s\n\n", a[0].TStringList[n]);
		}
	}

printf("key");
getchar();
	ListDel(&a[0], 0, sizeof(TStringList), sizeof(a),7);
	/* liste einen weniger */
	printf("list delete one line\n");
	ListSort(&a[0], 0, sizeof(TStringList), sizeof(a));
	for (int n = 0; n < 10; n++) {
		if (StringCheck(&a[0], 0, sizeof(TStringList), sizeof(a),n) == 0) {
			printf("%s\n\n", a[0].TStringList[n]);
		}
	}

printf("key");
getchar();
	ListAdd(&a[0],0, sizeof(TStringList), sizeof(a), "new string");

	printf("list new line:\n");
	ListSort(&a[0], 0,sizeof(TStringList), sizeof(a));
	for (int n = 0; n < 10; n++) {
		if (StringCheck(&a[0],0,sizeof(TStringList), sizeof(a), n) == 0) {
			printf("%s\n\n", a[0].TStringList[n]);
		}
	}

	printf("COUNT: %lld\n", a[0].TStringListCount);

	printf("Index found: %lld\n", ListIndex(&a[0], 0,sizeof(TStringList), sizeof(a), "new string"));

printf("key");
getchar();
	char *TEXT;
	ListText(&a[0],0,sizeof(TStringList), sizeof(a), &TEXT);
	printf("%s", TEXT);
	free(TEXT);

	for(s64 n = 0; n < 100000000; n++) {
			ListAdd(&a[5],5,sizeof(TStringList), sizeof(a), "TEXT 0");
	}

	printf("init: %lld\n", a[5].TStringListCount);

	StringSet(&a[5], 5, sizeof(TStringList), sizeof(a), 99999999, "hello julia" );
	printf("Index found: %lld\n", ListIndex(&a[5], 5,sizeof(TStringList), sizeof(a),"hello julia"));

printf("last key");
getchar();
	ListFree(&a[5], 5, sizeof(TStringList), sizeof(a));
	printf("%p   %lld  %lld\n", a[5].TStringList, a[5].TStringListCount, ListCount(&a[5], 5,sizeof(TStringList), sizeof(a)));

}
