#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <unistd.h>

#include "query-tools.h"
#include "define.h"
#include "util.h"

#include "Zhash.c"
char key[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};

void query(FILE *, FILE *, Term *, char *, int, int);
int searchTerm(Term *, int, char *);
int getQueryTerm(char *, char[MAXQUERY][WORDLEN]);
int sort(Term *, int, char[MAXQUERY][WORDLEN]);

long int totalTerm, totalDocs;
StopList stoplist[TOTLIST];
FileInfo *fileinfo;
long int indexDoc;
char *output;

int main(int argc, char *argv[])
{
	Term *terms;
	FILE *fvocH, *finvH, *fparH, *finfH, *fnmeH; //, *fzik;
	char buffer[BUFLEN], qry[BUFLEN];
	int i, len, HEAPSIZE;
	long int index;
	long int docno, doclen, offset;

	long int MIN_INDEX; // untuk hash agar tidak buang2 space
	long int MAX_INDEX; // untuk hash agar tidak buang2 space

	if (argc <= 1)
	{
		printf("input a query or more!!!\n");
		exit(1);
	}

	strcpy(qry, argv[1]);
	HEAPSIZE = argc > 2 ? atoi(argv[2]) : 15;

	if ((finvH = fopen("Program/out/index-db-hash/data.inv", "rb")) == NULL)
	{
		char cwd[250];
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			printf("Current working dir: %s\n", cwd);
		}
		printf("Cannot open inverted file [data.inv]...\n");
		return 0;
	}

	if ((fparH = fopen("Program/out/index-db-hash/data.par", "rb")) == NULL)
	{
		printf("Cannot open parameter file [data.par]...\n");
		return 0;
	}

	if ((fvocH = fopen("Program/out/index-db-hash/data.voc", "r")) == NULL)
	{
		printf("Cannot open vocabulary file [data.voc]...\n");
		return 0;
	}
	if ((finfH = fopen("Program/out/index-db-hash/data.wdl", "r")) == NULL)
	{
		printf("Cannot open information file [data.wdl]...\n");
		return 0;
	}

	if ((fnmeH = fopen("Program/out/index-db-hash/data.nme", "r")) == NULL)
	{
		printf("Cannot open file [data.nme]...\n");
		return 0;
	}
	// if ((fzik = fopen("Program/out/index-db/fzik.txt", "w")) == NULL)
	// {
	// 	printf("Cannot open file [fzik.txt]...\n");
	// 	return 0;
	// }

	loadStopList(stoplist); //saran jangan load : tapi linier saja

	/* load parameter file */
	fread(&totalDocs, sizeof(int), 1, fparH);
	fread(&totalTerm, sizeof(int), 1, fparH);
	fread(&MIN_INDEX, sizeof(int), 1, fparH);
	fread(&MAX_INDEX, sizeof(int), 1, fparH);

	// printf("doc : %ld \n", totalDocs);
	// printf("totalTerm  : %ld\n", totalTerm);
	// printf("MIN_INDEX  : %ld\n", MIN_INDEX);
	// printf("MAX_INDEX  : %ld\n", MAX_INDEX);

	fclose(fparH);
	printf("#Found distict_terms=%ld in documents=%ld\n", totalTerm, totalDocs);
	// return 1;

	/* allocate array files of type struct FileInfo and load file information
		 in data.inf in the format of [docno] [offset to data.nme] into an array,
		 so that binary search can be applied. The data in the array are sorted
		 in ascending order */

	fileinfo = (FileInfo *)malloc(sizeof(FileInfo) * (totalDocs + 1));
	for (i = 0; fscanf(finfH, "%ld %ld %ld", &docno, &doclen, &offset) == 3; i++)
	{
		fileinfo[i].docno = docno;
		// printf("docno : %ld \n", fileinfo[i].docno);

		fileinfo[i].doclen = doclen;
		// indexDoc = doclen; //// TODO FINISH OR NOT

		// printf("doclen : %ld \n", indexDoc);

		fileinfo[i].offset = offset;
		// printf("offset : %ld \n", fileinfo[i].offset);
	}
	fclose(finfH);

	/* 	allocate array terms of type struct Term and load terms in vocabulary
		file into an array, so that binary search can be applied. The data
		in the array are sorted in ascending order 
	*/

	terms = (Term *)malloc(sizeof(Term) * (totalTerm + 1));
	for (int a = 0; a < totalTerm; a++)
	{
		terms[a].len = -1;
	}
	// FILE *tmp = fopen("tmp.txt", "w");
	for (; fscanf(fvocH, "%s %ld %d %ld", buffer, &index, &len, &offset) == 4;)
	{
		char saveWord[strlen(buffer) + 1];
		strcpy(saveWord, buffer);
		uint64_t hash = siphash24(saveWord, strlen(saveWord), key);
		unsigned idx = hash;

		idx = idx < 0 ? idx * -1 : idx;
		idx %= totalTerm;
		// printf("idx : %d\n",idx);
		// fprintf(fzik, "%s\n", buffer);

		if (terms[idx].len == -1)
		{
			terms[idx].term = malloc(strlen(buffer) + 1);
			strcpy(terms[idx].term, buffer);
			terms[idx].len = len;
			terms[idx].offset = offset;
			// terms[idx].len = 1;
		}
		else
		{
			while (1)
			{
				idx++;
				idx = idx > totalTerm ? 0 : idx;
				// printf("%d\n", idx);
				if (terms[idx].len == -1)
				{
					terms[idx].term = malloc(strlen(buffer) + 1);
					strcpy(terms[idx].term, buffer);
					terms[idx].len = len;
					terms[idx].offset = offset;
					// terms[idx].len = 1;
					break;
				}
			}
		}

		// terms[i].term = malloc(strlen(buffer) + 1);

		// strcpy(terms[i].term, buffer);
		// printf("term : %s\n", terms[i].term);
		// printf("term : %s\t", buffer);

		// terms[i].len = len;
		// printf("len : %d\n", terms[i].len);
		// printf("len : %d\n", len);

		// terms[i].offset = offset;
		// printf("offset : %d\n", terms[i].offset);

		// terms[i].index = index;
		// fprintf(tmp, "%ld\n", terms[i].index);
	}
	// fclose(tmp);
	fclose(fvocH);
	// fclose(fzik);

	startTiming();
	// int tmp = 0;
	// for (int i = 0; i < totalTerm; i++)
	// {
	// 	if (terms[i].len == -1)
	// 	{
	// 		tmp++;
	// 	}
	// }
	// printf("tmp : %d\n", tmp);
	/* TODO */

	int lenDocName = 1;
	for (int tmp = totalDocs; tmp > 0; tmp /= 10)
	{
		lenDocName++;
	}
	output = (char *)malloc(sizeof(char *) * (7 + lenDocName * 2) * HEAPSIZE);

	// searchTerm(terms, totalTerm, qry);
	query(finvH, fnmeH, terms, qry, totalDocs, HEAPSIZE);
	stopTiming();

	printf("#Time time_required=%f mseconds\n", timingDuration());
	free(terms);
	free(fileinfo);
	fclose(finvH);
	fclose(fnmeH);

	// printf("%s", output);
	return 0;
}

