#include "Triangles.h" 
#include <set>

int main() {
	
	int N = 0;

	std::cin >> N;

	Triangle mas[N];

	for (int i = 0; i < N; i++) {
		double x1 = 0; double y1 = 0; double z1 = 0;
		double x2 = 0; double y2 = 0; double z2 = 0;
		double x3 = 0; double y3 = 0; double z3 = 0;

		std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;

		Point p1(x1, y1, z1);
		Point p2(x2, y2, z2);
		Point p3(x3, y3, z3);
		
		Triangle T (p1, p2, p3);
		mas[i] = T;
	}

	std::set<int> ans;

	for (int i = 0; i < N-1; i++) {
		for (int j = i+1; j < N; j++) {
			if (mas[i].triangle_intersection(mas[j])) {
				ans.insert(i);
				ans.insert(j);
			}
		}
	}
	
	for (auto i: ans)
		std::cout << i << "\n";

	return 0;
}
