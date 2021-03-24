#ifndef CG_OBJECT_H
#define CG_OBJECT_H
#include "stdafx.h"
#include "Transform.h"
#include "Mesh.h"
#include "Script.h"
#include "Texture.h"
#include "Material.h"
#include <vector>
#include <memory>
CG_BEGIN
class Object
{
public:
	Object() = default;
	bool isActive = true;
	Transform transform;
	Mesh *pMesh = nullptr;
	Material *pMaterial = nullptr;
	Texture *pTexture = nullptr;
	std::vector<std::shared_ptr<Script>> scripts;
	virtual ~Object()
	{
		delete pMesh;
		delete pMaterial;
		delete pTexture;
	}
};
CG_END
#endif