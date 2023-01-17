#version 410 core

layout(location=0) in vec3 vPosition;
layout(location=1) in vec3 vNormal;
layout(location=2) in vec2 vTexCoords;

out vec3 fNormal;
out vec4 fPosEye;
out vec2 fTexCoords;
out vec3 vecNormal;

out vec4 lightPosEye1;
out vec4 lightPosEye2;
out vec4 lightPosEye3;
out vec4 lightPosEye4;
out vec4 lightPosEye5;
out vec4 lightPosEye6;
out vec4 lightPosEye7;
out vec4 lightPosEye8;
out vec4 lightPosEye9;
out vec4 lightPosEye10;
out vec4 lightPosEye11;
out vec4 lightPosEye12;
out vec4 lightPosEye13; 

out vec4 fragPosLightSpace;

out vec3 fPos;

out vec3 vPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform	mat3 normalMatrix;
uniform mat4 lightSpaceTrMatrix;

uniform vec3 lightPos1;//de adaugat
uniform vec3 lightPos2;//de adaugat
uniform vec3 lightPos3;//de adaugat
uniform vec3 lightPos4;//de adaugat
uniform vec3 lightPos5;//de adaugat
uniform vec3 lightPos6;//de adaugat
uniform vec3 lightPos7;//de adaugat
uniform vec3 lightPos8;//de adaugat
uniform vec3 lightPos9;//de adaugat
uniform vec3 lightPos10;//de adaugat
uniform vec3 lightPos11;//de adaugat
uniform vec3 lightPos12;//de adaugat
uniform vec3 lightPos13;//de adaugat


void main() 
{
	//compute eye space coordinates
	fPosEye = view * model * vec4(vPosition, 1.0f);
	vPos = vPosition;
	fPos = vec3(model * vec4(vPosition, 1.0f));
	fNormal = normalize(normalMatrix * vNormal);
	vecNormal = vNormal;
	fTexCoords = vTexCoords;
	fragPosLightSpace = lightSpaceTrMatrix * model * vec4(vPosition, 1.0f);

	lightPosEye1 = view*model*vec4(lightPos1,1.0f);
	lightPosEye2 = view*model*vec4(lightPos2,1.0f);
	lightPosEye3 = view*model*vec4(lightPos3,1.0f);
	lightPosEye4 = view*model*vec4(lightPos4,1.0f);
	lightPosEye5 = view*model*vec4(lightPos5,1.0f);
	lightPosEye6 = view*model*vec4(lightPos6,1.0f);
	lightPosEye7 = view*model*vec4(lightPos7,1.0f);
	lightPosEye8 = view*model*vec4(lightPos8,1.0f);
	lightPosEye9 = view*model*vec4(lightPos9,1.0f);
	lightPosEye10 = view*model*vec4(lightPos10,1.0f);
	lightPosEye11 = view*model*vec4(lightPos11,1.0f);
	lightPosEye12 = view*model*vec4(lightPos12,1.0f);
	lightPosEye13 = view*model*vec4(lightPos13,1.0f);
	
	// gl_Position = projection * view * model * vec4(vPosition, 1.0f);
	gl_Position = projection * view * model * vec4(vPosition, 1.0f);
}
