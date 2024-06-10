#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>

class Gplot{
	public:
		Gplot(){ _pipe = nullptr; }
		virtual ~Gplot(){ close(); }
		bool isOpened() const{ return _pipe != nullptr; }
			
		void setup(std::string filename, float xmin, float xmax, float ymin, float ymax);
		void display(std:: string xlab, std::string ylab, std::string title);
		void open();
		void flush();
		void close();
		void write(const char *line);
		void write(const std::string &line);
		void execute();
	
	private:
		FILE* _pipe;
		size_t nbPts;
		float xmin, xmax, ymin, ymax;
		float *xd, *yd;
		std::vector<std::string> script;
};
	
void Gplot::setup(std::string filename, float xmin=0, float xmax=1, float ymin=-5, float ymax=5){
	std::ifstream fichier (filename);
	std::string ligne;	
	
	if(fichier.is_open()){
		fichier >> nbPts;
		///Alloction et lecture des données
		xd= new float[nbPts];
		yd = new float[nbPts];
		this ->ymin = 1e8;
		this ->ymax = -1e8;
		for (size_t i=0; i<nbPts; i++){
			getline(fichier, ligne, ',');	//jsqa la prochaine virgule
			xd[i] =atof(ligne.c_str());
			getline(fichier, ligne);
			yd[i] =atof(ligne.c_str());
			
			if(yd[i] < this ->ymin)	this ->ymin = yd[i];
			if(yd[i] > this ->ymax)	this ->ymax = yd[i];
		}
	}
	else std::cout <<"Impossible d'ouvrir le fichier"<<std::endl;
	
	this -> xmin = xd[0]; this ->xmax = xd[nbPts-1];
	
	if(this->ymin > ymin)	this->ymin = ymin;
	if(this->ymax < ymax)	this->ymax = ymax;
}

void Gplot::display(std:: string xlab="x", std::string ylab="y", std::string title="Title"){
	open();
	script.push_back("reset");
	script.push_back("set term wxt size 640,480");
	script.push_back("set title '" + title);
	script.push_back("set xlabel '" + xlab);
	script.push_back("set ylabel '" + ylab);
	script.push_back("set autoscale y");
	script.push_back("set nokey");
	script.push_back("set xzeroaxis");
	script.push_back("set xrange [" + std::to_string(xmin) + ":" + std::to_string(xmax) + "]");
	//script.push_back("set yrange [" + std::to_string(ymin) + ":" + std::to_string(ymax) + "]");
	
	///Reusable internal data bloc
	script.push_back("$data << EOF");
	for(size_t i=0; i<nbPts; i++)
		script.push_back(std::to_string(xd[i]) + " " + std::to_string(yd[i]));
	script.push_back("EOF");
	script.push_back("plot $data using 1:2 w linespoint pt 5, $data using 1:2 sm csplines,exp(-x*x)");
	
	execute();
}


void Gplot::open(){
	close();
	_pipe = popen("gnuplot -persist","w");		//"\\gnuplot\\bin\\gnuplot -persist","w"
}
void Gplot::flush(){
	if(isOpened())
		fflush(_pipe);
}
void Gplot::close(){
	if(isOpened()){
		pclose(_pipe);
		_pipe = nullptr;
	}
}

void Gplot::write(const char *line){
	if(isOpened() && line!= nullptr && line[0] != '\0')
		fprintf(_pipe, "%s\n", line);
}

void Gplot::write(const std::string &line){
	if(!line.empty())
		write(line.c_str());
}

void Gplot::execute(){
	if(isOpened()){
		for(size_t i=0; i<script.size(); i++){
			write(script[i]);
			flush();
		}
	}
}

int main(){
	Gplot plot;
	
	plot.setup("curve.txt", -3, 3);
	plot.display("t", "f(t)", "curve.txt");
	
	return 0;
}

