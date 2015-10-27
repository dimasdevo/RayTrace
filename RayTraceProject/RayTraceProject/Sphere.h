#ifndef SPHERE_H_INCLUDED
#define SPHERE_H_INCLUDED

#include "Point.h"

class Sphere{
private:
	Point center;
	float radius;
public:
	Sphere();
	void SetSphere(Point C,float r){
		center=C;
		radius=r;
	};
	Point GetCenter(){
		return center;
	};
	float GetRadius(){
		return radius;
	};
};

Sphere::Sphere(){};

// -------------- Function Sphere Intersection -----------------------------------------------

Point Interscetion_Point(Ray ray, float t){
	Point A=ray.getPosition();
	Vector B=(ray.getDirection()).mux(t);
	Point temp(A.GetX()+B.GetX(),A.GetY()+B.GetY(),A.GetZ()+B.GetZ());
	return temp;
}

float Distance_Point(Point A, Point B){
	float a=A.GetX()-B.GetX();
	float b=A.GetY()-B.GetY();
	float c=A.GetZ()-B.GetZ();
	float d=sqrt(a*a+b*b+c*c);
	return d;
}

float Intersection_Sphere(Ray ray, Sphere obj){
	float distance;
	Point ray_origin=ray.getPosition();
	Vector ray_direction=ray.getDirection();
	Point sphere_center=obj.GetCenter();
	float radius=obj.GetRadius();

	float a=ray_direction.GetX()*ray_direction.GetX()+
			ray_direction.GetY()*ray_direction.GetY()+
			ray_direction.GetZ()*ray_direction.GetZ();
	float b=(2*(ray_origin.GetX()-sphere_center.GetX())*ray_direction.GetX())+
			(2*(ray_origin.GetY()-sphere_center.GetY())*ray_direction.GetY())+
			(2*(ray_origin.GetZ()-sphere_center.GetZ())*ray_direction.GetZ());
	float c=(pow(ray_origin.GetX()-sphere_center.GetX(),2))+
			(pow(ray_origin.GetY()-sphere_center.GetY(),2))+
			(pow(ray_origin.GetZ()-sphere_center.GetZ(),2))-(radius*radius);
	float discriminat=b*b-4*a*c;
	//cout<<"discriminat : "<<discriminat<<'\n';
	if(discriminat>0){
		float x1=(-b+sqrt(discriminat))/2*a;
		float x2=(-b-sqrt(discriminat))/2*a;
		if(x1>0)
		{
			//cout<<"A"<<'\n';
			Point intersectionPoint=Interscetion_Point(ray,x1);
			distance=Distance_Point(ray.getPosition(),intersectionPoint);
			return distance;
		}
		else if(x2>0)
		{
			//cout<<"B"<<'\n';
			Point intersectionPoint=Interscetion_Point(ray,x1);
			distance=Distance_Point(ray.getPosition(),intersectionPoint);
			return distance;		
		}
		else return -1;
	}
	else return -1;
}

#endif
