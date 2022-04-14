#ifndef PACK_H_INCLUDED
#define PACK_H_INCLUDED

template <int numF,typename T>
void pack_Xdist(Fluid<numF,T> &f, T *XP_send, T *XM_send)
{
    int index = 0;
    int i1 = f.nE1;
    int index2 = 0;
    int i_1 = f.nB1;

 for(int i3 = 0; i3 < f.n3; i3++)
 {
  for(int i2 = 0; i2 < f.n2; i2++)
  {
   for(int dv=0;dv<27;dv++)
   {
      if(ex[dv]>0)
      {
        XP_send[index] = f(i1,i2,i3,dv);
        index ++;
      }
      if(ex[dv]<0)
      {
        XM_send[index2] = f(i_1,i2,i3,dv);
        index2 ++;
      }
    }
   }
 }
}

template <int numF,typename T>
void pack_Ydist(Fluid<numF,T> &f, T *YP_send, T *YM_send)
{
    int index = 0;
    int i2 = f.nE2;

 int index2 = 0;
 int i_2 = f.nB2;
 for(int i1 = 0; i1 < f.n1 ; i1++)
 {
  for(int i3 = 0; i3< f.n3;  i3++)
  {
   for(int dv=0;dv<27;dv++)
   {
     if(ey[dv]>0)
      {
        YP_send[index] = f(i1,i2,i3,dv);
        index ++;
      }
     if(ey[dv]<0)
      {
        YM_send[index2] = f(i1,i_2,i3,dv);
        index2 ++;
      }
    }
   }
 }
}

template <int numF,typename T>
void pack_Zdist(Fluid<numF,T> &f, T *ZP_send, T *ZM_send)
{
 int index = 0;
 int i3 = f.nE3;

 int index2 = 0;
 int i_3 = f.nB3;

 for(int i1 = 0; i1 < f.n1 ; i1++)
 {
  for(int i2 = 0; i2< f.n2;  i2++)
  {
   for(int dv=0;dv<27;dv++)
   {
    if(ez[dv]>0)
      {
        ZP_send[index] = f(i1,i2,i3,dv);
        index ++;
      }
    if(ez[dv]<0){
         ZM_send[index2] = f(i1,i2,i_3,dv);
        index2 ++;
      }
    }
   }
 }
}

template <int numF,typename T>
void unpack_Xdist(Fluid<numF,T> &f, T *XP_recv, T *XM_recv)
{
int index = 0;
 int i1 = f.nB1-1;
int index2 = 0;
 int i_1 = f.nE1+1;
 for(int i3 = 0; i3 < f.n3 ; i3++)
 {
  for(int i2 = 0; i2< f.n2;  i2++)
  {
   for(int dv=0;dv<27;dv++)
   {
      if(ex[dv]>0)
      {
        f(i1,i2,i3,dv) = XP_recv[index];
        index ++;
      }
      if(ex[dv]<0)
      {
        f(i_1,i2,i3,dv) = XM_recv[index2];
        index2 ++;
      }
    }
   }
 }

}

template <int numF,typename T>
void unpack_Ydist(Fluid<numF,T> &f, T *YP_recv, T *YM_recv)
{
int index = 0;
 int i2 = f.nB2-1;
int index2 = 0;
 int i_2 = f.nE2+1;
 for(int i1 = 0; i1 < f.n1 ; i1++)
 {
  for(int i3 = 0; i3< f.n3;  i3++)
  {
   for(int dv=0;dv<27;dv++)
   {
      if(ey[dv]>0)
      {
        f(i1,i2,i3,dv) = YP_recv[index];
        index ++;
      }
      if(ey[dv]<0)
      {
        f(i1,i_2,i3,dv) = YM_recv[index2];
        index2 ++;
    }
   }
 }
}
}

template <int numF,typename T>
void unpack_Zdist(Fluid<numF,T> &f, T *ZP_recv, T *ZM_recv)
{
    int index = 0;
    int i3 = f.nB3-1;
    int index2 = 0;
    int i_3 = f.nE3+1;

 for(int i1 = 0; i1 < f.n1 ; i1++)
 {
  for(int i2 = 0; i2< f.n2;  i2++)
  {
   for(int dv=0;dv<27;dv++)
   {
      if(ez[dv]>0)
      {
        f(i1,i2,i3,dv) = ZP_recv[index];
        index ++;
      }
      if(ez[dv]<0)
      {
        f(i1,i2,i_3,dv) = ZM_recv[index2];
        index2 ++;
      }
    }
   }
 }
}


#endif // PACK_H_INCLUDED
