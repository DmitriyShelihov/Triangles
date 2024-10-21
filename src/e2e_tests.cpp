#include <iostream>
#include "Triangles.h"
#include <fstream>
#include <set>

int main(int argc, char** argv) {		//argv[1] = ntests
	if (argc <= 1)
		return 0;
	int ntests = atoi(argv[1]);
	if (ntests < 1) 
		return 0;
	for (int k = 0; k < ntests; ++k) {
		std::ifstream in("Tests/test" + std::to_string(k) + ".txt");
		int N = 0;
		in >> N;

        Triangle mas[N];
 
        for (int i = 0; i < N; i++) {
      		double x1 = 0; double y1 = 0; double z1 = 0;
            double x2 = 0; double y2 = 0; double z2 = 0;
            double x3 = 0; double y3 = 0; double z3 = 0;
   
            in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;
   
            Point p1(x1, y1, z1);
            Point p2(x2, y2, z2);
            Point p3(x3, y3, z3);
   
            Triangle T (p1, p2, p3);
            mas[i] = T;
        }
   		in.close();
        std::set<int> ans;
   
        for (int i = 0; i < N-1; i++) {
            for (int j = i+1; j < N; j++) {
                if (mas[i].triangle_intersection(mas[j])) {
                    ans.insert(i);
                    ans.insert(j);
                }
            }
        }
		std::ofstream out("Ans/test" + std::to_string(k) + "_ans.txt");

        for (auto i: ans)
            out << i << "\n";
      	out.close();
	}
	return 0;
}
