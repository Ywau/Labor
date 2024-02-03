#pragma once

class Cone {
private:
	double height;
	double radius;
public:
	Cone(double h, double r);
	Cone() = default;
	double S();
	double V();
};