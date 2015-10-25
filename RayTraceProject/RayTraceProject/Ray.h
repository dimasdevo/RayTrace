#ifndef RAY_H_INCLUDED
#define RAY_H_INCLUDED

#include "Point.h"
//	-------------------	   Class Ray	----------------------------
class Ray{
private:
	Point position;
	Vector direction;
	float t_min, t_max;
public:
	Ray();
	Ray(Point);
	Ray(Point, Vector);
	void setRay(Point temp){
		position=temp;
	};
	Point getPosition(){
		return position;
	};
	Vector getDirection(){
		return direction;
	};
};

Ray::Ray(Point temp){
	position=temp;
}

Ray::Ray(Point temp, Vector temp1){
	position=temp;
	direction=temp1;
}

Ray::Ray(){}

#endif