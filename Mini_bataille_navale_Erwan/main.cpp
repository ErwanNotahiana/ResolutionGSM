#include <iostream>
#include "Play.hpp"

using namespace std;

int main(){
	cout<<"Mini-bataille navale"<<endl<<endl;
	
	Play menu;
	
	menu.displaySynopsis();
	menu.displayAide();
	while(menu.getReplay()==1){
		menu.armee();
		menu.emplacement();
		menu.jouer();
		menu.initialize();
	}
	
	return 0;
}
