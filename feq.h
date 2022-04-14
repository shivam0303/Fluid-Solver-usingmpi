#ifndef FEQUILIBRIUM_H
#define FEQUILIBRIUM_H


void fequilibrium(my_var *feq,my_var &rho,my_var &ux,my_var &uy,my_var &uz)
{
    my_var term1,term2;
    my_var u2=ux*ux+uy*uy+uz*uz;
    for(int a=0;a<numF;a++)
        {
            term1 = ux*ex[a] + uy*ey[a] +uz*ez[a];
            term2 = term1*term1;
            feq[a] = weight[a]*rho*(1.0 + 3.0*term1 + 4.5*term2 - 1.5*u2);
        }
}


#endif // FEQUILIBRIUM_H
