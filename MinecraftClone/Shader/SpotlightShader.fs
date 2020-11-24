// 프레그먼트 쉐이더 소스
#version 330 core								// 버전 3.3
out vec4 FragColor;								// 출력으로 4차원 벡터 컬러 값

in vec3 vertexColor;							// vertex shader로부터 입력을 받는다
in vec2 TexCoord;								// 텍스쳐 좌표
in vec3 Normal;									// 한 면의 노말
in vec3 FragPos;								// 변환되어 이동 된 버텍스 좌표

// sampler2D - 텍스쳐 타입
uniform sampler2D ourTexture1;					// uniform 코드에서 이 변수를 제어할 것이다
uniform sampler2D ourTexture2;

uniform float mixValue;							// 텍스쳐 블랜딩 값

uniform vec3 lightPos;							// 조명 위치
uniform vec3 lightColor;						// 조명 색상
uniform vec3 objectColor;						// 오브젝트 색상
uniform vec3 viewPos;							// 카메라 위치

// 머테리얼
struct Material {
    vec3 ambient;
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 
  
uniform Material material;

// 빛
struct Light {
	vec3 position;
	vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

	float constant;
	float linear;
	float quadratic;

	float cutOff;
    float outerCutOff;
};

uniform Light light; 

void main()
{
	// ambient - 주변광 - 전체적으로 조명 색상을 얇게 깐다
    // vec3 ambient = material.ambient * lightColor;
	vec3 ambient  = light.ambient * vec3(texture(material.diffuse, TexCoord));

	// diffuse - 난반사광 - 법선과 빛의 방향 내적이 양수인 경우(180 안쪽으로 들어올 경우)만 라이트 적용
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);			// 빛의 방향 얻는다
	float diff = max(dot(norm, lightDir), 0.0);						// 내적 계산
	// vec3 diffuse = (diff * material.diffuse) * lightColor;		// 빛 세기 적용
	vec3 diffuse  = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord));

	// specular - 정반사광 - 반사되는 지점에 라이트 적용
	vec3 viewDir = normalize(viewPos - FragPos);								// 카메라 위치 얻는다
	vec3 reflectDir = reflect(-lightDir, norm);									// 반사 방향을 구한다
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);	// 반사 방향과 카메라 위치 내적, 하이라이트를 위한 pow 계산
	//vec3 specular = material.specular * spec * lightColor;						// 빛 세기 적용
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));
	
	float theta     = dot(lightDir, normalize(-light.direction));
	float epsilon   = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0); 

	// we'll leave ambient unaffected so we always have a little light.
	diffuse  *= intensity;
	specular *= intensity;

	float distance    = length(lightPos - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	ambient  *= attenuation; 
	diffuse  *= attenuation;
	specular *= attenuation;
	
	FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), mixValue) * vec4(ambient + diffuse + specular, 1.0);
}