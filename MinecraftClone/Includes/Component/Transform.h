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

	// �� �����Ӹ��� ȣ��
	virtual void UpdateComponent() override;

};

