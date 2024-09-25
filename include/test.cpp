#include <iostream>
#include <cmath>
#include <cfloat>
#include "Triangles.h"


int main() {
	Point pp(1.14984, 2, 3.8174);
	Point pp1(1, 2, 3);
	Point p2 {};
	Point pp3(1.14984, 2, 3.8174);

	std::cout << pp1.valid() << std::endl ;
	std::cout << pp.equal(pp3) << std::endl;
}
