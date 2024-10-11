#include "Triangles.h" 

int main() {
	Point point1(0, 1, 0);
	Point point2(2, 2, 0);
	Point point3(2, 4, 0);
	Point point4(0, 0, 0);
	Point point5(0, 6, 0);
	Point point6(0, 10, 10);

	Triangle first(point1, point2, point3);
	Triangle second(point6, point4, point5);

	std::cout << "answer is:"  << first.triangle_intersection(second) << std::endl;
	return 0;
}
