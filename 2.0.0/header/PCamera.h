#pragma once
#include "PType.h"

namespace Pixel
{
	class Camera
	{
	public:
		Camera();
	public:
		Vector2 GetOffset() const;
		int GetOffsetX() const;
		int GetOffsetY() const;
	public:
		void SetOffset(Vector2 offset);
		void SetOffset(int x, int y);
		void SetOffsetX(int x);
		void SetOffsetY(int y);
	protected:
		Vector2 offset;
	};
}