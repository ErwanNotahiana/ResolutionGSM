/**		RAMANGASON Notahiana Erwan
 * 		M1 MISA (2022 - 2023), promotion 2024
 * 		erwan.ramangason@gmail.com
 * 		+261 34 85 670 14
 * 
 * 		Discrétisation 1D	(01-02-2023)	
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

//Ici nous trouvons les prototypes
double u(double x);
double f(double x);
vector< vector<double> > discretMat(int n, double pas);
void affiche_mat(int taille, vector< vector<double> > matrice, vector<double> b);
vector<double> discretVect(int n, double x0, double pas);
double pas(double x0, double xn, int n);
vector<double> seidel(int taille, vector<double> b, vector<vector<double>> mat);
vector< vector<double> > augmente(int taille, vector<vector<double>> matrice, vector<double> b);
void ecriture(int& taille, vector<double> vect, vector<double> xi);
void entre_donne(int& taille, double& x0, double& xn);
vector<double> division(double x0, int taille, double pas);
void afficheVect(int taille, vector<double> v);
vector<double> pred (int taille, vector<double> x);

//Fonction principale
int main(){
    cout<<"Discrétisation en 1D"<<endl<<endl;
    
    int n(0);
    double h(0), x0, xn;
    vector<double> fi, solution, xi, yi;
    vector< vector<double> > M;

    entre_donne(n, x0, xn);
    h=pas(-4, 4, n);
    cout << "Pas: " << h << endl << endl;
    fi=discretVect(n, -4, h);
    xi = division(x0, n, h);
    cout << "Solution (attendu) :";
    afficheVect(n, xi);
    yi = pred (n, xi);
    cout << "\n \n courbe de repere: ";
    afficheVect(n, yi);
    M=discretMat(n, h);
    cout << "\n \n Affichage de la matrice de notre problème: ";
    affiche_mat(n, M, fi);
    solution = seidel(n, fi, M);
    cout << "\n \n Affichage des aproximations des solutions proposées après Gauss-Seidel" << endl;
    afficheVect(n, solution);
    ecriture(n, solution, xi);

    return 0;
}

//Fonctions
///Cette fonction monte la première matrice de notre problème
vector< vector<double> > discretMat(int n, double pas){
    vector< vector<double> > M;
    vector<double> ligne;
    for (int i=0; i<n; i++){
        M.push_back(ligne);
        for(int j=0; j<n; j++){
            if(i==j)
                M[i].push_back(2.0/(pas*pas));
            else if(i==j-1 || i==j+1)
                M[i].push_back(-1.0/(pas*pas));
            else
                M[i].push_back(0);
        }
    }
    return M;
}
///Affichage de matriec
void affiche_mat(int taille, vector< vector<double> > matrice, vector<double> b){
	cout<<endl<<endl;
	for(int i=0; i<taille; i++){
		for(int j=0; j<taille; j++)
		cout<< matrice[i][j]<< "\t";
		cout<<"\t | \t "<<b[i];
		cout<<"\n \n";	
	}
}
///Il s'agit ici de notre fonction u(x)
double u(double x){
    return exp(-x*x);
}
///On a ici la dérivé seconde de la fonction u
double f(double x){         
    return ((2 - 4*x*x)*(u(x)));
}
///Cette fonction calcule le pas avec lequel on va diviser notre domaine (division régulière) 
double pas(double x0, double xn, int n){
    double h(0.0);
    h= double(xn-x0);
    h/=double(n-1);
    cout << "Le pas est: " << h << endl;
    return h;
}
///Cette fonction retourne un vecteur composé des dérivées seconde de la fonction
vector<double> discretVect(int n, double x0, double pas) {
    vector<double> fi;
    for(int i=0; i<=n; i++){
		///On a ici la CLD u(-4) = u(4) = 0
		if(i==0 || i==n)
			fi.push_back(0);
		else
			fi.push_back(f(x0 + i*pas));
	}
    return fi;
}

///Enfin on retrouve la résolution du système par la méthode de Gauss-Seidel
vector<double> seidel(int taille, vector<double> b, vector<vector<double>> mat){
    vector <double> x;
    ///On va d'abord stocker les résidu, aura besoin de leur somme pour voir quand s'arreter
	vector<double> res;
	double sr(0), s(0), eps(0.00000001);
	///Pour que le programme converge plus rapidement, on va initialiser les xi par 1
	for(int i=0; i<taille; i++){
		x.push_back(1);
		res.push_back(0);	///Celle ci doit etre nulle pour y stocker les résidu
	}		
	///A l'aide de l'algoritme, on va maintenant chercher le résidu
    for(int i = 0; i < taille; i++) {
        for(int j=0; j<taille; j++)
            s+= (mat[i][j]*x[j]);
        res[i]= b[i]-s;
        s=0;
        }
    ///le résidu est la somme des valeur absolue ce vector
    for(int i=0; i<taille; i++)	sr+= fabs(res[i]);    
    ///Avec le résidu, on peut maintenant chercher les approximations selon le niveau d'erreur recherché
	while(!(sr<eps)){
		for(int i=0; i<taille; i++){
			for(int j=0; j<taille; j++)
				s+=mat[i][j]*x[j];
			res[i]= b[i]-s;
			x[i] += (res[i]/mat[i][i]);
			s=0;
		}
		///On calcule de nouveau le résidu pour que l'approximation soit proche, on va aussi afficher le nombre d'itération jusqu'à la fin de la boucle
		sr=0;
		for(int i=0; i<taille; i++)
		sr+= fabs(res[i]);
	}
    return x;
}
///Ecriture sur fichier
void ecriture(int& taille, vector<double> vect, vector<double> xi){
	ofstream flux("curve.txt");
	
	if(flux){
		flux << taille << endl;
		for(int i=0; i<taille; i++)
			flux << xi[i] << ", " << vect[i] << endl;
	}
	else
		flux << "Erreur d'ecriture" << endl;
}
///Entrée des données par l'utilisateur
void entre_donne(int& taille, double& x0, double& xn){
	cout << "Veuillez rentrer le nombre de division: ";
	int n;
	while(!(cin>>n)){
		cin.clear();		
		cin.ignore(255, '\n');
	}
	taille = n;
	cout << "\n Rentrez le domaine sur lequel nous allons travailler: \nBorne inf :";
	double a, b;
	while(!(cin>>a)){
		cin.clear();		
		cin.ignore(255, '\n');
	}
	x0 = a;
    cout << "Borne sup: ";
	while(!(cin>>b)){
		cin.clear();		
		cin.ignore(255, '\n');
	}
	xn = b;
}
///Cette fonction nous renverra chaque coordonées des points où va passer notre aproximation
vector<double> division(double x0, int taille ,double pas){
	vector<double> xi;
	for(int i=0; i<taille; i++)
		xi.push_back(x0 + i*pas);
	return xi;
}
void afficheVect(int taille, vector<double> v){
	for(int i=0; i<taille; i++)
		cout << v[i] << "\t";
	cout << endl;
}
///Cette fontion nous montre les ordonnées aux absisses à chaque découpage
///Cela nous servira de réference pour comparer nos approximation
vector<double> pred(int taille, vector<double> x){
	vector<double> y;
	for(int i=0; i<taille; i++)
		y.push_back(f(x[i]));
	return y;
}
