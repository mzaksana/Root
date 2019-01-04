#include <stdlib.h>
/*
* 
*
* Author: Muammar Zikri Aksana
*/
typedef struct listnodeZ *ListNodePtrZ;
typedef struct docno *docnoPtrZ;
typedef struct indexList *listIndexPtrZ;

typedef struct indexListHead
{
	listIndexPtrZ list;
	unsigned size;
} listIndexHead;

typedef struct indexList
{
	long int index;
	listIndexPtrZ next;
} listIndex;

typedef struct listheadZ
{
	ListNodePtrZ head;
	unsigned size;
} ListHeadZ;

typedef struct listnodeZ
{
	char *word;
	docnoPtrZ listDocs;
	ListNodePtrZ next;
	unsigned size;

} ListNodeZ;

typedef struct docno
{
	long int docno;
	long int freq;
	docnoPtrZ next;
} docNo;

void insertIndex(listIndexHead *, int);
void readIndex(listIndexHead *);

int insertListDocs(ListNodeZ *, long int);
void readListDocsZ(ListNodeZ *);
int searchListZ(ListHeadZ *, char *, long int);
int insertListZ(ListHeadZ *, char *, long int, listIndexHead *, int);
void readListZ(ListHeadZ *);

void freeListZ(ListHeadZ *);

void readListFZ(ListHeadZ *, FILE *, FILE *);
void hashTraversalZ(ListHeadZ *, FILE *, FILE *, FILE *, listIndexHead *, FILE *, FILE *, FILE *);
void hashWriteZ(ListHeadZ *, FILE *, FILE *, FILE *, FILE *, long);
