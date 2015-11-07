#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED

#include "Point.h"
#include "Color.h"
//	-------------------	   Class Light	----------------------------
class Light{
private:
	Point position;
	Color Lightcolor;
public:
	Light();
	Light(Point,Color);
	void setLight(Point temp, Color temp1){
		position=temp;
		Lightcolor=temp1;
	};
	Point getPosition(){
		return position;
	};
	Color getColor(){
		return Lightcolor;
	};
};

Light::Light(Point temp, Color temp1){
	position=temp;
	Lightcolor=temp1;
}

Light::Light(){}

#endif