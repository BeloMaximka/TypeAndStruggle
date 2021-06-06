#pragma once
struct point {
	double x;
	double y;
};
struct ipoint {
	int x;
	int y;
};
point RotateVector(point PointFirst, double Angle);
point SumVectors(point PointFirst, point PointSecond);
point SubtractVectors(point PointFirst, point PointSecond);
double FindVectorLenght(point PointFirst);
double GetAngle(point PointFirst, point PointSecond);
point NormalizeVector(point PointFirst);
