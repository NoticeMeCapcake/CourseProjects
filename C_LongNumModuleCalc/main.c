#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "source.c"

int main()
{
    FILE *input, *output;
    char *symb, *point, operator = '0', in_name[200];
    int len = 0, j, flag = 0, minus_flag = 1, lines = 0;
    int *module_arr, module = 0, module_flag = 0, module_len = 0, error = 0;
    Operand *left_operand;
    Operand *right_operand;
    left_operand = (Operand*) calloc(1, sizeof(Operand));
    if(!left_operand)
    {
        printf ("ERROR. Allocation failure.");
        exit (-5);
    }
    right_operand = (Operand*) calloc(1, sizeof(Operand));
    if(!right_operand)
    {
        printf ("ERROR. Allocation failure.");
        exit (-5);
    }
    left_operand->length = 0;
    right_operand->length = 0;
    right_operand->value = (int*) calloc(1, sizeof(int));
    if(!right_operand->value)
    {
        printf ("ERROR. Allocation failure.");
        exit (-5);
    }
    left_operand->value = (int*) calloc(1, sizeof(int));
    if(!left_operand->value)
    {
        printf ("ERROR. Allocation failure.");
        exit (-5);
    }
    printf("Author: Kozlov Danila Olegovich\n");
    printf("Group: M8O-111B-20\n");
    printf("Teacher: Egorova Evgenia Kirillovna\n");
    printf("Cathedra: 813\n");
    printf("University: NIU MAI\n");
    printf("Integer calculator with big numbers.\n");
    printf("Calculates expressions from inputed text file.\n");
    printf("Creates or rewrites text file with results.\n");

    while (1)
    {
        printf("Enter input file name:\n");
        scanf("%199s", in_name);
        input = fopen(in_name, "r");
        if (input == NULL)
        {
            printf("ERROR. Can not open file.\n");
            printf("Please reinput.\n");
            continue;
        }
        break;
    }
    while (1)
    {
        printf("Enter output file name:\n");
        scanf("%199s", in_name);
        output = fopen(in_name, "w");
        if (output == NULL)
        {
            printf("ERROR. Can not open file.\n");
            printf("Please reinput.\n");
            continue;
        }
        break;
    }
    symb = (char*) calloc(1, sizeof(char));
    if(!symb)
    {
        printf ("ERROR. Allocation failure.");
        exit (-5);
    }
    module_arr = (int*) calloc(1, sizeof(int));
    if(!module_arr)
    {
        printf ("ERROR. Allocation failure.");
        exit (-5);
    }
    while(!feof(input))
    {
        fread(symb, sizeof(char), 1, input);
        if (feof(input))
        {
            fseek(input, 1, SEEK_END);
            fread(symb, sizeof(char), 1, input);
            if (symb[0] == '\n')
            {
                break;
            }
            else
            {
                lines++;
                if (len == 0 || error == 1 || module_flag == 0)
                {
                    error = 1;
                    fprintf(output, "%d: Encountered an ERROR\n", lines);
                    if (module_flag != 0)
                    {
                        free(module_arr);
                    }
                }
                else
                {
                    if (flag == 0)
                    {
                        left_operand->length = len;
                    }
                    else
                    {
                        right_operand->length = len;
                    }
                    spreader(left_operand, right_operand, operator);
                    if (left_operand->length < 0)
                    {
                        error = 1;
                    }
                    right_operand->length = module_len;
                    right_operand->value = module_arr;
                    if (error != 1)
                    {
                        spreader(left_operand, right_operand, '%');
                        fprintf(output, "%d: Answer - %d", lines, (left_operand->value)[0]);
                        for (j = 1; j < left_operand->length; j++)
                        {
                            fprintf(output, "%d", abs((left_operand->value)[j]));
                        }
                        fprintf(output, "\n");
                    }
                    else
                    {
                        fprintf(output, "%d: Encountered an ERROR\n", lines);
                        free(module_arr);
                    }
                }

                module = 0;
                module_len = 0;
                len = 0;
                flag = 0;
                module = 0;
                module_flag = 0;
                minus_flag = 1;
                right_operand->length = 0;
                left_operand->length = 0;
                free(left_operand->value);
                left_operand->value = (int*) calloc(1, sizeof(int));
                if(!left_operand->value)
                {
                    printf ("ERROR. Allocation failure.");
                    exit (-5);
                }
                error = 0;
                operator = '0';
                continue;
            }
        }
        if (symb[0] >= '0' && symb[0] <= '9')
        {
            if (error == 1)
            {
                continue;
            }
            if (flag == 0)
            {
                if (len > 5 && module_flag == 0)
                {
                    error = 1;
                    continue;
                }
                left_operand->value = realloc(left_operand->value, (len + 1) * sizeof(int));
                if(!left_operand->value)
                {
                    printf ("ERROR. Allocation failure.");
                    exit (-5);
                }
                (left_operand->value)[len] = strtol(symb, &point, 10) * minus_flag;
                len++;
                continue;
            }
            else
            {
                right_operand->value = realloc(right_operand->value, (len + 1) * sizeof(int));
                if(!right_operand->value)
                {
                    printf ("ERROR. Allocation failure.");
                    exit (-5);
                }
                (right_operand->value)[len] = strtol(symb, &point, 10) * minus_flag;
                len++;
                continue;
            }
        }
        else
        {
            switch (symb[0])
            {
                case ' ':
                    continue;
                case ':':
                    if (module_flag == 0 && error == 0 && len != 0 && minus_flag == 1 && len < 6)
                    {
                         module_arr = (int*) calloc(1, sizeof(int));
                         if(!module_arr)
                         {
                             printf ("ERROR. Allocation failure.");
                             exit (-5);
                         }
                        for (j = 0; j < len; j++)
                        {
                            module *= 10;
                            module_len++;
                            module += (left_operand->value)[j];
                            module_arr = realloc(module_arr, (j + 1) * sizeof(int));
                            if(!module_arr)
                            {
                                printf ("ERROR. Allocation failure.");
                                exit (-5);
                            }
                            module_arr[j] = (left_operand->value)[j];
                        }
                        if (module < 2 || module > 65536)
                        {
                            error = 1;
                            continue;
                        }
                        len = 0;
                        free(left_operand->value);
                        left_operand->value = (int*) calloc(1, sizeof(int));
                        if(!left_operand->value)
                        {
                            printf ("ERROR. Allocation failure.");
                            exit (-5);
                        }
                        module_flag = 1;
                        continue;
                    }
                    else
                    {
                        error = 1;
                        continue;
                    }
                case '+':
                    if (len == 0 || module == 0 || error == 1)
                    {
                        error = 1;
                        continue;
                    }
                    if (flag == 0)
                    {
                        left_operand->length = len;
                    }
                    else
                    {
                        right_operand->length = len;
                    }
                    spreader(left_operand, right_operand, operator);
                    if (left_operand->length < 0)
                    {
                        error = 1;
                    }
                    len = 0;
                    flag = 1;
                    operator = '+';
                    minus_flag = 1;
                    right_operand->value = (int*) calloc(1, sizeof(int));
                    if(!right_operand->value)
                    {
                        printf ("ERROR. Allocation failure.");
                        exit (-5);
                    }
                    continue;
                case '-':
                    if (len == 0 || error == 1 || module_flag == 0)
                    {
                        error = 1;
                        continue;
                    }
                    if (flag == 0)
                    {
                        left_operand->length = len;
                    }
                    else
                    {
                        right_operand->length = len;
                    }
                    spreader(left_operand, right_operand, operator);
                    if (left_operand->length < 0)
                    {
                        error = 1;
                    }
                    len = 0;
                    flag = 1;
                    operator = '-';
                    minus_flag = 1;
                    right_operand->value = (int*) calloc(1, sizeof(int));
                    if(!right_operand->value)
                    {
                        printf ("ERROR. Allocation failure.");
                        exit (-5);
                    }
                    continue;
                case '*':
                    if (len == 0 || error == 1 || module_flag == 0)
                    {
                        error = 1;
                        continue;
                    }
                    if (flag == 0)
                    {
                        left_operand->length = len;
                    }
                    else
                    {
                        right_operand->length = len;
                    }
                    spreader(left_operand, right_operand, operator);
                    if (left_operand->length < 0)
                    {
                        error = 1;
                    }
                    len = 0;
                    flag = 1;
                    operator = '*';
                    minus_flag = 1;
                    right_operand->value = (int*) calloc(1, sizeof(int));
                    if(!right_operand->value)
                    {
                        printf ("ERROR. Allocation failure.");
                        exit (-5);
                    }
                    continue;
                case '/':
                    if (len == 0 || error == 1 || module_flag == 0)
                    {
                        error = 1;
                        continue;
                    }
                    if (flag == 0)
                    {
                        left_operand->length = len;
                    }
                    else
                    {
                        right_operand->length = len;
                    }
                    spreader(left_operand, right_operand, operator);
                    if (left_operand->length < 0)
                    {
                        error = 1;
                    }
                    len = 0;
                    flag = 1;
                    operator = '/';
                    minus_flag = 1;
                    right_operand->value = (int*) calloc(1, sizeof(int));
                    if(!right_operand->value)
                    {
                        printf ("ERROR. Allocation failure.");
                        exit (-5);
                    }
                    continue;
                case '^':
                    if (len == 0 || error == 1 || module_flag == 0)
                    {
                        error = 1;
                        continue;
                    }
                    if (flag == 0)
                    {
                        left_operand->length = len;
                    }
                    else
                    {
                        right_operand->length = len;
                    }
                    spreader(left_operand, right_operand, operator);
                    if (left_operand->length < 0)
                    {
                        error = 1;
                    }
                    len = 0;
                    flag = 1;
                    operator = '^';
                    minus_flag = 1;
                    right_operand->value = (int*) calloc(1, sizeof(int));
                    if(!right_operand->value)
                    {
                        printf ("ERROR. Allocation failure.");
                        exit (-5);
                    }
                    continue;
                case '%':
                    if (len == 0 || error == 1 || module_flag == 0)
                    {
                        error = 1;
                        continue;
                    }
                    if (flag == 0)
                    {
                        left_operand->length = len;
                    }
                    else
                    {
                        right_operand->length = len;
                    }
                    spreader(left_operand, right_operand, operator);
                    if (left_operand->length < 0)
                    {
                        error = 1;
                    }
                    len = 0;
                    flag = 1;
                    minus_flag = 1;
                    operator = '%';
                    right_operand->value = (int*) calloc(1, sizeof(int));
                    if(!right_operand->value)
                    {
                        printf ("ERROR. Allocation failure.");
                        exit (-5);
                    }
                    continue;
                case '~':
                    if (error == 1 || module_flag == 0)
                    {
                        error = 1;
                        continue;
                    }
                    minus_flag = -1;
                    continue;
                case '\n':
                    lines++;
                    if (len == 0 || error == 1 || module_flag == 0)
                    {
                        error = 1;
                        fprintf(output, "%d: Encountered an ERROR\n", lines);
                        if (module_flag != 0)
                        {
                            free(module_arr);
                        }
                    }
                    else
                    {
                        if (flag == 0)
                        {
                            left_operand->length = len;
                        }
                        else
                        {
                            right_operand->length = len;
                        }
                        spreader(left_operand, right_operand, operator);
                        if (left_operand->length < 0)
                        {
                            error = 1;
                        }
                        right_operand->length = module_len;
                        right_operand->value = module_arr;
                        if (error != 1)
                        {
                            spreader(left_operand, right_operand, '%');
                            fprintf(output, "%d: Answer - %d", lines, (left_operand->value)[0]);
                            for (j = 1; j < left_operand->length; j++)
                            {
                                fprintf(output, "%d", abs((left_operand->value)[j]));
                            }
                            fprintf(output, "\n");
                        }
                        else
                        {
                            fprintf(output, "%d: Encountered an ERROR\n", lines);
                            free(module_arr);
                        }
                    }
                    module = 0;
                    module_len = 0;
                    len = 0;
                    flag = 0;
                    module = 0;
                    module_flag = 0;
                    minus_flag = 1;
                    right_operand->length = 0;
                    left_operand->length = 0;
                    free(left_operand->value);
                    left_operand->value = (int*) calloc(1, sizeof(int));
                    if(!left_operand->value)
                    {
                        printf ("ERROR. Allocation failure.");
                        exit (-5);
                    }
                    error = 0;
                    operator = '0';
                    continue;
                default:
                    error = 1;
                    continue;
            }
        }
    }
    printf("Program fininshed.\n");
    fclose(input);
    fclose(output);
    return 0;
}
