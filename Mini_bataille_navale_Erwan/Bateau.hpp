#include "Coordonnee.hpp"

class Bateau{
	private:
		Coordonnee position;
		bool etat;
		
	public:
		Bateau();
		Bateau(bool b, Coordonnee p);
		
		///Voyons les mutateurs et les accesseurs
		bool getEtat();
		Coordonnee getPosition();
		void setEtat(bool b);
		void setPosition(Coordonnee p);
		
		///Voyons ici une fonction qui va génerer aléatoirement la position d'un bateau
		void placeBateau();
		
		///Créons une fonction pour vérifier les coordonées des bateaux
		void verifier();
};
