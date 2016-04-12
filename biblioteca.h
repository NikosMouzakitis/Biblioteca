#ifndef BIBLIOTECA_H_INCLUDED
#define BIBLIOTECA_H_INCLUDED

#include <math.h>


// returns a pointer (integer ) to the space allocated for the matrice.

int * create_matrice(int columns,int rows)
{
    int *mat;
    mat = malloc( columns *rows *sizeof(int));


    return mat;
}


// arguments is the pointer to the matrice,columns and rows.prints the output to the screen.

void print_matrice(int *mat,int columns,int rows)
{
    int i,j;
    printf("Printing the matrice: \n");

    for(i=0; i<columns; i++)
    {
        for(j=0; j<rows; j++)
        {
            printf("%d\t",*(mat+i+j));
        }
        printf("\n");
    }

}

// initializes the matrice with random numbers.

void random_init(int *mat,int columns,int rows)
{
    int i,j;

    for(i=0; i<columns; i++)

        for(j=0; j<rows; j++)

            *(mat+i+j) = rand()%10 + 1;
}


// liberating the space allocated to the matrice.

void free_mat(int *mat)
{

    free(mat);

}


//prints out the binary form of an integer.
void print_binary(int num) {

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

        while(n >= 0) {

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


//If argument is a prime it returns itself,otherwise returns 0.
int isPrime(int n)
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


// checks out if the sum of two integers(primes preferable) minus 1 is a prime.
int combo1(int p1,int p2){

    int sum= p1 + p2 - 1 ;
    int i;
    if(isPrime(sum))
        return (1) ;
    else
        return (0) ;

}


//absolute value implementation.
int bi_abs (int a)
{
    if (a < 0)
        a = -a;
    return (a) ;
}


//prints in stdout the solutions of a quadratic equation.
void  quadratic_equation(int a,int b,int c)
{
    int discr = b*b - 4*a*c ;

    if(discr < 0)
        printf("No solutions availiable \n");
    else if (discr == 0)
        printf(" One solution twice : %.2f \n",(float) (-b ) / (2*a));
    else
    {
        float m,n ;
        m = ((-b) + sqrt(discr)) / 2*a ;
        n = ((-b) - sqrt(discr)) / 2*a ;
        printf("Two solutions : %.2f , %.2f \n",m,n);
    }
}


// absolute value implementation for doubles.
double bi_abs_d (double a)
{
    if (a < 0)
        a = -a;
    return (a) ;
}


// implemetation of "strlen" function.
int bi_strlen(char *str)
{
    int counter = 0;
    for(counter = 0 ; str[counter]!='\0' ; counter ++)
        ;
    return (counter) ;
}


// implementation of "strcmp" function.
int bi_strcmp(char *str1,char *str2)
{
    int i;
    if(bi_strlen(str1) != bi_strlen(str2))
        return (-1);
    for(i = 0; i < bi_strlen(str1); i++)
    {
        if(str1[i] != str2[i])
            return (-1);
    }
    return (0);
}


#endif // BIBLIOTECA_H_INCLUDED1
