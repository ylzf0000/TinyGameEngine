#ifndef CG_GAMESPACE_H
#define CG_GAMESPACE_H
#include "stdafx.h"
#include "Camera.h"
#include "Object.h"
#include "Light.h"
#include "Teapot.h"
#include "Line3D.h"
#include "AmbientLight.h"
#include <vector>
#include <memory>
CG_BEGIN
class GameSpace
{
public:
	GameSpace() = default;
	~GameSpace();

	Camera camera;
	AmbientLight *pAmbientLight = nullptr;
	Teapot *pTeapot=nullptr;

	std::vector<std::shared_ptr<Light>> lightList;
	std::vector<std::shared_ptr<Object>> objectList;
	std::vector<Line3D> lineList;

};
CG_END
#endif