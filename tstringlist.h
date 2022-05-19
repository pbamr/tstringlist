/*
 * Copyright (c) 2022/05/18, Peter Boettcher, Germany/NRW, Muelheim Ruhr
 * Urheber: 2022/05/12, Peter Boettcher, Germany/NRW, Muelheim Ruhr

 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses
 *
*/
	
	
	
/*
EXAMPLES:
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
	
	
*/
	
	
	
#ifndef tstringlist
#define tstringlist
	
	
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
	
	
	
	
	
typedef signed long long int s64;
typedef unsigned long long int u64;
	
	
	
typedef int bool;
#define true 1
#define false 0
	
	
	
	
	
	
	
	
	
//--------------------------------------------------------------------------------------------------------------------
//deklaration
typedef struct {
	//public
	char	**TStringList;
	s64	COUNT_BYTES_FILE;
	s64	COUNT_LINES_FILE;
	
	s64	TStringList_Length_Max;
	s64	TStringList_Lines;
	
	bool	DelDUP;
	bool	SORT;
	
	//public Funktionen
	s64 (*CountBytesFile)	(void *self, char *file_name);
	s64 (*CountLinesFile)	(void *self, char *file_name);
	s64 (*SetLines)		(void *self, s64 numbers);
	s64 (*DynStrcpy)	(void *self, s64 number, char *newstring);
	s64 (*DynStrcat)	(void *self, s64 number, char *newstring);
	s64 (*Del)		(void *self, s64 number);
	s64 (*CountLines)	(void *self);
	s64 (*StringLengthMax)	(void *self);
	s64 (*LoadFromFile)	(void *self, char *file_name);
	s64 (*DelDup)		(void *self);
	s64 (*DynFree)		(void *self);
	s64 (*MaxStr)		(void *self);
	s64 (*Add)		(void *self, char *newstring);
	s64 (*Sort)		(void *self);
	s64 (*SetSort)		(void *self, bool b);
	s64 (*SetDelDUP)	(void *self, bool b);
	
	
	
} TStringList;
	
	
	
	
	
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
	
	
	
	
	
int str_compare(const void *a, const void *b)
{
	const char **pa = (const char **)a;
	const char **pb = (const char **)b;
	return strcmp(*pa, *pb);
}
	
	
	
	
	
s64 Sort (void *self) {
	
	TStringList *struct_tstringlist = self;
	
	qsort(struct_tstringlist->TStringList, struct_tstringlist->TStringList_Lines, sizeof(char *), str_compare);
	
	return(0);
	
}	
	
	
	
	
	
s64 SetSort (void *self, bool b) {
	
	TStringList *struct_tstringlist = self;
	
	if (b == true) struct_tstringlist->SORT = true;
	else struct_tstringlist->SORT = false;
	
	return(0);
	
}	
	
	
	
	
	
s64 SetDelDUP (void *self, bool b) {
	
	TStringList *struct_tstringlist = self;
	
	if (b == true) struct_tstringlist->DelDUP = true;
	else struct_tstringlist->DelDUP = false;
	
	return(0);
	
}	
	
	
	
	
	
s64 Add(void *self, char *newstring)
{
	TStringList *struct_tstringlist = self;
	
	//New
	if (struct_tstringlist->TStringList_Lines == -1) {
		struct_tstringlist->TStringList = malloc(1 * sizeof(char *));
		if (struct_tstringlist->TStringList == NULL) return(-1);
		
		struct_tstringlist->TStringList[0] = malloc((strlen(newstring) + 1) * sizeof(char));
		
		if (struct_tstringlist->TStringList[struct_tstringlist->TStringList_Lines] == NULL) {
			//former state
			free(struct_tstringlist->TStringList);
			return(-1);
		}
		
		
		strcpy(struct_tstringlist->TStringList[0], newstring);
		struct_tstringlist->TStringList_Lines = 1;
		
		return(0);
	}
	
	//backup pointer
	char **backup_ptr = struct_tstringlist->TStringList;
	s64 lines = struct_tstringlist->TStringList_Lines + 1;
	
	//New LINE
	backup_ptr = realloc(backup_ptr, lines * sizeof(char *));
	if (backup_ptr == NULL) return(-1);
	else struct_tstringlist->TStringList = backup_ptr;
	
	//MEM Columns
	struct_tstringlist->TStringList[struct_tstringlist->TStringList_Lines] = malloc((strlen(newstring) + 1) * sizeof(char));
	if (struct_tstringlist->TStringList[struct_tstringlist->TStringList_Lines] == NULL) {
		//former state
		struct_tstringlist->TStringList = realloc(struct_tstringlist->TStringList, (lines - 1) * sizeof(char *));
		return(-1);
	}
	
	strcpy(struct_tstringlist->TStringList[struct_tstringlist->TStringList_Lines], newstring);
	struct_tstringlist->TStringList_Lines++;
	
	return(0);
}
	
	
	
	
	
