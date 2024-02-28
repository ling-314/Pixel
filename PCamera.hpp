#pragma once
#include "PType.hpp"

namespace Pixel
{
	// �����
	class Camera
	{
	public:
		Camera();
		Camera(float x, float y);
		Camera(Vector2 offset);
	public:
		// ��ȡƫ��
		Vector2 GetOffset() const;
		// ��ȡXƫ��
		float GetOffsetX() const;
		// ��ȡYƫ��
		float GetOffsetY() const;
	public:
		// ����ƫ��
		void SetOffset(Vector2 offset);
		// ����Xƫ��
		void SetOffsetX(float x);
		// ����Yƫ��
		void SetOffsetY(float y);
	private:
		Vector2 _offset;
	};
}