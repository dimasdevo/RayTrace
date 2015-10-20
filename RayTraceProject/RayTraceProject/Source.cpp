#include <iostream>

#define VECTOR 3
#define WIDTH 100
#define LENGTH 100

using namespace std;
//	-------------------	   Class Ray	----------------------------
class Ray{
private:
	float position[4];
public:
	Ray(float*);
	Ray();
	void setRay(float a[]){
		for(int i=0; i<VECTOR; i++){
			position[i]=a[i];
		}
	};
	float* getRay(){
		return position;
	};
};

Ray::Ray(float a[]){
	for(int i=0; i<VECTOR; i++){
		position[i]=a[i];
	}
}

Ray::Ray(){}


//	-------------------	   Class Camera	----------------------------
class Camera{
private:
	float lookfrom[4], lookto[4], up[4];
public:
	Camera(float*, float*, float*);
	void print(){
		for(int i=0; i<VECTOR; i++){
			printf("%f %f %f\n", lookfrom[i], lookto[i],up[i]);
		}
	}
	float* getEye(){
		return lookfrom;
	}
};


Camera::Camera(float a[], float b[], float c[]){
	for(int i=0; i<VECTOR; i++){
		lookfrom[i]=a[i];
		lookto[i]=b[i];
		up[i]=c[i];
	}
}
// ----------------- Codingan Part 1 (Camera Position)---------------------------------------------

// -----------------  Get Variable UVW (Faishal)---------------------------------------
Camera NormalizeUVW(Camera cam){
	Camera temp=cam;
	return temp;
}


float GetDirectionA(float fov, int size, int var){
	float direction=(var-(size/2))/size;
	return direction;
}

float GetDirectionB(float fov, int size, int var){
	float direction=((size/2)-var)/size;
	return direction;
}

Ray ComputeRay(Camera cam, Camera normCam, float a, float b){
	Ray temp;

	return temp;
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
	float posisiKamera[4][4];
	cout<<"Masukkan koordinat kamera: \n";
	for(int i=0; i<VECTOR; i++){
		for(int j=0; j<VECTOR; j++){
			cin>> posisiKamera[i][j];
		}
	}
	Camera A(posisiKamera[0], posisiKamera[1],posisiKamera[2]);
	RayTrace(A,WIDTH,LENGTH);
	return 0;
}