s64 MaxStr (void *self)
{
	TStringList *struct_tstringlist = self;
	
	s64 MAX;
	for (s64 n = 0; n < struct_tstringlist->TStringList_Lines; n++) {
		if (struct_tstringlist->TStringList[n] != NULL) {
			MAX = strlen(struct_tstringlist->TStringList[n]);
			if (MAX > struct_tstringlist->TStringList_Length_Max) struct_tstringlist->TStringList_Length_Max = MAX;
		}
	}
	
	return(0);
}
	
	
	
	
	
s64 DynFree (void *self)
{
	TStringList *struct_tstringlist = self;
	
	if (struct_tstringlist->TStringList_Lines == -1) return(-1);
	
	for (s64 n = 0; n < struct_tstringlist->TStringList_Lines; n++) {
		if (struct_tstringlist->TStringList[n] != NULL) free(struct_tstringlist->TStringList[n]);
	}
	
	free(struct_tstringlist->TStringList);
	struct_tstringlist->TStringList = NULL;
	
	
	struct_tstringlist->TStringList_Lines = -1;
	struct_tstringlist->TStringList_Length_Max = -1;
	struct_tstringlist->COUNT_BYTES_FILE = -1;
	struct_tstringlist->COUNT_LINES_FILE = -1;
	
	return(0);
	
}
	
	
	
	
	
s64 CountLinesFile(void *self, char *file_name)
{
	long long n = 1;
	int c;
	FILE *fp;
	
	fp = fopen(file_name, "r");
	if (!fp) return(-1);
	
	while ((c = fgetc(fp)) != EOF) {
		if (c == '\n') n++;
	}
	
	if (ferror(fp)) return(-1);
	
	fclose(fp);
	
	TStringList *struct_tstringlist = self;
	struct_tstringlist->COUNT_LINES_FILE = n;
	
	
	return(n);
}
	
	
	
	
	
s64 CountBytesFile(void *self, char *file_name)
{
	long n = 1;
	int c;
	FILE *fp;
	
	fp = fopen(file_name, "r");
	if (!fp) return(-1);
	
	
	while ((c = fgetc(fp)) != EOF) {
		n++;
	}
	
	if (ferror(fp)) { fclose(fp); return(-1); }
	
	fclose(fp);
	
	TStringList *struct_tstringlist = self;
	struct_tstringlist->COUNT_BYTES_FILE = n;
	
	return(n);
}
	
	
	
	
	
s64 SetLines(void *self, s64 numbers)
{
	TStringList *struct_tstringlist = self;
	
	if (numbers < 1) return(-1);
	if (numbers == struct_tstringlist->TStringList_Lines) return(0); //do nothing
	
	
	//New
	if (struct_tstringlist->TStringList_Lines == -1) {
		struct_tstringlist->TStringList = calloc(numbers, sizeof(char *));
		if (struct_tstringlist->TStringList == NULL) return(-1);
		struct_tstringlist->TStringList_Lines = numbers;
		
		//malloc
		//for (s64 n = 0; n < numbers; n++) struct_tstringlist->TStringList[n] = NULL;
		
		return(0);
	}
	
	//resize <
	if (numbers < struct_tstringlist->TStringList_Lines) {
		s64 diff = struct_tstringlist->TStringList_Lines - numbers;
		
		for (s64 n = diff - 1; n < struct_tstringlist->TStringList_Lines; n++) free(struct_tstringlist->TStringList[n]);
		
		struct_tstringlist->TStringList = realloc(struct_tstringlist->TStringList, numbers * sizeof(char *));
		struct_tstringlist->TStringList_Lines = numbers;
		
		return(0);
	}
	
	//resize >
	if (numbers > struct_tstringlist->TStringList_Lines) {
		s64 diff = numbers - struct_tstringlist->TStringList_Lines;
		
		char **tmp_ptr = struct_tstringlist->TStringList;
		tmp_ptr = realloc(tmp_ptr, numbers * sizeof(char *));
		if (tmp_ptr == NULL) return(-1);
		
		struct_tstringlist->TStringList = tmp_ptr;
		struct_tstringlist->TStringList_Lines = numbers;
		
		//VEREINFACHT VIELES
		for (s64 n = diff - 1; n < struct_tstringlist->TStringList_Lines; n++) {
			struct_tstringlist->TStringList[n] = NULL;
		}
		
		
		return(0);
	}
	
	return(0);
}
	
	
	
	
	
