#include "Transform.h"

Transform::Transform()
{
	// ������Ʈ �̸� ����
	SetComponentName("Transform");

	_position = vec3(0.0f, 0.0f, 0.0f);
	_rotation = vec3(0.0f, 0.0f, 0.0f);
	_scale = vec3(1.0f, 1.0f, 1.0f);
}

Transform::~Transform()
{
}

// �� �����Ӹ��� ȣ��
void Transform::UpdateComponent()
{
	//cout << "Transform Update" << endl;
}
