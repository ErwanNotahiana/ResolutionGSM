/**		RAMANGASON Notahiana Erwan
 * 		L3 MISA, promotion 2024
 * 		erwan.ramangason@gmail.com
 * 		+261 34 85 670 14
 * 
 * 		Résolution par la méthode de puissance itéré(20-09-2022)	
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

//prototype des fonctions
void lecture(int& taille, vector<vector<float>>& matrice, vector<float>& b);
float pdtScalaireVect(int taille, vector<float> a, vector<float> b);
vector<float> pdtScalaireMat(int taille, vector<vector<float>> A, vector<float> b);
vector<float> init_vect(int taille);
float norme(int taille, vector<float> v);
vector<float> diviseVect(int taille, vector<float> v, float d);
vector<float> puissanceItere(int taille, vector<vector<float>> A, vector<float> x);
void affiche_vect(int taille, vector<float> v);
///void deflation(int taille, vector<vector<float>> A, vector<float> x);

//fonction principal
int main(){
	cout<<"Méthode de puissance itéré"<<endl<<endl;
	
	int n;
	vector<float> x, u;
	vector<vector<float>> A;
	
	lecture(n, A, x);
	x=puissanceItere(n, A, x);
	affiche_vect(n, x);
	
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


///Cette fonction renvoie le produit scalaire de 2 vector
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

///Cette fonction renvoie la norme d'un vecteur
float norme(int taille, vector<float> v){
	float s(0);
	for(int i=0; i<taille; i++)
		s = s + (v[i]*v[i]);
	return sqrt(s);
}

///Cette fonction nous permettra de diviser notre vecteur par un scalaire
vector<float> diviseVect(int taille, vector<float> v, float d){
	vector<float> u;
	u=init_vect(taille);
	for(int i=0; i<taille; i++)
		u[i]=v[i]/d;
	return u;
}

///Ici c'est l'implémentation de l'algorithme
vector<float> puissanceItere(int taille, vector<vector<float>> A, vector<float> x){
	vector<float> y;
	float lamb0, lamb1, normeX;
	int iteration(0);
	lamb0=1000000;
	y=init_vect(taille);
	do{
		iteration++;
		normeX=  norme(taille, x);
		cout<<"La norme de x est: "<<normeX<<endl;
		
		y=diviseVect(taille, x, normeX);
		affiche_vect(taille, y);
		x=pdtScalaireMat(taille, A, y);
		affiche_vect(taille, x);
		
		lamb0=lamb1;
		lamb1=pdtScalaireVect(taille, x, y);
	}while(fabs(lamb0-lamb1)>0.000001);
	cout<<"On  réalisé "<<iteration<<" itérations!"<<endl;
	cout<<"On a comme valeur propre lamba = "<<lamb1<<endl;
	
	return y;
}
///Cette fonction affiche notre vecteur.	
void affiche_vect(int taille, vector<float> v){
	cout<<"Le vecteur propre associé est donc: "<<endl;
	for(int i=0; i<taille;i++)
		cout<<v[i]<<"\n"<<endl;
}

/*//Enfin la déflation est donné par la fonction suivante
void deflation(int taille, vector<vector<float>> A, vector<float> x){
	vector<float> y;
	y=init_vect(taille);
	
	for(int i=0; i<taille; i++){
		y=puissanceItere(taille, A, x)
	*/	
