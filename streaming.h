#ifndef STREAMING_H
#define STREAMING_H

template <int numF,typename T>
void streaming(Fluid<numF,T> &f)
{
    for(int i=f.nB1;i<=f.nE1;i++)          //local nx
     {
    for(int j=f.nB2;j<=f.nE2;j++)
       {
       for(int k=f.nB3;k<=f.nE3;k++)
             {

            for(int a=0;a<27;a++)
                  {

                  if (a==2 || a==9 || a==10 || a==13 || a==14 || a==23 || a==24 || a==25 || a==26 || a==4 ||  a==17 || a==18 || a==6)
                     {
                         int p=i-ex[a];
                         int q=j-ey[a];
                         int r=k-ez[a];
                         f(i,j,k,a)=f(p,q,r,a);
                     }
                 }
              }
           }
    }

    for(int i=f.nE1;i>=f.nB1;i--)
     {
      for(int j=f.nE2;j>=f.nB2;j--)
       {
       for(int k=f.nE3;k>=f.nB3;k--)
             {
              for(int a=0;a<27;a++)
                   {
                    if (a==1 || a==3 || a==5 || a==7 || a==8 || a==11 || a==12 || a==15 || a==16 || a==19 || a==20 || a==21 || a==22)
                      {
                      /*   int p=i-ex[a];
                         int q=j-ey[a];
                         int r=k-ez[a];
                        if(p==nx+1)
                            p=1;
                        if(p==0)
                            p=nx;
                        if(q==ny+1)
                            q=1;
                        if(q==0)
                            q=ny;
                        if(r==nx+1)
                            r=1;
                        if(r==0)
                            r=nz;
                        */
                        int p=i-ex[a];
                         int q=j-ey[a];
                         int r=k-ez[a];
                          f(i,j,k,a)=f(p,q,r,a);
                      }
                  }
                }
            }
      }
}

#endif // STREAMING_H



