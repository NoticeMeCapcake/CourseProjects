#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
int module(int*, int*, int, int);
int minus_f(int*, int*, int, int);
int plus_f(int*, int*, int, int);
int main()
{
	int *number1, *number2, len1, len2, i;
	printf("len1: ");
	scanf("%d", &len1);
	number1 = (int*) calloc(10000, sizeof(int));
	for (i = 0; i < len1; i++)
		scanf("%d", &number1[i]);
	getchar();
	printf("len2:");
	scanf("%d", &len2);
	number2 = (int*) calloc(len2, sizeof(int));
	for (i = 0; i < len2; i++)
		scanf("%d", &number2[i]);
	getchar();
	len1 = module(number1, number2, len1, len2);
	printf("LEN1 = %d\n", len1);
	for (i = 0; i < len1; i++)
		printf("%d", number1[i]);
	printf("\n");
}
int module(int *number1, int* number2, int len1, int len2)
{
	int sec_len = -15, i, *buf, minus = 1, nul = 0, len3 = len2;
    if (number2[0] == 0)
    {
        return -1;
    }
	if (number1[0] < 0)
	{
		minus = -1;
		for (i = 0; i < len1; i++)
		{
			number1[i] = abs(number1[i]);
		}
	}
	if (number2[0] < 0)
	{
		for (i = 0; i < len2; i++)
		{
			number2[i] = abs(number2[i]);
		}
	}

    while(len3 <= len1)
    {
        if (len3 - nul == len2)
        {
    		for (i = nul; i < len3; i++)
    		{
    			if (number2[i - nul] > number1[i])
    			{
					//printf("baka1\n");
    				len3++;
    				break;
    			}
    			if (number2[i - nul] < number1[i])
                {
					break;
				}
    		}
			if (len3 > len1)
			{
				printf("bakaexit\n");
				continue;
			}
        }
        else if (len3 - nul < len2)
        {
			//printf("baka2\n");
            len3++;
            continue;
        }
        sec_len = len2 - 1;
        for (i = len3 - 1; i >= nul; i--)
        {
            if (sec_len >= 0)
            {
                number1[i] = number1[i] - number2[sec_len];
                sec_len--;
            }
            if (number1[i] < 0)
            {
                number1[i] += 10;
                number1[i - 1]--;
            }
        }
		//for (i = 0; i < len1; i++)printf("sec num1 = %d\n", number1[i]);
		nul = 0;
        for (i = 0; i < len1; i++)
    	{
    		if (number1[i] == 0)
			{
				nul++;
			}
    		else
			{
				break;
			}
    	}
		//printf("---end---\n");
    }
    printf("noliki: %d\n", nul);

    if (nul > 0)
    {
        for (i = nul; i < len1; i++)
        {
            number1[i - nul] = number1[i];
        }
        len1 -= nul;
        if (len1 == 0)
        {
			*number1 = (int) calloc(1, sizeof(int));
			number1[0] = 0;
            len1++;
        }
        //*number1 = (int) calloc(len1, sizeof(int));
    }
    if (minus == -1 && number1[0] != 0)
    {
        sec_len = len1;
        len1 = len2;
        len2 = sec_len;
        buf = (int*) calloc(len1, sizeof(int));
        for (i = len1 - 1; i >= 0; i--)
        {
            buf[i] = number2[i];
        }
        number2 = (int*) calloc(len2, sizeof(int));
        for (i = len2 - 1; i >= 0; i--)
        {
            number2[i] = number1[i];
        }
        *number1 = (int) calloc(len1, sizeof(int));
        for (i = len1 - 1; i >= 0; i--)
        {
            number1[i] = buf[i];
        }
        //free(buf);
        sec_len = len2 - 1;
        for (i = len1 - 1; i >= 0; i--)
        {
            if (sec_len >= 0)
            {
                number1[i] = number1[i] - number2[sec_len];
                sec_len--;
            }
            if (number1[i] < 0)
            {
                number1[i] += 10;
                number1[i - 1]--;
            }
        }
        nul = 0;
        for (i = 0; i < len1; i++)
        {
            if (number1[i] == 0)
            {
                nul++;
            }
            else
            {
                break;
            }
        }
        if (nul > 0)
        {
            for (i = nul; i < len1; i++)
            {
                number1[i - nul] = number1[i];
            }
			len1 -= nul;
			//*number1 = (int) realloc(number1, len1 * sizeof(int));
        }
    }
	for (i = 0; i < len1; i++)
	{
		printf("num1 = %d\n", number1[i]);
	}
	free(buf);
	free(number2);
	return len1;
}
