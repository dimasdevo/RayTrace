#ifndef TRANSFORMATION_H_INCLUDED
#define TRANSFORMATION_H_INCLUDED

#include "Point.h"
#include <math.h>

#define PHI 3.14159265

using namespace std;

class Transformsphere{
private:
	float x,y,z;
public:
	Transformsphere(){};
	void SetXYZ(float a, float b, float c){
		x=a;
		y=b;
		z=c;
	}
	float GetX(){
		return x;
	}
	float GetY(){
		return y;
	}
	float GetZ(){
		return z;
	}
};

int round(double d){
        return static_cast<int>(d + 0.5);
}

// ---------------Tranformation Function------------------------- //
Point TransformTranslate(Point a, Point value){
    float temp1, temp2, temp3;
    temp1 = a.GetX() + value.GetX();
    temp2 = a.GetY() + value.GetY();
    temp3 = a.GetZ() + value.GetZ();

	Point res(temp1,temp2,temp3);
    return res;
}

Point TransformScale(Point a, Point value){
    float temp1, temp2, temp3;
    temp1 = a.GetX() * value.GetX();
    temp2 = a.GetY() * value.GetY();
    temp3 = a.GetZ() * value.GetZ();

	Point res(temp1,temp2,temp3);
    return res;
}

Point InvTransformScale(Point value, Point a){
    float temp1, temp2, temp3;
	temp1 = (1/value.GetX()) * a.GetX();
	temp2 = (1/value.GetY()) * a.GetY();
	temp3 = (1/value.GetZ()) * a.GetZ();

	Point res(temp1,temp2,temp3);
    return res;
}

Vector InvTransformScale(Point value, Vector a){
    float temp1, temp2, temp3;
	temp1 = (1/value.GetX()) * a.GetX();
	temp2 = (1/value.GetY()) * a.GetY();
	temp3 = (1/value.GetZ()) * a.GetZ();

	Vector res(temp1,temp2,temp3);
    return res;
}
float TransformScale(float a, Point value){
    float res=a*value.GetX();
    return res;
}

Point TransformRotate(Point a, Point center, float degree){
    float point1, point2, point3;
    // Koordinat titik yang akan dirotasi
    point1 = a.GetX();
    point2 = a.GetY();
    point3 = a.GetZ();

    float center1, center2, center3;
    // Koordinat sumbu
    center1 = center.GetX();
    center2 = center.GetY();
    center3 = center.GetZ();

    float tempx, tempy, tempz;
    // Sumbu x
    if(center1==1){
        tempx = point1;
        tempy = ( point2 * (cos( degree * PHI / 180.0 ) ) ) - ( point3 * (sin( degree * PHI / 180.0 ) ) );
        tempz = ( point2 * (sin( degree * PHI / 180.0 ) ) ) + ( point3 * (cos( degree * PHI / 180.0 ) ) );
    }
    // Sumbu y
    else if(center2==1){
        tempx = ( point3 * (sin( degree * PHI / 180.0 ) ) ) + ( point1 * (cos( degree * PHI / 180.0 ) ) );
        tempy = point2;
        tempz = ( point3 * (cos( degree * PHI / 180.0 ) ) ) - ( point1 * (sin( degree * PHI / 180.0 ) ) );
    }
    // Sumbu z
    else{
        tempx = ( point1 * (cos( degree * PHI / 180.0 ) ) ) - ( point2 * (sin( degree * PHI / 180.0 ) ) );
        tempy = ( point1 * (sin( degree * PHI / 180.0 ) ) ) + ( point2 * (cos( degree * PHI / 180.0 ) ) );
        tempz = point3;
    }

	Point res(tempx, tempy, tempz);
    return res;
}
#endif