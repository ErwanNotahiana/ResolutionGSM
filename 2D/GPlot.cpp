#ifndef DEF_GNUPLOT
#define DEF_GNUPLOT
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>

class GPlot {
    public:
        
        GPlot(){_pipe = nullptr; }
        virtual ~GPlot(){ close(); }
        bool isOpened() const { return _pipe != nullptr; }

        void setup(float xmin=0, float xmax=1, float ymin=0, float ymax=1, float zmin=5, float zmax=5);
        void display(std::string xlab="x", std::string ylab="y", std::string zlab="z", std::string title="Title");
        void open();
        void flush();
        void close();
        void write(const char *line);
        void write(const std::string &line);
        void execute();

    private:
        FILE* _pipe;
        float xmin, xmax, ymin, ymax, zmin, zmax;
        std::vector<std::string> script;

};

void GPlot::setup(float xmin, float xmax, float ymin, float ymax, float zmin, float zmax) {
    this->xmin = xmin; this->xmax = xmax;
    this->ymin = ymin; this->ymax = ymax;
    if(this->zmin > zmin) this->zmin = zmin;
    if(this->zmax < zmax) this->zmax = zmax;
}

void GPlot::display(std::string xlab, std::string ylab, std::string zlab, std::string title) {
    open();
    script.push_back("reset");
    script.push_back("set term wxt size 640,480");
    script.push_back("set title '" + title);
    script.push_back("set xlabel '" + xlab);
    script.push_back("set ylabel '" + ylab);
    script.push_back("set zlabel '" + zlab);
    script.push_back("set autoscale z");
    script.push_back("set nokey");
    script.push_back("set xzeroaxis");
    script.push_back("set yzeroaxis");
    script.push_back("set xrange [" + std::to_string(xmin) + ":" + std::to_string(xmax) + "]");
    script.push_back("set yrange [" + std::to_string(ymin) + ":" + std::to_string(ymax) + "]");
    script.push_back("splot 'surface.txt' u 1:2:3 w pm3d");

    execute();
}
void GPlot::open() {
    close();
    _pipe = popen("gnuplot -persist", "w");
}
void GPlot::flush() {
    if(isOpened()) {
        fflush(_pipe);
    }
}
void GPlot::close() {
    if(isOpened()) {
        pclose(_pipe);
        _pipe = nullptr;
    }
}
void GPlot::write(const char *line) {
    if(isOpened() && line != nullptr && line[0] != '\0') {
        fprintf(_pipe, "%s\n", line);
    }
}
void GPlot::write(const std::string &line) {
    if(!line.empty()) {
        write(line.c_str());
    }
}

void GPlot::execute() {
    if(isOpened()) {
        for(size_t i = 0; i < script.size(); i++) {
            write(script[i]);
            flush();
        }
    }
}
/*
int main(){
	GPlot plot;
	
	plot.setup(0, 30, 0, 20, -4, 4);
	plot.display("x", "y", "z", "surface.txt");
	
	return 0;
}*/

#endif //GNUPLOT
