//https://www.programmingsimplified.com/c/source-code/c-program-convert-string-to-integer-without-using-atoi-function
int toInt(char a[])
{
	int c, sign, offset, n;

	if (a[0] == '-')
	{ // Handle negative integers
		sign = -1;
	}

	if (sign == -1)
	{ // Set starting position to convert
		offset = 1;
	}
	else
	{
		offset = 0;
	}

	n = 0;

	for (c = offset; a[c] != '\0'; c++)
	{
		n = n * 10 + a[c] - '0';
	}

	if (sign == -1)
	{
		n = -n;
	}

	return n;
}