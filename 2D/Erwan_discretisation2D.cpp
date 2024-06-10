/**
 * 		RAMANGASON Notahiana Erwan
 * 		erwan.ramangason@gmail.com
 * 		+261 34 85 670 14
 * 
 * 		Discretisation 2D - 20 mars 2023
 * 
 * */

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include "GPlot.cpp"

using namespace std;

//Prototype des fonctions
double g(double x, double y);
double f(double x, double y);
double saisi(string s);
double pas(double a, double n);
vector<double> eigen(double dx, double dy, double m);
vector<vector<double>> S(double dx, double dy, double n, double m, double xo, double yo);
vector<vector<double>> sinusRapide(int n, int m, vector<vector<double>> s);
vector<vector<double>> transpose(int n, int m, vector<vector<double>> M);
vector<vector<double>> Ti(int m, double dx, double dy);
vector<double> tridag(vector<double> a, vector<double> b, vector<double> c, vector<double> r, int n);
vector<vector<double>> sinusInverse(int n, int m, vector<vector<double>> v);
double mse(int n, int m, vector<vector<double>> v, double dx, double dy, double xo, double yo);
///Fonction de sinft
void sinft(vector<double>& y, int n);
void realft(vector<double>& data, unsigned long n, int isign);
void four1(vector<double>& data, unsigned long nn, int isign);
///Affichage de vecteur et de matrice et de la courbe
void compare(int n, int m, double xo, double yo, double dx, double dy);
void affiche_mat(int n, int m, vector<vector<double>> matrice);
void affiche_vect(int taille, vector<double> v);
void tiret(int i){cout << "------------------------------------------------------------" << i << endl;}
void ecriture(int n, int m, vector<vector<double>> mat);

//Fonction principale
int main(){
	cout << "Discretistion 2D" << endl;
	
	GPlot plot;
	double x0(0), xn(20), y0(0), yn(30), dx, dy;
	int n(10), m(8);
	vector<double> di, drond, uj;
	vector<vector<double>> Snm, nu, h, ti, u, Y;
	
	///On commence par rentrer les valeurs des intervales d'études ainsi que le nombre de division.
	/// PS: Nous partons du principe sque nos intervales partent tous de 0
	//x0 = saisi("de la borne inférieure en x de notre intervalle");
	//y0 = saisi("de la borne inférieure en y de notre intervalle");
	xn = saisi("de la borne supérieure en x de notre intervalle");
	yn = saisi("de la borne supérieure en y de notre intervalle");
	n = saisi("du nombre de division en x ou i)");
	m = saisi("du nombre de division en y ou j");
	
	cout << endl << endl;
	///On procede ensuite au calcul de la valeur du calcul de chaque pas
	//ETO JERENA SAO DIA MISU MIFAMADIKA NY M SY N
	dx = pas(xn-x0, n);
	dy = pas(yn-y0, m);
		cout << "Les pas sont: " << dx << " et " << dy << endl;
	
	///Ensuite, on passe au calcul des valeurs propres des 2 matrices
	di = eigen(dx, dy, n);
	for(int i=0; i<n; i++)
		drond.push_back(-1);
	affiche_vect(n, di);	affiche_vect(n, drond);
		
	///On construit la matrice Si
	Snm = S(dx, dy, n, m, x0, y0);
		cout << endl << "La matrice S:" << endl;
		affiche_mat(n, m, Snm);

	
	///Ensuite on monte la matrice des nu
	nu = sinusRapide(n, m, Snm);
		cout << endl << "La matrice nu:" << endl;
		affiche_mat(n, m, nu);
		
	///La matrice h sera l'inverse de nu, qui nous servira lors de la résolution de notre problème
	h = transpose(n, m, nu);
		cout << endl << "La matrice h:" << endl;
		affiche_mat(m, n, h);
		
	///On momntera ensuite la matrice Ti des valeurs propres
	ti = Ti(n, dx, dy);
		cout << endl << "La matrice ti:" << endl;
		affiche_mat(n, n, ti);
		
	///On procèdera ensuite à la résolution de Ti.Ui = hi, on utilisera la méthode tridiag pour cela
	for(int i=0; i<m; i++){
		uj = tridag(drond, di, drond, h[i], n);
		//affiche_vect(n, uj);
		//tiret(i);
		u.push_back(uj);
		uj.clear();
	}
		cout << endl << "La matrice u avant transposition:" << endl;
		affiche_mat(m, n, u);
	u = transpose(m, n, u);
		cout << endl << "La matrice u après transposition:" << endl;
		affiche_mat(n, m, u);
		
	///Enfin on va résoudre notre problème par la transformation de sinus inverse
	Y = sinusInverse(n, m, u);
		cout << endl << "La matrice finale obtenue est:" << endl;
		affiche_mat(n, m, Y);
		
	///Nous allons maintenant calculer l'erreur et l'afficher afin de voir notre marge
	cout << "Nous avons comme erreur: MSE = " << mse(n, m, Y, dx, dy, x0, y0) << endl;
	compare(n, m, x0, y0, dx, dy);
	
	ecriture(n, m, Y);
	plot.setup(0, 30, 0, 20, -4, 4);
	plot.display("x", "y", "z", "surface.txt");
	
	return 0;
}

