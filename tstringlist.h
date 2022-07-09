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





#ifndef tstringlist
#define tstringlist


#include <stdlib.h>
#include <stdio.h>
#include <string.h>




typedef signed long long int s64;
typedef unsigned long long int u64;



typedef int bool;
#define true 1
#define false 0









//--------------------------------------------------------------------------------------------------------------------
//deklaration
typedef struct {
	//public
	s64 INIT;

	char	**TStringList;
	s64	FILE_COUNT_BYTES;
	s64	FILE_COUNT_LINES;

	s64	TStringListCount;
	s64	TStringListLengthMax;

	bool	LDelDUP;
	bool	LSORT;

} TStringList;





/*
s64 ListInitState(void *self, s64 size_n, s64 size_struc, s64 size_all)
s64 ListSetDelDUP (void *self, s64 size_n, s64 size_struc, s64 size_all, bool b) {
s64 ListMaxStr (void *self, s64 size_n, s64 size_struc, s64 size_all)
s64 ListCount(void *self, s64 size_n, s64 size_struc, s64 size_all)


s64 ListFree (void *self, s64 size_n, s64 size_struc, s64 size_all)
s64 ListText(void *self, s64 size_n, s64 size_struc, s64 size_all, char **TEXT)
s64 ListIndex(void *self, s64 size_n, s64 size_struc, s64 size_all, char *search_string)
s64 ListSetSort (void *self, s64 size_n, s64 size_struc, s64 size_all, bool b) {
s64 ListAdd(void *self, s64 size_n, s64 size_struc, s64 size_all, char *newstring)
s64 ListSetLength(void *self, s64 size_n, s64 size_struc, s64 size_all,s64 numbers)
s64 ListDel(void *self, s64 size_n, s64 size_struc, s64 size_all, s64 number)
s64 ListDelDup(void *self, s64 size_n, s64 size_struc, s64 size_all)

s64 LoadFromFile(void *self, s64 size_n, s64 size_struc, s64 size_all, char *file_name)
s64 FileCountLines(void *self, s64 size_n, s64 size_struc, s64 size_all,char *file_name)
s64 FileCountBytes(void *self, s64 size_n, s64 size_struc, s64 size_all, char *file_name)


s64 StringCheck (void *self, s64 size_n, s64 size_struc, s64 size_all,s64 number)
s64 StringSet (void *self, s64 size_n, s64 size_struc, s64 size_all,s64 number, char *newstring)
s64 StringAdd (void *self, s64 size_n, s64 size_struc, s64 size_all,s64 number, char *add_string)
s64 StringDel(void *self, s64 size_n, s64 size_struc, s64 size_all,s64 number, s64 pos, s64 size)
s64 StringReplace(void *self, s64 size_n, s64 size_struc, s64 size_all,s64 number, s64 pos, char *replace_string)
s64 StringLengthMax(void *self, s64 size_n, s64 size_struc, s64 size_all)
s64 StringInsert(void *self, s64 size_n, s64 size_struc, s64 size_all,s64 number, s64 pos, char *insert_string)
*/





s64 ListInitState(void *self, s64 size_n, s64 size_struc, s64 size_all)
{
	if (size_n >= (size_all / size_struc)) return(-1);
	TStringList *struct_tstringlist = self;
	if (struct_tstringlist->INIT != 1234567890) return(-1);

	return(0);

}





s64 ListStringMax(void *self, s64 size_n, s64 size_struc, s64 size_all)
{
	if (size_n >= (size_all / size_struc)) return(-1);
	TStringList *struct_tstringlist = self;
	if (struct_tstringlist->INIT != 1234567890) return(-1);

	return(struct_tstringlist->TStringListLengthMax);

}





s64 ListFree (void *self, s64 size_n, s64 size_struc, s64 size_all)
{
	if (size_n >= (size_all / size_struc)) return(-1);
	TStringList *struct_tstringlist = self;
	if (struct_tstringlist->INIT != 1234567890) return(-1);

	for (s64 n = 0; n < struct_tstringlist->TStringListCount; n++) {
		if (struct_tstringlist->TStringList[n] != NULL) free(struct_tstringlist->TStringList[n]);
	}

	free(struct_tstringlist->TStringList);
	struct_tstringlist->TStringList = NULL;


	struct_tstringlist->TStringListCount = -1;
	struct_tstringlist->TStringListLengthMax = -1;
	struct_tstringlist->FILE_COUNT_BYTES = -1;
	struct_tstringlist->FILE_COUNT_LINES = -1;

	return(0);

}





