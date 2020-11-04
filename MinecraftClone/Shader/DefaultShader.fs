// 프레그먼트 쉐이더 소스
#version 330 core								// 버전 3.3
out vec4 FragColor;								// 출력으로 4차원 벡터 컬러 값

in vec3 vertexColor;							// vertex shader로부터 입력을 받는다
in vec2 TexCoord;								// 텍스쳐 좌표

uniform vec3 lightColor;

void main()
{
	FragColor = vec4(vertexColor * lightColor, 1.0);
	//* vec4(vertexColor, 1.0);	// 텍스쳐 셋팅
}