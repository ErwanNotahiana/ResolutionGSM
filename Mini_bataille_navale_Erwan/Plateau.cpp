#include "Plateau.hpp"
#include <iostream>

using namespace std;

///Constructeurs
Plateau::Plateau(){
	caractere='~';
	for(int i=0; i<12; i++){
		for(int j=0; j<12; j++)
			mer[i][j]=caractere;
	}
}

Plateau::Plateau(char c){
	caractere=c;
}

///Accesseur et muteur
char Plateau::getCaractere(){return caractere;}
char Plateau::getCase(int i, int j){return mer[i][j];}

void Plateau::setCaractere(char c){caractere=c;}
void Plateau::setCase(char c, int i, int j){mer[i][j]=c;}

///Autres
void Plateau::display(){
	///On va afficher les coordonnées de chaque case avec le tableau
	cout<<"\t";
	for(int i=0; i<12; i++)
		cout<<" "<<i<<" ";
	cout<<endl;
	
	///On affiche ensuite le reste du tableau
	for(int i=0; i<12; i++){
		cout<<" "<<i<<".\t";
		for(int j=0; j<12; j++)
			cout<<" "<<mer[j][i]<<" ";
		cout<<endl;
	}
}
	 
