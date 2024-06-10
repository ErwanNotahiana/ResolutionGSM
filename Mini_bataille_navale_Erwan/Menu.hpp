#include "Plateau.hpp"
#include "Bateau.hpp"
#include "Viseur.hpp"

class Play{
	private:
		Plateau plateau;
		std::vector<Bateau> bateau;
		Viseur viseur;
		int nbBateau;
		bool win;
		
	public:
		Menu();
		Menu(Plateau p, std::vector<Bateau> b, Viseur v, int n);
		
		///Place aux accesseur et muteurs
		Plateau getPlateau();
		std::vector<Bateau> getBateau();
		Viseur getViseur();
		int getNbBateau();
		bool getVictoire();
		void setPlateau(Plateau p);
		void setBateau(std::vector<Bateau> b);
		void setViseur(Viseur v);
		void setNbBateau(int n);
		void setVictoire(bool w)
		
		///Voyons maintenant ce que notre menu fera
		void displayInitial();
		void touch();
		void miss();
};
		
		
