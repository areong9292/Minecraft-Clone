// 프레그먼트 쉐이더 소스
#version 330 core								// 버전 3.3
out vec4 FragColor;								// 출력으로 4차원 벡터 컬러 값

in vec3 vertexColor;							// vertex shader로부터 입력을 받는다
in vec2 TexCoord;								// 텍스쳐 좌표

// sampler2D - 텍스쳐 타입
uniform sampler2D ourTexture;					// uniform 코드에서 이 변수를 제어할 것이다

void main()
{
   FragColor = texture(ourTexture, TexCoord) * vec4(vertexColor, 1.0);	// 텍스쳐 셋팅
}