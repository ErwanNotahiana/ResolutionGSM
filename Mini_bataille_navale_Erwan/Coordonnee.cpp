#include "Coordonnee.hpp"
#include <iostream>

using namespace std;

Coordonnee::Coordonnee(){
	x=0;
	y=0;
}

Coordonnee::Coordonnee(int a, int b){
	x=a;
	y=b;
}

int Coordonnee::getX(){return x;}
int Coordonnee::getY(){return y;}

void Coordonnee::setX(int a){x=a;}
void Coordonnee::setY(int b){y=b;}

bool operator == (Coordonnee point1, Coordonnee point2){
	if(point1.getX()==point2.getX() && point1.getY()==point2.getY())
		return true;
	else
		return false;
}
