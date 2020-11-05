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

	void SetPosition(vec3 position);
	void SetPosition(float x, float y, float z);
	vec3 GetPosition();

	void SetRotation(vec3 rotation);
	void SetRotation(float x, float y, float z);
	vec3 GetRotation();

	void SetScale(vec3 scale);
	void SetScale(float x, float y, float z);
	vec3 GetScale();
};