s64 ListText(void *self, s64 size_n, s64 size_struc, s64 size_all, char **TEXT)
{
	if (size_n >= (size_all / size_struc)) return(-1);
	TStringList *struct_tstringlist = self;
	if (struct_tstringlist->INIT != 1234567890) return(-1);

	s64 len	= 0;
	s64 n	= 0;

	if (struct_tstringlist->TStringListCount == 0) return(-1);
	len = strlen(struct_tstringlist->TStringList[0]) + 2;
	*TEXT = calloc(len, sizeof(char));
	strcpy(*TEXT, struct_tstringlist->TStringList[0]);
	strcat(*TEXT, "\n");


	if (struct_tstringlist->TStringListCount < 2) return(-1);
	for (n = 1; n < struct_tstringlist->TStringListCount; n++) {
		len += strlen(struct_tstringlist->TStringList[n]) + 2;

		*TEXT = realloc(*TEXT, len * sizeof(char));

		strcat(*TEXT, struct_tstringlist->TStringList[n]);
		strcat(*TEXT, "\n");

	}

	return(0);
}




s64 ListIndex(void *self, s64 size_n, s64 size_struc, s64 size_all, char *search_string)
{
	if (size_n >= (size_all / size_struc)) return(-1);
	TStringList *struct_tstringlist = self;
	if (struct_tstringlist->INIT != 1234567890) return(-1);

	for (s64 n = 0; n < struct_tstringlist->TStringListCount; n++) {
		if (strstr(struct_tstringlist->TStringList[n], search_string) != NULL) return(n);
	}

	return(-1);
}





s64 StringInsert(void *self, s64 size_n, s64 size_struc, s64 size_all,s64 number, s64 pos, char *insert_string)
{
	if (size_n >= (size_all / size_struc)) return(-1);
	TStringList *struct_tstringlist = self;
	if (struct_tstringlist->INIT != 1234567890) return(-1);

	if (number < 0 ) return(-1);
	if (struct_tstringlist->TStringListCount == -1) return(-1);
	if (number >= struct_tstringlist->TStringListCount) return(-1);
	if (struct_tstringlist->TStringList[number] == NULL) return(-1);

	s64 length = strlen(struct_tstringlist->TStringList[number]);
	if (pos > length) return(-1);

	char *buffer = calloc(length + 1, sizeof(char));
	if (buffer == NULL) return(-1);

	strcpy(buffer, struct_tstringlist->TStringList[number]);

	s64 insert_string_length = strlen(insert_string);

	length += insert_string_length;


	struct_tstringlist->TStringList[number] = realloc(struct_tstringlist->TStringList[number], (length + 1) * sizeof(char));
	if (struct_tstringlist->TStringList[number] == NULL) return(-1);

	strcpy(struct_tstringlist->TStringList[number] + pos, insert_string);
	strcat(struct_tstringlist->TStringList[number] + pos + insert_string_length, buffer + pos);

	free(buffer);

	return(0);
}





s64 StringDel(void *self, s64 size_n, s64 size_struc, s64 size_all,s64 number, s64 pos, s64 size)
{
	if (size_n >= (size_all / size_struc)) return(-1);
	TStringList *struct_tstringlist = self;
	if (struct_tstringlist->INIT != 1234567890) return(-1);

	if (number < 0 ) return(-1);
	if (struct_tstringlist->TStringListCount == -1) return(-1);
	if (number >= struct_tstringlist->TStringListCount) return(-1);
	if (struct_tstringlist->TStringList[number] == NULL) return(-1);


	if (pos > strlen(struct_tstringlist->TStringList[number]))  return(-1);

	if ((size + pos) >= strlen(struct_tstringlist->TStringList[number])) size = strlen(struct_tstringlist->TStringList[number]) - pos;

	strcpy(struct_tstringlist->TStringList[number] + pos, struct_tstringlist->TStringList[number] + pos + size);
	struct_tstringlist->TStringList[number] = realloc(struct_tstringlist->TStringList[number], (size + 1) * sizeof(char));

	return(0);
}





