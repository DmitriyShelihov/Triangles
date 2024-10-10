#include "Triangles.h" 

int main() {
	Point point1(0,0,0);
	Point point2(0,6,0);
	Point point3(7,0,0);
	Point point4(1,1,0);
	Point point5(1,2,0);
	Point point6(2,1,0);
	
	Triangle first(point1, point2, point3);
	
	Plane plane1 = first.plane();
	plane1.print();
	std::cout << "A: " << plane1.A() << ", B: " << plane1.B() << ", C: " << plane1.C() << ", D:" << plane1.D() << "\n";
	Triangle second(point6, point4, point5);

	Plane plane2 = second.plane();
	plane2.print();
	std::cout << "A: " << plane2.A() << ", B: " << plane2.B() << ", C: " << plane2.C() << ", D:" << plane2.D() << "\n";
	Line line = plane1.plane_intersection(plane2);

	line.print();
	
	printf("\n");

	std::cout << "answer is:"  << first.triangle_intersection(second) << std::endl;
	return 0;
}
