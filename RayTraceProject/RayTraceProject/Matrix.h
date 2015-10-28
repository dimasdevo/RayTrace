#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

#include "Vector.h"
#include <iostream>

using namespace std;
//	-------------------	   Class Camera	----------------------------
class Matrix{
private:
	Vector X, Y, Z;
public:
	Matrix(Vector, Vector, Vector);

	Vector GetX(){
		return X;
	}

	Vector GetY(){
		return Y;
	}

	Vector GetZ(){
		return Z;
	}

};


Matrix::Matrix(Vector a, Vector b, Vector c){
	X=a;
	Y=b;
	Z=c;
}

#endif