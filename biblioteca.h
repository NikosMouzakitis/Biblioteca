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

#endif // BIBLIOTECA_H_INCLUDED