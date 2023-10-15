#include "PFunction.h"

bool Pixel::Collision(CollisionBox collisionBox1, CollisionBox collisionBox2)
{
	return (
		(collisionBox1.rightBottom.x >= collisionBox2.leftTop.x && collisionBox1.rightBottom.x <= collisionBox2.rightBottom.x) ||
		(collisionBox2.rightBottom.x >= collisionBox1.leftTop.x && collisionBox2.rightBottom.x <= collisionBox1.rightBottom.x)
		);
}

bool Pixel::Collision(CollisionBox collisionBox, Point point)
{
	return (
		point.x >= collisionBox.leftTop.x &&
		point.x <= collisionBox.rightBottom.x &&
		point.y >= collisionBox.leftTop.y &&
		point.y <= collisionBox.rightBottom.y
		);
}
