#ifndef INTERSECTION_H_INCLUDED
#define INTERSECTION_H_INCLUDED

#include "IntersectionPoint.h"

class Intersection{
private:
	//if obj==1 circle, obj==2 triangle
	int obj;
	int obj_list;
	IntersectionPoint Hit;
public:
	Intersection(){};
	void Set_Intersection(int a, int b){
		obj=a;
		obj_list=b;
	}
	void SetIntersectionPoint(IntersectionPoint temp){
		Hit=temp;
	}
	int Get_Obj(){
		return obj;
	}
	int Get_ObjList(){
		return obj_list;
	}
	IntersectionPoint GetInterSectionPoint(){
		return Hit;
	}
};

#endif