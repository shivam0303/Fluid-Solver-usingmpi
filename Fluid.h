#ifndef FLUID_H
#define FLUID_H

template<int numF,typename T>
class Fluid
{
    public:
        int m1,m2,m3; //size of grid
        int n1,n2,n3;
        T *ptr;
        int sizegrid;
        int numElem;
        int nE1,nE2,nE3;
        int nB1,nB2,nB3;
        Fluid(int local_nx,int local_ny,int local_nz,int dummy_x=1,int dummy_y=1,int dummy_z=1)
        {
            m1=local_nx;
            m2=local_ny;
            m3=local_nz;

            n1=local_nx+2*dummy_x;
            n2=local_ny+2*dummy_y;
            n3=local_nz+2*dummy_z;

            nE1=local_nx+dummy_x-1;          // End coordinate
            nE2=local_ny+dummy_y-1;
            nE3=local_nz+dummy_z-1;

            nB1=dummy_x;                     // Beginning coordinate
            nB2=dummy_y;
            nB3=dummy_z;

            sizegrid=n1*n2*n3;               // // total grid size
            numElem=sizegrid*numF;
            ptr=(T*) malloc(numElem*sizeof(T));
        }



        int getIndex (int i, int j,int k, int a) const
        {
            return ((k*n2+j)*n1 + i)*numF +a;
        }

        T operator()(const int i1,int i2,int i3,int a)const{return ptr[getIndex(i1,i2,i3,a)];}
        T& operator()(const int i1,int i2,int i3,int a){return ptr[getIndex(i1,i2,i3,a)];}

};

#endif // FLUID_H
