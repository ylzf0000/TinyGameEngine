#ifndef CG_TEAPOT_H
#define CG_TEAPOT_H
#include "stdafx.h"
#include "Object.h"
#include <fstream>
#include <vector>
CG_BEGIN
class Teapot :public Object
{
public:
	Teapot();
private:
	std::fstream teapotFile;
	
};
CG_END
#endif // CG_TEAPOT_H
