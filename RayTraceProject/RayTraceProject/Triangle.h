#ifndef TRIANGLE_H_INCLUDED
#define TRIANGLE_H_INCLUDED

#include "Point.h"
#include "Vector.h"
#include "Ray.h"

class Triangle{
private:
	Point A;
	Point B;
	Point C;
public:
	Triangle(Point, Point, Point);
	Point GetA(){
		return A;
	};
	Point GetB(){
		return B;
	};
	Point GetC(){
		return C;
	};
};

Triangle::Triangle(Point a, Point b, Point c){
	A=a;
	B=b;
	C=c;
}

// -------------- Function Triangle Intersection -----------------------------------------------

bool Intersection_Triangle(Ray ray, Triangle obj){
	Point A=obj.GetA();
	Point B=obj.GetB();
	Point C=obj.GetC();
	Vector A1=LengthPoint(C,A);
	Vector B1=LengthPoint(B,A);
	Vector temp=A1.crossProduct(B1);
	Vector n=temp.normalize();
	float a=(ray.getDirection()).dotProduct(n);
	if(a==0){
		//Ray Paralel
	}else{
		float t = (dotProduct(n,A)-dotProduct(n,ray.getPosition()))/(n.dotProduct(ray.getDirection()));
	
		float Qx=(ray.getPosition()).GetX()+(t*(ray.getDirection()).GetX());
		float Qy=(ray.getPosition()).GetY()+(t*(ray.getDirection()).GetY());
		float Qz=(ray.getPosition()).GetZ()+(t*(ray.getDirection()).GetZ());

		//[CA x QA]*n>0
		//[BC x QC]*n>0
		//[AB x QB]*n>0

		Point Q(Qx,Qy,Qz);

		Vector CA=A1;
		Vector BC=LengthPoint(B,C);
		Vector AB=LengthPoint(A,B);

		Vector QA=LengthPoint(Q,A);
		Vector QC=LengthPoint(Q,C);
		Vector QB=LengthPoint(Q,B);

		float test1=(CA.crossProduct(QA)).dotProduct(n);
		float test2=(BC.crossProduct(QC)).dotProduct(n);
		float test3=(AB.crossProduct(QB)).dotProduct(n);

		if((test1>=0)&&(test2>=0)&&(test3>=0)){
			return true;
		}else
			return false;
	}
}

#endif