s64 DynStrcpy (void *self, s64 number, char *newstring)
{
	TStringList *struct_tstringlist = self;
	
	if (number < 0 ) return(-1);
	if (struct_tstringlist->TStringList_Lines == -1) return(-1);
	if (struct_tstringlist->TStringList == NULL) return(-1);
	if (number >= struct_tstringlist->TStringList_Lines) return(-1);
	
	
	if (struct_tstringlist->TStringList[number] != NULL) free(struct_tstringlist->TStringList[number]);
	
	
	s64 len = strlen(newstring) + 1;
	struct_tstringlist->TStringList[number] = malloc(len * sizeof(char *));
	strcpy(struct_tstringlist->TStringList[number], newstring);
	
	return(0);
	
}
	
	
	
	
	
s64 DynStrcat (void *self, s64 number, char *newstring)
{
	TStringList *struct_tstringlist = self;
	
	if (number < 0 ) return(-1);
	if (number >= struct_tstringlist->TStringList_Lines) return(-1);
	if (struct_tstringlist->TStringList == NULL) return(-1);
	
	s64 len = strlen(struct_tstringlist->TStringList[number]) +  strlen(newstring) + 1;
	
	struct_tstringlist->TStringList[number] = realloc(struct_tstringlist->TStringList[number], len * sizeof(char *));
	strcat(struct_tstringlist->TStringList[number], newstring);
	
	return(0);
	
}
	
	
	
	
	
s64 Del(void *self, s64 number)
{
	TStringList *struct_tstringlist = self;
	s64 lines_max = struct_tstringlist->TStringList_Lines;
	
	if (number < 0) return(-1);
	if (number >= struct_tstringlist->TStringList_Lines) return(-1);
	
	
	//if number = last line
	if (number == struct_tstringlist->TStringList_Lines - 1) {
		//delete
		free(struct_tstringlist->TStringList[number]);
		struct_tstringlist->TStringList = realloc(struct_tstringlist->TStringList, (struct_tstringlist->TStringList_Lines - 1) * sizeof(char *));
		struct_tstringlist->TStringList_Lines--;
		return(0);
	}
	
	//delete
	free(struct_tstringlist->TStringList[number]);
	
	//address last line -> delete line
	struct_tstringlist->TStringList[number] = struct_tstringlist->TStringList[struct_tstringlist->TStringList_Lines - 1];
	
	struct_tstringlist->TStringList = realloc(struct_tstringlist->TStringList, (struct_tstringlist->TStringList_Lines - 1) * sizeof(char *));
	struct_tstringlist->TStringList_Lines--;
	
	return(0);
}
	
	
	
	
	
s64 CountLines(void *self)
{
	TStringList *struct_tstringlist = self;
	return(struct_tstringlist->TStringList_Lines);
}
	
	
	
	
	
	
s64 DelDup(void *self)
{
	TStringList *struct_tstringlist = self;
	
	qsort(struct_tstringlist->TStringList, struct_tstringlist->TStringList_Lines, sizeof(char *), str_compare);
	
	s64 counter = 0;
	for (s64 n = struct_tstringlist->TStringList_Lines - 1; n > 0; n--) {
		if (strcmp(struct_tstringlist->TStringList[n - 1], struct_tstringlist->TStringList[n]) == 0) {
			free(struct_tstringlist->TStringList[n]);
			struct_tstringlist->TStringList[n] = struct_tstringlist->TStringList[struct_tstringlist->TStringList_Lines - 1 - counter];
			counter++;
		}
	}
	
	
	struct_tstringlist->TStringList_Lines -= counter;
	struct_tstringlist->TStringList = realloc(struct_tstringlist->TStringList, struct_tstringlist->TStringList_Lines * sizeof(char *));
	
	return(0);
}
	
	
	
	
	
s64 StringLengthMax(void *self)
{
	TStringList *struct_tstringlist = self;
	return(struct_tstringlist->TStringList_Length_Max);
}
	
	
	
	
	
