#ifndef INITIALISATION_H
#define INITIALISATION_H

template<int numF,typename T>
class initialisation
{
    public:
        my_var t;
        my_var feq[27];
        my_var rho0 = 1.0;

        my_var ux,uy,uz,u2,rho;
        initialisation(Fluid<numF,T> &f)
        {
            for (int i=0;i<f.n1;i++)
                {
                    for (int j=0;j<f.n2;j++)
                        {
                            for (int k=0;k<f.n3;k++)
                            {
                                for (int a=0;a<numF;a++)
                                    {
                                        f(i,j,k,a) = weight[a]*rho0;
                                    }

                            }
                        }
                }
        }
        initialisation(Fluid<numF,T> &f,int *coord,my_var r,my_var u_x,my_var u_y,my_var u_z)
        {
            ux=u_x;
            uy=u_y;
            uz=u_z;
            rho=r;

            float pi = acos(-1);
            for(int i=0;i<f.m1+2;i++)
                {
                    for(int j=0;j<f.m2+2;j++)
                        {
                            int local_nx=f.m1;
                            int local_ny=f.m2;
                            int local_nz=f.m3;
                            for(int k=0;k<f.m3+2;k++)
                                {
ux= U0*sin((coord[0]*local_nx+i)*(2*pi/nx))*(cos(3*(coord[1]*local_ny+j)*(2*pi/ny))*cos((coord[2]*local_nz+k)*(2*pi/nz)) - cos((coord[1]*local_ny+j)*(2*pi/ny))*cos(3*(coord[2]*local_nz+k)*(2*pi/nz)));
uy= U0*sin((coord[1]*local_ny+j)*(2*pi/ny))*(cos(3*(coord[2]*local_nz+k)*(2*pi/nz))*cos((coord[0]*local_nx+i)*(2*pi/nx)) - cos((coord[2]*local_nz+k)*(2*pi/nz))*cos(3*(coord[0]*local_nx+i)*(2*pi/nx)));
uz= U0*sin((coord[2]*local_nz+k)*(2*pi/nz))*(cos(3*(coord[0]*local_nx+i)*(2*pi/nx))*cos((coord[1]*local_ny+j)*(2*pi/ny)) - cos((coord[0]*local_nx+i)*(2*pi/nx))*cos(3*(coord[1]*local_ny+j)*(2*pi/ny)));
u2=ux*ux+uy*uy+uz*uz;
                                    for(int a=0;a<27;a++)
                                        {
                                            t =  ex[a]*ux + ey[a]*uy + ez[a]*uz;
                                            u2 = ux*ux + uy*uy + uz*uz;
                                            f(i,j,k,a) = weight[a]*rho0*(1 + 3*t + 4.5*t*t - 1.5*u2);

                                        }
                                }

                        }
                }
        }

};

#endif // INITIALISATION_H