void query(FILE *finv, FILE *fnme, Term *arrterm, char *query, int N, int HEAPSIZE)
{
	long int *ilbuf;
	long int freqwd, docno, offset, tempd;
	int i, t, pos, len, totalqterm;
	float fw;
	double *accumulator;
	double s_q_d, tempr;
	Heap *heap;
	char buffer[BUFLEN];
	char queryterm[MAXQUERY][WORDLEN];

	if (*query != '\0')
	{

		totalqterm = getQueryTerm(query, queryterm); /*get only query terms that are not stopword */
		// totalqterm = 1; /*get only query terms that are not stopword */
		if (totalqterm == 0)
		{
			printf("#All query terms are stopword\n");
		}
		else
		{
			heap = (Heap *)malloc(sizeof(Heap) * HEAPSIZE);

			/* sort query terms in ascending order based on fw of the term,
				 rare term is more interesting and should be examined first */
			//sort(arrterm, totalqterm, queryterm);

			/* allocate array of accumulator and set all to zero */
			accumulator = (double *)malloc(sizeof(double) * N);
			for (i = 0; i < N; i++)
			{
				accumulator[i] = 0;
			}

			/* for each query terms, calculate the similarity */
			for (i = 0; i < totalqterm; i++)
			{
				/* search query term in array of term */
				pos = searchTerm(arrterm, totalTerm, queryterm[i]);
				// printf("pos term : %d\n", pos);
				// return;
				if (pos < 0)
				{
					printf("#Word ['%s'] is not indexed\n", queryterm[i]);
					return;
				}
				else
				{
					len = arrterm[pos].len;
					offset = arrterm[pos].offset;

					// printf("len : %d \n", len);
					// printf("offset : %ld\n", offset);
					// printf("index : %ld\n", arrterm[pos].index);
					/* read inverted list for the term */
					fseek(finv, offset, 0);
					ilbuf = (long int *)malloc(sizeof(long int) * (len));
					fread(ilbuf, sizeof(int), len, finv);
					// for (int v = 0; v < len; v++)
					// {
					// 	printf("finv : %ld\n", ilbuf[v]);
					// }
					fw = len / 2;
					printf("#Word word=%s, fw (num of doc containing the word) doc_num=%f\n", queryterm[i], fw);

					/* for each pair, show the result */
					for (t = 0; t < fw; t++)
					{
						// printf("ilbuf[t * 2] : %ld\n", ilbuf[t * 2]);
						// printf("freqwd : %ld\n", ilbuf[t * 2 + 1]);
						docno = ilbuf[t * 2];
						freqwd = ilbuf[t * 2 + 1];
						s_q_d = log(N / fw + 1) * log(freqwd + 1);
						//printf("s q d : %lf\n", s_q_d);
						accumulator[docno] += s_q_d;
					}
					free(ilbuf);
				}
			}

			/* Normalize accumulator by document length */
			for (i = 0; i < N; i++)
			{
				// printf(" %lf / %ld \n ", accumulator[i], fileinfo[docno].doclen);
				accumulator[i] += accumulator[i] / fileinfo[docno].doclen; /*using L(D)*/
															    //printf(" accumulator %d : %lf\n", i, accumulator[i]);
			}

			/* build heap of size HEAPSIZE */
			for (i = 0; i < N; i++)
			{
				if (i < HEAPSIZE)
				{
					buildHeap(heap, i, i, accumulator[i]);
				}
				else
				{
					/* compare new value with the root of the heap, if the new value is
			 		larger then the root, insert the new value into the heap */
					if (accumulator[i] > heap[0].ranked)
					{

						heap[0].ranked = heap[HEAPSIZE - 1].ranked;
						heap[0].docno = heap[HEAPSIZE - 1].docno;
						heap[HEAPSIZE - 1].ranked = accumulator[i];
						heap[HEAPSIZE - 1].docno = i;
					}

					/* adjust heap */
					for (t = (HEAPSIZE / 2) - 1; t >= 0; t--)
					{
						adjustHeap(heap, t, HEAPSIZE);
					}
				}
			}

			/* sort heap: bubble sort */
			for (i = HEAPSIZE - 1; i > 0; i--)
			{
				for (t = 0; t < i; t++)
				{
					//printf("rank %lf\n", heap[t].ranked);
					if (heap[t].ranked < heap[t + 1].ranked)
					{
						tempr = heap[t].ranked;
						tempd = heap[t].docno;
						heap[t].ranked = heap[t + 1].ranked;
						heap[t].docno = heap[t + 1].docno;
						heap[t + 1].ranked = tempr;
						heap[t + 1].docno = tempd;
					}
				}
			}

			// sprintf(output, "\n#Top %dth documents are:\n", HEAPSIZE);
			printf("#Top ranked=%d th documents are:\n", HEAPSIZE);

			/* print heap */
			for (i = 0; i < HEAPSIZE; i++)
			{
				offset = fileinfo[heap[i].docno].offset;
				// printf("offset at : %ld ", offset);
				fseek(fnme, offset, 0);
				fgets(buffer, STRPATH, fnme);
				buffer[strlen(buffer) - 1] = '\0'; /*eliminate character '\n' sucked by fgets*/
				char *token = buffer;
				token = strtok(buffer, "\t");
				token = strtok(NULL, "");

				//printf("Document [%s] or docno %ld ranked = %f\n",buffer,heap[i].docno,heap[i].ranked);
				printf("#List docno=%ld doc_rank=%f docname=%s\n", heap[i].docno, heap[i].ranked, token);
				// sprintf(&output[strlen(output)], "\t%ld\t\t%f\n", heap[i].docno, heap[i].ranked);
			}
			// printf("%s", output);
			free(accumulator);
		}
	}
}

