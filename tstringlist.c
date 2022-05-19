#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <malloc.h>
#include "tstringlist.h"
	
	
	
//EXAMPLES:
void test0(TStringList *x)
{
	
	x->DynStrcpy(x, 10, "hallo aaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
	
	
}
	
	
	
void test(TStringList x)
{
	
	x.DynStrcpy(&x, 10, "hallo bbbbbbbbbbbbbbbbbbb");
	
	
}
	

	
	
TStringList b[1000];
TStringList a;
TStringList CLEAR;
	
	
//--------------------------------------------------------------------------------------------------
void main(void) {
	
TStringListCreate(&a);
printf("%ld  %ld %ld %ld\n", a.COUNT_BYTES_FILE, a.COUNT_LINES_FILE, a.TStringList_Length_Max, a.TStringList_Lines);
a.DynFree(&a);
a.LoadFromFile(&a, "file.txt");
	
for (s64 n = 0; n < a.TStringList_Lines; n++) {
	printf("%s\n", a.TStringList[n]);
}
printf("LoadFrom: %ld  %ld %ld %ld\n\n", a.COUNT_BYTES_FILE, a.COUNT_LINES_FILE, a.TStringList_Length_Max, a.TStringList_Lines);
	
	
a.DynFree(&a);
a.SetDelDUP(&a, true);
a.LoadFromFile(&a, "file.txt");
	
for (s64 n = 0; n < a.TStringList_Lines; n++) {
	printf("%s\n", a.TStringList[n]);
}
printf("LoadFrom with DelDUP: %ld  %ld %ld %ld\n\n", a.COUNT_BYTES_FILE, a.COUNT_LINES_FILE, a.TStringList_Length_Max, a.TStringList_Lines);
	
a.Del(&a, 1);
for (s64 n = 0; n < a.TStringList_Lines; n++) {
	printf("%s\n", a.TStringList[n]);
}
printf("after del: %ld  %ld %ld %ld\n\n", a.COUNT_BYTES_FILE, a.COUNT_LINES_FILE, a.TStringList_Length_Max, a.TStringList_Lines);

	
	
	
TStringListCreate(&b[88]);
printf("%ld\n", b[88].SetLines(&b[88], 1000000));
printf("setlines: %ld  %ld %ld %ld\n", b[88].COUNT_BYTES_FILE, b[88].COUNT_LINES_FILE, b[88].TStringList_Length_Max, b[88].TStringList_Lines);
	
b[88].DynStrcpy(&b[88], 12, "hello");
b[88].DynStrcat(&b[88], 12, " + hello");
printf("%s\n", b[88].TStringList[12]);

b[88].Del(&b[88], 12);
b[88].Add(&b[88], "Hello");
b[88].DynFree(&b[88]);
	
	
	
	
	
	
	

}