s64 StringReplace(void *self, s64 size_n, s64 size_struc, s64 size_all,s64 number, s64 pos, char *replace_string)
{
	if (size_n >= (size_all / size_struc)) return(-1);
	TStringList *struct_tstringlist = self;
	if (struct_tstringlist->INIT != 1234567890) return(-1);

	if (number < 0 ) return(-1);
	if (struct_tstringlist->TStringListCount == -1) return(-1);
	if (number >= struct_tstringlist->TStringListCount) return(-1);
	if (struct_tstringlist->TStringList[number] == NULL) return(-1);


	s64 len = strlen(struct_tstringlist->TStringList[number]);
	if (len < 1) return(-1);

	if ((len - 1) < pos) return(-1);
	if (len < (pos + strlen(replace_string))) return(-1);

	strncpy(struct_tstringlist->TStringList[number] + pos, replace_string, strlen(replace_string));

	return(0);
}





int str_compare(const void *a, const void *b)
{
	const char **pa = (const char **)a;
	const char **pb = (const char **)b;
	return strcmp(*pa, *pb);
}





s64 ListSort (void *self, s64 size_n, s64 size_struc, s64 size_all) {
	if (size_n >= (size_all / size_struc)) return(-1);
	TStringList *struct_tstringlist = self;
	if (struct_tstringlist->INIT != 1234567890) return(-1);

	qsort(struct_tstringlist->TStringList, struct_tstringlist->TStringListCount, sizeof(char *), str_compare);

	return(0);

}





s64 ListSetSort (void *self, s64 size_n, s64 size_struc, s64 size_all, bool b) {
	if (size_n >= (size_all / size_struc)) return(-1);
	TStringList *struct_tstringlist = self;
	if (struct_tstringlist->INIT != 1234567890) return(-1);

	if (b == true) struct_tstringlist->LSORT = true;
	else struct_tstringlist->LSORT = false;

	return(0);

}




s64 ListSetDelDUP (void *self, s64 size_n, s64 size_struc, s64 size_all, bool b) {
	if (size_n >= (size_all / size_struc)) return(-1);
	TStringList *struct_tstringlist = self;
	if (struct_tstringlist->INIT != 1234567890) return(-1);

	if (b == true) struct_tstringlist->LDelDUP = true;
	else struct_tstringlist->LDelDUP = false;

	return(0);

}





s64 ListAdd(void *self, s64 size_n, s64 size_struc, s64 size_all, char *newstring)
{
	if (size_n >= (size_all / size_struc)) return(-1);
	TStringList *struct_tstringlist = self;
	if (struct_tstringlist->INIT != 1234567890) return(-1);

	//New
	if (struct_tstringlist->TStringListCount == -1) {
		struct_tstringlist->TStringList = malloc(1 * sizeof(char *));
		if (struct_tstringlist->TStringList == NULL) return(-1);

		struct_tstringlist->TStringList[0] = malloc((strlen(newstring) + 1) * sizeof(char));

		if (struct_tstringlist->TStringList[struct_tstringlist->TStringListCount] == NULL) {
			//former state
			free(struct_tstringlist->TStringList);
			return(-1);
		}


		strcpy(struct_tstringlist->TStringList[0], newstring);
		struct_tstringlist->TStringListCount = 1;

		return(0);
	}

	//backup pointer
	char **backup_ptr = struct_tstringlist->TStringList;
	s64 lines = struct_tstringlist->TStringListCount + 1;

	//New LINE
	backup_ptr = realloc(backup_ptr, lines * sizeof(char *));
	if (backup_ptr == NULL) return(-1);
	else struct_tstringlist->TStringList = backup_ptr;

	//MEM Columns
	struct_tstringlist->TStringList[struct_tstringlist->TStringListCount] = malloc((strlen(newstring) + 1) * sizeof(char));
	if (struct_tstringlist->TStringList[struct_tstringlist->TStringListCount] == NULL) {
		//former state
		struct_tstringlist->TStringList = realloc(struct_tstringlist->TStringList, (lines - 1) * sizeof(char *));
		return(-1);
	}

	strcpy(struct_tstringlist->TStringList[struct_tstringlist->TStringListCount], newstring);
	struct_tstringlist->TStringListCount++;

	return(0);
}





