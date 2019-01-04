#include <stdio.h>

int main(int argc, char const *argv[])
{
	FILE *fp = fopen("Program/out/index-db/data.nme", "r");

	printf("tes");
	fclose(fp);
	return 0;
}