/* getQueryTerm is the function to parse the query into
	 several terms */
int getQueryTerm(char *query, char queryterm[MAXQUERY][WORDLEN])
{
	char word[WORDLEN];
	char *pw = word;
	char *pq = query;
	int totalqueryterm = 0;

	query[strlen(query)] = '\0'; /* replace character '\n' with '\0'I*/
	while (*pq != '\0')
	{
		while (isspace(*pq))
		{
			pq++;
		}

		while (*pq != '\0')
		{
			if (!isalnum(*pq))
			{
				pq++;
				break;
			}
			*pw = *pq;
			pq++;
			pw++;
		}
		*pw = '\0';
		if (strlen(word) != 0)
		{
			/* check whether the word is a stopword, if
	 it is not, then add to queryterm array */
			if (!isstopword(word, TOTLIST, stoplist))
			{
				strcpy(queryterm[totalqueryterm++], word);
			}
		}
		word[0] = '\0';
		pw = word;
	}
	return totalqueryterm;
}

/* searchTerm is the function to search the uploaded terms from vocabulary
	 file using binary search method */
int searchTerm(Term *arrterm, int num, char *query)
{
	// printf("query : %s \n", query);
	// printf("size : %d \n", arrterm->len);
	// int high = num - 1, low = 0, mid;
	char saveWord[strlen(query) + 1];
	strcpy(saveWord, query);
	uint64_t hash = siphash24(saveWord, strlen(saveWord), key);
	unsigned idx = hash;

	idx = idx < 0 ? idx * -1 : idx;
	idx %= totalTerm;
	int flag = idx;
	// int index = num - 1;
	// printf("text : %s idx : %d\n", arrterm[idx].term, idx);

	// printf("idx : %d \n", idx);
	// int dump = 0;
	do
	{
		if (strcmp(arrterm[idx].term, saveWord) == 0)
		{
			// printf("text : %s idx : %d\n", arrterm[idx].term, idx);
			return idx;
		}
		idx++;
		idx = idx >= totalTerm ? 0 : idx;
	} while (idx != flag);
	return -1;
}

/* sort is a function to sort query terms by their frequency value in ascending
	 order, rare term should examine first in order to heuristically limited the
	 accumulator */
int sort(Term *arrterm, int totalqterm, char queryterm[MAXQUERY][WORDLEN])
{
	int i, t, pos;
	char temp[WORDLEN];
	float fw1, fw2;

	for (i = totalqterm - 1; i > 0; i--)
	{
		for (t = 0; t < i; t++)
		{
			pos = searchTerm(arrterm, totalTerm, queryterm[t]);
			fw1 = arrterm[pos].len / 2;
			pos = searchTerm(arrterm, totalTerm, queryterm[t + 1]);
			fw2 = arrterm[pos].len / 2;
			if (fw1 > fw2) /*sort in ascending order*/
			{
				strcpy(temp, queryterm[t]);
				strcpy(queryterm[t], queryterm[t + 1]);
				strcpy(queryterm[t + 1], temp);
			}
		}
	}
	return 1;
}