s64 ListMaxStr (void *self, s64 size_n, s64 size_struc, s64 size_all)
{
	if (size_n >= (size_all / size_struc)) return(-1);
	TStringList *struct_tstringlist = self;
	if (struct_tstringlist->INIT != 1234567890) return(-1);

	s64 MAX;
	for (s64 n = 0; n < struct_tstringlist->TStringListCount; n++) {
		if (struct_tstringlist->TStringList[n] != NULL) {
			MAX = strlen(struct_tstringlist->TStringList[n]);
			if (MAX > struct_tstringlist->TStringListLengthMax) struct_tstringlist->TStringListLengthMax = MAX;
		}
	}

	return(0);
}







s64 FileCountLines(void *self, s64 size_n, s64 size_struc, s64 size_all,char *file_name)
{
	if (size_n >= (size_all / size_struc)) return(-1);
	TStringList *struct_tstringlist = self;
	if (struct_tstringlist->INIT != 1234567890) return(-1);

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

	struct_tstringlist->FILE_COUNT_LINES = n;


	return(n);
}





s64 FileCountBytes(void *self, s64 size_n, s64 size_struc, s64 size_all, char *file_name)
{
	if (size_n >= (size_all / size_struc)) return(-1);
	TStringList *struct_tstringlist = self;
	if (struct_tstringlist->INIT != 1234567890) return(-1);

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

	return(n);
}





s64 ListSetLength(void *self, s64 size_n, s64 size_struc, s64 size_all,s64 numbers)
{
	if (size_n >= (size_all / size_struc)) return(-1);
	TStringList *struct_tstringlist = self;
	if (struct_tstringlist->INIT != 1234567890) return(-1);

	if (numbers < 1) return(-1);
	if (numbers == struct_tstringlist->TStringListCount) return(-1); //do nothing


	//New
	if (struct_tstringlist->TStringListCount == -1) {
		struct_tstringlist->TStringList = calloc(numbers, sizeof(char *));
		if (struct_tstringlist->TStringList == NULL) return(-1);
		struct_tstringlist->TStringListCount = numbers;

		//malloc
		//for (s64 n = 0; n < numbers; n++) struct_tstringlist->TStringList[n] = NULL;

		return(0);
	}

	//resize <
	if (numbers < struct_tstringlist->TStringListCount) {
		s64 diff = struct_tstringlist->TStringListCount - numbers;

		for (s64 n = diff - 1; n < struct_tstringlist->TStringListCount; n++) free(struct_tstringlist->TStringList[n]);

		struct_tstringlist->TStringList = realloc(struct_tstringlist->TStringList, numbers * sizeof(char *));
		struct_tstringlist->TStringListCount = numbers;

		return(0);
	}

	//resize >
	if (numbers > struct_tstringlist->TStringListCount) {
		s64 diff = numbers - struct_tstringlist->TStringListCount;

		char **tmp_ptr = struct_tstringlist->TStringList;
		tmp_ptr = realloc(tmp_ptr, numbers * sizeof(char *));
		if (tmp_ptr == NULL) return(-1);

		struct_tstringlist->TStringList = tmp_ptr;
		struct_tstringlist->TStringListCount = numbers;

		for (s64 n = diff - 1; n < struct_tstringlist->TStringListCount; n++) {
			struct_tstringlist->TStringList[n] = NULL;
		}

		return(0);
	}

	return(0);
}





s64 StringCheck (void *self, s64 size_n, s64 size_struc, s64 size_all,s64 number)
{
	if (size_n >= (size_all / size_struc)) return(-1);
	TStringList *struct_tstringlist = self;
	if (struct_tstringlist->INIT != 1234567890) return(-1);

	if (number < 0 ) return(-1);
	if (struct_tstringlist->TStringListCount == -1) return(-1);
	if (number >= struct_tstringlist->TStringListCount) return(-1);
	if (struct_tstringlist->TStringList[number] == NULL) return(-1);

	return(0);

}





