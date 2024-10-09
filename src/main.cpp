#include "Triangles.h" 

int main() {
	Point point1(6, 0, 0);
	Point point2(-3, 5, 0);
	Point point3(-3, -5, 0);
	Point point4(0, 4, 4);
	Point point5(0, -4, 4);
	Point point6(0, 0, -4);
	
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

	Segment seg1(point1, point3);
	Segment seg2(point4, point6);
	Line line_xxx (point4, point6);

	Point point_xxx = seg1.intersection_with_line_on_plane(line_xxx);

	point_xxx.print();

	std::cout << first.triangle_intersection(second) << std::endl;
	return 0;
}
