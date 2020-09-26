// 버텍스 쉐이더 소스
#version 330 core								// 버전 3.3
												// 입력 여러 개 받을 시 location 뒤 숫자 증가
layout (location = 0) in vec3 aPos;				// 입력으로 3차원 벡터 aPos 받는다
layout (location = 1) in vec3 aColor;			// 입력으로 3차원 벡터 aColor 받는다
out vec3 vertexColor;							// specify a color output to the fragment shader

void main()
{
   gl_Position = vec4(aPos, 1.0);				// 받은 입력(버텍스) 포지션 지정
	vertexColor = aColor;						// 출력 값 셋팅, 이 출력은 fragment shader로 전달된다
}												// gl_Position - 버텍스 쉐이더의 출력