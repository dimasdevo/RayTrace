#include <iostream>
#include <math.h>
#include <string>
#include "Point.h"
#include "Vector.h"
#include "Matrix.h"
#include "Camera.h"
#include "Ray.h"
#include "Sphere.h"
#include "Triangle.h"
#include "FreeImage.h"

#define VECTOR 3
#define PHI 3.14159265

using namespace std;

class Intersection{
private:
	//if obj==1 circle, obj==2 triangle
	int obj;
	int obj_list;
public:
	Intersection(){};
	void Set_Intersection(int a, int b){
		obj=a;
		obj_list=b;
	}
	int Get_Obj(){
		return obj;
	}
	int Get_ObjList(){
		return obj_list;
	}
};

class Scene{
private:
	Sphere sphere[10];
	Triangle tri[10];
	int sphereCount;
	int triCount;
public:
	Scene();
	void Add_Sphere(int radius, Point center){
		sphere[sphereCount].SetSphere(center,radius);
		sphereCount++;
	}
	void Add_Triangle(Point A, Point B, Point C){
		tri[triCount].SetTriangle(A,B,C);
		triCount++;
	}
	int Get_SphereCount(){
		return sphereCount;
	}
	int Get_TriCount(){
		return triCount;
	}
	Sphere Get_Sphere(int flag){
		return sphere[flag];
	}
	Triangle Get_Tri(int flag){
		return tri[flag];
	}
};
Scene::Scene(){
	sphereCount=0;
	triCount=0;
};
// ----------------- Codingan Part 2 (Ray intersection)---------------------------------------------
Intersection Intersect(Ray ray, Scene scene){
	Intersection intersectionInfo;
	int triCount=scene.Get_TriCount();
	int SphereCount=scene.Get_SphereCount();
	// Find Intersection
	int obj=-1, obj_list=-1;
	float t=-1, mindist=-1;
	for(int i=0; i<triCount; i++){
		Triangle tri=scene.Get_Tri(i);
		t=Intersection_Triangle(ray, tri);
		if(t!=-1 && mindist<t){
			obj=2;
			obj_list=i;
		}
	}
	for(int j=0; j<SphereCount; j++){
		Sphere sphere=scene.Get_Sphere(i);
		t=Intersection_Sphere(ray, sphere);
		if(t!=-1 && mindist<t){
			obj=1;
			obj_list=j;
		}
	}
	intersectionInfo.Set_Intersection(obj,obj_list);
	return intersectionInfo;
}
// ----------------- Codingan Part 1 (Camera Position)---------------------------------------------

// -----------------  Get Variable UVW (Faishal)---------------------------------------

// ----------------- Cross, Dot, Normalize Product Function (+)-------------------------------------------------

Matrix NormalizeUVW(Camera cam){
	Vector u,v,w;

	Point eye = cam.GetLookFrom();
	Point center = cam.GetLookTo();
	Point up = cam.GetUp();

	Vector a=LengthPoint(eye,center);
	Vector b(up.GetX(), up.GetY(), up.GetZ());

	w = a.normalize();
	u = (b.crossProduct(w)).normalize();
	v = w.crossProduct(u);

	Matrix temp(u,v,w);

	return temp;
}

float GetNFovy(float fov){
    return tan((fov/2)*PHI/180);
}

float GetNFovx(float Nfovy, float aspectRatio){
	return Nfovy/aspectRatio;
}

float GetDirectionA(float fov, int size, int var){
	float direction=fov*((float)var-(size/2))/size;
	return direction;
}

float GetDirectionB(float fov, int size, int var){
	float direction=fov*((float)(size/2)-var)/size;
	return direction;
}

Ray ComputeRay(Camera cam, Matrix norm, float a, float b){
	float n;
	Point eye;
	Vector U, V, W, temps, tempp;
	eye=cam.GetLookFrom();
	U=norm.GetX();
	V=norm.GetY();
	W=norm.GetZ();

	temps.SetX(U.GetX()*a+V.GetX()*b-W.GetX());
	temps.SetY(U.GetY()*a+V.GetY()*b-W.GetY());
	temps.SetZ(U.GetZ()*a+V.GetZ()*b-W.GetZ());

	n=sqrt((temps.GetX()*temps.GetX())+(temps.GetY()*temps.GetY())+(temps.GetZ()*temps.GetZ()));

	tempp.SetX((temps.GetX()/n));
	tempp.SetY((temps.GetY()/n));
	tempp.SetZ((temps.GetZ()/n));

	Ray temp(eye, tempp);
	return temp;
}


Ray RayThruPixel(Camera cam, int i, int j, float width, float length){
	Ray temp;
	
	Matrix norm = NormalizeUVW(cam);
	float fovy=cam.Getfovy();
	float Nfovy=GetNFovy(fovy);
	float Nfovx=GetNFovx(Nfovy,width/length);
	float a=GetDirectionA(Nfovx, width, j);
	float b=GetDirectionB(Nfovy, length, i);
	temp=ComputeRay(cam,norm,a,b);
	return temp;
}


//  --------------------- RayTrace Algorithm --------------------------------------
void RayTrace(Camera cam, float width, float length, Scene scene){
	for(int i=0; i<width; i++){
		for(int j=0; j<length; j++){
			Ray ray=RayThruPixel(cam, i, j, width, length);
			cout<<ray.getPosition().GetX()<<" "<<ray.getPosition().GetY()<<" "<<ray.getPosition().GetZ()<<'\n';
			cout<<ray.getDirection().GetX()<<" "<<ray.getDirection().GetY()<<" "<<ray.getDirection().GetZ()<<'\n';
			system("PAUSE");
			Intersection hit=Intersect(ray,scene);
		}
	}
}

//  ---------------------- Main Program.c -----------------------------------

int main(int argc, char *argv[]){
	Point posisiKamera[4];
	float a,b,c,fov,width,length;
	cout<<"Masukkan Panjang dan Lebar gambar :"<<'\n';
	cin>>width>>length;
	cout<<"Masukkan koordinat kamera: \n";
	for(int i=0; i<VECTOR; i++){
		cin>>a>>b>>c;
		posisiKamera[i].SetX(a);
		posisiKamera[i].SetY(b);
		posisiKamera[i].SetZ(c);
	}
	cin>>fov;
	Camera A(posisiKamera[0], posisiKamera[1], posisiKamera[2],fov);
	A.print();
	system("PAUSE");
	RayTrace(A,width,length);
	return 0;
}
