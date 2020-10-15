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
	//cout << "Transform Update" << endl;
}
