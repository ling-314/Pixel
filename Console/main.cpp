#include <Windows.h>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	SetConsoleTitle(L"Pixel Console");

	HANDLE input, output;
	if (argc == 3)
	{
		sscanf_s(argv[1], "%p", &input);
		sscanf_s(argv[2], "%p", &output);
	}
	else return -1;

	if (input == INVALID_HANDLE_VALUE || output == INVALID_HANDLE_VALUE) return -1;

	char flag;
	unsigned int length;

	for (;;)
	{
		if (ReadFile(input, &flag, 1, nullptr, nullptr))
		{
			if (flag == 'w')
			{
				if (ReadFile(input, &length, sizeof(unsigned int), nullptr, nullptr))
				{
					char* buf = new char[length + 1];
					while (!ReadFile(input, buf, length, nullptr, nullptr));
					buf[length] = '\0';
					cout << buf;
					delete[] buf;
				}
			}
			else if (flag == 'r')
			{
				string str;
				cin >> str;
				length = str.length();
				if (WriteFile(output, &length, sizeof(unsigned int), nullptr, nullptr))
				{
					WriteFile(output, str.c_str(), length, nullptr, nullptr);
				}
			}
			else if (flag == 'c')
			{
				char color[3] = { 0 };
				if (ReadFile(input, &color, 2, nullptr, nullptr))
				{
					char cmdLine[9];
					sprintf_s(cmdLine, "color %s", color);
					system(cmdLine);
				}
			}
			else if (flag == 'q')
			{
				break;
			}
		}
	}
	
	return 0;
}