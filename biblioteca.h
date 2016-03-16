#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED

#include <math.h>


void print_binary(int num){
   
    int i,n,rm;
    i = num;

    if(i == 0)
        printf("0");

    else if ( i == 1)
            printf("1");
    else
    {
        for( n = 0; pow(2.0,n) <= i; n++)
                        ;

        n--;

        while(n >= 0){

            if( i >= pow(2.0,n))
            {
                printf("1");
                i = i % (int ) pow(2.0,n);
                n--;
            }
            else if (i < pow(2.0,n))
            {

                printf("0");
                n--;
            }

        }

    }

}


int isPrime(int n) // if n prime returns value of n,else returns zero(0)
{
   int i, count = 0;

   for(i = 2; i < n; i++)

      if(n % i )
        count += 1;
   if(count == n - 2)
        return (n);
   else
    return (0) ;
}

int combo1(int p1,int p2) // checks out if the sum of two integers(primes preferable) minus 1 is a prime.
{

    int sum= p1 + p2 - 1 ;
    int i;
    if(isPrime(sum))
        return (1) ;
    else
        return (0) ;

}

int bi_abs (int a)
{
    if (a < 0)
        a = -a;
    return (a) ;
}

void  quadratic_equation(int a,int b,int c)
  {
          int discr = b*b - 4*a*c ;
          
          if(discr < 0)
                  printf("No solutions availiable \n");
          else
                  if (discr == 0)
                          printf(" One solution twice : %.2f \n",(float) (-b ) / (2*a));
                  else
                  {
                          float m,n ;
                          m = ((-b) + sqrt(discr)) / 2*a ;
                          n = ((-b) - sqrt(discr)) / 2*a ;
                          printf("Two solutions : %.2f , %.2f \n",m,n);
                  }
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