s64 StringSet (void *self, s64 size_n, s64 size_struc, s64 size_all,s64 number, char *newstring)
{
	if (size_n >= (size_all / size_struc)) return(-1);
	TStringList *struct_tstringlist = self;
	if (struct_tstringlist->INIT != 1234567890) return(-1);

	if (number < 0 ) return(-1);
	if (struct_tstringlist->TStringListCount == -1) return(-1);
	if (struct_tstringlist->TStringList == NULL) return(-1);
	if (number >= struct_tstringlist->TStringListCount) return(-1);


	if (struct_tstringlist->TStringList[number] != NULL) free(struct_tstringlist->TStringList[number]);


	s64 len = strlen(newstring) + 1;
	struct_tstringlist->TStringList[number] = malloc(len * sizeof(char *));
	strcpy(struct_tstringlist->TStringList[number], newstring);

	return(0);

}






s64 StringAdd (void *self, s64 size_n, s64 size_struc, s64 size_all,s64 number, char *add_string)
{
	if (size_n >= (size_all / size_struc)) return(-1);
	TStringList *struct_tstringlist = self;
	if (struct_tstringlist->INIT != 1234567890) return(-1);

	if (number < 0 ) return(-1);
	if (struct_tstringlist->TStringListCount == -1) return(-1);
	if (struct_tstringlist->TStringList == NULL) return(-1);
	if (number >= struct_tstringlist->TStringListCount) return(-1);


	//New
	if (struct_tstringlist->TStringList[number] == NULL) {
		s64 length = strlen(add_string);
		struct_tstringlist->TStringList[number] = calloc(length + 1,  sizeof(char));
		if (struct_tstringlist->TStringList[number] == NULL) return(-1);

		strcpy(struct_tstringlist->TStringList[number], add_string);

		return(0);
	}


	s64 add_string_length = strlen(add_string);
	char *buffer;
	buffer = calloc(add_string_length + 1, sizeof(char));
	strcpy(buffer, add_string);

	s64 len = strlen(struct_tstringlist->TStringList[number]) +  add_string_length + 1;


	struct_tstringlist->TStringList[number] = realloc(struct_tstringlist->TStringList[number], len * sizeof(char));
	strcat(struct_tstringlist->TStringList[number], buffer);

	return(0);

}





s64 ListDel(void *self, s64 size_n, s64 size_struc, s64 size_all, s64 number)
{
	if (size_n >= (size_all / size_struc)) return(-1);
	TStringList *struct_tstringlist = self;
	if (struct_tstringlist->INIT != 1234567890) return(-1);

	//s64 lines_max = struct_tstringlist->TStringListCount;

	if (number < 0) return(-1);
	if (number >= struct_tstringlist->TStringListCount) return(-1);


	//if number = last line
	if (number == struct_tstringlist->TStringListCount - 1) {
		//delete
		free(struct_tstringlist->TStringList[number]);
		struct_tstringlist->TStringList = realloc(struct_tstringlist->TStringList, (struct_tstringlist->TStringListCount - 1) * sizeof(char *));
		struct_tstringlist->TStringListCount--;
		return(0);
	}

	//delete
	free(struct_tstringlist->TStringList[number]);

	//address last line -> delete line
	struct_tstringlist->TStringList[number] = struct_tstringlist->TStringList[struct_tstringlist->TStringListCount - 1];

	struct_tstringlist->TStringList = realloc(struct_tstringlist->TStringList, (struct_tstringlist->TStringListCount - 1) * sizeof(char *));
	struct_tstringlist->TStringListCount--;

	return(0);
}





s64 ListCount(void *self, s64 size_n, s64 size_struc, s64 size_all)
{
	if (size_n >= (size_all / size_struc)) return(-1);
	TStringList *struct_tstringlist = self;
	if (struct_tstringlist->INIT != 1234567890) return(-1);

	return(struct_tstringlist->TStringListCount);
}






