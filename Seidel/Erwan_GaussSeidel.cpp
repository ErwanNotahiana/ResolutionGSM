/**		RAMANGASON Notahiana Erwan
 * 		L3 MISA, promotion 2024
 * 		erwan.ramangason@gmail.com
 * 		+261 34 85 670 14
 * 
 * 		Résolution par la méthode de Gauss-Seidel	(23-08-2022)	
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
//#define eps 0.000001 ;

using namespace std;

//On commence toujours par les prototypes des fonctions
void lecture(int& taille, vector<vector<float>>& matrice, vector<float>& b);
void affiche_pb(int taille, vector<vector<float>> matriceAug);
void augmente(int taille, vector<vector<float>> matrice, vector<vector<float>>& matriceAup, vector<float> b);
void seidel(int taille, vector<float>& x, vector<vector<float>> matriceAug);

int main(){
	cout<<"Méthode de Gauss-Seidel"<<endl<<endl;
	
	vector<vector<float>> A;
	vector<vector<float>> aug;
	vector<float> b, x;
	int n;
	
	///On va commencer par initialiser toute nos variables
	lecture(n, A, b);
	augmente(n,A,aug,b);
	affiche_pb(n,aug);

	///On passe ensuite a la résolution du probleme 
	seidel(n,x,aug);
	
	return 0;
}

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

///Cette fonction va afficher le probleme
void affiche_pb(int taille, vector<vector<float>> matriceAug){
	cout<<endl<<endl;
	for(int i=0; i<taille; i++){
		for(int j=0; j<taille; j++)
			cout<<"+ "<<matriceAug[i][j]<< " .x["<<j+1<<"]\t";
		cout<<" = \t "<<matriceAug[i][taille];
		cout<<"\n \n";	
	}
}

///C'est avec cette fonction que l'on va créer notre matrice augmentée
void augmente(int taille, vector<vector<float>> matrice, vector<vector<float>>& matriceAup, vector<float> b){
	vector<float> ligne;
	for(int i=0; i<taille; i++){
		matriceAup.push_back(ligne);
		for(int j=0; j<taille; j++)
			matriceAup[i].push_back(matrice[i][j]);
		matriceAup[i].push_back(b[i]);
	}
}
///Enfin on retrouve la résolution du système par la méthode de Gauss-Seidel
void seidel(int taille, vector<float>& x, vector<vector<float>> matriceAug){
	///On va d'abord stocker les résidu, aura besoin de leur somme pour voir quand s'arreter
	vector<float> res;
	float sr(0), s(0);
	int iterateur(0);
	///Pour que le programme converge plus rapidement, on va initialiser les xi par 1
	for(int i=0; i<taille; i++){
		x.push_back(1);
		res.push_back(0);	///Celle ci doit etre nulle pour y stocker les résidu
	}		
	///A l'aide de l'algoritme, on va maintenanr chercher le résidu
    for(int i = 0; i < taille; i++) {
        s=0;
        for(int j=0; j<taille; j++)
            s+= (matriceAug[i][j]*x[j]);
        res[i]= matriceAug[i][taille]-s;
        ///le résidu est la somme des valeur absolue ce vector
        sr+= fabs(res[i]);
    }
    s=0;
    ///Avec le résidu, on peut maintenant chercher les approximations selon le niveau d'erreur recherché
	float eps(0.00001);
	while(sr>eps){
		for(int i=0; i<taille; i++){
			s=0;
			for(int j=0; j<taille; j++)
				s+=matriceAug[i][j]*x[j];
			res[i]= matriceAug[i][taille]-s;
			x[i] += (res[i]/matriceAug[i][i]);
		}
		///On calcule de nouveau le résidu pour que l'approximation soit proche, on va aussi afficher le nombre d'itération jusqu'à la fin de la boucle
		sr=0;
		for(int i=0; i<taille; i++)
			sr+= fabs(res[i]);
		iterateur++;
		if(iterateur==100)
			break;
	}
	///Enfin, on va avoir les réponses:
	cout<<"On obtient les approoximations au bout de "<<iterateur<<"opérations. On a alors"<<endl;
	for(int i=0; i<taille; i++){
		cout<<"x["<<i+1<<"] = "<<x[i]<<"\t";
		cout<<endl<<endl;
	}
}
		
	
