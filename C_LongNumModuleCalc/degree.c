#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

int multiply(int*, int*, int, int);
int degree_f(int*, int*, int, int);
int main()
{
	int *number1, number2[] = {2, 5, 5}, len1, len2 = 3, i;
	printf("len1");
	scanf("%d", &len1);
	number1 = (int*) calloc(len1, sizeof(int));
	for (i = 0; i < len1; i++)
		scanf("%d", &	number1[i]);
	getchar();
	len1 = degree_f(number1, number2, len1, len2);
	printf("LEN1 = %d\n", len1);
	for (i = 0; i < len1; i++)
		printf("%d", number1[i]);
	printf("\n");
}
int degree_f(int* number1, int* number2, int len1, int len2)
{
    int j, i, *bufi, minus = 1, len3 = 0, k, *buf;
	int degree = 0, buffy = 0, nul = 0;
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
        number1[0] = 0;
		*number1 = (int) realloc(&number1, 1 * sizeof(int));
        return 1;
	}
    for (i = 0; i < len2; i++)
    {
        degree *= 10;
        degree += number2[i];
    }
    printf("degree - %d\n", degree);
    bufi = (int*) calloc(len1, sizeof(int));
    for (i = 0; i < len1; i++)
    {
        bufi[i] = number1[i];
    }
    len2 = len1;
    for (k = 1; k < degree; k++)
    {
		len3 = len1 + len2;
        printf("%d: len %d\n", k, len1);
        //for (i = 0; i < len1; i++) printf("--%d--\n", number1[i]);
		buf = (int*) calloc(len3, sizeof(int));
		for (i = len2 - 1; i >= 0; i--)
		{
			buffy = len2 - i;
			//printf("len3 - buffy = %d\n", len3 - buffy);
			for (j = len1 - 1; j >= 0; j--)
			{
				buf[len3 - buffy] += number1[j] * bufi[i];
				if (buf[len3 - buffy] >= 10)
				{
					buf[len3 - buffy - 1] += buf[len3 - buffy] / 10;
					buf[len3 - buffy] %= 10;
				}
				buffy++;
			}
		}
		nul = 0;
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
		len1 = len3 - nul;
		//free(&number1);
		*number1 = (int) realloc(&number1, len1 * sizeof(int));
		//*number1 = (int) calloc(len1, sizeof(int));
		for (i = 0; i < len1; i++)
		{
			//printf("- buff = %d\n", buf[i + nul]);
			number1[i] = buf[i + nul];
		}
		//*buf = (int) realloc(&buf, 0 * sizeof(int));
		//for (i = 0; i < len3; i++)
		//free(&buf);
		//printf("len1 = %d\n", len1);
    }
	for (i = 0; i < len1; i++)
	{
		if (minus == -1 && degree % 2 == 1)
		{
			number1[i] *= minus;
		}
	}
	//*number1 = (int) realloc(&number1, len1 * sizeof(int));
	return len1;
}

int multiply(int* number1, int* number2, int len1, int len2)
{
    int j, i, *buf, minus = 1, nul = 0;
	int len3 = len1 + len2, buffy = 0;
    //free(buf);
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
    printf("--len1 = %d | len2 = %d | len3 = %d\n", len1, len2, len3);
    buf = (int*) calloc(len3, sizeof(int));
	for (i = len2 - 1; i >= 0; i--)
	{
		buffy = len2 - i;
		//printf("len3 - buffy = %d\n", len3 - buffy);
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
		free(buf);
	}
	len1 = len3 - nul;
	*number1 = (int) realloc(&number1, len1 * sizeof(int));
	for (i = 0; i < len1; i++)
	{
		printf("- buff = %d\n", buf[i + nul]);
		number1[i] = buf[i + nul] * minus;
	}
    //buf = (int*) realloc(buf, 0 * sizeof(int));
	return len1;
}
