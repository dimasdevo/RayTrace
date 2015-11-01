#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

//  ------------------  Class Point ----------------------

class Point{
private:
	float x,y,z;
public:
	Point();
	Point(float,float,float);
	float GetX(){
		return x;
	}
	float GetY(){
		return y;
	}
	float GetZ(){
		return z;
	}
	void SetXYZ(float a, float b, float c){
		x=a;
		y=b;
		z=c;
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

	float dotProduct(Point a){
		float a1,a2,a3,sum;
		a1 = a.GetX();
		a2 = a.GetY();
		a3 = a.GetZ();

		sum = x*a1+y*a2+z*a3;
		return sum;
	}
};

Point::Point(float a, float b, float c){
	x=a;
	y=b;
	z=c;
}
Point::Point(){};

#endif