#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "Point.h"
#include <iostream>

using namespace std;
//	-------------------	   Class Camera	----------------------------
class Camera{
private:
	Point lookfrom, lookto, up;
	float fovy;
public:
	Camera(Point, Point, Point);
	Camera(Point, Point, Point, float);
	void print(){
		cout<<lookfrom.GetX()<<" "<<lookfrom.GetY()<<" "<<lookfrom.GetZ()<<'\n';
		cout<<lookto.GetX()<<" "<<lookto.GetY()<<" "<<lookto.GetZ()<<'\n';
		cout<<up.GetX()<<" "<<up.GetY()<<" "<<up.GetZ()<<'\n';
	}

	Point GetLookFrom(){
		return lookfrom;
	}

	Point GetLookTo(){
		return lookto;
	}

	Point GetUp(){
		return up;
	}

	float Getfovy(){
		return fovy;
	}

};


Camera::Camera(Point a, Point b, Point c){
	lookfrom=a;
	lookto=b;
	up=c;
}

Camera::Camera(Point a, Point b, Point c, float d){
	lookfrom=a;
	lookto=b;
	up=c;
	fovy=d;
}

#endif