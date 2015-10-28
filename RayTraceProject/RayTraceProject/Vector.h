#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

//  ------------------  Class Point ----------------------
#include <math.h>
#include "Point.h"

class Vector{
private:
	float x,y,z;
public:
	Vector();
	Vector(float,float,float);
	float GetX(){
		return x;
	}
	float GetY(){
		return y;
	}
	float GetZ(){
		return z;
	}
	void SetX(float a){
		x=a;
	}
	void SetY(float b){
		y=b;
	}
	void SetZ(float c){
		z=c;
	}
	Vector normalize(){
		float garisdua = sqrt((x*x)+(y*y)+(z*z));
	    Vector c(x/garisdua, y/garisdua, z/garisdua);
		return c;
	}

	Vector crossProduct(Vector a)
	{
		float a1,a2,a3,b1,b2,b3;
		a1 = a.GetX();
		a2 = a.GetY();
		a3 = a.GetZ();

		b1 = (y*a3) - (z*a2);
		b2 = ((z*a1) - (x*a3));
		b3 = (x*a2) - (y*a1);
		Vector b(b1,b2,b3);
		return b;
	}

	Vector mux(float a){
		Vector temp(x*a,y*a,z*a);
		return temp;
	}
	
	float dotProduct(Vector a){
		float a1,a2,a3,sum;
		a1 = a.GetX();
		a2 = a.GetY();
		a3 = a.GetZ();

		sum = x*a1+y*a2+z*a3;
		return sum;
	}

};

Vector::Vector(float a, float b, float c){
	x=a;
	y=b;
	z=c;
}
Vector::Vector(){};

Vector LengthPoint(Point a, Point b){
	Vector temp(a.GetX()-b.GetX(),a.GetY()-b.GetY(),a.GetZ()-b.GetZ());
	return temp;
}


float dotProduct(Vector a, Point b){
	float a1,a2,a3,b1,b2,b3,sum;
	a1 = a.GetX();
	a2 = a.GetY();
	a3 = a.GetZ();

	b1 = b.GetX();
	b2 = b.GetY();
	b3 = b.GetZ();

	sum = a1*b1+a2*b2+a3*b3;
	return sum;
}

float dotProduct(Vector a, float b){
	float a1,a2,a3,sum;
	a1 = a.GetX();
	a2 = a.GetY();
	a3 = a.GetZ();

	sum = a1*b+a2*b+a3*b;
	return sum;
}

#endif