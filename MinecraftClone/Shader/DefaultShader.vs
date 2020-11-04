// 버텍스 쉐이더 소스
#version 330 core								// 버전 3.3
												// 입력 여러 개 받을 시 location 뒤 숫자 증가
layout (location = 0) in vec3 aPos;				// 입력으로 3차원 벡터 aPos 받는다
layout (location = 1) in vec3 aColor;			// 입력으로 3차원 벡터 aColor 받는다
out vec3 vertexColor;							// specify a color output to the fragment shader

uniform mat4 transform;

uniform mat4 world;								// 월드
uniform mat4 view;								// 뷰
uniform mat4 projection;						// 투영

void main()
{
	// gl_Position - 버텍스 쉐이더의 출력
	gl_Position = projection * view * world * vec4(aPos, 1.0);	// 받은 입력(버텍스) 포지션 지정
																// 변환 행렬 곱셈으로 변환 처리

	vertexColor = aColor;										// 출력 값 셋팅, 이 출력은 fragment shader로 전달된다
}