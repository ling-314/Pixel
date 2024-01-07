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
		float GetOffsetX() const;
		float GetOffsetY() const;
	public:
		void SetOffset(Vector2 offset);
		void SetOffset(float x, float y);
		void SetOffsetX(float x);
		void SetOffsetY(float y);
	protected:
		Vector2 _offset;
	};
}