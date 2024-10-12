#include "Triangles.h" 

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

	int mas1[100];
	int p = 0;
	for (int i = 0; i < N-1; i++) {
		for (int j = i + 1; j < N; j++) {
			if (mas[i].triangle_intersection(mas[j])) {
				mas1[p] = i;
				p++;
				std::cout << "ANSWER:{{{{{{{{{{{{{{{{{"  << i << " with " << j << "}}}}}}}}}}}}}}}}}" << "\n";				
			}
		}
	}
	printf("\n%d\n", p);
	for (int i = 0; i < p; i++)
		printf("%d ", mas1[i]);
	return 0;
}
