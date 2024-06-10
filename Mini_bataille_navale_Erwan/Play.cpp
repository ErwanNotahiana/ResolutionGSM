#include "Play.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

///Constructeurs
Play::Play(){
	bateauAbattu=0;
	nbBateau=3;
	replay=1;
	win=false;
	nbTir=50;
}

Play::Play(Plateau p, vector<Bateau> b, Coordonnee v, int n, int a, int r, bool w){
	plateau=p;
	bateau=b;
	viseur=v;
	nbBateau=n;
	replay=r;
	win=w;
}

///Accesseur et muteur
Plateau Play::getPlateau(){return plateau;}
vector<Bateau> Play::getBateau(){return bateau;}
Coordonnee Play::getViseur(){return viseur;}
int Play::getNbBateau(){return nbBateau;}
int Play::getReplay(){return replay;}
bool Play::getWin(){return win;}

void Play::setPlateau(Plateau p){plateau=p;}
void Play::setBateau(vector<Bateau> b){bateau=b;}
void Play::setViseur(Coordonnee v){viseur=v;}
void Play::setNbBateau(int n){nbBateau=n;}
void Play::setWin(bool w){win=w;}

///Autres fonctions
///Nos 2 fonctions d'affichage ici font appelle a des fichiers textes
void Play::displaySynopsis(){							///Cette fonction affiche le synopsis
	ifstream synopsis ("synopsis.txt");
	if(synopsis){
		string ligne;
		while(getline(synopsis, ligne))
			cout<<ligne<<endl;
	}
	else
		cout<<"Erreur lors de l'affichage du synopsis"<<endl;
}

void Play::displayAide(){								///Celle-ci affiche comment jouer
	ifstream aide ("aide.txt");
	if(aide){
		string ligne;
		while(getline(aide, ligne))
			cout<<ligne<<endl;
	}
	else
		cout<<"Erreur lors de l'affichage de l'aide"<<endl;
}

void Play::armee(){										///C'est a partie de la que l'on va generer les bateaux (positions)
	///On commence par creer un de bateau avant de l'ajouter a nore tableau(vector)
	Bateau boat;
	srand(time(0));
	///On lui donne des coordonnees aleatoires
	for(int i(0); i<nbBateau; i++){
		boat.placeBateau();
		///Ici, on va s'assurer qu'a une seule coordonnee corresponde un bateau
		for(int j(0); j<i; j++){
			int testeur(0);
			while(boat.getPosition()==bateau[j].getPosition() && testeur<5){
				///Si les coordonnees fournies par la fonction appartiennent deja a un bateau, alors on demande a notre fonction de generer nouvelles
				boat.placeBateau();
				testeur++;
				///On va juste voir si la fonction marche comme il faut
				if(!(testeur<5)){
					cout<<"Erreur lors de la randomisation"<<endl;
					break;
					}
			}
		}
		///Apres avoir finit notre bateau, nous allons l'ajouter a notre vector avant d'en creer un autre
		bateau.push_back(boat);
	}
}
		
void Play::saisiViseur(){									///Cette fonction demande a l'utilisateur de rentrer sa cible
	int a, b;
	
	cout<<"Entrez les coordonées ou vous voulez tirer (abscisse x, ordonnee y)\n *PS:le nombre doit etre compris entre [0-11]*:  "<<endl;

	while(a<0||a>11){
		cout<<"x: ";
		a=renvoieInt();
	}
	while(b<0||b>11){
		cout<<"y: ";
		b=renvoieInt();
	}
	
	viseur.setX(a);
	viseur.setY(b);
}

void Play::jouer(){												///C'est ici tout le deroulement de notre partie
	///On commence par afficher notre plateau
	plateau.display();
	int tir(0), i(0), j(0), taille(0);
	while(bateauAbattu<nbBateau && tir<nbTir){
		///On saisit la cible, et on s'assure que le joueur ne tire pas sur un endroit ou il l'a deja fait
		saisiViseur();
		for(j=0 ;j<taille; j++){
			if(viseur==shoot[j]){
				while(viseur==shoot[j]){
					cout<<"Attention! Vous avez deja tiré là"<<endl;
					saisiViseur();
					j=0;
				}
			}
		}
		shoot.push_back(viseur);		//On y stoque les coups precedents
		taille++;
		for(i=0; i<nbBateau; i++){
			if(viseur==bateau[i].getPosition()){
				plateau.setCase('x', viseur.getX(), viseur.getY());
				bateau[i].setEtat(false);
				bateauAbattu++;
				cout<<"Boum! Dans le mille"<<endl;
				break;
			}
		}
		if(i==nbBateau){
			cout<<"Plouf! Loupé"<<endl;
			plateau.setCase('o', viseur.getX(), viseur.getY());
		}
		tir++;
		cout<<"Tir restant: "<<nbTir-tir<<endl<<endl;
		plateau.display();
	}///On realise cette bouvle jusqua ce qu'il n'y ai plus de sous marins ou balles
	if(bateauAbattu==nbBateau)
		win=true;
	else
		win=false;
	displayFin();
}	

int Play::renvoieInt(){											///Cette methode s'assure que l'utilisateur retourne bien un nombre
	int n;
	while(!(cin>>n)){
		cout<<"Attention! Ne rentrez que des entiers!!\t";
		cin.clear();		
		cin.ignore(255, '\n');
	}
	return n;
}

void Play::displayFin(){										///C'est la fin de la partie
	int rejouer(0);
	if(win)
		cout<<"Felicitation! Vous les avez tous eus, ils font moins les fier maintenant."<<endl;
	else
		cout<<"Nous n'avons plus de torpille! Vous ferez mieux la prochaine fois"<<endl;
	while(rejouer!=1 && rejouer!=2){
		cout<<"Voulez vous rejouer?\n1. Oui\n2. Non"<<endl;
		rejouer=renvoieInt();
	}
	replay=rejouer;
}
	
void Play::initialize(){										///Si l'utilisateur souhaite rejouer, il sera necessaire de re-initialiser nos attributs avant de les reuiliser
	Plateau plateauInitial;
	win=false;
	plateau=plateauInitial;
	bateau.clear();
	bateauAbattu=0;
}

void Play::emplacement(){
	for(auto boat : bateau)
		boat.verifier();
	cout<<endl;
}
