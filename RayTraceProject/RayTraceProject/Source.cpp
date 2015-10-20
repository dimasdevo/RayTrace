#include <iostream>
#include <math.h>

#define VECTOR 3
#define WIDTH 100
#define LENGTH 100

using namespace std;

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
	void SetX(float a){
		x=a;
	}
	void SetY(float b){
		y=b;
	}
	void SetZ(float c){
		z=c;
	}
};

Point::Point(float a, float b, float c){
	x=a;
	y=b;
	z=c;
}
Point::Point(){};

//	-------------------	   Class Ray	----------------------------
class Ray{
private:
	Point Position;
	Point Direction;
	float t_min, t_max;
public:
	Ray(Point);
	Ray();
	void setRay(Point temp){
		Position=temp;
	};
	Point getRay(){
		return Position;
	};
};

Ray::Ray(Point temp){
	Position=temp;
}

Ray::Ray(){}
//	-------------------	   Class Camera	----------------------------
class Camera{
private:
	Point lookfrom, lookto, up;
public:
	Camera(Point, Point, Point);
	
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
};


Camera::Camera(Point a, Point b, Point c){
	lookfrom=a;
	lookto=b;
	up=c;
}
// ----------------- Codingan Part 1 (Camera Position)---------------------------------------------

// -----------------  Get Variable UVW (Faishal)---------------------------------------
Camera NormalizeUVW(Camera cam){
	Camera temp=cam;
	return temp;
}


float GetDirectionA(float fov, int size, int var){
	float direction=((float)var-(size/2))/size;
	return direction;
}

float GetDirectionB(float fov, int size, int var){
	float direction=((float)(size/2)-var)/size;
	return direction;
}

Ray ComputeRay(Camera cam, Camera normCam, float a, float b){
	Ray temp;
	float n;
	Point temp0, temp1[3], temps, tempp;
	temp0=cam.GetLookFrom();
	temp1[0]=normCam.GetLookFrom();
	temp1[1]=normCam.GetLookTo();
	temp1[2]=normCam.GetUp();
	
	temps.SetX(temp1[0].GetX()*a+temp1[1].GetX()*b-temp1[2].GetX());
	temps.SetY(temp1[0].GetX()*a+temp1[1].GetX()*b-temp1[2].GetX());
	temps.SetZ(temp1[0].GetX()*a+temp1[1].GetX()*b-temp1[2].GetX());
	
	n=sqrt((temps.GetX()*temps.GetX())+(temps.GetY()*temps.GetY())+(temps.GetZ()*temps.GetZ()));
	
	tempp.SetX(temp0.GetX()+(temps.GetX()/n));
	tempp.SetY(temp0.GetY()+(temps.GetY()/n));
	tempp.SetZ(temp0.GetZ()+(temps.GetZ()/n));

	cout<<tempp.GetX()<<" "<<tempp.GetY()<<" "<<tempp.GetZ()<<'\n';
	cout<<temp1[0].GetX()<<" "<<temp1[0].GetY()<<" "<<temp1[0].GetZ()<<'\n';
	cout<<temp1[1].GetX()<<" "<<temp1[1].GetY()<<" "<<temp1[1].GetZ()<<'\n';
	cout<<temp1[2].GetX()<<" "<<temp1[2].GetY()<<" "<<temp1[2].GetZ()<<'\n';


	system("PAUSE");
	return temp0;
}

Ray RayThruPixel(Camera cam, int i, int j){
	Ray temp;
	Camera normCam = NormalizeUVW(cam);
	normCam.print();
	system("PAUSE");
	float a=GetDirectionA(1, WIDTH, j);
	float b=GetDirectionB(1, LENGTH, i);
	temp=ComputeRay(cam,normCam,a,b);
	return temp;
}


//  --------------------- RayTrace Algorithm --------------------------------------
void RayTrace(Camera cam, int width, int height){
	for(int i=0; i<width; i++){
		for(int j=0; j<height; j++){
			Ray ray=RayThruPixel(cam, i, j);
		}
	}
}

//  ---------------------- Main Program.c -----------------------------------

int main(int argc, char *argv[]){
	Point posisiKamera[4];
	float a,b,c;
	cout<<"Masukkan koordinat kamera: \n";
	for(int i=0; i<VECTOR; i++){
		cin>>a>>b>>c;
		posisiKamera[i].SetX(a);
		posisiKamera[i].SetY(b);
		posisiKamera[i].SetZ(c);
	}
	Camera A(posisiKamera[0], posisiKamera[1], posisiKamera[2]);
	A.print();
	system("PAUSE");
	RayTrace(A,WIDTH,LENGTH);
	return 0;
}