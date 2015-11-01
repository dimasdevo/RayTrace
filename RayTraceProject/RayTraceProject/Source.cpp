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
#include "Transformation.h"

#define VECTOR 3
#define PHI 3.14159265
#define BPP 24

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
	void Add_Sphere(Sphere temp){
		sphere[sphereCount]=temp;
		sphereCount++;
	}
	void Add_Triangle(Triangle temp){
		tri[triCount]=temp;
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
		Sphere sphere=scene.Get_Sphere(j);
		if(sphere.GetTTransform()>0){
			//cout<<"aye";
			Ray temp=ray;
			for (int a = 0; a < sphere.GetTTransform(); a++)
			{
				Point scale=sphere.GetTransformSphere(a);
				temp.setRay(InvTransformScale
					(scale,temp.getPosition()),InvTransformScale(scale,temp.getDirection()));
			}
			t=Intersection_Sphere(temp,sphere);
		}
		else{
			t=Intersection_Sphere(ray, sphere);
		}
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

	tempp=temps.normalize();

	Ray temp(eye, tempp);
	return temp;
}


Ray RayThruPixel(Camera cam, int i, int j, float width, float height){
	Ray temp;

	Matrix norm = NormalizeUVW(cam);
	float fovy=cam.Getfovy();
	float Nfovy=GetNFovy(fovy);
	float Nfovx=GetNFovx(Nfovy,width/height);
	float a=GetDirectionA(Nfovx, width, j)*(Nfovy/Nfovx);
	float b=GetDirectionB(Nfovy, height, i)*(Nfovx/Nfovy);
	temp=ComputeRay(cam,norm,a,b);
	return temp;
}


//  --------------------- RayTrace Algorithm --------------------------------------
void RayTrace(Camera cam, float width, float height, Scene scene, char output[]){
	FreeImage_Initialise();

	FIBITMAP* bitmap=FreeImage_Allocate(width, height, BPP);
	RGBQUAD color;

	if(!bitmap)
		exit(1);

	for(int i=0; i<height; i++){
		for(int j=0; j<width; j++){
			Ray ray=RayThruPixel(cam, i, j, width, height);
			Intersection hit=Intersect(ray,scene);
			if(hit.Get_Obj()>0){
				color.rgbGreen=255;
				color.rgbBlue=255;
				color.rgbRed=255;
				FreeImage_SetPixelColor(bitmap,j,height-i-1,&color);
				//cout<<hit.Get_Obj()<<'\n';
			}
			else{
				color.rgbGreen=255;
				color.rgbBlue=0;
				color.rgbRed=0;
				FreeImage_SetPixelColor(bitmap,j,height-i-1,&color);
			}
		}
	}
	if(FreeImage_Save(FIF_PNG,bitmap,output,0))
		cout<<"Image berhasil dicetak";
	FreeImage_DeInitialise();
}

//  ---------------------- Main Program.c -----------------------------------

