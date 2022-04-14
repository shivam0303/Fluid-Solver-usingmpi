#ifndef MACROSCOPIC_H
#define MACROSCOPIC_H
template <int numF,typename T>
void macroscopic(Fluid<numF,T> &f,my_var &rho,my_var &ux,my_var &uy,my_var &uz,int i,int j,int k)
        {
            rho=0.0;
            ux=0.0;
            uy=0.0;
            uz=0.0;
              for (int a=0;a<numF;a++)
                    {
                        rho += f(i,j,k,a);
                        ux += f(i,j,k,a)*ex[a];
                        uy += f(i,j,k,a)*ey[a];
                        uz+= f(i,j,k,a)*ez[a];
                    }
                    ux /= rho;
                    uy /= rho;
                    uz /= rho;
        }





#endif // MACROSCOPIC_H
