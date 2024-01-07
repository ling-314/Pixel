#pragma once
#include <vector>
#include <string>
#include "PWindow.h"
#include "PFunction.h"

namespace Pixel
{
	class ConsolePlus :
		public Window
	{
	public:
		class Output
		{
		public:
			Output(ConsolePlus* console);
			Output& operator<<(std::string text);
		protected:
			ConsolePlus* _console;
		};
	public:
		~ConsolePlus();
		// 初始化
		virtual bool Init() override;
		// 打印文本
		void Print(std::string text);
	protected:
		Scene _scene;
	protected:
		void _UpdateNode();
	};
}