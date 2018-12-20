typedef enum
{
	FALSE, TRUE
}Boolean;

Boolean check_first_digit(char *);
Boolean check_length(char *);
Boolean check_integer(char *);
Boolean check_digit(char *);

Boolean check_first_digit(char *tc_num)
{
    if(tc_num[0] - '0' == 0)
        return FALSE;

    return TRUE;
}

Boolean check_length(char *tc_num)
{
    short cnt = 0;

    for( ; tc_num[cnt] != '\0'; cnt++);

    if(cnt != 11)
        return FALSE;

    return TRUE;
}

Boolean check_integer(char *tc_num)
{
    for(short i = 0; tc_num[i] != '\0'; i++)
        if(tc_num[i] - '0' < 0 || tc_num[i] - '0' > 9)
            return FALSE;

    return TRUE;
}

Boolean check_digit(char *tc_num)
{
    int num1 = 0, num2 = 0;

    for(short i = 0; i < 9; i++)
    {
        if(i % 2 == 0)
            num1 += tc_num[i] - '0';
        else
            num2 += tc_num[i] - '0';
    }

    int digit_10 = ((num1 * 7) - num2) % 10;
    int digit_11 = 0;

    for(short i = 0; i < 9; i++)
            digit_11 += tc_num[i] - '0';

    digit_11 = (digit_10 + digit_11) % 10;

    if(tc_num[9] - '0' != digit_10 || tc_num[10] - '0' != digit_11)
        return FALSE;

    return TRUE;
}