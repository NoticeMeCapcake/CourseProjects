#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
int division(int*, int*, int, int);
int main()
{
	int *number1, number2[] = {1, 2, 6, 8}, len1, len2 = 4, i;
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
	int sec_len = -15, i, *buf, minus = 1, nul = 0;
	int len3 = len2, ans_len = 1;
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
    buf = (int*) calloc(1, sizeof(int));

    while(len3 <= len1)
    {
        if (len3 - nul == len2)
        {
    		for (i = nul; i < len3; i++)
    		{
    			if (number2[i - nul] > number1[i])
    			{
					if (sec_len != -15 && len1 != len3)
					{
						ans_len++;
			        	buf = (int*) realloc(buf, ans_len * sizeof(int));
	                    buf[ans_len - 1] = 0;
						//printf("baka-in\n");
					}
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
				//printf("bakaexit\n");
				continue;
			}
        }
        else if (len3 - nul < len2)
        {
			//printf("baka2\n");
			if (len1 != len3)
			{
				ans_len++;
	        	buf = (int*) realloc(buf, ans_len * sizeof(int));
	            buf[ans_len - 1] = 0;
			}
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
        buf[ans_len - 1]++;
		//printf("---end---\n");
    }
	printf("ans len %d\n", ans_len);
	for (i = 0; i < ans_len; i++) printf("ans = %d\n", buf[i]);
	number1 = (int*) realloc(number1, ans_len * sizeof(int));
	for (i = 0; i < ans_len; i++)
	{
		number1[i] = buf[i] * minus;
	}
	return ans_len;
}
