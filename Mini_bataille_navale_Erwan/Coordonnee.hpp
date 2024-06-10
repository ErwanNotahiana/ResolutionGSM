

class Coordonnee{
	private:
		int x;
		int y;
		
	public:
		Coordonnee();
		Coordonnee(int a, int b);
		
		int getX();
		int getY();
		void setX(int a);
		void setY(int b);
};

///Il se peut que l'on soit ammene a comparer des coordonnees, on va donc surcharger le comparateur d'egalite ==
bool operator == (Coordonnee point1, Coordonnee point2);
