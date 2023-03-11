#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
int plus_f(int*, int*, int, int);
int minus_f(int*, int*, int, int);
int main()
{
	int *number1, number2[] = {5, 6, 8, 2, 9, 9, 0, 7}, len1 = 0, len2 = 8, i = 0;
	printf("len1");
	scanf("%d", &len1);
	number1 = (int*) calloc(len1, sizeof(int));
	for (i = 0; i < len1; i++) scanf("%d", &number1[i]);
	getchar();
	len1 = minus_f(number1, number2, len1, len2);
	printf("LEN1 = %d\n", len1);
	for (i = 0; i < len1; i++) printf("%d", number1[i]);
	printf("\n");
}
int plus_f(int *number1, int* number2, int len1, int len2)
{
	int j = 0, i = 0, *buf, minus = 1, nul = 0, len_max = 0, k = 0;
    if (number1[0] < 0 && number2[0] < 0)
    {
        minus = -1;
        for (i = 0; i < len1; i++)
		{
			number1[i] = abs(number1[i]);
		}
        for (i = 0; i < len2; i++)
		{
			number2[i] = abs(number2[i]);
		}
    }
    else if (number2[0] < 0)
    {
        for (i = 0; i < len2; i++)
		{
			number2[i] = abs(number2[i]);
		}
        return minus_f(number1, number2, len1, len2);
    }
    else if (number1[0] < 0)
    {
        j = len1;
        len1 = len2;
        len2 = j;
        buf = (int*) calloc(len2, sizeof(int));
        for (i = 0; i < len2; i++)
		{
			number1[i] = abs(number1[i]);
            buf[i] = number1[i];
		}
		free(number1);
        number1 = (int*) calloc(len1, sizeof(int));
        for (i = len1 - 1; i >= 0; i--) number1[i] = number2[i];
		free(number2);
        number2 = (int*) calloc(len2, sizeof(int));
        for (i = len2 - 1; i >= 0; i--) number2[i] = buf[i];
		free(buf);
        return minus_f(number1, number2, len1, len2);
    }
    if (len2 > len1)
    {
        len_max = len2 + 1;
    }
    else
    {
        len_max = len1 + 1;
    }
	j = len1;
	k = len2;
    buf = (int*) calloc(len_max, sizeof(int));
    for (i = len_max - 1; i > 0; i--)
    {
		j--;
		k--;
		if (j >= 0)
		{
			buf[i] += number1[j];
		}
		if (k >= 0)
		{
			buf[i] += number2[k];
		}
        if (buf[i] >= 10)
        {
            buf[i] -= 10;
            buf[i - 1] += 1;
        }
    }
    nul = 0;
    for (i = 0; i < len_max + 1; i++)
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
    len1 = len_max - nul;
    *number1 = (int) realloc(&number1, len1 * sizeof(int));
    for (i = 0; i < len1; i++)
    {
        number1[i] = buf[i + nul] * minus;
    }
    return len1;
}
int minus_f(int *number1, int* number2, int len1, int len2)
{
	int j = 0, k = 0, i = 0, *buf, minus = 1, nul = 0, len_max = 0, less = 0;

	if (number1[0] < 0 && number2[0] < 0)
	{
		buf = (int*) calloc(len2, sizeof(int));
        for (i = 0; i < len2; i++)
		{
			number1[i] = abs(number1[i]);
            buf[i] = number1[i];
		}

        number1 = (int*) calloc(len1, sizeof(int));
        for (i = len1 - 1; i >= 0; i--) number1[i] = abs(number2[i]);

        number2 = (int*) calloc(len2, sizeof(int));
        for (i = len2 - 1; i >= 0; i--) number2[i] = buf[i];
		free(buf);
	}

	else if (number2[0] < 0)
	{
		for (i = 0; i < len2; i++) number2[i] = abs(number2[i]);
		return plus_f(number1, number2, len1, len2);
	}

	else if (number1[0] < 0)
	{
		for (i = 0; i < len2; i++) number2[i] *= -1;
		return plus_f(number1, number2, len1, len2);
	}

	if (len1 == len2)
	{
		len_max = len1;
		for (i = 0; i < len1; i++)
		{
			if (number1[i] < number2[i])
			{
				less = 1;
				break;
			}
			else if (number2[i] < number1[i])
			{
				less = 2;
				break;
			}
		}
		if (less == 0)
		{
			free(number1);
			number1 = (int*) calloc(1, sizeof(int));
			return 1;
		}
	}
	if (len2 > len1 || less == 1)
    {
		less = 1;
		minus = -1;
        len_max = len2;
    }
    else if (len2 < len1 || less == 2)
    {
		less = 2;
        len_max = len1;
    }

	buf = (int*) calloc(len_max, sizeof(int));
	j = len1;
	k = len2;
	for (i = len_max; i >= 0; i--)
	{
		j--;
		k--;
		if (less == 2)
		{
			if (j >= 0)
			{
				buf[i] += number1[j];
			}
			if (k >= 0)
			{
				buf[i] -= number2[k];
			}
			if (buf[i] < 0)
			{
				buf[i] += 10;
				number1[i - 1] -= 1;
			}
		}
		if (less == 1)
		{
			if (k >= 0)
			{
				buf[i] += number2[k];
			}
			if (j >= 0)
			{
				buf[i] -= number1[j];
			}
			if (buf[i] < 0)
			{
				buf[i] += 10;
				number2[i - 1] -= 1;
			}
		}
	}
	nul = 0;
	for (i = 0; i < len_max; i++)
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
	len1 = len_max - nul;
	*number1 = (int) realloc(&number1, len1 * sizeof(int));
    for (i = 0; i < len1; i++)
    {
		number1[i] = buf[i + nul] * minus;
	}
	return len1;
}
