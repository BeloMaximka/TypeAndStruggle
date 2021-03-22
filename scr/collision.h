#pragma once
#include "main.h"
#include "point.h"

struct collisionbox {
	point TopLeft;
	point BottomRight;	
};

bool IsColliding(collisionbox First, collisionbox Second);
collisionbox UpdateCollision(point Pos, double Height, double Width);
