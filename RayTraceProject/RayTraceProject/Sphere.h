#ifndef SPHERE_H_INCLUDED
#define SPHERE_H_INCLUDED

#include "Point.h"

class Sphere{
private:
	Point center;
	float radius;
public:
	Sphere(Point,float);
	Point GetCenter(){
		return center;
	};
	float GetRadius(){
		return radius;
	};
};

Sphere::Sphere(Point C, float r){
	center=C;
	radius=r;
}

// -------------- Function Sphere Intersection -----------------------------------------------

bool Intersection_Sphere(Ray ray, Sphere obj){
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
			(pow(ray_origin.GetZ()-sphere_center.GetZ(),2))+(radius*radius);
	float discriminat=b*b-4*a*c;
	if(discriminat>0){
		float x1=(-b+sqrt(discriminat))/2*a;
		float x2=(-b-sqrt(discriminat))/2*a;
		if(x1>0 && x2>0){
			return true;
		}
		else if(x1>0)
		{
			return true;
		}
		else if(x2>0)
		{
			return true;
		}
		else return false;
	}
	else return false;
}

#endif
