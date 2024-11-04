#include <iostream>
#include <fstream>

int ntriangles = 500;

int main(int argc, char** argv) {
	if (argc <= 1)
		return 0;
	int ntests = atoi(argv[1]);

	if (ntests > 20) {
		std::cout << "Are you sure?\nPress 1/0 if yes/not\n";
		bool res = 0;
		std::cin >> res;
		if (res == 0) {
			std::cout << "Stopped\n";
			return 0;
		}
	}
	for (int i = 0; i < ntests; i++) {
		std::ofstream out("Tests/test" + std::to_string(i) + ".txt");
		double stepx = 0; double stepy = 0; double stepz = 0;
		out << ntriangles << "\n";
		for (int j = 0; j < ntriangles; j++) { 
			stepx += 10; stepy += 10; stepz += 10;
			out << stepx + rand()%100 + rand()/10000000000.0 << " " << stepy + rand()%100 + rand()/10000000000.0 << " " << stepz + rand()%100 + rand()/10000000000.0 << " " <<
			stepx + rand()%100 + rand()/10000000000.0 << " " << stepy + rand()%100 + rand()/10000000000.0 << " " << stepz + rand()%100 + rand()/10000000000.0 << " " << 
			stepx + rand()%100 + rand()/10000000000.0 << " " << stepy + rand()%100 + rand()/10000000000.0 << " " << stepz + rand()%100 + rand()/10000000000.0 << "\n";
		}
		out.close();
	}	
	return 0;
}
