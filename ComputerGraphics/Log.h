#pragma once
#include "stdafx.h"
#include <fstream>
CG_BEGIN
class Log
{
public:
	template <typename T>
	static void Out(const T &str)
	{
		outfile << str << std::endl;
	}
	static std::fstream outfile;
};
CG_END