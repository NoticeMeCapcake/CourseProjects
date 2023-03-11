typedef struct
{
    int length;
    int *value;
} Operand;

void spreader(Operand *, Operand *, char); /* to clear operands from insignificant
zeroes and to select function */
void division_f(Operand *, Operand *); /* operation division function */
void degree_f(Operand *, Operand *); /* operationpower function */
void minus_f(Operand *, Operand *); /* operationminus function */
void plus_f(Operand *, Operand *); /* operation plus function */
void mult_f(Operand *, Operand *); /* operation multiply function */
void module_f(Operand *, Operand *); /* operation module function */


void division_f(Operand *left_operand, Operand *right_operand)
{
	int sec_len = -15, i, *buf, minus = 1, nul = 0, *number1 = left_operand->value;
	int len3 = right_operand->length, ans_len = 1, *number2 = right_operand->value;
    if (number2[0] == 0)
    {
        free(number2);
        left_operand->length = -1;
        return;
    }
	if (number1[0] < 0)
	{
		minus *= -1;
		for (i = 0; i < left_operand->length; i++)
		{
			number1[i] = abs(number1[i]);
		}
	}
	if (number2[0] < 0)
	{
        minus *= -1;
		for (i = 0; i < right_operand->length; i++)
		{
			number2[i] = abs(number2[i]);
		}
	}
    buf = (int*) calloc(1, sizeof(int));
    if(!buf)
    {
        printf ("ERROR. Allocation failure.");
        exit (-5);
    }
    while(len3 <= left_operand->length)
    {
        if (len3 - nul == right_operand->length)
        {
    		for (i = nul; i < len3; i++)
    		{
    			if (number2[i - nul] > number1[i])
    			{
					if (sec_len != -15 && left_operand->length != len3)
					{
						ans_len++;
			        	buf = (int*) realloc(buf, ans_len * sizeof(int));
                        if(!buf)
                        {
                            printf ("ERROR. Allocation failure.");
                            exit (-5);
                        }
	                    buf[ans_len - 1] = 0;
					}
    				len3++;
    				break;
    			}
    			if (number2[i - nul] < number1[i])
                {
					break;
				}
    		}
			if (len3 > left_operand->length)
			{
				continue;
			}
        }
        else if (len3 - nul < right_operand->length)
        {
			if (left_operand->length != len3)
			{
				ans_len++;
	        	buf = (int*) realloc(buf, ans_len * sizeof(int));
                if(!buf)
                {
                    printf ("ERROR. Allocation failure.");
                    exit (-5);
                }
	            buf[ans_len - 1] = 0;
			}
            len3++;
            continue;
        }
        sec_len = right_operand->length - 1;
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
        nul = 0;
        for (i = 0; i < left_operand->length; i++)
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
    }
    free(number1);
	number1 = (int*) calloc(ans_len, sizeof(int));
    if(!number1)
    {
        printf ("ERROR. Allocation failure.");
        exit (-5);
    }
	for (i = 0; i < ans_len; i++)
	{
		number1[i] = buf[i] * minus;
	}
    free(buf);
    left_operand->value = number1;
    left_operand->length = ans_len;
	return;
}

