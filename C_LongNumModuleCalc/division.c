#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
int division(int*, int*, int, int);
int main()
{
	int *number1, number2[] = {2, 2, 1}, len1, len2 = 3, i;
	printf("len1");
	scanf("%d", &len1);
	number1 = (int*) calloc(len1, sizeof(int));
	for (i = 0; i < len1; i++)
		scanf("%d", &number1[i]);
	getchar();
	len1 = division(number1, number2, len1, len2);
	printf("LEN1 = %d\n", len1);
	for (i = 0; i < len1; i++)
		printf("%d", number1[i]);
	printf("\n");
}
int division(int *number1, int* number2, int len1, int len2)
{
	int j, i, *buf, minus = 1, nul = 0, whi = 1;
	int ret_flag = 0, len3 = 1;
    buf = calloc(1, sizeof(int));
    if (number2[0] == 0)
    {
        return -1;
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
    while(whi)
    {
        for (i = 0; i < len3; i++)
        {
            if (buf[i] >= 10)
            {
				buf[i] = 0;
                if (i == len3 - 1)
                {
                    len3++;
                    buf = (int*) realloc(buf, len3 * sizeof(int));
                    buf[len3 - 1] = 0;
                }
                buf[i + 1]++;
            }
        }
		if (len1 == len2 && ret_flag != 1)
		{
			for (i = 0; i < len1; i++)
			{
				if (number2[i] > number1[i])
				{
					ret_flag = 1;
					break;
				}
				if (number2[i] < number1[i]) break;
				if (i == len1 - 1)
				{
                    ret_flag = 1;
                    buf[0]++;
				    continue;
				}
			}
		}
		else if (len1 < len2 && ret_flag != 1)
		{
			ret_flag = 1;
		}
		if (ret_flag == 1)
		{
			number1 = (int*) realloc(number1, len3 * sizeof(int));
            for (i = 0; i < len3; i++)
			{
				number1[i] = buf[len3 - 1 - i] * minus;
			}
			return len3;
		}
        j = 1;
    	for (i = len1 - 1; i >= 0; i--)
		{
            if (j <= len2)
            {
                number1[i] = number1[i] - number2[len2 - j];
            }
            if (number1[i] < 0)
            {
                number1[i] += 10;
                number1[i - 1]--;
            }
            j++;

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
	    	number1 = (int*) realloc(number1, (len1 - nul) * sizeof(int));
	        len1 -= nul;
		}
    	buf[0]++;
    }
}
