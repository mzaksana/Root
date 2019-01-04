#include <stdio.h>
#include "define.h"
#include "Ztype.c"

/*
* 
*
* Author: Muammar Zikri Aksana
*/

void insertIndex(listIndexHead *headList, int index)
{
	listIndexPtrZ new = (listIndexPtrZ)malloc(sizeof(listIndexPtrZ));
	new->index = index;
	new->next = headList->list;
	headList->list = new;
	headList->size++;
}
void readIndex(listIndexHead *listHead)
{
	listIndexPtrZ current = listHead->list;
	while (current != NULL)
	{
		printf("\tindex : %ld\n", current->index);
		current = current->next;
	}
}
int insertListDocs(ListNodeZ *ls, long int docno)
{
	int totalvalue = 0;
	docnoPtrZ current = ls->listDocs;

	while (current->docno != -1) // trick for pointer dump -- solution add new struct for head to lisf of documents
	{
		if (current->docno == docno)
		{
			current->freq++;
			return totalvalue;
		}
		current = current->next;

		totalvalue += 2;
	}
	ls->size++;
	docnoPtrZ new = (docnoPtrZ)malloc(sizeof(docnoPtrZ));
	new->docno = docno;
	new->freq++;
	new->next = ls->listDocs;
	ls->listDocs = new;

	return totalvalue;
}

void readListDocsZ(ListNodeZ *ls)
{
	docnoPtrZ current = ls->listDocs;
	while (current != NULL)
	{
		printf("\tdocno : %ld \t freq : %ld", current->docno, current->freq);
		current = current->next;
	}
}
int searchListZ(ListHeadZ *ls, char *word, long int docno)
{
	ListNodePtrZ current = ls->head;
	while (current != NULL)
	{
		if (strcmp(current->word, word) == 0)
		{
			insertListDocs(ls->head, docno);
			//current->size++;
			return 1;
		}
		current = current->next;
	}
	return 0;
}
int insertListZ(ListHeadZ *ls, char *word, long int docno, listIndexHead *headList, int index)
{

	if (ls->head == NULL)
	{
		insertIndex(headList, index); // untuk catat index mana saja yang digunakan dari total index hash
	}

	if (ls->head != NULL)
	{
		if (strcmp(ls->head->word, word) != 0)
		{
			collision++;
		}

		if (searchListZ(ls, word, docno) == 1)
		{
			return 1;
		}

		// insertListDocs(ls->head, docno);
		// return 1;
	}

	ListNodePtrZ new;
	/* if it is the same document, then just update the frequency, without having to
     create new linked list node */
	// printf("insert\n");

	new = (ListNodePtrZ)malloc(sizeof(ListNodeZ));
	if (new == NULL)
	{
		printf("Memory allocation for linked list node fails...\n");
		return 0;
	}
	new->word = (char *)malloc(strlen(word) + 1);
	char *pCh = new->word;
	strcpy(pCh, word);

	// insertListDocs(new, docno);
	docnoPtrZ newDocs = (docnoPtrZ)malloc(sizeof(docnoPtrZ));
	newDocs->docno = -1;
	// newDocs->freq++;
	newDocs->next = new->listDocs;
	new->listDocs = newDocs;

	new->size++;
	newDocs = (docnoPtrZ)malloc(sizeof(docnoPtrZ));
	newDocs->docno = docno;
	newDocs->freq++;
	newDocs->next = new->listDocs;
	new->listDocs = newDocs;

	new->next = ls->head;
	ls->head = new;
	ls->size++;

	return 0;
}

void readListZ(ListHeadZ *ls)
{
	ListNodePtrZ current = ls->head;
	while (current != NULL)
	{
		//fwrite(&(current->docno), sizeof(long int), 1, finv);
		//fwrite(&(current->freq), sizeof(long int), 1, finv);
		printf("text :\t %s \t size : %d", current->word, current->size);
		readListDocsZ(current);
		printf("\n");
		current = current->next;
	}
}

void freeListZ(ListHeadZ *ls)
{
	ListNodePtrZ next;
	ListNodePtrZ current = ls->head;

	while (current != NULL)
	{
		next = current->next;
		current = NULL;
		current = next;
	}
}

void readListFZ(ListHeadZ *ls, FILE *finv, FILE *finvH)
{

	docnoPtrZ current = ls->head->listDocs;

	while (current->docno != -1)
	{
		fwrite(&(current->docno), sizeof(long int), 1, finv);
		fwrite(&(current->freq), sizeof(long int), 1, finv);

		fwrite(&(current->docno), sizeof(long int), 1, finvH);
		fwrite(&(current->freq), sizeof(long int), 1, finvH);
		current = current->next;
	}
}

void hashTraversalZ(ListHeadZ *invertedIndex, FILE *finv, FILE *fvoc, FILE *fpar, listIndexHead *headList, FILE *finvH, FILE *fvocH, FILE *fparH)
{

	listIndexPtrZ current = headList->list;
	while (current != NULL)
	{
		hashWriteZ(&invertedIndex[current->index], finv, fvoc, finvH, fvocH, current->index);
		distinctWord++;
		current = current->next;
	}
	fwrite(&distinctWord, sizeof(long int), 1, fpar);
	fwrite(&distinctWord, sizeof(long int), 1, fparH);
}

void hashWriteZ(ListHeadZ *invertedIndex, FILE *finv, FILE *fvoc, FILE *finvH, FILE *fvocH, long index)
{
	long int offset, offsetH;
	offset = ftell(finv);
	offsetH = ftell(finvH);
	readListFZ(invertedIndex, finv, finvH);

	// printf("fvoc : %s %d %ld\n", invertedIndex->head->word, invertedIndex->head->size, offset);
	fprintf(fvoc, "%s %d %ld\n", invertedIndex->head->word, invertedIndex->head->size * 2, offset);
	fprintf(fvocH, "%s %ld %d %ld\n", invertedIndex->head->word, index, invertedIndex->head->size * 2, offsetH);

	// printf("%s\n", invertedIndex->head->word);
}

/* OPEN ADDRESSING */