int main(int argc, char *argv[])
{
	Point posisiKamera[4];
	Scene scene;
	float a,b,c,fov,width,height;
	int jmlInput, jmlTrans, inpTransformasi, inpBenda;
	cout<<"Masukkan Lebar dan Tinggi gambar :"<<'\n';
	cin>>width>>height;
	cout<<"Masukkan koordinat kamera: \n";
	for(int i=0; i<VECTOR; i++)
	{
		cin>>a>>b>>c;
		posisiKamera[i].SetX(a);
		posisiKamera[i].SetY(b);
		posisiKamera[i].SetZ(c);
	}
	cin>>fov;
	Camera A(posisiKamera[0], posisiKamera[1], posisiKamera[2],fov);
	A.print();
	cout<<"Masukkan Jumlah Benda : ";
	cin>>jmlInput;
	for (int i = 0; i < jmlInput; i++)
	{
		float x,y,z,radius;
		float x1,x2,x3,y1,y2,y3,z1,z2,z3;
		Point sphere1, Tri1, Tri2, Tri3;
		Sphere sphere;
		Triangle tri;
		cout<<"Masukkan Jenis Benda : \n 1. Lingkaran \n 2. Triangle \n Benda:";
		cin>>inpBenda;
		if(inpBenda==1)
		{
			cout<<"Masukkan inputan lingkaran (x,y,z,radius): \n";
			cin>>x>>y>>z>>radius;
			sphere1.SetXYZ(x,y,z);
			sphere.SetSphere(sphere1,radius);
		}
		else if(inpBenda==2)
		{
			cout<<"Masukkan inputan segitiga (x,y,z): \n";
			cin>>x1>>y1>>z1>>x2>>y2>>z2>>x3>>y3>>z3;
			Tri1.SetXYZ(x1,y1,z1);
			Tri2.SetXYZ(x2,y2,z2);
			Tri3.SetXYZ(x3,y3,z3);
			tri.SetTriangle(Tri1,Tri2,Tri3);
		}
		else
		{
			cout<<"Salah menginputkan benda";
		}
		cout<<"Masukkan jumlah transformasi : ";
		cin>>jmlTrans;
		for (int j = 0; j < jmlTrans; j++)
		{
			cout<<"Nilai Transformasi : 1. Translasi\n 2. Rotasi\n 3. Scale \n Intruksi: ";
			cin>>inpTransformasi;
			if(inpTransformasi==1){
				float x, y, z;
				cout<<"Masukkan Translasi :";
				cin>>x>>y>>z;
				Point temp(x,y,z);
				if (inpBenda==1)
				{
					sphere1=TransformTranslate(sphere.GetCenter(),temp);
					sphere.SetSphere(sphere1,sphere.GetRadius());
				}
				else if(inpBenda==2){
					Tri1=TransformTranslate(tri.GetA(),temp);
					Tri2=TransformTranslate(tri.GetB(),temp);
					Tri3=TransformTranslate(tri.GetC(),temp);
					tri.SetTriangle(Tri1,Tri2,Tri3);
				}
			}
			else if(inpTransformasi==2){
				float x, y, z, derajat;
				cout<<"Masukkan Rotasi :";
				cin>>x>>y>>z>>derajat;
				Point temp(x,y,z);
				if(inpBenda==1)
				{
					sphere1=TransformRotate(sphere.GetCenter(),temp,derajat);
					sphere.SetSphere(sphere1,sphere.GetRadius());
				}
				else if(inpBenda==2);
				{
					Tri1=TransformRotate(tri.GetA(),temp,derajat);
					Tri2=TransformRotate(tri.GetB(),temp,derajat);
					Tri3=TransformRotate(tri.GetC(),temp,derajat);
					tri.SetTriangle(Tri1,Tri2,Tri3);
					system("PAUSE");
				}
			}
			else if(inpTransformasi==3){
				float x, y, z;
				cout<<"Masukkan Scale :";
				cin>>x>>y>>z;
				Point temp(x,y,z);
				if(inpBenda==1)
				{
					if(x!=y || y!=z ||z!=x)
					{
						cout<<"special case";
						//Special Case-
						int iter=sphere.GetTTransform();
						sphere.SetTransform(temp,iter);
					}
					else
					{
						radius=TransformScale(radius,temp);
						sphere.SetSphere(sphere.GetCenter(),radius);
					}
				}
				else if(inpBenda==2)
				{
					Tri1=TransformScale(tri.GetA(),temp);
					Tri2=TransformScale(tri.GetB(),temp);
					Tri3=TransformScale(tri.GetC(),temp);
					tri.SetTriangle(Tri1,Tri2,Tri3);
				}
			}
			else
			{
				cout<<"Salah memasukkan transformasi";
			}
		}
		if(inpBenda==1){
			scene.Add_Sphere(sphere);
		}
		else if(inpBenda==2){
			scene.Add_Triangle(tri);
		}
	}
	char output[100];
	cout<<"Masukkan Output(.png) :";
	cin>>output;
	RayTrace(A,width,height,scene,output);
	system("PAUSE");
	return 0;
}
