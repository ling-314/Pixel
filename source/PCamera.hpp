#pragma once
#include "PType.hpp"

namespace Pixel
{
	// 摄像机
	class Camera
	{
	public:
		Camera();
		Camera(float x, float y);
		Camera(Vector2 offset);
	public:
		// 获取偏移
		Vector2 GetOffset() const;
		// 获取X偏移
		float GetOffsetX() const;
		// 获取Y偏移
		float GetOffsetY() const;
	public:
		// 设置偏移
		void SetOffset(Vector2 offset);
		// 设置X偏移
		void SetOffsetX(float x);
		// 设置Y偏移
		void SetOffsetY(float y);
	private:
		Vector2 _offset;
	};
}