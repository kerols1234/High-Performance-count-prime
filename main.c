#include <stdio.h>
#include <string.h>
#include "mpi.h"

int isPrime(int n)
{
    if (n <= 1)
        return 0;

    if (n <= 3 || n == 5)
        return 1;

    if (n % 2 == 0 || n % 3 == 0 || n % 5 == 0)
        return 0;

    int i;
    for (i = 7; i * i <= n; i = i + 2)
        if (n % i == 0)
            return 0;

    return 1;
}

int main(int argc, char * argv[])
{
    int c = 0,l,u;
    int my_rank;
    int p;

    MPI_Status status;

    MPI_Init( &argc, &argv );

    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    MPI_Comm_size(MPI_COMM_WORLD, &p);

    if( my_rank != 0)
    {
        int message[2];
        MPI_Recv(message, 2, MPI_INT, 0, 0, MPI_COMM_WORLD, &status );

        l = message[0];
        u = message[1];

        if(l <= 2)
            c++;

        if(l % 2 == 0)
            l++;

        int i = l;

        for(; i<= u; i+=2)
            c += isPrime(i);

        printf("Total number of prime numbers in P%d is: %d",my_rank,c);
        MPI_Send( c, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else
    {
        scanf("%d %d",&l,&u);

        int source,x,f,v=0;

        x = u-l+1;
        f = x/p-1;

        if((p-1)=> x)
            f = 1;
        else if(x%(p-1) != 0)
            v = x%(p-1);

        for( source = 1; source < p ; source++)
        {
            int message[2];
            message[0] = l;
            l+=f;
            message[1] = l-1;
            MPI_Send( message, 2, MPI_INT, source, 0, MPI_COMM_WORLD);
        }

        if(v != 0)
        {
            for(source = l; source <= u ; source++)
                c += isPrime(i);

            printf("Total number of prime numbers in P%d is: %d",my_rank,c);
        }

        for( source = 1; source < p ; source++)
        {
            MPI_Recv(x, 1, MPI_INT, source, 0, MPI_COMM_WORLD, &status );
            c+=x;
        }
        printf("Total number of prime numbers is: %d",c);
    }

    MPI_Finalize();

    return 0;
}
//2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97
