#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GLMHeader.h>

#include <iostream>

#include "../Includes/Component/Transform.h"
class Camera : Transform
{
public:
	Camera();
	~Camera();

	void Init(int screenWidth, int screenHeight);

	// ī�޶� ��ġ
	void SetCameraPos(vec3 position);
	vec3 GetCameraPos();

	// ī�޶� ���
	void SetTargetPos(vec3 cameraTarget);
	vec3 GetTargetPos();

	// ī�޶� ����
	void SetCameraFront(vec3 cameraFront);
	vec3 GetCameraFront();

	// ī�޶� ��
	void SetCameraUp(vec3 cameraUp);
	vec3 GetCameraUp();

	// �� ��Ʈ����
	void SetViewMatrix(mat4 viewMatrix);
	mat4 GetViewMatrix();
	void SetCameraLookAt();

	// ���� ��Ʈ����
	void SetProjectionMatrix(mat4 projectionMatrix);
	mat4 GetProjectionMatrix();
	void SetCameraPerspective();

	void SetCameraCallback(GLFWwindow* window);

	// �� �����Ӹ��� ȣ��, ī�޶� ���� ����
	virtual void UpdateComponent() override;

	void SetCameraSpeed(float deltaTime);
	void SetCameraSpeedUp();
	void SetCameraSpeedDown();
	void SetCameraLeftRightMove(bool isLeft);
	void SetCameraUpDownMove(bool isUp);
	void SetCameraTopBottomMove(bool isTop);

private:
	// ī�޶� ��ġ
	vec3 cameraPos;

	// ī�޶� Ÿ��
	vec3 cameraTarget;

	// ī�޶� ���� ����
	vec3 cameraFront;

	// ī�޶� �� ����
	vec3 cameraUp;

	// ī�޶� �̵� �ӵ�
	float cameraSpeed = 0.05f;
	float cameraSpeedCalc = 2.5f;

	// ī�޶� ����
	float cameraSensitivity = 0.05f;

	// ù ���콺 �������� ����
	bool firstMouse = true;

	// ������ ī�޶� ��ġ
	double lastX = 0;
	double lastY = 0;

	// x,y ȸ����
	float m_yaw = -90.0f;
	float m_pitch = 0.0f;

	// �þ߰�(��)
	float Zoom = 45.0f;

	// ī�޶� �ø� ��� ��ġ
	float near = 0.1f;
	float far = 100.0f;

	mat4 viewMatrix, projectionMatrix;

	int screenWidth, screenHeight;

public:
	// ���콺 ������, ��ũ�� �ݹ�
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};

