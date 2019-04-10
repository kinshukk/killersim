#include "Simplex.h"
#include <iostream>


int SimplexNoise::fastfloor(double x)
{
  return x>0?(int)x:(int)x-1;
}

double SimplexNoise::dot(int g[],double x,double y)
{
	return g[0]*x+g[1]*y;
}


double SimplexNoise::noisegen(double xin,double yin)
{
 double n1,n2,n0;
 final double F2=0.5*(sqrt(3.0)-1.0);
 double s=(xin+yin)*F2;
 int i=floor(xin+s);
 int j=floor(yin+s);

 final double G2=(3.0-sqrt(3.0))/6.0;
 double t=(i+j)*G2;
 double X0=i-t;
 double Y0=j-t;
 double x0=xin-X0;
 double y0=yin-Y0;

 int ioff1,joff1;
 if(x0>y0)
  {
   ioff1=1;
   joff1=0;
  }
else 
   {
    ioff1=0;
    joff1=1;
   } 
 double x1=x0-ioff1+G2;
 double y1=y0-joff1+G2;
 double x2=x0-1.0+2.0*G2;
 double y2=y0-1.0+2.0*G2;

 int iand=i&255;
 int jand=j&255;

 int g0=perm[iand+perm[jand]]%12;
 int g1= perm[iand + ioff1 +perm[jand+joff1]]%12;
 int g2=perm[iand+1+perm[jand+1]]%12;

 double t0=0.5-x0*x0-y0*y0;
 if(t0<0)
  n0=0.0;
 else 
  {
   t0*=t0;
   n0=t0*t0*dot(grad3[g0],x0,y0);
  }

  double t1=0.5-x1*x1-y1*y1;
 if(t1<0)
  n1=0.0;
 else 
  {
   t1*=t1;
   n1=t1*t1*dot(grad3[g1],x1,y1);
  }
  double t2=0.5-x2*x2-y2*y2;
 if(t2<0)
  n2=0.0;
 else 
  {
   t2*=t2;
   n2=t2*t2*dot(grad3[g2],x2,y2);
  }  

return 70.0*(n0+n1+n2);

}