void degree_f(Operand *left_operand, Operand *right_operand)
{
    int j, i, *bufi, minus = 1, len3 = 0, k, *buf, *number2 = right_operand->value;
	int degree = 0, buffy = 0, nul = 0, *number1 = left_operand->value;
	if (number1[0] == 0 || number2[0] < 0)
	{
		free(left_operand->value);
		free(right_operand->value);
		left_operand->value = (int*) calloc(1, sizeof(int));
        if(!left_operand->value)
        {
            printf ("ERROR. Allocation failure.");
            exit (-5);
        }
        (left_operand->value)[0] = 0;
        left_operand->length = 1;
        return;
	}
	if (number2[0] == 0)
	{
		free(left_operand->value);
		free(right_operand->value);
		left_operand->value = (int*) calloc(1, sizeof(int));
        if(!left_operand->value)
        {
            printf ("ERROR. Allocation failure.");
            exit (-5);
        }
        (left_operand->value)[0] = 1;
        left_operand->length = 1;
        return;
	}
    if (number1[0] < 0)
	{
		minus *= -1;
		for (i = 0; i < left_operand->length; i++)
		{
			number1[i] = abs(number1[i]);
		}
	}
    for (i = 0; i < right_operand->length; i++)
    {
        degree *= 10;
        degree += number2[i];
    }
    bufi = (int*) calloc(left_operand->length, sizeof(int));
    if(!bufi)
    {
        printf ("ERROR. Allocation failure.");
        exit (-5);
    }
    for (i = 0; i < left_operand->length; i++)
    {
        bufi[i] = number1[i];
    }
    right_operand->length = left_operand->length;
    for (k = 1; k < degree; k++)
    {
		len3 = left_operand->length + right_operand->length;
		buf = (int*) calloc(len3, sizeof(int));
        if(!buf)
        {
            printf ("ERROR. Allocation failure.");
            exit (-5);
        }
		for (i = right_operand->length - 1; i >= 0; i--)
		{
			buffy = right_operand->length - i;
			for (j = left_operand->length - 1; j >= 0; j--)
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
		left_operand->length = len3 - nul;
		free(number1);
		number1 = (int*) calloc(left_operand->length, sizeof(int));
        if(!bufi)
        {
            printf ("ERROR. Allocation failure.");
            exit (-5);
        }
		for (i = 0; i < left_operand->length; i++)
		{
			number1[i] = buf[i + nul];
		}
		free(buf);
    }
    if (degree % 2 != 0)
    {
        for (i = 0; i < left_operand->length; i++)
        {
            number1[i] *= minus;
        }
    }
    left_operand->value = number1;
    printf("%d\n", left_operand->length);
    for (i = 0; i < left_operand->length; i++)
    {
        printf("%d", (left_operand->value)[i]);
    }
    printf("\n");
	free(bufi);
	free(number2);
	return;
}


void module_f(Operand *left_operand, Operand *right_operand)
{
	int sec_len = -15, i, *buf, minus = 1, nul = 0, len3 = right_operand->length;
    int *number2 = right_operand->value, *number1 = left_operand->value;

    if (number2[0] == 0)
    {
		free(right_operand->value);
        left_operand->length = -1;
        return;
    }
	if (number1[0] < 0)
	{
		minus = -1;
		for (i = 0; i < left_operand->length; i++)
		{
			number1[i] = abs(number1[i]);
		}
	}
	if (number2[0] < 0)
	{
		for (i = 0; i < right_operand->length; i++)
		{
			number2[i] = abs(number2[i]);
		}
	}

    while(len3 <= left_operand->length)
    {
        if (len3 - nul == right_operand->length)
        {
    		for (i = nul; i < len3; i++)
    		{
    			if (number2[i - nul] > number1[i])
    			{
    				len3++;
    				break;
    			}
    			if (number2[i - nul] < number1[i])
                {
					break;
				}
    		}
			if (len3 > left_operand->length)
			{
				continue;
			}
        }
        else if (len3 - nul < right_operand->length)
        {
            len3++;
            continue;
        }
        sec_len = right_operand->length - 1;
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
		nul = 0;
        for (i = 0; i < left_operand->length; i++)
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
    }
    while(1)
    {
        if (nul > 0)
        {
            buf = (int*) calloc(left_operand->length - nul, sizeof(int));
            if(!buf)
            {
                printf ("ERROR. Allocation failure.");
                exit (-5);
            }
            for (i = nul; i < left_operand->length; i++)
            {
                buf[i - nul] = number1[i];
            }
            left_operand->length -= nul;
            if (left_operand->length == 0)
            {
                left_operand->length = 1;
            }
            free(number1);
            number1 = (int*) calloc (left_operand->length,sizeof(int));
            if(!number1)
            {
                printf ("ERROR. Allocation failure.");
                exit (-5);
            }
            for (i = 0; i < left_operand->length; i++)
            {
                number1[i] = buf[i];
            }
            free(buf);
        }
        if (minus == -1 && number1[0] != 0)
        {
            minus = 1;
            sec_len = left_operand->length;
            left_operand->length = right_operand->length;
            right_operand->length = sec_len;
            buf = number2;
            number2 = number1;
            number1 = buf;
            sec_len = right_operand->length - 1;
            for (i = left_operand->length - 1; i >= 0; i--)
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
            for (i = 0; i < left_operand->length; i++)
            {
                if (number2[i] == 0)
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
                continue;
            }
        }
        break;
    }
    free(number2);
	left_operand->value = number1;
	return;
}


void plus_f(Operand *left_operand, Operand *right_operand)
{
	int j = 0, i = 0, *buf, minus = 1, nul = 0, len_max = 0, k = 0;
    int *number1 = left_operand->value, *number2 = right_operand->value;
    if (number1[0] < 0 && number2[0] < 0)
    {

        minus = -1;
        for (i = 0; i < left_operand->length; i++)
		{
			number1[i] = abs(number1[i]);
		}
        for (i = 0; i < right_operand->length; i++)
		{
			number2[i] = abs(number2[i]);
		}
    }
    else if (number2[0] < 0)
    {
        for (i = 0; i < right_operand->length; i++)
		{
			number2[i] = abs(number2[i]);
		}
        minus_f(left_operand, right_operand);
        return ;
    }
    else if (number1[0] < 0)
    {
        j = left_operand->length;
        left_operand->length = right_operand->length;
        right_operand->length = j;

        buf = right_operand->value;
        right_operand->value = left_operand->value;
        left_operand->value = buf;
        for (i = 0; i < right_operand->length; i++)
        {
            (right_operand->value)[i] = abs((right_operand->value)[i]);
        }

        minus_f(left_operand, right_operand);
        return;
    }
    if (right_operand->length > left_operand->length)
    {
        len_max = right_operand->length + 1;
    }
    else
    {
        len_max = left_operand->length + 1;
    }
	j = left_operand->length;
	k = right_operand->length;
    buf = (int*) calloc(len_max, sizeof(int));
    if(!buf)
    {
        printf ("ERROR. Allocation failure.");
        exit (-5);
    }
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
    left_operand->length = len_max - nul;
    free(number2);
    free(number1);
    number1 = (int*) calloc(left_operand->length, sizeof(int));
    if(!number1)
    {
        printf ("ERROR. Allocation failure.");
        exit (-5);
    }
    for (i = 0; i < left_operand->length; i++)
    {
        number1[i] = buf[i + nul] * minus;
    }
    free(buf);
    left_operand->value = number1;
    return;
}


void minus_f(Operand *left_operand, Operand *right_operand)
{
	int j = 0, k = 0, i = 0, *buf, minus = 1, nul = 0, len_max = 0, less = 0;
    int *number1 = left_operand->value, *number2 = right_operand->value;

	if (number1[0] < 0 && number2[0] < 0)
	{
        j = left_operand->length;
        left_operand->length = right_operand->length;
        right_operand->length = j;

        buf = right_operand->value;
        right_operand->value = left_operand->value;
        left_operand->value = buf;
        number1 = left_operand->value;
        number2 = right_operand->value;
        for (i = 0; i < left_operand->length; i++)
		{
			number1[i] = abs(number1[i]);
		}
        for (i = 0; i < right_operand->length; i++)
		{
			number2[i] = abs(number2[i]);
		}
	}
	else if (number2[0] < 0)
	{
		for (i = 0; i < right_operand->length; i++)
        {
            number2[i] = abs(number2[i]);
        }
        plus_f(left_operand, right_operand);
		return;
	}
	else if (number1[0] < 0)
	{
		for (i = 0; i < right_operand->length; i++)
        {
            number2[i] *= -1;
        }
        plus_f(left_operand, right_operand);
		return;
	}
	if (left_operand->length == right_operand->length)
	{
		len_max = left_operand->length;
		for (i = 0; i < left_operand->length; i++)
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
            free(number2);
			free(number1);
			left_operand->value = (int*) calloc(1, sizeof(int));
            if(!left_operand->value)
            {
                printf ("ERROR. Allocation failure.");
                exit (-5);
            }
            left_operand->length = 1;
			return;
		}
	}
	if (right_operand->length > left_operand->length || less == 1)
    {
		less = 1;
		minus = -1;
        len_max = right_operand->length;
    }
    else if (right_operand->length < left_operand->length)
    {
		less = 2;
        len_max = left_operand->length;
    }
	buf = (int*) calloc(len_max, sizeof(int));
    if(!buf)
    {
        printf ("ERROR. Allocation failure.");
        exit (-5);
    }
	j = left_operand->length;
	k = right_operand->length;
	for (i = len_max - 1; i >= 0; i--)
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
    left_operand->length = len_max - nul;
    free(number1);
    free(number2);
	number1 = (int*) calloc(left_operand->length, sizeof(int));
    if(!number1)
    {
        printf ("ERROR. Allocation failure.");
        exit (-5);
    }
    for (i = 0; i < left_operand->length; i++)
    {
		number1[i] = buf[i + nul] * minus;
	}
    free(buf);
    left_operand->value = number1;
	return;
}


