#include <iostream>
#include <math.h>
#include "Point.h"
#include "Vector.h"
#include "Matrix.h"
#include "Camera.h"
#include "Ray.h"
#include "Sphere.h"
#include "FreeImage.h"

#define VECTOR 3
#define PHI 3.14159265

using namespace std;

// ----------------- Codingan Part 2 (Ray intersection)---------------------------------------------


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
void RayTrace(Camera cam, float width, float length){
	for(int i=0; i<width; i++){
		for(int j=0; j<length; j++){
			Ray ray=RayThruPixel(cam, i, j, width, length);
			cout<<ray.getPosition().GetX()<<" "<<ray.getPosition().GetY()<<" "<<ray.getPosition().GetZ()<<'\n';
			cout<<ray.getDirection().GetX()<<" "<<ray.getDirection().GetY()<<" "<<ray.getDirection().GetZ()<<'\n';
			system("PAUSE");
			//bool hit=Intersect(ray,scene);
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
