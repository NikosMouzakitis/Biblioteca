#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED

int bi_abs (int a)
{
    if (a < 0)
        a = -a;
    return (a) ;
}

double bi_abs_d (double a)
{
    if (a < 0)
        a = -a;
    return (a) ;
}

int bi_strlen(char *str)
{
    int counter = 0;
    for(counter = 0 ; str[counter]!='\0' ;counter ++)
        ;
        return (counter) ;
}

int bi_strcmp(char *str1,char *str2)
{
    int i;
    if(bi_strlen(str1) != bi_strlen(str2))
        return (-1);
    for(i = 0; i < bi_strlen(str1);i++)
    {
        if(str1[i] != str2[i])
            return (-1);
    }
    return (0);
}

#endif // BIBLIOTECA_H_INCLUDED1