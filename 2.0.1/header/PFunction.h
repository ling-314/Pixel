#pragma once
#include <string>
#include <locale>
#include <atlconv.h>
#include "PNode.h"

namespace Pixel
{
	// 是否碰撞
	bool Collision(CollisionBox collisionBox, CollisionBox collisionBox2);
	// 是否碰撞
	bool Collision(CollisionBox collisionBox, Point point);
	// string转wstring
	std::wstring ToWideString(std::string str);
	// wstring转string
	std::string ToByteString(std::wstring str);
}