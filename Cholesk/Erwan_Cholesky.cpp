/**		RAMANGASON Notahiana Erwan
 * 		L3 MISA, promotion 2024
 * 		erwan.ramangason@gmail.com
 * 		+261 34 85 670 14
 * 
 * 		Résolution par la méthode de Cholesky	(23-08-2022)	
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

//On commence par définir nos prototypes
void lecture(int& taille, vector<vector<float>>& matrice, vector<float>& b);
void affiche_mat(int taille, vector<vector<float>> matrice);
void affiche_vect(int taille, vector<float> v);
vector<float> init_vect(int taille);
vector<vector<float>> init_mat(int taille);
void factorisation(vector<vector<float>> matrice, vector<vector<float>>& lower, int taille);
vector<vector<float>> transpose(vector<vector<float>> mat, int taille);
void forwardSub(int taille, vector<float> b, vector<float>& y, vector<vector<float>> lower);
void backwardSub(int taille, vector<float> y, vector<float>& x, vector<vector<float>> upper);

//Ensuite, passons à la fonction principale
int main(){
	cout<<"Méthode de Cholesky"<<endl<<endl;
	
	vector<vector<float>> A, Low, Up;	
	///Il s'agit de la matrice en question ainsi que les 2 matrices triangulaire issues de la factorisation
	vector<float> b, x, y;
	int n;
	

	//affiche_mat(6,A); affiche_vect(6,b);
	///On commence par créer les matrices et les vecteurs 
	lecture(n,A,b);
	cout<<"On a la matrice A, ainsi que le vecteur associé au problème: "<<endl;
	affiche_mat(n, A);
	affiche_vect(n,b);
	Low=init_mat(n);
	Up=init_mat(n);
	x=init_vect(n);
	y=init_vect(n);
	///On procède ensuite à la factorisation de Cholesky pour avoir la matrice triangulaire inférieur
	factorisation(A, Low, n);
	//affiche_mat(n, Low);
	Up=transpose(Low, n);
	affiche_mat(n, Low);	
	affiche_mat(n, Up);
	///On passe maintenant a la resolution du probleme: On a divisé le problème en 2 équation et on va les resoudre un a un:
	forwardSub(n,b,y,Low);
	backwardSub(n,y,x,Up);
	
	return 0;
}

//On termine par la définition de nos fonctions

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
vector<float> init_vect(int taille){
	vector<float> v; 
	for(int i=0; i<taille; i++)
		v.push_back(0);
	return v;
}
vector<vector<float>> init_mat(int taille){
	vector<float> ligne;
	vector<vector<float>> mat;
	for(int i=0; i<taille; i++){
		mat.push_back(ligne);
		for(int j=0; j<taille; j++)
			mat[i].push_back(0);
	}
	return mat;
}
///Cette fonction nous donne la matrice triangulaire inférieure après la factorisation de Cholesky. On implémantera l'algorithme correspondant
void factorisation(vector<vector<float>> matrice, vector<vector<float>>& lower, int taille){
	float s;
	for(int j=0; j<taille; j++){
		for(int i=j; i<taille; i++){
			if(i==j){
				s=0;
				for(int k=0; k<j; k++)		//
						s+= (lower[i][k]*lower[i][k]);
				lower[i][j]=sqrt(matrice[i][j]-s);
			}
			else{
				s=0;
				for(int k=0; k<j; k++)		//
					s+= (lower[i][k]*lower[j][k]);
				lower[i][j]=(matrice[i][j]-s)/lower[j][j];
			}
		}
	}
}

///En transposant la matrice triangulaire inférieure, on obtient la supérieure, achevant ainsi la factorisation.
vector<vector<float>> transpose(vector<vector<float>> mat, int taille){
	float temp;
	for(int i=0; i<taille; i++){
		for(int j=i+1; j<taille; j++){
			temp=mat[i][j];
			mat[i][j]=mat[j][i];
			mat[j][i]=temp;
		}
	}
	return mat;
}

///On a les 2 calculs pour la résolution du problème ici
void forwardSub(int taille, vector<float> b, vector<float>& y, vector<vector<float>> lower){
	float s(0);
	for(int i=0; i<taille; i++){
		s=0;
		for(int j=0; j<i; j++)
			s+= (y[j]*lower[i][j]);
		y[i]=(b[i]-s)/lower[i][i];
	}
}
void backwardSub(int taille, vector<float> y, vector<float>& x, vector<vector<float>> upper){
	float s(0);
	for(int i=taille-1; i>=0; i--){
		s=0;
		for(int j=i; j<taille; j++)
			s+= (x[j]*upper[i][j]);
		x[i]=(y[i]-s)/upper[i][i];
	}
	///On va maintenant afficher les solutions:
	cout<<"Ainsi, les solutions de notre problème sont donc: "<<endl;
	for(int i=0; i<taille; i++)
		cout<<"x["<<i+1<<"]= "<<x[i]<<"\t";
	cout<<endl;
}
			
	
	
