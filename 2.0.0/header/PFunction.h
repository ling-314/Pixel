#pragma once
#include <string>
#include <locale>
#include <atlconv.h>
#include "PNode.h"

namespace Pixel
{
	// �Ƿ���ײ
	bool Collision(CollisionBox collisionBox, CollisionBox collisionBox2);
	// �Ƿ���ײ
	bool Collision(CollisionBox collisionBox, Point point);
	// stringתwstring
	std::wstring ToWideString(std::string str);
	// wstringתstring
	std::string ToByteString(std::wstring str);
}