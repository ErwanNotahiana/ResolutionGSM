#include "Plateau.hpp"
#include "Bateau.hpp"
#include <vector>


class Play{
	private:
		Plateau plateau;
		std::vector<Bateau> bateau;
		std::vector<Coordonnee> shoot;
		int nbTir;
		Coordonnee viseur;
		int nbBateau;
		int bateauAbattu;
		int replay;
		bool win;
		
	public:
		Play();
		Play(Plateau p, std::vector<Bateau> b, Coordonnee v, int n, int a, int r, bool w);
		
		///Place aux accesseur et muteurs
		Plateau getPlateau();
		std::vector<Bateau> getBateau();
		Coordonnee getViseur();
		int getNbBateau();
		int getBateauAbattu();
		int getReplay();
		bool getWin();
		void setPlateau(Plateau p);
		void setBateau(std::vector<Bateau> b);
		void setViseur(Coordonnee v);
		void setNbBateau(int n);
		void setBateauAbattu(int a);
		void setWin(bool w);
		
		///Voyons maintenant ce que notre menu fera
		void displaySynopsis();
		void displayAide();
		void saisiViseur();
		void armee();			
		void jouer();
		void displayFin();
		void initialize();		
		
		///Nous allons verifier la coordonnée de chaque bateaux
		void emplacement();
		
		///Enfin nous allons créer une methode de saisi pour notre programme
		int renvoieInt();

};
		
		