//Implémentation des fonctions
///Fonctionc d'affichage
void affiche_mat(int n, int m, vector<vector<double>> matrice){
	cout<<endl<<endl;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++)
			cout<< matrice[i][j]<< "\t";
	cout<<"\n \n";	
	}
}
void affiche_vect(int taille, vector<double> v){
	cout<<endl<<endl;
	for(int i=0; i<taille;i++)
		cout<<v[i]<<"\n"<<endl;
}
///Nous commençons respectivement par la fonction que nous allons utiliser ainsi que sa dérivée seconde
double g(double x, double y){
	//return exp(-x*x -y*y);
		return cos(x)+cos(y);
    //	return exp(x*x - y*y)
}
double f(double x, double y){
	//return 4*(x*x + y*y - 1)*g(x, y);;
	  return -cos(x)-cos(y);
    //	return 4*(x*x + y*y)*g(x, y)
}
///Fonction simple qui nous permet de saisir les valeurs par l'utilisateur
double saisi(string s){
	double temp;
	cout << "Veuillez rentrer la valeur " << s << ": ";
	cin >> temp;
	return temp;
}
///Fonction simple qui calcule le pas de discrétisation
double pas(double a, double n){
	return a/(n+1);
}
///Fonction qui nous donne les valeurs propores de nos matrices du 1e membre dans notre système
vector<double> eigen(double dx, double dy, double m){
	vector<double> v;
	for(int i=0; i<m; i++)
		v.push_back(2+2*(dy/dx)*(dy/dx)*(1-cos(M_PI*i/(double)(m+1))));
	return v;
}
///Cette fonction nous permettra de monter notre matrice S de 2nd membre
vector<vector<double>> S(double dx, double dy, double n, double m, double xo, double yo){
	vector<vector<double>> s;
	vector<double> si;
	double alp, gam;
	alp = -1/(dx*dx);
	gam = -1/(dy*dy);
	//	cout << "La valeur de alpha et de beta: " << alp << ", " << gam << endl;
	///Nous monterons cette matrice ligne par ligne
	///Ligne 1
	si.push_back(f(xo+dx, yo+dy) - gam*g(xo, yo+dy) - alp*g(xo+dx, yo));
	for(int j=2; j<m; j++)
		si.push_back(f(xo+dx, yo+j*dy) - gam*g(xo, yo+j*dy));
	si.push_back(f(xo+dx, yo+m*dy) - gam*g(xo, m*dy) - alp*g(xo+dx, yo+(m+1)*dy));
	s.push_back(si);
	///Ligne 2 à n-1
	for(int i=2; i<n; i++){
		si.clear();
		si.push_back(f(xo+i*dx, yo+dy) - alp*g(xo + i*dx, yo));
		for(int j=2; j<m; j++)
			si.push_back(f(xo+i*dx, yo+j*dy));
		si.push_back(f(xo+i*dx, yo+m*dy) - alp*g(xo+i*dx, yo+(m+1)*dy));
		s.push_back(si);
	}
	///Ligne n
	si.clear();
	si.push_back(f(xo+n*dx, yo+dy) - alp*g(xo+n*dx, yo) - gam*g(xo+(n+1)*dx, yo+dy));
	for(int j=2; j<m; j++)
		si.push_back(f(xo+n*dx, yo+j*dy) - gam*g(xo+(n+1)*dx, yo+j*dy));
	si.push_back(f(xo+n*dx, yo+m*dy) - alp*g(xo+n*dx, yo+(m+1)*dy) - gam*g(xo+(n+1)*dx, yo+m*dy));
	s.push_back(si);
	return s;
}
///Fonction qui implémente l'algorithme pour avoir la matrice des nu
vector<vector<double>> sinusRapide(int n, int m, vector<vector<double>> s){
	vector <double> nj;
	vector<vector<double>> nu;
	//double temp(0);
	for(int j=0; j<n; j++){
		nj.clear();
		for(int k=0; k<m; k++){
			//temp = 0;
			for(int l=0; l<m; l++)
				nj.push_back(s[j][k]);
				//temp += (double)(sqrt((double)(m+1)/2.0))*s[l][j] * sin((double)(M_PI*k*l)/(double)(m+1));
			//nj.push_back((double)(2.0/(m+1))*temp);
		}
		sinft(nj, m);
		nu.push_back(nj);
	}
	return nu;
}
///Une fonction qui inverse une matrice afin d'obtenir les hi
vector<vector<double>> transpose(int n, int m, vector<vector<double>> M){
	vector<vector<double>> mat;
	vector<double> vect;
	tiret(0);
	for(int i=0; i<m; i++){
		vect.clear();
		tiret(1);
		for(int j=0; j<n; j++){
			tiret(2+i);
			vect.push_back(M[j][i]);
		}
		mat.push_back(vect);
	}
	return mat;
}
///La fonction pour avoir la matrice des valeurs propores
vector<vector<double>> Ti(int m, double dx, double dy){
	vector<double> di, vect;
	vector<vector<double>> mat;
	di = eigen(dx, dy, m);
	for(int i=0; i<m; i++){
		vect.clear();
		for(int j=0; j<m; j++){
			if(i==j)
				vect.push_back(di[i]);
			else if(i==j+1 || i+1==j)
				vect.push_back(-1);
			else
				vect.push_back(0);
		}
		mat.push_back(vect);
	}
	return mat;
}
///Fonction de résolution
vector<double> tridag(vector<double> a, vector<double> b, vector<double> c, vector<double> r, int n) {
	vector<double> u, gam;
	float bet;
	
	for(int i=0; i<n; i++){	
		gam.push_back(0);
		u.push_back(0);
	}
	if (b[0] == 0.0) 
		cout << "Error 1 in tridag" << endl;
	u[0]=r[0]/(bet=b[0]);

	for(int j=1;j<n;j++){
		gam[j]=c[j-1]/bet;
		bet=b[j]-a[j]*gam[j];
		if (bet == 0.0)	
			cout << "Error 2 in tridag" << endl;
		u[j]=(r[j]-a[j]*u[j-1])/bet;
	}
	for (int j=(n-2);j>=0;j--)
		u[j] -= gam[j+1]*u[j+1];
	return u;
}
vector<vector<double>> sinusInverse(int n, int m, vector<vector<double>> v){
	//double temp;
	vector<double> yj;
	vector<vector<double>> y;
	for(int j=0; j<n; j++){
		yj.clear();
		for(int k=0; k<m; k++){
			//for(int l=0; l<m; l++)
				yj.push_back(v[j][m]);
				//temp += v[j][j] * sin(((double)M_PI*k*l)/(m+1));
				//temp += v[l][j] * sin(((double)M_PI*k*l)/(m+1));
			//yj.push_back(temp);
		}
		sinft(yj, m);
		y.push_back(yj);
	}
	return y;
}
///Calcul de la minsquared error
double mse(int n, int m, vector<vector<double>> v, double dx, double dy, double xo, double yo){
	double loss;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++)
			loss += (v[i][j] - f(xo+i*dx, yo+j*dy))*(v[i][j] - f(xo+i*dx, yo+j*dy));
	}
	return loss/(double)(n*m);
}
void compare(int n, int m, double xo, double yo, double dx, double dy){
	cout<< endl << "On a coomme matrice de comparaison"<<endl;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++)
			cout<< f(xo+i*dx, yo+j*dy) << "\t";
	cout<<"\n \n";	
	}
}

