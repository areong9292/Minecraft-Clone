#include "GameObject.h"

GameObject::GameObject()
{
	_transform = new Transform();
	_name = "GameObject";

	_listComponent.push_back(_transform);
}

GameObject::GameObject(string name)
{
	_transform = new Transform();
	_name = name;

	_listComponent.push_back(_transform);
}

GameObject::~GameObject()
{
	// ��� ������Ʈ�� �����Ѵ�
	for (int i = 0; i < (int)_listComponent.size(); i++)
	{
		delete _listComponent[i];
	}
}

// �� �����Ӹ��� ȣ��
void GameObject::UpdateComponents()
{
	for (int i = 0; i < (int)_listComponent.size(); i++)
	{
		_listComponent[i]->UpdateComponent();
	}
}

void GameObject::SetName(string name)
{
	_name = name;
}

int GameObject::GetComponentCount()
{
	return (int)_listComponent.size();
}