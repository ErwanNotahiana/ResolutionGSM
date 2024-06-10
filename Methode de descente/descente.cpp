/**		RAMANGASON Notahiana Erwan
 * 		L3 MISA, promotion 2024
 * 		erwan.ramangason@gmail.com
 * 		+261 34 85 670 14
 * 
 * 		Résolution par la méthode de descente de gradient(13-09-2022)	
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

//#define eps (0.000001) ;

using namespace std;

//prototype des fonctions
void lecture(int& taille, vector<vector<float>>& matrice, vector<float>& b);
void affiche_mat(int taille, vector<vector<float>> matrice);
void affiche_vect(int taille, vector<float> v);
float norme(int taille, vector<float> v);
float pdtScalaireVect(int taille, vector<float> a, vector<float> b);
vector<float> pdtScalaireMat(int taille, vector<vector<float>> A, vector<float> b);
void descente(int taille, vector<vector<float>> A, vector<float> b);
vector<float> init_vect(int taille);
vector<float> reverseSigne(int taille, vector<float> v);

//Fonction principale
int main(){
	cout << "Methode itérative: descente de gradient"<<endl;
	
	int taille;
	vector<vector<float>> A;
	vector<float> b;
	
	lecture(taille, A, b);
	descente(taille, A, b);
	
	return 0;
}

//Définition des fonctions
///La première fonction nous permet la lectire du fichier par le programme
void lecture(int& taille, vector<vector<float>>& matrice, vector<float>& b){
	///On declare d'abord notre flux
	ifstream donnees("data.txt");
	vector <float> ligne;
	float l;
	///Vérifions d'abors que le flux existe
	if(donnees){
		///On commence par recuperer la taille, elle sea donc mise a la 1ere ligne dans notre ficher
		string str_taille;
		getline(donnees, str_taille);
		taille=stoi(str_taille);
	
		///On va ensuite récuperer les valeurs dans notre matrice, soit les coefficients
		for(int i=0; i<taille; i++){
			///On récupère chaque i-ème ligne de notre matrice
			matrice.push_back(ligne);
			for(int j=0; j<taille; j++){
				l=0;
				donnees >> l;
				matrice[i].push_back(l);
			}
		}
		///Ici on rajoute le 2nd membre, Il sera représenté en vecteur ligne dans notre fichier
		for(int k=0; k<taille; k++){
			l=0;
			donnees >> l;
			b.push_back(l);
		}
	}
	///Si il n'y a pas d'erreur, le code se déroulera normalement
	else
		cout<<"ERREUR!!!"<<endl;
}

///Ensuite, on a ici 2 fonctions qui servent à l'affichage
void affiche_mat(int taille, vector<vector<float>> matrice){
	cout<<endl<<endl;
	for(int i=0; i<taille; i++){
		for(int j=0; j<taille; j++)
		cout<< matrice[i][j]<< "\t";
	cout<<"\n \n";	
	}
}
void affiche_vect(int taille, vector<float> v){
	cout<<endl<<endl;
	for(int i=0; i<taille;i++)
		cout<<v[i]<<"\n"<<endl;
}

///Cette fonction renvoie la norme d'un vecteur
float norme(int taille, vector<float> v){
	float s(0);
	for(int i=0; i<taille; i++)
		s = s + (v[i]*v[i]);
	return sqrt(s);
}

///Cette fonction renvoiie le produit scalaire de 2 vector
float pdtScalaireVect(int taille, vector<float> a, vector<float> b){
	float s(0);
	for(int i=0; i<taille; i++)
		s = s + (a[i]*b[i]);
	return s;
}
vector<float> init_vect(int taille){
	vector<float> v; 
	for(int i=0; i<taille; i++)
		v.push_back(0);
	return v;
}
///Cette fonction renvoie le produit d'une matrice avec un vecteur
vector<float> pdtScalaireMat(int taille, vector<vector<float>> A, vector<float> b){
	vector<float> r;
	r=init_vect(taille);
	for(int i=0; i<taille; i++){
		for(int j=0; j<taille; j++)
			r[i] = r[i] + b[j]*A[i][j];
	}
	return r;
} 
///C'est ici  qu'on implémente l'algorithme de descente de gradient
void descente(int taille, vector<vector<float>> A, vector<float> b){
	vector<float>  x, r, z, y;		///x est la solution, r est le résidu,(en vecteur)
	float direction(1);			///alpha, représente la direction emprunté lors de la descente
	int iteration(0);
	x=init_vect(taille);
	r=init_vect(taille);
	z=init_vect(taille);
	y=init_vect(taille);
	
	cout<<"Rentrez les coordonées de x: "<<endl;
	for(int i=0; i<taille; i++){
		cin>>r[i];
	//	cout<<" ,\t ";
	}
	y=pdtScalaireMat(taille, A, x);
	for(int i=0; i<taille; i++)
		r[i] = b[i] - y[i];
		
	while(norme(taille, r) >0.000001){
		z= pdtScalaireMat(taille, A, r);
		z=reverseSigne(taille, z);
		direction = (norme(taille, r)*norme(taille, r))/pdtScalaireVect(taille, z, r);
		for(int i=0; i<taille; i++){
			x[i] = x[i] - direction*r[i];
		//for(int i=0; i<taille; i++)
			r[i] = r[i] - direction*z[i];}
		iteration++;
		/*if(iteration==30)
			break;*/
	}
	cout<<"On a alors la solution x(";
	for(int i=0; i<taille; i++)
		cout<<x[i]<<",	";
	cout<<"On a aboutit à cette solution au bout de "<<iteration<<" itérations!"<<endl;
}
	
///Utile pour ajouter un moins à un vecteur
vector<float> reverseSigne(int taille, vector<float> v){
	vector<float> u;
	u=init_vect(taille);
	for(int i=0; i<taille; i++)
		u[i]= -v[i];
	return u;
}
