#include "math.h"
#include<iostream>

#ifndef Simplex
#define Simplex 

using namespace std;

public class SimplexNoise
{   
	static int perm[512];
    static
    {
    	for(int i=0; i<512; i++) 
		perm[i]=p[i & 255];
    }
	int grad3[][] = {{1,1,0},{-1,1,0},{1,-1,0},{-1,-1,0},{1,0,1},{-1,0,1},{1,0,-1},{-1,0,-1},{0,1,1},{0,-1,1},{0,1,-1},{0,-1,-1}};
	int fastfloor(double x);
	double dot(int g[], double x, double y);
  

    public static double noisegen(double xin,double yin);	

};
#endif
