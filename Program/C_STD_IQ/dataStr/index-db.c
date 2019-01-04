/*
 * by tfa at informatika.unsyiah.ac.id/tfa
 * edited by Muammar Zikri Aksana
 */

#include <sys/time.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "define.h"
#include "util.h"

#include "ZSTData.c"
#include "Zhash.c"

extern int errno;
char key[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};

int main(void)
{
	FILE *fdat, *finv, *fvoc, *fpar, *fnme, *finf;
	FILE *finvH, *fvocH, *fparH, *fnmeH, *finfH;
	int errnum;
	DIR *dp;
	struct dirent *ep;
	char dirdata[STRPATH];
	long int docno, offset, doclen;
	char path[STRPATH];
	char word[WORDLEN];
	// char class[WORDLEN];
	StopList stoplist[TOTLIST];

	ListHeadZ *invertedIndex;
	invertedIndex = (ListHeadZ *)malloc(INDEX * sizeof(ListHeadZ) + 1);

	for (int a = 0; a < INDEX; a++)
	{
		invertedIndex[a].head = NULL;
		invertedIndex[a].size = 0;
	}

	listIndexHead LIST_INDEX;

	long int MIN_INDEX; // untuk hash agar tidak buang2 space
	long int MAX_INDEX; // untuk hash agar tidak buang2 space
	int flag = 1;

	loadStopList(stoplist);

	if ((fnme = fopen("Program/out/index-db/data.nme", "w")) == NULL)
	{
		printf("Cannot create data.nme file...\n");
		return 0;
	}
	if ((finf = fopen("Program/out/index-db/data.wdl", "w")) == NULL)
	{
		printf("Cannot create file info without doclen [data.wdl]...\n");
		return 0;
	}
	if ((finv = fopen("Program/out/index-db/data.inv", "wb")) == NULL)
	{
		printf("Cannot create inverted file [data.inv]...\n");
		return 0;
	}
	if ((fpar = fopen("Program/out/index-db/data.par", "wb")) == NULL)
	{
		printf("Cannot create parameter file [data.par]...\n");
		return 0;
	}
	if ((fvoc = fopen("Program/out/index-db/data.voc", "w")) == NULL)
	{
		printf("Cannot create vocabulary file [data.voc]...\n");
		return 0;
	}

	if ((fnmeH = fopen("Program/out/index-db-hash/data.nme", "w")) == NULL)
	{
		printf("Cannot create data.nme file...\n");
		return 0;
	}
	if ((finfH = fopen("Program/out/index-db-hash/data.wdl", "w")) == NULL)
	{
		printf("Cannot create file info without doclen [data.wdl]...\n");
		return 0;
	}
	if ((finvH = fopen("Program/out/index-db-hash/data.inv", "wb")) == NULL)
	{
		printf("Cannot create inverted file [data.inv]...\n");
		return 0;
	}
	if ((fparH = fopen("Program/out/index-db-hash/data.par", "wb")) == NULL)
	{
		printf("Cannot create parameter file [data.par]...\n");
		return 0;
	}
	if ((fvocH = fopen("Program/out/index-db-hash/data.voc", "w")) == NULL)
	{
		printf("Cannot create vocabulary file [data.voc]...\n");
		return 0;
	}

	printf("Data directory: ");
	scanf("%s", dirdata);
	int countFile = 0;
	startTiming();
	char saveDir[strlen(dirdata) + 1];
	strcpy(saveDir, dirdata);
	/* open directory where documents are stored */
	dp = opendir(dirdata);
	int file_count = 0;
	DIR *dirp;
	struct dirent *entry;

	dirp = opendir(dirdata); /* There should be error handling after this */
	while ((entry = readdir(dirp)) != NULL)
	{

		file_count++;
	}
	closedir(dirp);
	// printf("dir : %d", file_count);
	// return 1;
	// printf("count file in dir : %d\n", file_count);

	if (dp != NULL)
	{
		docno = 0;
		printf("\nWait, reading documents...\n");
		while ((ep = readdir(dp)) && file_count--)
		{
			strcpy(dirdata, saveDir); // trick for bug var dirdata
			printf("dirdata %s \n", dirdata);
			if ((strcmp(ep->d_name, ".") != 0) && (strcmp(ep->d_name, "..") != 0))
			{
				bzero(path, sizeof(path));
				strcpy(path, dirdata);
				strcat(path, ep->d_name);

				printf("%d : path %s \n", countFile++, path);
				printf("path %s \n", path);

				// printf("dirdata %s \n", dirdata);

				if ((fdat = fopen(path, "r")) == NULL)
				{
					errnum = errno;
					printf("Opening %s file [%s] failed...\n", path, ep->d_name);
					fprintf(stderr, "Value of errno: %d\n", errno);
					perror("Error printed by perror");
					fprintf(stderr, "Error opening file: %s\n", strerror(errnum));
					// return 0;
					fclose(fdat); // flag close for handling : continue at line 142
					continue;
				}
				else
				{
					// continue;

					if ((docno != 0) && ((docno % 1000) == 0))
					{
						printf("%ldth documents\n", docno);
					}
					doclen = 0;
					offset = ftell(fnme);

					/* read the doc and get all words */
					while (!feof(fdat))
					{
						getword(fdat, word); /* parse each words */

						if (isalpha(word[0]))
						{

							wordToLower(word); /* convert word to lower case */
							if (!isstopword(word, TOTLIST, stoplist))
							{

								wordCount++;
								char saveWord[strlen(word) + 1];
								strcpy(saveWord, word);
								// unsigned key = crc32a(word) % INDEX;

								uint64_t hash = siphash24(saveWord, strlen(saveWord), key);
								unsigned idx = hash;

								idx = idx < 0 ? idx * -1 : idx;
								idx %= INDEX;

								insertListZ(&invertedIndex[idx], saveWord, docno, &LIST_INDEX, idx);
								// printf("idx : %d\n", idx);

								if (flag)
								{
									MIN_INDEX = idx;
									MAX_INDEX = idx;
									flag = 0;
								}
								else
								{
									MIN_INDEX = MIN_INDEX > idx ? idx : MIN_INDEX;
									MAX_INDEX = MAX_INDEX < idx ? idx : MAX_INDEX;
								}
							}
						}
						doclen += strlen(word);
					}

					fprintf(fnme, "%ld\t%s\n", docno, ep->d_name);
					fprintf(fnmeH, "%ld\t%s\n", docno, ep->d_name);

					fprintf(finf, "%ld\t %ld \t%ld\n", docno, doclen, offset);  /* store docno, doclen & offset */
					fprintf(finfH, "%ld\t %ld \t%ld\n", docno, doclen, offset); /* store docno, doclen & offset */
				}

				docno++;
				fclose(fdat);
			}
		}
		(void)closedir(dp);
		fclose(fnme);
		fclose(finf);
		fclose(fnmeH);
		fclose(finfH);
		printf("%ldth documents\n", docno);
	}
	else
	{
		printf("Cannot access data directory...\n");
		return 0;
	}

	/* record number of documents being indexed */
	fwrite(&docno, sizeof(long int), 1, fpar);
	fwrite(&docno, sizeof(long int), 1, fparH);
	// startTiming();

	hashTraversalZ(invertedIndex, finv, fvoc, fpar, &LIST_INDEX, finvH, fvocH, fparH);

	// printf("size : %d\n", LIST_INDEX.size);
	fwrite(&MIN_INDEX, sizeof(long int), 1, fparH);
	fwrite(&MAX_INDEX, sizeof(long int), 1, fparH);

	fclose(fvoc);
	fclose(fpar);
	fclose(finv);
	fclose(fvocH);
	fclose(fparH);
	fclose(finvH);

	printf("Freeing memory...\n");
	// freeTree(&bst);
	printf("\nGenerating index complete.\n");
	stopTiming();
	printf("Time required: %f seconds\n\n", timingDuration() * 1e-2);
	// printf("hasil");
	// int null = 0;
	printf("distintc : %ld\n", distinctWord);
	printf("collison : %d\n", collision);
	printf("count word : %d\n", wordCount);
	// printf("Min : %ld\n", MIN_INDEX);
	// printf("Max : %ld\n", MAX_INDEX);

	return 1;
	// FILE *fps = fopen("size.txt", "w");
	// // /* Printf hash with direct link list*/
	// listIndexPtrZ current = LIST_INDEX.list;
	// while (current != NULL)
	// {
	// 	fprintf(fps, "%d\n", invertedIndex[current->index].size);
	// 	// readListZ(&invertedIndex[current->index]);
	// 	current = current->next;
	// }
	// fclose(fps);
	// //	printf("index : %d\n", LIST_INDEX.size);

	// return 1;
}
