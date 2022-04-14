template <int numF,typename T>
void print(Fluid<numF,T> &f,int t,int i,int j,int k,int fileprint)
{
    my_var m=0;
    FILE *file;
    file=fopen("fluid_velocity.dat","w");
    for(int a=0;a<27;a++)
        {
            m+= (f(i,j,k,a)*ex[a]);

        }
        if(fileprint==1)
        {

            file=fopen("fluid_velocity.dat","a");
            fprintf(file,"t=%d\t ux[20][25][25]= %.6f \n",t,m);
        }
        printf("t=%d\t ",t);
        printf("ux[%d][%d][%d]= %.6f",i,j,k,m);
        printf("\n");

}



