#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
int mult_f(int*, int*, int, int);
int main()
{
	int *number1, number2[] = {5, 9}, len1, len2 = 2, i;
	printf("len1");
	scanf("%d", &len1);
	number1 = (int*) calloc(len1, sizeof(int));
	for (i = 0; i < len1; i++)
		scanf("%d", &	number1[i]);
	getchar();
	len1 = mult_f(number1, number2, len1, len2);
	printf("LEN1 = %d\n", len1);
	for (i = 0; i < len1; i++)
		printf("%d", number1[i]);
	printf("\n");
}
int mult_f(int* number1, int* number2, int len1, int len2)
{
    int j, i, *buf, minus = 1, nul = 0;
	int len3 = len1 + len2, buffy = 0;
	if (number1[0] == 0 || number2[0] == 0)
	{
		number1 = (int*) calloc(1, sizeof(int));
		return 1;
	}
    if (number1[0] < 0)
	{
		minus *= -1;
		for (i = 0; i < len1; i++)
		{
			number1[i] = abs(number1[i]);
		}
	}
	if (number2[0] < 0)
	{
        minus *= -1;
		for (i = 0; i < len2; i++)
		{
			number2[i] = abs(number2[i]);
		}
	}
    buf = (int*) calloc(len3, sizeof(int));
	printf("baka\n");
    for (i = len2 - 1; i >= 0; i--)
	{
		buffy = len2 - i;
		for (j = len1 - 1; j >= 0; j--)
		{
			buf[len3 - buffy] += number1[j] * number2[i];
			if (buf[len3 - buffy] >= 10)
			{
				buf[len3 - buffy - 1] += buf[len3 - buffy] / 10;
				buf[len3 - buffy] %= 10;
			}
			buffy++;
		}
	}
	printf("baka1\n");
	for (i = 0; i < len3; i++)
	{
		if (buf[i] == 0)
		{
			nul++;
		}
		else
		{
			break;
		}
	}
	printf("baka2\n");
	len1 = len3 - nul;
	*number1 = (int) realloc(&number1, len1 * sizeof(int));
	for (i = 0; i < len1; i++)
	{
		number1[i] = buf[i + nul] * minus;
	}
	printf("baka3\n");
	free(buf);
	printf("baka4\n");
	return len1;
}
