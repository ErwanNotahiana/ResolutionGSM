

class Plateau{
	private:
		char caractere;
		char mer[12][12];			///Comme il s'agit d'un plateau immobile, on utilisera un tableau statique
		
	public:
		Plateau();
		Plateau(char c);
		
		///Accesseur et muteur
		char getCaractere();
		char getCase(int i, int j);
		void setCaractere(char c);
		void setCase(char c, int i, int j);
		
		///Voyons une fonction qui affiche notre jeu.
		void display();
};