void mult_f(Operand *left_operand, Operand *right_operand)
{
    int j, i, *buf, minus = 1, nul = 0, *number1 = left_operand->value;
	int len3 = left_operand->length + right_operand->length, buffy = 0, *number2 = right_operand->value;
	if (number1[0] == 0 || number2[0] == 0)
	{
        free(number1);
        free(number2);
		left_operand->value = (int*) calloc(1, sizeof(int));
        if(!left_operand->value)
        {
            printf ("ERROR. Allocation failure.");
            exit (-5);
        }
        left_operand->length = 1;
		return;
	}
    if (number1[0] < 0)
	{
		minus *= -1;
		for (i = 0; i < left_operand->length; i++)
		{
			number1[i] = abs(number1[i]);
		}
	}
	if (number2[0] < 0)
	{
        minus *= -1;
		for (i = 0; i < right_operand->length; i++)
		{
			number2[i] = abs(number2[i]);
		}
	}
    buf = (int*) calloc(len3, sizeof(int));
    if(!buf)
    {
        printf ("ERROR. Allocation failure.");
        exit (-5);
    }
    for (i = right_operand->length - 1; i >= 0; i--)
	{
		buffy = right_operand->length - i;
		for (j = left_operand->length - 1; j >= 0; j--)
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
	}
	left_operand->length = len3 - nul;
    free(number1);
	number1 = (int*) calloc(left_operand->length, sizeof(int));
    if(!number1)
    {
        printf ("ERROR. Allocation failure.");
        exit (-5);
    }
	for (i = 0; i < left_operand->length; i++)
	{
		number1[i] = buf[i + nul] * minus;
	}
	free(buf);
    free(number2);
    left_operand->value = number1;
	return;
}

