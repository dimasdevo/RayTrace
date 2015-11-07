#ifndef SPHERE_H_INCLUDED
#define SPHERE_H_INCLUDED

#include "Color.h"
#include "Point.h"
#include "Transformation.h"
#include "IntersectionPoint.h"

class Sphere{
private:
	Point center;
	float radius;
	Transformsphere transform[100];
	int t_transform;
	Color emission;
	Color diffuse;
	Color specular;
	float shiness;
public:
	Sphere();
	void SetSphere(Point C,float r){
		center=C;
		radius=r;
	};
	void SetTransform(Point a, int iter){
		transform[iter].SetXYZ(a.GetX(),a.GetY(),a.GetZ());
		t_transform++;
	}
	void SetEmission(Color temp){
		emission=temp;
	}
	void SetDiffuse(Color temp){
		diffuse=temp;
	}
	void SetSpecular(Color temp){
		specular=temp;
	}
	void SetShiness(float temp){
		shiness=temp;
	}
	Point GetTransformSphere(int iter){
		Point res(transform[iter].GetX(),transform[iter].GetY(),transform[iter].GetZ());
		return res;
	}
	int GetTTransform()
	{
		return t_transform;
	}
	Point GetCenter(){
		return center;
	};
	float GetRadius(){
		return radius;
	};
	Color GetEmission(){
		return emission;
	}
	Color GetDiffuse(){
		return diffuse;
	}
	Color GetSpecular(){
		return specular;
	}
	float GetShiness(){
		return shiness;
	}
};

Sphere::Sphere(){
	t_transform=0;
};

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

IntersectionPoint Intersection_Sphere(Ray ray, Sphere obj){
	IntersectionPoint IntersectionHit;
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
		float x1=(-b+sqrt(discriminat))/(2*a);
		float x2=(-b-sqrt(discriminat))/(2*a);
		if(x1>0 && x2>0){
			Point intersectionPoint;
			float distance;
			Point intersectionPoint1=Interscetion_Point(ray,x1);
			float distance1=Distance_Point(ray.getPosition(),intersectionPoint1);
			Point intersectionPoint2=Interscetion_Point(ray,x2);
			float distance2=Distance_Point(ray.getPosition(),intersectionPoint2);
			if(distance1>distance2){
				distance=distance1;
				intersectionPoint=intersectionPoint1;
			}else{
				distance=distance2;
				intersectionPoint=intersectionPoint2;
			}
			IntersectionHit.SetDistance(distance);
			IntersectionHit.SetIntersectionPoint(intersectionPoint);
			Vector Normal(intersectionPoint.GetX()-sphere_center.GetX(),intersectionPoint.GetY()-sphere_center.GetY(),intersectionPoint.GetZ()-sphere_center.GetZ());
			Normal.normalize();
			IntersectionHit.SetNormal(Normal);
			return IntersectionHit;
		}
		else if(x1>0)
		{
			//cout<<"A"<<'\n';
			Point intersectionPoint=Interscetion_Point(ray,x1);
			distance=Distance_Point(ray.getPosition(),intersectionPoint);
			IntersectionHit.SetDistance(distance);
			IntersectionHit.SetIntersectionPoint(intersectionPoint);
			Vector Normal(intersectionPoint.GetX()-sphere_center.GetX(),intersectionPoint.GetY()-sphere_center.GetY(),intersectionPoint.GetZ()-sphere_center.GetZ());
			Normal.normalize();
			IntersectionHit.SetNormal(Normal);
			return IntersectionHit;
		}
		else if(x2>0)
		{
			//cout<<"B"<<'\n';
			Point intersectionPoint=Interscetion_Point(ray,x2);
			distance=Distance_Point(ray.getPosition(),intersectionPoint);
			IntersectionHit.SetDistance(distance);
			IntersectionHit.SetIntersectionPoint(intersectionPoint);
			Vector Normal(intersectionPoint.GetX()-sphere_center.GetX(),intersectionPoint.GetY()-sphere_center.GetY(),intersectionPoint.GetZ()-sphere_center.GetZ());
			Normal.normalize();
			IntersectionHit.SetNormal(Normal);
			return IntersectionHit;
		}
		else{
			IntersectionHit.SetDistance(-1);
			return IntersectionHit;
		}
	}
	else {
		IntersectionHit.SetDistance(-1);
		return IntersectionHit;
	}
}

#endif
