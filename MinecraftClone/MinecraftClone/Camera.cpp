#include "Camera.h"

Camera::Camera()
{
	// 카메라 이동 속도
	cameraSpeed = 0.05f;

	// 첫 마우스 동작인지 여부
	firstMouse = true;

	// 마지막 카메라 위치
	lastX = 0;
	lastY = 0;

	// x,y 회전값
	m_yaw = -90.0f;
	m_pitch = 0.0f;

	// 시야각(줌)
	Zoom = 45.0f;

	viewMatrix = mat4(1.0f);
}

Camera::~Camera()
{
}

void Camera::Init(int screenWidth, int screenHeight)
{
	this->screenWidth = screenWidth;
	this->screenHeight = screenHeight;
}

void Camera::SetPosition(vec3 position)
{
	this->cameraPos = position;
}

vec3 Camera::GetPosition()
{
	return cameraPos;
}

void Camera::SetTargetPos(vec3 cameraTarget)
{
	this->cameraTarget = cameraTarget;
}

vec3 Camera::GetTargetPos()
{
	return cameraTarget;
}

void Camera::SetCameraFront(vec3 cameraFront)
{
	this->cameraFront = cameraFront;
}

vec3 Camera::GetCameraFront()
{
	return cameraFront;
}

void Camera::SetCameraUp(vec3 cameraUp)
{
	this->cameraUp = cameraUp;
}

vec3 Camera::GetCameraUp()
{
	return cameraUp;
}

void Camera::SetViewMatrix(mat4 viewMatrix)
{
	this->viewMatrix = viewMatrix;
}

mat4 Camera::GetViewMatrix()
{
	return viewMatrix;
}

void Camera::SetCameraLookAt()
{
	viewMatrix = lookAt(cameraPos,					// 카메라 위치
		cameraPos + cameraFront,	// 카메라 방향
		cameraUp);					// 카메라 위
}

void Camera::SetProjectionMatrix(mat4 projectionMatrix)
{
	this->projectionMatrix = projectionMatrix;
}

mat4 Camera::GetProjectionMatrix()
{
	return projectionMatrix;
}

void Camera::SetCameraPerspective()
{
	// 투영 매트릭스
	projectionMatrix = perspective(
		radians(Zoom),								// 사이각
		(float)screenWidth / (float)screenHeight,	// 화면 비율 (width / height)
		near,										// 시작 점과 가장 가까운 평면까지의 거리
		far);										// 시작 점과 가장 먼 평면까지의 거리
}

void Camera::SetCameraCallback(GLFWwindow * window)
{
	// 커서 움직임 발생 시 호출 할 콜백 등록
	//glfwSetCursorPosCallback(window, mouse_callback);

	// 마우스 스크롤 시 호출 할 콜백 등록
	//glfwSetScrollCallback(window, scroll_callback);
}

void Camera::CameraUpdate()
{
	// 뷰, 투영 매트릭스 갱신
	SetCameraLookAt();
	SetCameraPerspective();
}

void Camera::SetCameraSpeed(float deltaTime)
{
	cameraSpeed = cameraSpeedCalc * deltaTime;
}

void Camera::SetCameraSpeedUp()
{
	cameraSpeedCalc = 5.0f;
}

void Camera::SetCameraSpeedDown()
{
	cameraSpeedCalc = 2.5f;
}

void Camera::SetCameraLeftRightMove(bool isLeft)
{
	if (isLeft)
		cameraPos -= normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
	else
		cameraPos += normalize(cross(cameraFront, cameraUp)) * cameraSpeed;
}

void Camera::SetCameraUpDownMove(bool isUp)
{
	if (isUp)
		cameraPos += cameraSpeed * cameraFront;
	else
		cameraPos -= cameraSpeed * cameraFront;
}

void Camera::mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.01f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	m_yaw += xoffset;
	m_pitch += yoffset;

	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	vec3 direction;
	direction.x = cos(radians(m_yaw)) * cos(radians(m_pitch));
	direction.y = sin(radians(m_pitch));
	direction.z = sin(radians(m_yaw)) * cos(radians(m_pitch));
	cameraFront = normalize(direction);
}

void Camera::scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
	Zoom -= (float)yoffset;
	if (Zoom < 1.0f)
		Zoom = 1.0f;
	if (Zoom > 45.0f)
		Zoom = 45.0f;
}
