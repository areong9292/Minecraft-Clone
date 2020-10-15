#pragma once
#include <GLMHeader.h>
#include "Component.h"
class Transform : public Component
{
public:
	Transform();
	~Transform();

	vec3 _position;
	vec3 _rotation;
	vec3 _scale;

	// 매 프레임마다 호출
	virtual void UpdateComponent() override;

};

