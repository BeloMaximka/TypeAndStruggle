#include "main.h"

bool IsColliding(collisionbox First, collisionbox Second) {
	if (First.TopLeft.x >= Second.BottomRight.x || Second.TopLeft.x >= First.BottomRight.x) {
		return false;
	}
	else if (First.TopLeft.y >= Second.BottomRight.y || Second.TopLeft.y >= First.BottomRight.y) {
		return false;
	}
	else
	{
		return true;
	}
}
collisionbox UpdateCollision(point Pos, double Height, double Width) {
	collisionbox NewCollision;
	NewCollision.BottomRight.x = Pos.x + Width / 2;
	NewCollision.BottomRight.y = Pos.y + Height / 2;
	NewCollision.TopLeft.x = Pos.x - Width / 2;
	NewCollision.TopLeft.y = Pos.y - Height / 2;
	return NewCollision;
}