//Utilisation de sinft
void sinft(vector<double>& y, int n)
{
	//void realft(float data[], unsigned long n, int isign);
	int j,n2=n+2;
	double sum,y1,y2;
	double theta,wi=0.0,wr=1.0,wpi,wpr,wtemp;

	theta=3.14159265358979/(double) n;
	wtemp=sin(0.5*theta);
	wpr = -2.0*wtemp*wtemp;
	wpi=sin(theta);
	y[1]=0.0;
	for (j=2;j<=(n>>1)+1;j++) {
		wr=(wtemp=wr)*wpr-wi*wpi+wr;
		wi=wi*wpr+wtemp*wpi+wi;
		y1=wi*(y[j]+y[n2-j]);
		y2=0.5*(y[j]-y[n2-j]);
		y[j]=y1+y2;
		y[n2-j]=y1-y2;
	}
	realft(y,n,1);
	y[1]*=0.5;
	sum=y[2]=0.0;
	for (j=1;j<=n-1;j+=2) {
		sum += y[j];
		y[j]=y[j+1];
		y[j+1]=sum;
	}
}
void realft(vector<double>& data, unsigned long n, int isign)
{
	//void four1(float data[], unsigned long nn, int isign);
	unsigned long i,i1,i2,i3,i4,np3;
	double c1=0.5,c2,h1r,h1i,h2r,h2i;
	double wr,wi,wpr,wpi,wtemp,theta;

	theta=3.141592653589793/(double) (n>>1);
	if (isign == 1) {
		c2 = -0.5;
		four1(data,n>>1,1);
	} else {
		c2=0.5;
		theta = -theta;
	}
	wtemp=sin(0.5*theta);
	wpr = -2.0*wtemp*wtemp;
	wpi=sin(theta);
	wr=1.0+wpr;
	wi=wpi;
	np3=n+3;
	for (i=2;i<=(n>>2);i++) {
		i4=1+(i3=np3-(i2=1+(i1=i+i-1)));
		h1r=c1*(data[i1]+data[i3]);
		h1i=c1*(data[i2]-data[i4]);
		h2r = -c2*(data[i2]+data[i4]);
		h2i=c2*(data[i1]-data[i3]);
		data[i1]=h1r+wr*h2r-wi*h2i;
		data[i2]=h1i+wr*h2i+wi*h2r;
		data[i3]=h1r-wr*h2r+wi*h2i;
		data[i4] = -h1i+wr*h2i+wi*h2r;
		wr=(wtemp=wr)*wpr-wi*wpi+wr;
		wi=wi*wpr+wtemp*wpi+wi;
	}
	if (isign == 1) {
		data[1] = (h1r=data[1])+data[2];
		data[2] = h1r-data[2];
	} else {
		data[1]=c1*((h1r=data[1])+data[2]);
		data[2]=c1*(h1r-data[2]);
		four1(data,n>>1,-1);
	}
}

