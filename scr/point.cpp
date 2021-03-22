#include "main.h"

point RotateVector(point PointFirst, double Angle) {
    Angle *= (M_PI / 180);
    point PointRotated;
    PointRotated.x = PointFirst.x * cos(Angle) - PointFirst.y * sin(Angle);
    PointRotated.y = PointFirst.x * sin(Angle) + PointFirst.y * cos(Angle);
    return PointRotated;
}
point SumVectors(point PointFirst, point PointSecond) {
    PointFirst.x = PointFirst.x + PointSecond.x;
    PointFirst.y = PointFirst.y + PointSecond.y;
    return PointFirst;
}
point SubtractVectors(point PointFirst, point PointSecond) {
    PointFirst.x = PointFirst.x - PointSecond.x;
    PointFirst.y = PointFirst.y - PointSecond.y;
    return PointFirst;
}
double FindVectorLenght(point PointFirst) {
    return sqrt(pow(PointFirst.x, 2) + pow(PointFirst.y, 2));
}
double GetAngle(point PointFirst, point PointSecond) {
    PointFirst.x -= PointSecond.x;
    PointFirst.y -= PointSecond.y;
    PointFirst = NormalizeVector(PointFirst);
    double Degrees = atan2(PointFirst.x, PointFirst.y) * 180 / M_PI;
    if (Degrees > 90 && Degrees <= 180)
    {
        Degrees = abs(450 - Degrees);
    }
    if (Degrees > -180 && Degrees <= -90)
    {
        Degrees = abs(90 - Degrees);
    }
    if (Degrees >= -90 && Degrees < 0)
    {
       Degrees = abs(90-Degrees);
    }
    if (Degrees >= 0 && Degrees <= 90)
    {
       Degrees = abs(Degrees - 90);
    }

    return (Degrees);
   
}
point NormalizeVector(point PointFirst) {
    double VectorLenght = FindVectorLenght(PointFirst);
    if (VectorLenght > 0)
    {
        PointFirst.x /= VectorLenght;
        PointFirst.y /= VectorLenght;
    }
    return PointFirst;
}