void spreader(Operand *left_operand, Operand *right_operand, char operator)
{
    int nul = 0, i, *number1 = left_operand->value, *number2 = right_operand->value;
    if (operator == '0')
    {
        return;
    }
    if (left_operand->length > 1)
    {
        for (i = 0; i < left_operand->length; i++)
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
            for (i = nul; i < left_operand->length; i++)
            {
                number1[i - nul] = number1[i];
            }
            left_operand->length -= nul;
            if (left_operand->length == 0)
            {
    			left_operand->value = (int*) calloc(1, sizeof(int));
                if(!left_operand->value)
                {
                    printf ("ERROR. Allocation failure.");
                    exit (-5);
                }
                left_operand->length++;
            }
            else
            {
                left_operand->value = (int*) realloc(left_operand->value, left_operand->length * sizeof(int));
                if(!left_operand->value)
                {
                    printf ("ERROR. Allocation failure.");
                    exit (-5);
                }
            }
        }
    }
    if (right_operand->length > 1)
    {
        nul = 0;
        for (i = 0; i < right_operand->length; i++)
        {
            if (number2[i] == 0)
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
            for (i = nul; i < right_operand->length; i++)
            {
                number2[i - nul] = number2[i];
            }
            right_operand->length -= nul;
            if (right_operand->length == 0)
            {
    			right_operand->value = (int*) calloc(1, sizeof(int));
                if(!right_operand->value)
                {
                    printf ("ERROR. Allocation failure.");
                    exit (-5);
                }
                right_operand->length++;
            }
            else
            {
                right_operand->value = (int*) realloc(right_operand->value, right_operand->length * sizeof(int));
                if(!right_operand->value)
                {
                    printf ("ERROR. Allocation failure.");
                    exit (-5);
                }
            }
        }
    }
    switch (operator)
    {
        case '+':
            plus_f(left_operand, right_operand);
            return;
        case '-':
            minus_f(left_operand, right_operand);
            return;
        case '*':
            mult_f(left_operand, right_operand);
            return;
        case '/':
            division_f(left_operand, right_operand);
            return;
        case '%':
            module_f(left_operand, right_operand);
            return;
        case '^':
            degree_f(left_operand, right_operand);
            return;
    }
}
