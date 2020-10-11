#include "Camera.h"

Camera::Camera()
{
	// ī�޶� �̵� �ӵ�
	cameraSpeed = 0.05f;

	// ù ���콺 �������� ����
	firstMouse = true;

	// ������ ī�޶� ��ġ
	lastX = 0;
	lastY = 0;

	// x,y ȸ����
	m_yaw = -90.0f;
	m_pitch = 0.0f;

	// �þ߰�(��)
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
	viewMatrix = lookAt(cameraPos,					// ī�޶� ��ġ
		cameraPos + cameraFront,	// ī�޶� ����
		cameraUp);					// ī�޶� ��
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
	// ���� ��Ʈ����
	projectionMatrix = perspective(
		radians(Zoom),								// ���̰�
		(float)screenWidth / (float)screenHeight,	// ȭ�� ���� (width / height)
		near,										// ���� ���� ���� ����� �������� �Ÿ�
		far);										// ���� ���� ���� �� �������� �Ÿ�
}

void Camera::SetCameraCallback(GLFWwindow * window)
{
	// Ŀ�� ������ �߻� �� ȣ�� �� �ݹ� ���
	//glfwSetCursorPosCallback(window, mouse_callback);

	// ���콺 ��ũ�� �� ȣ�� �� �ݹ� ���
	//glfwSetScrollCallback(window, scroll_callback);
}

void Camera::CameraUpdate()
{
	// ��, ���� ��Ʈ���� ����
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
