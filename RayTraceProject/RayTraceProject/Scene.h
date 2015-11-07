#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include "Sphere.h"
#include "Triangle.h"
#include "Light.h"
#include "Color.h"

class Scene{
private:
	Sphere sphere[10];
	Triangle tri[10];
	Light lightsource[10];
	int sphereCount;
	int triCount;
	int lightcount;
	Color ambient;
public:
	Scene();
	void Add_Sphere(Sphere temp){
		sphere[sphereCount]=temp;
		sphereCount++;
	}
	void Add_Triangle(Triangle temp){
		tri[triCount]=temp;
		triCount++;
	}
	void Add_Light(Light temp){
		lightsource[lightcount]=temp;
		lightcount++;
	}
	void Add_Ambient(Color temp){
		ambient=temp;
	}
	int Get_SphereCount(){
		return sphereCount;
	}
	int Get_TriCount(){
		return triCount;
	}
	int Get_LightCount(){
		return lightcount;
	}
	Sphere Get_Sphere(int flag){
		return sphere[flag];
	}
	Triangle Get_Tri(int flag){
		return tri[flag];
	}
	Light Get_Light(int flag){
		return lightsource[flag];
	}
	Color Get_Ambient(){
		return ambient;
	}
};
Scene::Scene(){
	sphereCount=0;
	triCount=0;
	lightcount=0;
};

#endif