#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr

void four1(vector<double>& data, unsigned long nn, int isign)
{
	unsigned long n,mmax,m,j,istep,i;
	double wtemp,wr,wpr,wpi,wi,theta;
	double tempr,tempi;

	n=nn << 1;
	j=1;
	for (i=1;i<n;i+=2) {
		if (j > i) {
			SWAP(data[j],data[i]);
			SWAP(data[j+1],data[i+1]);
		}
		m=nn;
		while (m >= 2 && j > m) {
			j -= m;
			m >>= 1;
		}
		j += m;
	}
	mmax=2;
	while (n > mmax) {
		istep=mmax << 1;
		theta=isign*(6.28318530717959/mmax);
		wtemp=sin(0.5*theta);
		wpr = -2.0*wtemp*wtemp;
		wpi=sin(theta);
		wr=1.0;
		wi=0.0;
		for (m=1;m<mmax;m+=2) {
			for (i=m;i<=n;i+=istep) {
				j=i+mmax;
				tempr=wr*data[j]-wi*data[j+1];
				tempi=wr*data[j+1]+wi*data[j];
				data[j]=data[i]-tempr;
				data[j+1]=data[i+1]-tempi;
				data[i] += tempr;
				data[i+1] += tempi;
			}
			wr=(wtemp=wr)*wpr-wi*wpi+wr;
			wi=wi*wpr+wtemp*wpi+wi;
		}
		mmax=istep;
	}
}
#undef SWAP
///Cette derniere fonction ecrira notre résultat final dans un fuchier texte destiné à etre lu par un programme d'affichage
void ecriture(int n, int m, vector<vector<double>> mat){
	ofstream flux("surface.txt");
	
	if(flux){
		for(int i=0; i<n; i++){
			for(int j=0; j<m; j++)
				flux << i << ", " << j << ", "<< mat[i][j] << endl;
			flux << endl;
		}
	}
	else
		flux << "Erreur d'ecriture" << endl;
}
