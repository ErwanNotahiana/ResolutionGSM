/*	RAMANGASON Notahiana Erwan
  	L3 MISA promotion 2024
	erwan.ramangason@gmail.com
	+261 34 85 670 14
  	Methode du pivot de Gauss	*/
 
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
	
	///On va commencer par créer une matrice. On aura pour cela besoin de sa taille
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
/**Cette fonction est la méthode de Gauss sans pivotage partiel, nous utiliserons dans notre programme celle avec pivotage partiel
void resolution(int taille, vector<vector<float>>& matrice, vector<float>& b){
	for(int k=0; k<taille-1; k++){
		for(int i=k+1; i<taille; i++){
			for(int j=k+1; j<taille; j++)
				matrice[i][j]=matrice[i][j]-(matrice[i][k]/matrice[k][k])*matrice[k][j];
		b[i]=b[i]-(matrice[i][k]/matrice[k][k])*b[k];
		matrice[i][k]=0;
		}
	}
}*/
///Cette fonction donne les solutions apres avoir utilisé le pivot de Gauss
void solution(int taille, vector<vector<float>>& matrice, vector<float>& b){
	cout<<"Les solutions sont donc: "<<endl;
	float s(0);
	///On va stocker les réponses dans un vector, on va créer ce conteneur
	vector<float> x;
	x.clear();
	for(int i=0; i<taille; i++)
		x.push_back(0);
	//float x[taille] = {0};
	for(int i=taille-1; i>=0; i--){
		s=0;		
		///Nous avons ici l'algorithme  de résolution du triangle supérieur
		for(int j =i+1;j<taille; j++)
			s+=(matrice[i][j]*x[j]);
		x[i]=(b[i]-s)/matrice[i][i];
	}
	for(int i=0; i<taille; i++)
		cout<< "x["<<i+1<<"]= "<<x[i]<<" \t ";
	cout<<endl<<endl;
}
///Cette fonction lit le fichier texte dans lequel on note le probleme, sa dimension... et l'implémente  notre programme
void lecture(int& taille, vector<vector<float>>& matrice, vector<float>& b){
	///On declare d'abord notre flux
	ifstream donnees("data.txt");
	vector <float> ligne;
	float l;
	///On testera toujours le flux
	if(donnees){
		///On commence par recuperer la taille, elle sea donc mise a la 1ere ligne dans notre ficher
		string str_taille;
		getline(donnees, str_taille);
		taille=stoi(str_taille);
		///On va ensuite récuperer les valeurs dans notre matrice, soit les coefficients
		for(int i=0; i<taille; i++){
			///On remplit la i-ème ligne
			matrice.push_back(ligne);
			for(int j=0; j<taille; j++){
				l=0;
				donnees >> l;
				matrice[i].push_back(l);
			}
		}
		///Ici on rajoute le 2nd membre, on le notera sous forme de vecteur ligne. 
		for(int k=0; k<taille; k++){
			l=0;
			donnees >> l;
			b.push_back(l);
		}
	}
	else
		cout<<"ERREUR!!!"<<endl;
}
///Cette fonction nous servira a permuter les lignes apres avoir trouver le pivot maximium
void exchange(int l, int taille, int i, vector<vector<float>>& matrice, vector<float>& b){
	///On permute la matrice..
	vector<float> tempa;
			tempa=matrice[i];
			matrice[i]=matrice[l];
			matrice[l]=tempa;	
	///..puis le 2nd membre
	float tempb;
		tempb=b[i];
		b[i]=b[l];
		b[l]=tempb;
	}
/**C'est ici que se trouve la fonction pour la méthode de Gauss avec pivotage partiel
 * Elle consiste à choisir le pivot le plus élevé et d'intervertir sa place de facon a toujours avoir une matrice triangulaire*/
void resolv_pivotage(int taille, vector<vector<float>>& matrice, vector<float>& b){
	int indiceMax(0);		///Il s'agit de l'indice du maximum, qui sera notre pivot
	float max;				///Une variable qui stock la valeur du pivot maximal
	for(int k=0; k<taille; k++){
		///On prend comme pivot initial le premier coeficient
		indiceMax=k;
		///On cherche ensuite la plus grande valeur pour cette colonne
		maximum(taille, indiceMax, k, max, matrice);
		///On intervertit acev la i-ème colonne
		exchange(indiceMax, taille,k, matrice, b);
		///On va afficher la patrice pour vérifier chaque étape
		affiche_mat(taille, matrice, b);
		cout<<endl<<endl;
		///Maintenant nous allons échelonner cette colonne en implémentant l'algorithme
		for(int i=k+1; i<taille; i++){
			for(int j=k+1; j<taille; j++)
				matrice[i][j]=matrice[i][j]-(matrice[i][k]*matrice[k][j]/matrice[k][k]);
		b[i]=b[i]-(matrice[i][k]/matrice[k][k])*b[k];
		matrice[i][k]=0;
		}
	}
}
///Enfin cette fonction nous permettra de voir quelle valeur (maximal) prendre comme pivot pour chaque ligne
void maximum(int taille, int& indicePivot, int debut, float& max, vector<vector<float>>& matrice){
	///Comme on utilise des floats, on travailleras sur les valeurs absolues quand on compare
	max=fabs(matrice[debut][debut]);
	for(int i=debut+1; i<taille; i++){
		if(fabs(matrice[i][debut])>max){
			max=fabs(matrice[i][debut]);
			indicePivot=i;
		}
	}
}
			
	
	
