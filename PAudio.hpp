#pragma once
#include <string>
#include <Windows.h>
#include "PFunction.hpp"

namespace Pixel
{
	// ��Ƶ
	class Audio
	{
	public:
		Audio();
		Audio(std::string path);
		~Audio();
		// ����
		void Play();
		// ��ͣ
		void Pause();
		// ��������
		void Continue();
		// ֹͣ
		void Stop();
		// �ر���Ƶ�ļ�
		void Close();
	public:
		// ��ȡ��Ƶ·��
		std::string GetPath() const;
		// �Ƿ�
	public:
		// ������Ƶ·��
		void SetPath(std::string path);
	private:
		std::string _path;
	};
}