//OS doesn't matter
s64 LoadFromFile(void *self, char *file_name)
{
	long max_bytes = 0;
	int c;
	FILE *fp;
	long max_lines = 0;
	char *TEXT;
	long str_length = 0;
	
	
	
	fp = fopen(file_name, "r");
	if (!fp) return(-1);
	
	while ((c = fgetc(fp)) != EOF) {
		max_bytes++;
	}
	
	if (ferror(fp)) { fclose(fp); return(-1); }
	
	fseek(fp, 0, SEEK_SET);
	
	while ((c = fgetc(fp)) != EOF) {
		if (c == '\n') max_lines++;
	}
	
	fseek(fp, 0, SEEK_SET);
	
	
	TEXT = calloc(max_bytes, sizeof(char));
	if (TEXT == NULL) { fclose(fp); return(-1); }
	
	fread(TEXT, max_bytes, sizeof(char), fp);
	
	if (ferror(fp)) { fclose(fp); return(-1); }
	
	fclose(fp);
	
	//Zeilen reservieren
	TStringList *struct_tstringlist = self;
	
	struct_tstringlist->COUNT_LINES_FILE = max_lines;
	struct_tstringlist->COUNT_BYTES_FILE = max_bytes;
	
	struct_tstringlist->TStringList = calloc(max_lines, sizeof(char *));
	if (struct_tstringlist->TStringList == NULL) return(-1);
	
	long lines = 0;
	long start = 0;
	long len = 0;
	
	
	for (int n = 0; n < max_bytes; n++) {
		if (TEXT[n] == '\n') {
			if (n > start) {
				struct_tstringlist->TStringList[lines] = malloc((n - start + 1) * sizeof(char));
				strncpy(struct_tstringlist->TStringList[lines], &TEXT[start], n - start);
				
				struct_tstringlist->TStringList[lines][n - start] = '\0';
				len = n - start;
				if (len > struct_tstringlist->TStringList_Length_Max) struct_tstringlist->TStringList_Length_Max = len;
				
				start = n + 1; 
				lines++;
			}
			else start++;
		}
	}
	
	
	
	struct_tstringlist->TStringList_Lines = lines;
	
	if (struct_tstringlist->DelDUP == true) {
		qsort(struct_tstringlist->TStringList, struct_tstringlist->TStringList_Lines, sizeof(char *), str_compare);
		
		s64 counter = 0;
		for (s64 n = struct_tstringlist->TStringList_Lines - 1; n > 0; n--) {
			if (strcmp(struct_tstringlist->TStringList[n - 1], struct_tstringlist->TStringList[n]) == 0) {
				free(struct_tstringlist->TStringList[n]);
				struct_tstringlist->TStringList[n] = struct_tstringlist->TStringList[struct_tstringlist->TStringList_Lines - 1 - counter];
				counter++;
			}
		}
		
		struct_tstringlist->TStringList_Lines -= counter;
		struct_tstringlist->TStringList = realloc(struct_tstringlist->TStringList, struct_tstringlist->TStringList_Lines * sizeof(char *));
	}
	
	if (struct_tstringlist->SORT == true) {
		qsort(struct_tstringlist->TStringList, struct_tstringlist->TStringList_Lines, sizeof(char *), str_compare);
	}
	
	
	return(0);
}
	
	
	
	
	
	
//--------------------------------------------------------------------------------------------------------------------
s64 TStringListCreate(void *self) {
	
	
	TStringList *struct_tstringlist = self;
	
	
	struct_tstringlist->CountBytesFile = &CountBytesFile;
	struct_tstringlist->CountLinesFile = &CountLinesFile;
	struct_tstringlist->SetLines = &SetLines;
	struct_tstringlist->DynStrcpy = &DynStrcpy;
	struct_tstringlist->DynStrcat = &DynStrcat;
	struct_tstringlist->Del = &Del;
	struct_tstringlist->CountLines = &CountLines;
	struct_tstringlist->StringLengthMax = &StringLengthMax;
	struct_tstringlist->LoadFromFile = &LoadFromFile;
	struct_tstringlist->DelDup = &DelDup;
	struct_tstringlist->DynFree = &DynFree;
	struct_tstringlist->MaxStr = &MaxStr;
	struct_tstringlist->Add = &Add;
	struct_tstringlist->Sort = &Sort;
	struct_tstringlist->SetSort = &SetSort;
	struct_tstringlist->SetDelDUP = &SetDelDUP;
	
	
	struct_tstringlist->COUNT_BYTES_FILE = -1;
	struct_tstringlist->COUNT_LINES_FILE = -1;
	struct_tstringlist->TStringList_Length_Max = -1;
	struct_tstringlist->TStringList_Lines = -1;
	struct_tstringlist->DelDUP = false;
	struct_tstringlist->SORT = false;
	//(*struct_tstringlist).DelDUP = false;		//geht auch so
	
	return(0);
}	
	
#endif
	
	
