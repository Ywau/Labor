#include "L(1)_CMakeProject1.h"

#include <iostream>

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#include "L(1)_CMakeProject1.hpp"


Cone::Cone(double h, double r) : height(h), radius(r) {
}

double Cone::S() {
	double l = sqrt(pow(radius, 2)) + pow(height, 2);
	return 3.14 * radius * l + 3.14 * pow(radius, 2);
}

double Cone::V() {
	return (1.0 / 3.0) * M_PI * pow(radius, 2) * height;
}


int main() {
	double height;
	double radius;

	std::cout << "Enter the height of the cone: ";
	std::cin >> height;

	std::cout << "Enter the radius of the cone: ";
	std::cin >> radius;

	Cone cone(height, radius);

	std::cout << "The surface area of the cone = " << cone.S() << std::endl;
	std::cout << "The volume of the cone = " << cone.V() << std::endl;
	return 0;

}