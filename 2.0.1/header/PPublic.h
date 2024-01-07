#pragma once

namespace Pixel
{
	template<typename T> void SafeRelease(T* type)
	{
		if (type)
		{
			type->Release();
			type = nullptr;
		}
	}
}