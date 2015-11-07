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
#include "Color.h"
#include "Light.h"
#include "Intersection.h"
#include "Scene.h"
#include "IntersectionPoint.h"

#define VECTOR 3
#define PHI 3.14159265
#define BPP 24

using namespace std;

// ----------------- Codingan Part 2 (Ray intersection)---------------------------------------------
Intersection Intersect(Ray ray, Scene scene){
	Intersection intersectionInfo;
	IntersectionPoint intersectionhit,temp;
	int triCount=scene.Get_TriCount();
	int SphereCount=scene.Get_SphereCount();
	// Find Intersection
	int obj=-1, obj_list=-1;
	float t=-1, mindist=-1;
	for(int i=0; i<triCount; i++){
		Triangle tri=scene.Get_Tri(i);
		temp=Intersection_Triangle(ray, tri);
		t=temp.GetDistance();
		if(t!=-1 && mindist<t){
			obj=2;
			obj_list=i;
			intersectionhit=temp;
		}
	}
	for(int j=0; j<SphereCount; j++){
		Sphere sphere=scene.Get_Sphere(j);
		if(sphere.GetTTransform()>0){
			//cout<<"aye";
			Ray tempRay=ray;
			for (int a = 0; a < sphere.GetTTransform(); a++)
			{
				Point scale=sphere.GetTransformSphere(a);
				tempRay.setRay(InvTransformScale
					(scale,tempRay.getPosition()),InvTransformScale(scale,tempRay.getDirection()));
			}
			temp=Intersection_Sphere(tempRay,sphere);
			t=temp.GetDistance();
		}
		else{
			temp=Intersection_Sphere(ray, sphere);
			t=temp.GetDistance();
		}
		if(t!=-1 && mindist<t){
			obj=1;
			obj_list=j;
			intersectionhit=temp;
		}
	}
	intersectionInfo.Set_Intersection(obj,obj_list);
	intersectionInfo.SetIntersectionPoint(intersectionhit);
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
	return Nfovy*aspectRatio;
}

float GetDirectionA(float fov, float size, int var){
	float direction=fov*((float)var-((float)size/2))/(size/2);
	return direction;
}

float GetDirectionB(float fov, float size, int var){
	float direction=fov*((size/2)-(float)var)/(size/2);
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
	float a=GetDirectionA(Nfovx, width, j);
	float b=GetDirectionB(Nfovy, height, i);
	temp=ComputeRay(cam,norm,a,b);
	return temp;
}

//---------------------- Hint Color --------------------------------------------

