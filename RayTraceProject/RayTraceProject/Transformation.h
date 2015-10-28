#ifndef TRANSFORMATION_H_INCLUDED
#define TRANSFORMATION_H_INCLUDED

#include "Vector.h"
#include <math.h>

#define PHI 3.14159265

using namespace std;

int round(double d){
        return static_cast<int>(d + 0.5);
}

// ---------------Tranformation Function------------------------- //
Vector TransformTranslate(Vector a, Vector value){
    float temp1, temp2, temp3;
    temp1 = a.GetX() + value.GetX();
    temp2 = a.GetY() + value.GetY();
    temp3 = a.GetZ() + value.GetZ();

    Vector res(temp1,temp2,temp3);
    return res;
}

Vector TransformScale(Vector a, Vector value){
    float temp1, temp2, temp3;
    temp1 = a.GetX() * value.GetX();
    temp2 = a.GetY() * value.GetY();
    temp3 = a.GetZ() * value.GetZ();

    Vector res(temp1,temp2,temp3);
    return res;
}

Vector TransformRotate(Vector a, Vector center, float degree){
    float point1, point2, point3;
    // Koordinat titik yang akan dirotasi
    point1 = a.GetX();
    point2 = a.GetY();
    point3 = a.GetZ();

    float center1, center2, center3;
    // Koordinat sumbu
    center1 = center.GetX();
    center2 = center.GetY();
    center3 = center.GetZ();

    float tempx, tempy, tempz;
    // Sumbu x
    if(center1==1){
        tempx = point1;
        tempy = ( point2 * (round(cos( degree * PHI / 180.0 )*100)/100) ) - ( point3 * (round(sin( degree * PHI / 180.0 )*100)/100) );
        tempz = ( point2 * (round(sin( degree * PHI / 180.0 )*100)/100) ) + ( point3 * (round(cos( degree * PHI / 180.0 )*100)/100) );
    }
    // Sumbu y
    else if(center2==1){
        tempx = ( point3 * (round(sin( degree * PHI / 180.0 )*100)/100) ) + ( point1 * (round(cos( degree * PHI / 180.0 )*100)/100) );
        tempy = point2;
        tempz = ( point3 * (round(cos( degree * PHI / 180.0 )*100)/100) ) - ( point1 * (round(sin( degree * PHI / 180.0 )*100)/100) );
    }
    // Sumbu z
    else{
        tempx = ( point1 * (round(cos( degree * PHI / 180.0 )*100)/100) ) - ( point2 * (round(sin( degree * PHI / 180.0 )*100)/100) );
        tempy = ( point1 * (round(sin( degree * PHI / 180.0 )*100)/100) ) + ( point2 * (round(cos( degree * PHI / 180.0 )*100)/100) );
        tempz = point3;
    }

    Vector res(tempx, tempy, tempz);
    return res;
}
#endif