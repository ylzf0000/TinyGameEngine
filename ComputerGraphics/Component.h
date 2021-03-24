#ifndef CG_COMPONENT_H
#define CG_COMPONENT_H
#include "stdafx.h"
CG_BEGIN
class Component
{
public:
	bool isActive = true;
	virtual ~Component() = default;
protected:
};
CG_END
#endif // CG_COMPONENT_H