Color FindColor(Intersection hit, Scene scene,Ray ray){
	Color Background;
	Color Object;
	if(hit.Get_Obj()>0){
		IntersectionPoint hitpoint=hit.GetInterSectionPoint();
		Object.AddColor(scene.Get_Ambient());
		if (hit.Get_Obj()==1)
		{
			Sphere sphere=scene.Get_Sphere(hit.Get_ObjList());
			Object.AddColor(sphere.GetEmission());
			//cout<<Object.GetRed()<<" "<<Object.GetGreen()<<" "<<Object.GetBlue()<<'\n';
			for (int i = 0; i < scene.Get_LightCount(); i++)
			{
				Light light=scene.Get_Light(i);
				Color lightcolor=light.getColor();
				// Li = Bisa Berubah
				float Li=1;
				Point VertPost=hitpoint.GetInterSectionPoint();
				Point Position=ray.getPosition();
				//cout<<"VertPost:"<<VertPost.GetX()<<" "<<VertPost.GetY()<<" "<<VertPost.GetZ()<<'\n';
				Vector ViewDir(Position.GetX()-VertPost.GetX(),Position.GetY()-VertPost.GetY(),Position.GetZ()-VertPost.GetZ());
				ViewDir.normalize();
				//cout<<"ViewDir:"<<ViewDir.GetX()<<" "<<ViewDir.GetY()<<" "<<ViewDir.GetZ()<<'\n';
				Point LightPos=light.getPosition();
				//cout<<"LightPost:"<<LightPos.GetX()<<" "<<LightPos.GetY()<<" "<<LightPos.GetZ()<<'\n';
				Vector LightDir(LightPos.GetX()-VertPost.GetX(),LightPos.GetY()-VertPost.GetY(),-1*(LightPos.GetZ()-VertPost.GetZ()));
				LightDir.normalize();
				//cout<<"LightDir:"<<LightDir.GetX()<<" "<<LightDir.GetY()<<" "<<LightDir.GetZ()<<'\n';
				Vector Normal=hitpoint.GetNormal();
				Normal.normalize();
				//cout<<"Normal:"<<Normal.GetX()<<" "<<Normal.GetY()<<" "<<Normal.GetZ()<<'\n';
				Vector HalfDir(LightDir.GetX()+ViewDir.GetX(),LightDir.GetY()+ViewDir.GetY(),LightDir.GetZ()+ViewDir.GetZ());
				HalfDir.normalize();
				//cout<<"HalfDir:"<<HalfDir.GetX()<<" "<<HalfDir.GetY()<<" "<<HalfDir.GetZ()<<'\n';
				float lamb=LightDir.dotProduct(Normal);
				float spectangle=HalfDir.dotProduct(Normal);
				//cout<<lamb<<"-"<<spectangle<<'\n';
				if(lamb<0)lamb=0;
				if(spectangle<0)spectangle=0;
				Color HasilLamb=dotColor(sphere.GetDiffuse(),lamb);
				//cout<<HasilLamb.GetRed()<<" "<<HasilLamb.GetGreen()<<" "<<HasilLamb.GetBlue()<<'\n';
				Color HasilSpec=dotColor(sphere.GetSpecular(),pow(spectangle,sphere.GetShiness()));
				HasilLamb.AddColor(HasilSpec);
				//cout<<HasilLamb.GetRed()<<" "<<HasilLamb.GetGreen()<<" "<<HasilLamb.GetBlue()<<'\n';
				//HasilLamb.SetRGB(pow(HasilLamb.GetRed(),sphere.GetShiness()),pow(HasilLamb.GetGreen(),sphere.GetShiness()),pow(HasilLamb.GetBlue(),sphere.GetShiness()));
				//cout<<HasilLamb.GetRed()<<" "<<HasilLamb.GetGreen()<<" "<<HasilLamb.GetBlue()<<'\n';
				HasilLamb.SetRGB(HasilLamb.GetRed()*lightcolor.GetRed(),HasilLamb.GetGreen()*lightcolor.GetGreen(),HasilLamb.GetBlue()*lightcolor.GetBlue());
				//cout<<HasilLamb.GetRed()<<" "<<HasilLamb.GetGreen()<<" "<<HasilLamb.GetBlue()<<'\n';
				Object.AddColor(HasilLamb);
				//cout<<Object.GetRed()<<" "<<Object.GetGreen()<<" "<<Object.GetBlue()<<'\n';
				//system("PAUSE");

			}
		}
		else if (hit.Get_Obj()==2)
		{
			Triangle tri=scene.Get_Tri(hit.Get_ObjList());
			Object.AddColor(tri.GetEmission());
			for (int i = 0; i < scene.Get_LightCount(); i++)
			{
				Light light=scene.Get_Light(i);
				// Li = Bisa Berubah
				float Li=1;
				// Hi Half Angle
				Point VertPost=hitpoint.GetInterSectionPoint();
				Vector ViewDir(VertPost.GetX()*-1,VertPost.GetY()*-1,VertPost.GetZ()*-1);
				ViewDir.normalize();
				Point LightPos=light.getPosition();
				Vector LightDir(LightPos.GetX()-VertPost.GetX(),LightPos.GetY()-VertPost.GetY(),LightPos.GetZ()-VertPost.GetZ());
				LightDir.normalize();
				Vector Normal=hitpoint.GetNormal();
				Vector HalfDir(LightDir.GetX()+ViewDir.GetX(),LightDir.GetY()+ViewDir.GetY(),LightDir.GetZ()+ViewDir.GetZ());
				HalfDir.normalize();
				float lamb=LightDir.dotProduct(Normal);
				if(lamb<0)lamb=0;
				float spectangle=HalfDir.dotProduct(Normal);
				if(spectangle<0)spectangle=0;
				Object.AddColor(dotColor(tri.GetDiffuse(),lamb));
				Object.AddColor(dotColor(tri.GetSpecular(),pow(spectangle,tri.GetShiness())));
				//cout<<lamb<<"-"<<spectangle<<'\n';
			}

		}
		return Object;
	}
	else{
		Background.SetRGB(0,0,0);
		return Background;
	}
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
			Color image=FindColor(hit, scene,ray);
			color.rgbGreen=image.NormalizeG();
			color.rgbBlue=image.NormalizeB();
			color.rgbRed=image.NormalizeR();
			FreeImage_SetPixelColor(bitmap,j,height-i-1,&color);
		}
	}
	if(FreeImage_Save(FIF_PNG,bitmap,output,0))
		cout<<"Image berhasil dicetak";
	FreeImage_DeInitialise();
}