s64 ListDelDup(void *self, s64 size_n, s64 size_struc, s64 size_all)
{
	if (size_n >= (size_all / size_struc)) return(-1);
	TStringList *struct_tstringlist = self;
	if (struct_tstringlist->INIT != 1234567890) return(-1);

	qsort(struct_tstringlist->TStringList, struct_tstringlist->TStringListCount, sizeof(char *), str_compare);

	s64 counter = 0;
	for (s64 n = struct_tstringlist->TStringListCount - 1; n > 0; n--) {
		if (strcmp(struct_tstringlist->TStringList[n - 1], struct_tstringlist->TStringList[n]) == 0) {
			free(struct_tstringlist->TStringList[n]);
			struct_tstringlist->TStringList[n] = struct_tstringlist->TStringList[struct_tstringlist->TStringListCount - 1 - counter];
			counter++;
		}
	}


	struct_tstringlist->TStringListCount -= counter;
	struct_tstringlist->TStringList = realloc(struct_tstringlist->TStringList, struct_tstringlist->TStringListCount * sizeof(char *));

	return(0);
}





s64 StringLengthMax(void *self, s64 size_n, s64 size_struc, s64 size_all)
{
	if (size_n >= (size_all / size_struc)) return(-1);
	TStringList *struct_tstringlist = self;
	if (struct_tstringlist->INIT != 1234567890) return(-1);

	return(struct_tstringlist->TStringListLengthMax);
}





s64 LoadFromFile(void *self, s64 size_n, s64 size_struc, s64 size_all, char *file_name)
{
	if (size_n >= (size_all / size_struc)) return(-1);
	TStringList *struct_tstringlist = self;


	s64 max_bytes = 0;
	int c;
	FILE *fp;
	s64 max_lines = 0;
	char *TEXT;
	//long str_length = 0;



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
	struct_tstringlist->FILE_COUNT_LINES = max_lines;
	struct_tstringlist->FILE_COUNT_BYTES = max_bytes;

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
				if (len > struct_tstringlist->TStringListLengthMax) struct_tstringlist->TStringListLengthMax = len;

				start = n + 1; 
				lines++;
			}
			else start++;
		}
	}



	struct_tstringlist->TStringListCount = lines;

	if (struct_tstringlist->LDelDUP == true) {
		qsort(struct_tstringlist->TStringList, struct_tstringlist->TStringListCount, sizeof(char *), str_compare);

		s64 counter = 0;
		for (s64 n = struct_tstringlist->TStringListCount - 1; n > 0; n--) {
			if (strcmp(struct_tstringlist->TStringList[n - 1], struct_tstringlist->TStringList[n]) == 0) {
				free(struct_tstringlist->TStringList[n]);
				struct_tstringlist->TStringList[n] = struct_tstringlist->TStringList[struct_tstringlist->TStringListCount - 1 - counter];
				counter++;
			}
		}

		struct_tstringlist->TStringListCount -= counter;
		struct_tstringlist->TStringList = realloc(struct_tstringlist->TStringList, struct_tstringlist->TStringListCount * sizeof(char *));
	}

	if (struct_tstringlist->LSORT == true) {
		qsort(struct_tstringlist->TStringList, struct_tstringlist->TStringListCount, sizeof(char *), str_compare);
	}


	return(0);
}





//--------------------------------------------------------------------------------------------------------------------
s64 TStringListCreate(void *self, s64 n_size, s64 size_struc, s64 size_all)
{
	if (n_size > (size_all / size_struc)) return(-1);
	TStringList *struct_tstringlist = self;
	if (struct_tstringlist->INIT == 1234567890) return(0);

	struct_tstringlist->INIT = 1234567890;
	struct_tstringlist->FILE_COUNT_BYTES = -1;
	struct_tstringlist->FILE_COUNT_LINES = -1;
	struct_tstringlist->TStringListLengthMax = -1;
	struct_tstringlist->TStringListCount = -1;
	struct_tstringlist->LDelDUP = false;
	struct_tstringlist->LSORT = false;
	//(*struct_tstringlist).DelDUP = false;		//geht auch so
	return(0);
}

#endif


