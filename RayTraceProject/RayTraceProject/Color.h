#ifndef COLOR_H_INCLUDED
#define COLOR_H_INCLUDED

//  ------------------  Class Point ----------------------

class Color{
private:
	float red,green,blue;
public:
	Color();
	Color(float,float,float);
	float GetRed(){
		return red;
	}
	float GetGreen(){
		return green;
	}
	float GetBlue(){
		return blue;
	}
	void SetRGB(float a, float b, float c){
		red=a;
		green=b;
		blue=c;
	}
	void SetRed(float a){
		red=a;
	}
	void SetGreen(float b){
		green=b;
	}
	void SetBlue(float c){
		blue=c;
	}
	float NormalizeR(){
		float temp=red*255;
		if (temp>255)
		{
			return 255;
		}
		return temp;
	}
	float NormalizeG(){
	float temp=green*255;
		if (temp>255)
		{
			return 255;
		}
		return temp;
	}
	float NormalizeB(){
	float temp=blue*255;
		if (temp>255)
		{
			return 255;
		}
		return temp;	
	}

	void AddColor(Color temp){
		red=red+temp.GetRed(); 
		green=green+temp.GetGreen(); 
		blue=blue+temp.GetBlue();
	}

};

Color::Color(float a, float b, float c){
	red=a;
	green=b;
	blue=c;
}
Color::Color(){
	red=0;
	green=0;
	blue=0;
};

Color dotColor(Color temp, float a){
	Color res;
	res.SetRed(temp.GetRed()*a);
	res.SetGreen(temp.GetGreen()*a);
	res.SetBlue(temp.GetBlue()*a);
	return res;
}


#endif