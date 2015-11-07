#ifndef INTERSECTIONPOINT_H_INCLUDED
#define INTERSECTIONPOINT_H_INCLUDED

#include "Point.h"

class IntersectionPoint{
private:
	float distance;
	Point intersectionpoint;
	Vector normal;
public:
	IntersectionPoint(){};
	void SetDistance(float temp){
		distance=temp;
	}
	void SetIntersectionPoint(Point temp){
		intersectionpoint=temp;
	}
	void SetNormal(Vector temp){
		normal=temp;
	}
	float GetDistance(){
		return distance;
	}
	Point GetInterSectionPoint(){
		return intersectionpoint;
	}
	Vector GetNormal(){
		return normal;
	}
};

#endif