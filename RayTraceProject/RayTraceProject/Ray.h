#ifndef RAY_H_INCLUDED
#define RAY_H_INCLUDED

#include "Point.h"
//	-------------------	   Class Ray	----------------------------
class Ray{
private:
	Point position;
	Vector direction;
public:
	Ray();
	Ray(Point);
	Ray(Point, Vector);
	void setRay(Point temp){
		position=temp;
	};
	void setRay(Point temp1, Vector temp2){
		position=temp1;
		direction=temp2;
	}
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