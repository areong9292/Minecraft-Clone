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

	// 카메라 위치
	void SetCameraPos(vec3 position);
	vec3 GetCameraPos();

	// 카메라 대상
	void SetTargetPos(vec3 cameraTarget);
	vec3 GetTargetPos();

	// 카메라 정면
	void SetCameraFront(vec3 cameraFront);
	vec3 GetCameraFront();

	// 카메라 위
	void SetCameraUp(vec3 cameraUp);
	vec3 GetCameraUp();

	// 뷰 매트릭스
	void SetViewMatrix(mat4 viewMatrix);
	mat4 GetViewMatrix();
	void SetCameraLookAt();

	// 투영 매트릭스
	void SetProjectionMatrix(mat4 projectionMatrix);
	mat4 GetProjectionMatrix();
	void SetCameraPerspective();

	void SetCameraCallback(GLFWwindow* window);

	// 매 프레임마다 호출, 카메라 정보 갱신
	virtual void UpdateComponent() override;

	void SetCameraSpeed(float deltaTime);
	void SetCameraSpeedUp();
	void SetCameraSpeedDown();
	void SetCameraLeftRightMove(bool isLeft);
	void SetCameraUpDownMove(bool isUp);
	void SetCameraTopBottomMove(bool isTop);

private:
	// 카메라 위치
	vec3 cameraPos;

	// 카메라 타겟
	vec3 cameraTarget;

	// 카메라 방향 벡터
	vec3 cameraFront;

	// 카메라 업 벡터
	vec3 cameraUp;

	// 카메라 이동 속도
	float cameraSpeed = 0.05f;
	float cameraSpeedCalc = 2.5f;

	// 카메라 감도
	float cameraSensitivity = 0.05f;

	// 첫 마우스 동작인지 여부
	bool firstMouse = true;

	// 마지막 카메라 위치
	double lastX = 0;
	double lastY = 0;

	// x,y 회전값
	float m_yaw = -90.0f;
	float m_pitch = 0.0f;

	// 시야각(줌)
	float Zoom = 45.0f;

	// 카메라 컬링 평면 위치
	float near = 0.1f;
	float far = 100.0f;

	mat4 viewMatrix, projectionMatrix;

	int screenWidth, screenHeight;

public:
	// 마우스 움직임, 스크롤 콜백
	void mouse_callback(GLFWwindow* window, double xpos, double ypos);
	void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};

