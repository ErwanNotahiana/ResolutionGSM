#include <iostream>
#include <ctime>				//ou time.h, bibliotheque de c 
#include <cstdlib>
#include "Bateau.hpp"

///Constructeurs
Bateau::Bateau(){
	etat=true;
}

Bateau::Bateau(bool t, Coordonnee p){
	position=p;
	etat=t;
}

///Accesseurs et muteurs
bool Bateau::getEtat(){return etat;}
Coordonnee Bateau::getPosition(){return position;}

void Bateau::setEtat(bool b){etat=b;}
void Bateau::setPosition(Coordonnee p){position=p;}

///Autres
void Bateau::placeBateau(){
	int a, b;			///Ils serviront de coordonées a notre bateau
		a=rand()%12;
		b=rand()%12;
	
	Coordonnee c(a,b);
	position=c;
}		
	
///Cette derniere fonction ne sera pas affiche dans notre jeu. Elle servira a le tester car elle donne la solution  
void Bateau::verifier(){
	std::cout<<"("<<position.getX()<<","<<position.getY()<<")\t";
}
