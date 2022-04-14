#ifndef COLLISION_H
#define COLLISION_H

template <int numF,typename T>

void collision(Fluid<numF,T> &f)
{
    my_var rho,ux,uy,uz;
    float tau = 0.6;
    my_var feq[numF];
    for (int i=f.nB1;i<=f.nE1;i++)
        {
            for (int j=f.nB2;j<=f.nE2;j++)
                {
                    for (int k=f.nB3;k<=f.nE3;k++)
                    {
                        macroscopic(f,rho,ux,uy,uz,i,j,k);
                        fequilibrium(feq,rho,ux,uy,uz);
                        for (int a=0;a<numF;a++)
                            {
                                    f(i,j,k,a) = f(i,j,k,a) - (f(i,j,k,a) -feq[a])/tau;
                            }
                    }
                }
        }

}
;
#endif // COLLISION_H
