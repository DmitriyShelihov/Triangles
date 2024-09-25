#pragma once 

class Point {
	public:
		double x = NAN;
		double y = NAN;
		double z = NAN;
		Point () {}		
		Point (double _x, double _y, double _z) 
			: x(_x), y(_y), z(_z) {}
		double radius() {
			return std::sqrt(x*x + y*y + z*z);
		}
		void print() {
			std::cout << "{" << x << ", "  << y << ", " << z << "}"; 
		}
		bool valid() {
			return !(std::isnan(x) || std::isnan(y) || std::isnan(z));
		}
		bool equal(const Point rhs) {
			return (std::fabs(x - rhs.x) < DBL_EPSILON * fmax(fabs(x), fabs(rhs.x)) && 
					std::fabs(y - rhs.y) < DBL_EPSILON * fmax(fabs(y), fabs(rhs.y)) && 
					std::fabs(z - rhs.z) < DBL_EPSILON * fmax(fabs(z), fabs(rhs.z)));
		}

};

class Segment {
	private:
		Point point1;
		Point point2;
	public:
		Snippet (Point _point1, Point _point2) 
			: point1(_point1), point2(_point2) {}
		double length () {
			return std::sqrt(std::pow(point1.x-point2.x, 2) + std::pow(point1.y-point2.y, 2) + std::pow(point1.z-point2.z, 2));
		}
		
		bool valid() {
			return point1.valid() && point2.valid();
		}
		void print() {
			std::cout << "Segment { ";
			point1.print();
			std::cout << ", ";
			point2.print();
			std::cout << " }";
		}
		bool point_belongs_segment(Point point) {
			return (point.x-point1.x) * (point2.y-point1.y) == (point.y-point1.y) * (point2.x-point1.x) &&
				   (point.y-point1.y) * (point2.z-point1.z) == (point.z-point1.z) * (point2.y-point1.y) &&
				   (point.x-point1.x) * (point2.z-point1.z) == (point.z-point1.z) * (point2.x-point1.x) &&
				   std::fabs(point.x-point2.x) <= std::fabs(point1.x-point2.x) && 
				   std::fabs(point.x-point1.x) <= std::fabs(point1.x-point2.x) &&
				   std::fabs(point.y-point2.y) <= std::fabs(point1.y-point2.y) &&
				   std::fabs(point.y-point1.y) <= std::fabs(point1.y-point2.y) &&
				   std::fabs(point.z-point2.z) <= std::fabs(point1.z-point2.z) &&
				   std::fabs(point.z-point1.z) <= std::fabs(point1.z-point2.z);
		}
		bool point_belongs_same_segment_line(Point point) {
			return (point.x-point1.x) * (point2.y-point1.y) == (point.y-point1.y) * (point2.x-point1.x) &&
                   (point.y-point1.y) * (point2.z-point1.z) == (point.z-point1.z) * (point2.y-point1.y) &&
                   (point.x-point1.x) * (point2.z-point1.z) == (point.z-point1.z) * (point2.x-point1.x);
		}
	
}

class Triangle {	
	private: 
		Point point1;
		Point point2;
		Point point3;
	public:
		Triangle (Point _point1, Point _point2, Point _point3) 
			: point1(_point1), point2(_point2), point3(_point3) {}
		bool valid() {
			return point1.valid() && point2.valid() && point3.valid() && !point1.equal(point2) && !point1.equal(point3) && !point3.equal(point2);
		}
		void print() {
			std::cout << "Triangle { ";
			point1.print();
			std::cout << ", ";
			point2.print();
			std::cout << ", ";
			point3.print();
			std::cout << " }";
		}
		bool degenerate_triangle() {
			Segment side (point1, point2);
			return side.point_belongs_same_segment_line(Point point3); 
		}
}

class Line {
	private:
		Point point1;
		Point point2;
	public:
		Line (Point _point1, Point _point2) 
			: point1(_point1), point2(_point2) {}
		bool valid() {
			return point1.valid() && point2.valid() && !point1.equal(point2);
		}
		void print() {
			std::cout << "Line { ";
			point1.print();
			std::cout << ", ";
			point2.print();
			std::cout << " }";
		}
		bool point_belongs_line(Point point) {
        	return (point.x-point1.x) * (point2.y-point1.y) == (point.y-point1.y) * (point2.x-point1.x) &&
                   (point.y-point1.y) * (point2.z-point1.z) == (point.z-point1.z) * (point2.y-point1.y) &&
                   (point.x-point1.x) * (point2.z-point1.z) == (point.z-point1.z) * (point2.x-point1.x);
        }

}

class Plane {
	private:
		Point point1;
		Point point2;
		Point point3;
	public:
		Plane (Point _point1, Point _point2, Point _point3)
			: point1(_point1), point2(_point2), point3(_point3) {}
		bool valid() {
			Line line (point1, point2);
			return point1.valid() && point2.valid() && point3.valid() && line.point_belongs_line(point3);
		}
		void print() {
         	std::cout << "Plane { ";
          	point1.print();
          	std::cout << ", ";
          	point2.print();
          	std::cout << ", ";
          	point3.print();
          	std::cout << " }";
		}
		
		Line plane_intersection(Plane plane2) {
					
		}
}