//  ---------------------- Main Program.c -----------------------------------

int main(int argc, char *argv[])
{
	Light light;
	Color ambient, emmision, diffuse, specular,LightColor; 
	Point posisiKamera[4], posisiLight;
	Scene scene;
	float a,b,c,fov,width,height,R,G,B, shiness;
	int jmlInput, jmlTrans, inpTransformasi, inpBenda, jmlLight;
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
	cout<<"Masukkan Warna Ambient :";
	cin>>R>>G>>B;
	ambient.SetRGB(R,G,B);
	scene.Add_Ambient(ambient);
	cout<<"Masukkan Jumlah Light :";
	cin>>jmlLight;
	for (int i = 0; i < jmlLight; i++)
	{
		cout<<"Masukkan Variabel Light : (Position dan RGB :) \n";
		cin>>a>>b>>c>>R>>G>>B;
		LightColor.SetRGB(R,G,B);
		posisiLight.SetXYZ(a,b,c);
		light.setLight(posisiLight,LightColor);
		scene.Add_Light(light);
	}
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
			cout<<"Masukkan Warna Emission :";
			cin>>R>>G>>B;
			emmision.SetRGB(R,G,B);
			sphere.SetEmission(emmision);
			cout<<"Masukkan Warna Diffuse :";
			cin>>R>>G>>B;
			diffuse.SetRGB(R,G,B);
			sphere.SetDiffuse(diffuse);
			cout<<"Masukkan Warna Specular :";
			cin>>R>>G>>B;
			specular.SetRGB(R,G,B);
			sphere.SetSpecular(specular);
			cout<<"Masukkan Shiness :";
			cin>>shiness;
			sphere.SetShiness(shiness);
		}
		else if(inpBenda==2)
		{
			cout<<"Masukkan inputan segitiga (x,y,z): \n";
			cin>>x1>>y1>>z1>>x2>>y2>>z2>>x3>>y3>>z3;
			Tri1.SetXYZ(x1,y1,z1);
			Tri2.SetXYZ(x2,y2,z2);
			Tri3.SetXYZ(x3,y3,z3);
			tri.SetTriangle(Tri1,Tri2,Tri3);
			cout<<"Masukkan Warna Emission :";
			cin>>R>>G>>B;
			emmision.SetRGB(R,G,B);
			tri.SetEmission(emmision);
			cout<<"Masukkan Warna Diffuse :";
			cin>>R>>G>>B;
			diffuse.SetRGB(R,G,B);
			tri.SetDiffuse(diffuse);
			cout<<"Masukkan Warna Specular :";
			cin>>R>>G>>B;
			specular.SetRGB(R,G,B);
			tri.SetSpecular(specular);
			cout<<"Masukkan Shiness :";
			cin>>shiness;
			tri.SetShiness(shiness);
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
				else if(inpBenda==2)
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
