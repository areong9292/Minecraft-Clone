// 프레그먼트 쉐이더 소스
#version 330 core								// 버전 3.3
out vec4 FragColor;								// 출력으로 4차원 벡터 컬러 값

in vec3 vertexColor;							// vertex shader로부터 입력을 받는다
in vec2 TexCoord;								// 텍스쳐 좌표

// sampler2D - 텍스쳐 타입
uniform sampler2D ourTexture1;					// uniform 코드에서 이 변수를 제어할 것이다
uniform sampler2D ourTexture2;

uniform float mixValue;
uniform vec3 lightColor;

void main()
{
	// ourTexture1, ourTexture2 섞어서 사용
	// 최종 컬러 값이 두 텍스쳐의 조합이다
	// 3번째 인자 값 만큼 두 텍스쳐 사이를 선형보간 한다
	// 0이 첫번째 전체, 1이 두번째 전체이므로 0.2는 첫번째 텍스쳐 80%, 두번째 텍스쳐 20%다
	FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), mixValue) * vec4(vertexColor * lightColor, 1.0);;
	//* vec4(vertexColor, 1.0);	// 텍스쳐 셋팅
}