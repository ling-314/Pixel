#include <Windows.h>
#include <stdio.h>
#include <string>
#include <tchar.h>

namespace Pixel
{
	// 控制台
	class Console
	{
	public:
		Console();
		virtual ~Console();
		// 初始化
		bool Init();
		// 销毁
		void Destory();
	public:
		// 设置颜色
		// 参数格式见 color 命令
		bool SetColor(const char color[3]) const;
		// 输出
		bool Output(std::string str) const;
		// 输入
		bool Input(std::string* str);
	protected:
		PROCESS_INFORMATION piProcInfo;
		HANDLE _output;
		HANDLE _input;
	};
}