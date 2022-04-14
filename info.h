#ifndef INFO_H_INCLUDED
#define INFO_H_INCLUDED

#include "mpi.h"

enum nebRank
{
 NEB_ZERO_ZERO_ZERO,
 NEB_P1_ZERO_ZERO ,
 NEB_M1_ZERO_ZERO ,
 NEB_ZERO_P1_ZERO ,
 NEB_ZERO_M1_ZERO ,
 NEB_ZERO_ZERO_P1 ,
 NEB_ZERO_ZERO_M1
};

struct info
{
    info(int n1, int n2, int n3, int wrap1=1, int wrap2=1, int wrap3=1, int reorderGiven=1)
    {
        dim[0]=n1;   dim[1]=n2;   dim[2]=n3;
        period[0]=wrap1;   period[1]=wrap2;   period[2]=wrap3;
        reorder=reorderGiven;

        MPI_Cart_create(MPI_COMM_WORLD, ndims, dim, period, reorder, &comm);
        MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

        MPI_Cart_coords(comm, my_rank, ndims, coord);
        for(int i=0;i<7;i++)
        {
            nList[i]=-300;
        }
    }
    MPI_Comm comm;
    int dim[3],ndims=3;
    int reorder;
    int period[3];
    int my_rank;
    int nList[7];
    int coord[3];

    void GetList()
    {
        int disp = 1;
        nList[NEB_ZERO_ZERO_ZERO] = my_rank;
        MPI_Cart_shift(comm,0,disp,&nList[NEB_M1_ZERO_ZERO],&nList[NEB_P1_ZERO_ZERO]);
        MPI_Cart_shift(comm,1,disp,&nList[NEB_ZERO_M1_ZERO],&nList[NEB_ZERO_P1_ZERO]);
        MPI_Cart_shift(comm,2,disp,&nList[NEB_ZERO_ZERO_M1],&nList[NEB_ZERO_ZERO_P1]);
        //printf("rank = %d\t NEB(-X) = %d\t NEB(+X)=%d\t NEB(-Y)=%d\t NEB(+Y)=%d\t NEB(-Z)=%d\t NEB(+Z)=%d\n",nList[NEB_ZERO_ZERO_ZERO],nList[NEB_M1_ZERO_ZERO],nList[NEB_P1_ZERO_ZERO],nList[NEB_ZERO_M1_ZERO],nList[NEB_ZERO_P1_ZERO],nList[NEB_ZERO_ZERO_M1],nList[NEB_ZERO_ZERO_P1]);

    }
};

#endif // INFO_H_INCLUDED
