#ifndef COMMUNICATION_H_INCLUDED
#define COMMUNICATION_H_INCLUDED

void recvComm_X(int myRank, int *myneighbours, MPI_Request *request, my_var *DataReceive_XP, my_var *DataReceive_XM, int m1, int m2, int m3, info info3d)
{
 int dataSize_PlaneYZ = 9*m2*m3;
 int tag = 0;
 MPI_Irecv(DataReceive_XP, dataSize_PlaneYZ, MPI_DOUBLE, myneighbours[NEB_M1_ZERO_ZERO], tag, MPI_COMM_WORLD, &request[0]);
 tag = 1;
 MPI_Irecv(DataReceive_XM, dataSize_PlaneYZ, MPI_DOUBLE, myneighbours[NEB_P1_ZERO_ZERO], tag, MPI_COMM_WORLD, &request[1]);
}

void sendComm_X(int myRank,  int *myneighbours, MPI_Request *request, my_var *DataSend_XP, my_var *DataSend_XM, int m1, int m2, int m3, info info3d)
{
 int dataSize_PlaneYZ = 9*m2*m3;
 int tag = 0;
 MPI_Isend(DataSend_XP, dataSize_PlaneYZ, MPI_DOUBLE, myneighbours[NEB_P1_ZERO_ZERO], tag, MPI_COMM_WORLD, &request[2]);
 tag  = 1;
 MPI_Isend(DataSend_XM, dataSize_PlaneYZ, MPI_DOUBLE, myneighbours[NEB_M1_ZERO_ZERO], tag, MPI_COMM_WORLD, &request[3]);
}

void recvComm_Y(int myRank, int *myneighbours, MPI_Request *request, my_var *DataReceive_YP, my_var *DataReceive_YM, int m1, int m2, int m3, info info3d)
{
 int dataSize_PlaneXZ = 9*m1*m3;
 int tag = 0;
 MPI_Irecv(DataReceive_YP, dataSize_PlaneXZ, MPI_DOUBLE, myneighbours[NEB_ZERO_M1_ZERO], tag, MPI_COMM_WORLD, &request[0]);
 tag = 1;
 MPI_Irecv(DataReceive_YM, dataSize_PlaneXZ, MPI_DOUBLE, myneighbours[NEB_ZERO_P1_ZERO], tag, MPI_COMM_WORLD, &request[1]);
}

void sendComm_Y(int myRank,  int *myneighbours, MPI_Request *request, my_var *DataSend_YP, my_var *DataSend_YM, int m1, int m2, int m3,info info3d)
{
 int dataSize_PlaneXZ = 9*m1*m3;
 int tag = 0;
 MPI_Isend(DataSend_YP, dataSize_PlaneXZ, MPI_DOUBLE, myneighbours[NEB_ZERO_P1_ZERO], tag, MPI_COMM_WORLD, &request[2]);
 tag  = 1;
 MPI_Isend(DataSend_YM, dataSize_PlaneXZ, MPI_DOUBLE, myneighbours[NEB_ZERO_M1_ZERO], tag, MPI_COMM_WORLD, &request[3]);
}

void recvComm_Z(int myRank, int *myneighbours, MPI_Request *request, my_var *DataReceive_ZP, my_var *DataReceive_ZM, int m1, int m2, int m3, info info3d)
{
 int dataSize_PlaneXY = 9*m1*m2;
 int tag = 0;
 MPI_Irecv(DataReceive_ZP, dataSize_PlaneXY, MPI_DOUBLE, myneighbours[NEB_ZERO_ZERO_M1], tag, MPI_COMM_WORLD, &request[0]);
 tag = 1;
 MPI_Irecv(DataReceive_ZM, dataSize_PlaneXY, MPI_DOUBLE, myneighbours[NEB_ZERO_ZERO_P1], tag, MPI_COMM_WORLD, &request[1]);
}

void sendComm_Z(int myRank,  int *myneighbours, MPI_Request *request, my_var *DataSend_ZP, my_var *DataSend_ZM, int m1, int m2, int m3, info info3d)
{
 int dataSize_PlaneXY = 9*m1*m2;
 int tag = 0;
 MPI_Isend(DataSend_ZP, dataSize_PlaneXY, MPI_DOUBLE, myneighbours[NEB_ZERO_ZERO_P1], tag, MPI_COMM_WORLD, &request[2]);
 tag  = 1;
 MPI_Isend(DataSend_ZM, dataSize_PlaneXY, MPI_DOUBLE, myneighbours[NEB_ZERO_ZERO_M1], tag, MPI_COMM_WORLD, &request[3]);
}


#endif // COMMUNICATION_H_INCLUDED
