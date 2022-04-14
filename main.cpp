#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef double my_var;   int const numF=27;
const int nx=100,ny=100,nz=100;

my_var U0=0.05;

my_var *XP_send, *XP_recv, *YP_send, *YP_recv, *ZP_send, *ZP_recv, *XM_send, *XM_recv, *YM_send, *YM_recv, *ZM_send, *ZM_recv;

#include "D3Q27.h"
#include "Fluid.h"
#include "initialisation.h"
#include "macroscopic.h"
#include "feq.h"
#include "collision.h"
#include "streaming.h"
#include "info.h"
#include "communication.h"
#include "print.c"
#include "pack.h"
#include "mpi.h"

using namespace std;

my_var* dyn_mem_alloc(int m1, int m2)
{
  my_var *temp= new my_var[m1*m2*9];
  return temp;
}

void Pack_dist(int n1, int n2, int n3)
{
  XP_send = dyn_mem_alloc(n2,n3);
  XP_recv = dyn_mem_alloc(n2,n3);
  YP_send = dyn_mem_alloc(n1,n3);
  YP_recv = dyn_mem_alloc(n1,n3);
  ZP_send = dyn_mem_alloc(n1,n2);
  ZP_recv = dyn_mem_alloc(n1,n2);
  XM_send = dyn_mem_alloc(n2,n3);
  XM_recv = dyn_mem_alloc(n2,n3);
  YM_send = dyn_mem_alloc(n1,n3);
  YM_recv = dyn_mem_alloc(n1,n3);
  ZM_send = dyn_mem_alloc(n1,n2);
  ZM_recv = dyn_mem_alloc(n1,n2);
}

int main(int argc, char **argv)
{
    int myRank, s;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myRank);
    MPI_Comm_size(MPI_COMM_WORLD, &s);

    int t,time=100;
    int px,py,pz;

    px=2;   py=2;   pz=1;

    int dummy_x,dummy_y,dummy_z;
    dummy_x=1;  dummy_y=1;  dummy_z=1;

    int local_nx = nx/px;
    int local_ny = ny/py;
    int local_nz = nz/pz;

    Fluid<numF,my_var> f(local_nx,local_ny,local_nz,dummy_x,dummy_y,dummy_z);

    info info3d(px,py,pz,1,1,1,1);
    info3d.GetList();

    MPI_Request request1[4], request2[4], request3[4];
    MPI_Status status1[4], status2[4], status3[4];

    initialisation<numF,my_var> obj(f,info3d.coord,1,0,0,0);
    Pack_dist(f.n1,f.n2,f.n3);

    for(t=1;t<time;t++)
    {
        collision(f);

    recvComm_X(myRank, info3d.nList, request1, XP_recv, XM_recv, f.n1,f.n2,f.n3, info3d);
    pack_Xdist(f, XP_send, XM_send);
    sendComm_X(myRank, info3d.nList, request1, XP_send, XM_send, f.n1,f.n2,f.n3, info3d);
    MPI_Waitall(4, request1, status1);
    unpack_Xdist(f, XP_recv, XM_recv);

    recvComm_Y(myRank, info3d.nList, request2, YP_recv, YM_recv, f.n1,f.n2,f.n3, info3d);
    pack_Ydist(f, YP_send, YM_send);
    sendComm_Y(myRank, info3d.nList, request2, YP_send, YM_send, f.n1,f.n2,f.n3, info3d);
    MPI_Waitall(4, request2, status2);
    unpack_Ydist(f, YP_recv, YM_recv);

    recvComm_Z(myRank, info3d.nList, request3, ZP_recv, ZM_recv, f.n1,f.n2,f.n3, info3d);
    pack_Zdist(f, ZP_send, ZM_send);
    sendComm_Z(myRank, info3d.nList, request3, ZP_send, ZM_send,f.n1,f.n2,f.n3, info3d);
    MPI_Waitall(4, request3, status3);
    unpack_Zdist(f, ZP_recv, ZM_recv);

        streaming(f);

int local_x1 = 1 + info3d.coord[0]*local_nx;             // X global coordinates
int local_x2 = local_x1 + (local_nx-1);

int local_y1 = 1 + info3d.coord[1]*local_ny;
int local_y2 = local_y1 + (local_ny-1);

int local_z1 = 1 + info3d.coord[2]*local_nz;
int local_z2 = local_z1 + (local_nz-1);


//printf("Rank= %d, global_x=%d %d, global_y=%d %d, global_z=%d %d\n", myRank,local_x1,local_x2,local_y1,local_y2,local_z1,local_z2);

    int ux_x=20,ux_y=25,ux_z=25;
    if((ux_x>=local_x1 && ux_x <= local_x2) && (ux_y>=local_y1 && ux_y <= local_y2) && (ux_z>=local_z1 && ux_z <= local_z2))
    {
        cout<<"Rank of processor is : "<<myRank<<" ,";
        print(f,t,ux_x,ux_y,ux_z,0);
    }
    }

     free(f.ptr);
     MPI_Finalize();

    return 0;
}
