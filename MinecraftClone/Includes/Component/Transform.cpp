#include "Transform.h"

Transform::Transform()
{
	// 컴포넌트 이름 셋팅
	SetComponentName("Transform");

	_position = vec3(0.0f, 0.0f, 0.0f);
	_rotation = vec3(0.0f, 0.0f, 0.0f);
	_scale = vec3(1.0f, 1.0f, 1.0f);
}

Transform::~Transform()
{
}

// 매 프레임마다 호출
void Transform::UpdateComponent()
{
}

void Transform::SetPosition(vec3 position)
{
	_position = position;
}

void Transform::SetPosition(float x, float y, float z)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;
}

vec3 Transform::GetPosition()
{
	return _position;
}

void Transform::SetRotation(vec3 rotation)
{
	_rotation = rotation;
}

void Transform::SetRotation(float x, float y, float z)
{
	_rotation.x = x;
	_rotation.y = y;
	_rotation.z = z;
}

vec3 Transform::GetRotation()
{
	return _rotation;
}

void Transform::SetScale(vec3 scale)
{
	_scale = scale;
}

void Transform::SetScale(float x, float y, float z)
{
	_scale.x = x;
	_scale.y = y;
	_scale.z = z;
}

vec3 Transform::GetScale()
{
	return _scale;
}
