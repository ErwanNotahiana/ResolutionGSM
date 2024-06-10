/*	RAMANGASON Notahiana Erwan
  	L3 MISA promotion 2024
	erwan.ramangason@gmail.com
	+261 34 85 670 14
	
  	Methode du pivot de Gauss*/
 
 #include <iostream>
 #include <cmath>
 #include <vector>
 #include <fstream>

using namespace std;

//On voit ici les prototypes de fonctions
void lecture(int& taille, vector<vector<float>>& matrice, vector<float>& b);
void affiche_mat(int taille, vector<vector<float>>& matrice, vector<float>& b);
///void resolution(int taille, vector<vector<float>>& matrice, vector<float>& b);
void solution(int taille, vector<vector<float>>& matrice, vector<float>& b);
void resolv_pivotage(int taille, vector<vector<float>>& matrice, vector<float>& b);
void exchange(vector<float>* pivot, vector<float>* iterateur);
void maximum(int taille, int& indicePivot, int debut, float& max, vector<vector<float>>& matrice);

//On a ici la fonction principale
int main(){
	cout<<"Diagonalisation de matrice et résolution de systèmes"<<endl<<endl;
	
	int n;
	vector < vector<float> > mat;
	vector<float> b;	///Il s'agi ici du 2nd membre
	
	lecture(n, mat, b);
	affiche_mat(n, mat, b);
	///resolution(n, mat, b);
	resolv_pivotage(n, mat, b);
	affiche_mat(n, mat, b);
	solution(n,mat,b);
		
	return 0;
}

//Ici on a les fonctions que l'on utilise
///Il nous faut une fonction qui affiche la matrice
void affiche_mat(int taille, vector<vector<float>>& matrice, vector<float>& b){
	cout<<endl<<endl;
	for(int i=0; i<taille; i++){
		for(int j=0; j<taille; j++)
		cout<< matrice[i][j]<< "\t";
		cout<<"\t | \t "<<b[i];
		cout<<"\n \n";	
	}
}
/**Cette fonction est la méthode de Gauss sans pivotage partiel, nous nous servirons dans notre programme de celle avec pivotage
void resolution(int taille, vector<vector<float>>& matrice, vector<float>& b){
	for(int k=0; k<taille-1; k++){
		for(int i=k+1; i<taille; i++){
			for(int j=k+1; j<taille; j++)
				matrice[i][j]=matrice[i][j]-(matrice[i][k]/matrice[k][k])*matrice[k][j];
		b[i]=b[i]-(matrice[i][k]/matrice[k][k])*b[k];
		matrice[i][k]=0;
		}
	}
}	*/
///Cette fonction nous donne les solutions de notre problème après avoir  utilisé la méthode de Gauss pour triagonaliser la matrice
void solution(int taille, vector<vector<float>>& matrice, vector<float>& b){
	cout<<"Les solutions sont donc: "<<endl;
	float s(0);
	///On utiliseras un vector pour contenir les solutions
	vector<float> x;
	x.clear();
	for(int i=0; i<taille; i++)
		x.push_back(0);
	//float x[taille] = {0};
	for(int i=taille-1; i>=0; i--){
		///Ici on calcul les solutions finales suite a la résolution du système triangulaire supérieur
		s=0;		
		for(int j =i+1;j<taille; j++)
			s+=(matrice[i][j]*x[j]);
		x[i]=(b[i]-s)/matrice[i][i];
	}
	///Et on affiche le résultat
	for(int i=0; i<taille; i++)
		cout<< "x["<<i+1<<"]= "<<x[i]<<" \t ";
	cout<<endl<<endl;
}
///C'est ici que se passe la lecture et l'implémentation des données rentrées dans notre fichier texte
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
///C'est ici que l'on permute les lignes après avoir choisit le pivot le plus élevé
void exchange(int l, int taille, int i, vector<vector<float>>& matrice, vector<float>& b){
	///On permute la matrice
	vector<float> tempa;
			tempa=matrice[i];
			matrice[i]=matrice[l];
			matrice[l]=tempa;
	///On permute la 2e colonne	
	float tempb;
		tempb=b[i];
		b[i]=b[l];
		b[l]=tempb;
	}
///C'est ici que se trouve la méthode de Gauss avec pivotage partiel
void resolv_pivotage(int taille, vector<vector<float>>& matrice, vector<float>& b){
	///Il s'agit de l'indice du coefficient maximum, qui sera notre pivot
	int indiceMax(0);		
	///On utilisera cette variable pour stocker la valeur la plus élevé (notre pivot)
	float max;
	for(int k=0; k<taille; k++){
		///On initialisera notre pivot à la position la plus haute
		indiceMax=k;
		///On cherchera la valeur maximale sur la colonne, et on la considèrera comme pivot
		maximum(taille, indiceMax, k, max, matrice);
		///On permtera ensuite la place du pivot pour qu'il soit sur la diagonale, afin d'avoir une forme triangulaire
		exchange(indiceMax, taille,k, matrice, b);
		///On affichera l'échelonnage a chaque étape pour vérifier nos opérations
		affiche_mat(taille, matrice, b);
		cout<<endl<<endl;
		///Maintenant nous allons échelonner cette colonne, on implémente l'algorithme
		for(int i=k+1; i<taille; i++){
			for(int j=k+1; j<taille; j++)
				matrice[i][j]=matrice[i][j]-(matrice[i][k]*matrice[k][j]/matrice[k][k]);
		b[i]=b[i]-(matrice[i][k]/matrice[k][k])*b[k];
		matrice[i][k]=0;
		}
	}
}
///Enfin cette fonction recherche notre pivot, qui sera la valeur la plus élevé de notre colonne	
void maximum(int taille, int& indicePivot, int debut, float& max, vector<vector<float>>& matrice){
	max=fabs(matrice[debut][debut]);
	for(int i=debut+1; i<taille; i++){
		if(fabs(matrice[i][debut])>max){
			max=fabs(matrice[i][debut]);
			indicePivot=i;
		}
	}
}
			
