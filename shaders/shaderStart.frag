#version 410 core

in vec3 fNormal;
in vec4 fPosEye;
in vec2 fTexCoords;
in vec4 fragPosLightSpace;
in vec3 vecNormal;

//PUNCTIFORMA
in vec4 lightPosEye1;
uniform vec3 lightColor1;
in vec4 lightPosEye2;
uniform vec3 lightColor2;
in vec4 lightPosEye3;
uniform vec3 lightColor3;
in vec4 lightPosEye4;
uniform vec3 lightColor4;
in vec4 lightPosEye5;
uniform vec3 lightColor5;
in vec4 lightPosEye6;
uniform vec3 lightColor6;
in vec4 lightPosEye7;
uniform vec3 lightColor7;
in vec4 lightPosEye8;
uniform vec3 lightColor8;
in vec4 lightPosEye9;
uniform vec3 lightColor9;
in vec4 lightPosEye10;
uniform vec3 lightColor10;
in vec4 lightPosEye11;
uniform vec3 lightColor11;
in vec4 lightPosEye12;
uniform vec3 lightColor12;
in vec4 lightPosEye13;
uniform vec3 lightColor13;

out vec4 fColor;
in vec3 fPos;

//lighting DIRECTIONALA
uniform	vec3 lightDir;
uniform	vec3 lightColor;

//texture
uniform sampler2D diffuseTexture;
uniform sampler2D specularTexture;
uniform sampler2D shadowMap;

uniform int withFog;
uniform int withLight;

vec3 ambient;
float ambientStrength = 0.2f;
vec3 diffuse;
vec3 specular;
float shadow;
float specularStrength = 0.5f;
float shininess = 32.0f;

vec3 ambientPoint1;
float ambientPointStrength = 0.2f;
vec3 diffusePoint1;
vec3 specularPoint1;
float specularPointStrength = 0.5f;
float shininessPoint = 32.0f;

vec3 ambientPoint2;
vec3 diffusePoint2;
vec3 specularPoint2;

vec3 ambientPoint3;
vec3 diffusePoint3;
vec3 specularPoint3;

vec3 ambientPoint4;
vec3 diffusePoint4;
vec3 specularPoint4;

vec3 ambientPoint5;
vec3 diffusePoint5;
vec3 specularPoint5;

vec3 ambientPoint6;
vec3 diffusePoint6;
vec3 specularPoint6;

vec3 ambientPoint7;
vec3 diffusePoint7;
vec3 specularPoint7;

vec3 ambientPoint8;
vec3 diffusePoint8;
vec3 specularPoint8;

vec3 ambientPoint9;
vec3 diffusePoint9;
vec3 specularPoint9;

vec3 ambientPoint10;
vec3 diffusePoint10;
vec3 specularPoint10;

vec3 ambientPoint11;
vec3 diffusePoint11;
vec3 specularPoint11;

vec3 ambientPoint12;
vec3 diffusePoint12;
vec3 specularPoint12;

vec3 ambientPoint13;
vec3 diffusePoint13;
vec3 specularPoint13;

vec3 ambientSpot;
vec3 diffuseSpot;
vec3 specularSpot;

uniform vec3 spotDir;
uniform vec3 spotPos;
uniform float spotCutOff;

float spotQuadratic = 0.02f;
float spotLinear = 0.09f;
float spotConstant = 1.0f;

vec3 spotLightAmbient = vec3(0.0f, 0.0f, 0.0f);
vec3 spotLightSpecular = vec3(1.0f, 1.0f, 1.0f);
vec3 spotLightColor = vec3(12,12,12);

uniform float spotlight1;
uniform float spotlight2;

uniform int spot;

in vec3 vPos;

float computeShadow() 
{
	vec3 normalizedCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	normalizedCoords = normalizedCoords * 0.5 + 0.5;
	
	if (normalizedCoords.z > 1.0f)
		return 0.0f;
	
	float closestDepth = texture(shadowMap, normalizedCoords.xy).r;
	float currentDepth = normalizedCoords.z;
	
	// float bias = max(0.05f * (1.0f - dot(normalize(fNormal), lightDir)), 0.005f);
	// float shadow = currentDepth - bias > closestDepth ? 1.0f : 0.0f;
	float bias = 0.001f;
    //float shadow = currentDepth - bias > closestDepth ? 1.0f : 0.0f;
	float shadow = 0.0;
	vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
	for(int x = -1; x <= 1; ++x)
	{
		for(int y = -1; y <= 1; ++y)
		{
			float pcfDepth = texture(shadowMap, normalizedCoords.xy + vec2(x, y) * texelSize).r; 
			shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
		}    
	}
	shadow /= 9.0;
	//float shadow = currentDepth > closestDepth ? 1.0 : 0.0;

	return shadow;
}


void computePointLightComponents()
{		
	float constant = 1.0f;
	float linear = 0.22f;
	float quadratic = 0.20f;

	vec3 cameraPosEye = vec3(0.0f);//in eye coordinates, the viewer is situated at the origin
	
	//transform normal
	vec3 normalEye = normalize(fNormal);	
	
	//point1
	//compute light direction
	//vec3 lightDirN = normalize(lightDir);
	vec3 lightDirN = normalize(lightPosEye1.xyz - fPosEye.xyz);
	
	//compute view direction 
	vec3 viewDirN = normalize(cameraPosEye - fPosEye.xyz);
		
	//compute half vector
	vec3 halfVector = normalize(lightDirN + viewDirN);
	
	//compute distance to light
	float dist = length(lightPosEye1.xyz - fPosEye.xyz);
	//compute attenuation
	float att = 1.0f / (constant + linear*dist + quadratic*(dist*dist));
		
	//compute ambient light
	ambientPoint1 = att * ambientPointStrength * lightColor1;
	
	//ambient *= (texture(ambientTexture, fTexCoords)).xyz;
	ambientPoint1 *= (texture(diffuseTexture, fTexCoords)).xyz;
	
	
	//compute diffuse light
	diffusePoint1 = att * max(dot(normalEye, lightDirN), 0.0f) * lightColor1;
	diffusePoint1 *= (texture(diffuseTexture, fTexCoords)).xyz;
	
	//compute specular light
	//vec3 reflection = reflect(-lightDirN, normalEye);
	//float specCoeff = pow(max(dot(viewDirN, reflection), 0.0f), shininess);
	float specCoeff = pow(max(dot(normalEye, halfVector), 0.0f), shininess);
	specularPoint1 = att * specularPointStrength * specCoeff * lightColor1;
	specularPoint1 *= (texture(specularTexture, fTexCoords)).xyz;
	
	
	//POINT2
	lightDirN = normalize(lightPosEye2.xyz - fPosEye.xyz);
	viewDirN = normalize(cameraPosEye - fPosEye.xyz);
	halfVector = normalize(lightDirN + viewDirN);
	dist = length(lightPosEye2.xyz - fPosEye.xyz);
	att = 1.0f / (constant + linear*dist + quadratic*(dist*dist));
	ambientPoint2 = att * ambientPointStrength * lightColor1;
	ambientPoint2 *= (texture(diffuseTexture, fTexCoords)).xyz;
	diffusePoint2 = att * max(dot(normalEye, lightDirN), 0.0f) * lightColor2;
	diffusePoint2 *= (texture(diffuseTexture, fTexCoords)).xyz;
	specCoeff = pow(max(dot(normalEye, halfVector), 0.0f), shininess);
	specularPoint2 = att * specularPointStrength * specCoeff * lightColor2;
	specularPoint2 *= (texture(specularTexture, fTexCoords)).xyz;
	
	//POINT3
	lightDirN = normalize(lightPosEye3.xyz - fPosEye.xyz);
	viewDirN = normalize(cameraPosEye - fPosEye.xyz);
	halfVector = normalize(lightDirN + viewDirN);
	dist = length(lightPosEye3.xyz - fPosEye.xyz);
	att = 1.0f / (constant + linear*dist + quadratic*(dist*dist));
	ambientPoint3 = att * ambientPointStrength * lightColor1;
	ambientPoint3 *= (texture(diffuseTexture, fTexCoords)).xyz;
	diffusePoint3 = att * max(dot(normalEye, lightDirN), 0.0f) * lightColor3;
	diffusePoint3 *= (texture(diffuseTexture, fTexCoords)).xyz;
	specCoeff = pow(max(dot(normalEye, halfVector), 0.0f), shininess);
	specularPoint3 = att * specularPointStrength * specCoeff * lightColor3;
	specularPoint3 *= (texture(specularTexture, fTexCoords)).xyz;
	
	//POINT4
	lightDirN = normalize(lightPosEye4.xyz - fPosEye.xyz);
	viewDirN = normalize(cameraPosEye - fPosEye.xyz);
	halfVector = normalize(lightDirN + viewDirN);
	dist = length(lightPosEye4.xyz - fPosEye.xyz);
	att = 1.0f / (constant + linear*dist + quadratic*(dist*dist));
	ambientPoint4 = att * ambientPointStrength * lightColor4;
	ambientPoint4 *= (texture(diffuseTexture, fTexCoords)).xyz;
	diffusePoint4 = att * max(dot(normalEye, lightDirN), 0.0f) * lightColor4;
	diffusePoint4 *= (texture(diffuseTexture, fTexCoords)).xyz;
	specCoeff = pow(max(dot(normalEye, halfVector), 0.0f), shininess);
	specularPoint4 = att * specularPointStrength * specCoeff * lightColor4;
	specularPoint4 *= (texture(specularTexture, fTexCoords)).xyz;
		
	//POINT5
	lightDirN = normalize(lightPosEye5.xyz - fPosEye.xyz);
	viewDirN = normalize(cameraPosEye - fPosEye.xyz);
	halfVector = normalize(lightDirN + viewDirN);
	dist = length(lightPosEye5.xyz - fPosEye.xyz);
	att = 1.0f / (constant + linear*dist + quadratic*(dist*dist));
	ambientPoint5 = att * ambientPointStrength * lightColor5;
	ambientPoint5 *= (texture(diffuseTexture, fTexCoords)).xyz;
	diffusePoint5 = att * max(dot(normalEye, lightDirN), 0.0f) * lightColor5;
	diffusePoint5 *= (texture(diffuseTexture, fTexCoords)).xyz;
	specCoeff = pow(max(dot(normalEye, halfVector), 0.0f), shininess);
	specularPoint5 = att * specularPointStrength * specCoeff * lightColor5;
	specularPoint5 *= (texture(specularTexture, fTexCoords)).xyz;
	
	//POINT6
	lightDirN = normalize(lightPosEye6.xyz - fPosEye.xyz);
	viewDirN = normalize(cameraPosEye - fPosEye.xyz);
	halfVector = normalize(lightDirN + viewDirN);
	dist = length(lightPosEye6.xyz - fPosEye.xyz);
	att = 1.0f / (constant + linear*dist + quadratic*(dist*dist));
	ambientPoint6 = att * ambientPointStrength * lightColor6;
	ambientPoint6 *= (texture(diffuseTexture, fTexCoords)).xyz;
	diffusePoint6 = att * max(dot(normalEye, lightDirN), 0.0f) * lightColor6;
	diffusePoint6 *= (texture(diffuseTexture, fTexCoords)).xyz;
	specCoeff = pow(max(dot(normalEye, halfVector), 0.0f), shininess);
	specularPoint6 = att * specularPointStrength * specCoeff * lightColor6;
	specularPoint6 *= (texture(specularTexture, fTexCoords)).xyz;
	
	//POINT7
	lightDirN = normalize(lightPosEye7.xyz - fPosEye.xyz);
	viewDirN = normalize(cameraPosEye - fPosEye.xyz);
	halfVector = normalize(lightDirN + viewDirN);
	dist = length(lightPosEye7.xyz - fPosEye.xyz);
	att = 1.0f / (constant + linear*dist + quadratic*(dist*dist));
	ambientPoint7 = att * ambientPointStrength * lightColor7;
	ambientPoint7 *= (texture(diffuseTexture, fTexCoords)).xyz;
	diffusePoint7 = att * max(dot(normalEye, lightDirN), 0.0f) * lightColor7;
	diffusePoint7 *= (texture(diffuseTexture, fTexCoords)).xyz;
	specCoeff = pow(max(dot(normalEye, halfVector), 0.0f), shininess);
	specularPoint7 = att * specularPointStrength * specCoeff * lightColor7;
	specularPoint7 *= (texture(specularTexture, fTexCoords)).xyz;
	
	//POINT8
	lightDirN = normalize(lightPosEye8.xyz - fPosEye.xyz);
	viewDirN = normalize(cameraPosEye - fPosEye.xyz);
	halfVector = normalize(lightDirN + viewDirN);
	dist = length(lightPosEye8.xyz - fPosEye.xyz);
	att = 1.0f / (constant + linear*dist + quadratic*(dist*dist));
	ambientPoint8 = att * ambientPointStrength * lightColor8;
	ambientPoint8 *= (texture(diffuseTexture, fTexCoords)).xyz;
	diffusePoint8 = att * max(dot(normalEye, lightDirN), 0.0f) * lightColor8;
	diffusePoint8 *= (texture(diffuseTexture, fTexCoords)).xyz;
	specCoeff = pow(max(dot(normalEye, halfVector), 0.0f), shininess);
	specularPoint8 = att * specularPointStrength * specCoeff * lightColor8;
	specularPoint8 *= (texture(specularTexture, fTexCoords)).xyz;
	
	//POINT9
	lightDirN = normalize(lightPosEye9.xyz - fPosEye.xyz);
	viewDirN = normalize(cameraPosEye - fPosEye.xyz);
	halfVector = normalize(lightDirN + viewDirN);
	dist = length(lightPosEye9.xyz - fPosEye.xyz);
	att = 1.0f / (constant + linear*dist + quadratic*(dist*dist));
	ambientPoint9 = att * ambientPointStrength * lightColor9;
	ambientPoint9 *= (texture(diffuseTexture, fTexCoords)).xyz;
	diffusePoint9 = att * max(dot(normalEye, lightDirN), 0.0f) * lightColor9;
	diffusePoint9 *= (texture(diffuseTexture, fTexCoords)).xyz;
	specCoeff = pow(max(dot(normalEye, halfVector), 0.0f), shininess);
	specularPoint9 = att * specularPointStrength * specCoeff * lightColor9;
	specularPoint9 *= (texture(specularTexture, fTexCoords)).xyz;
	
	//POINT10
	lightDirN = normalize(lightPosEye10.xyz - fPosEye.xyz);
	viewDirN = normalize(cameraPosEye - fPosEye.xyz);
	halfVector = normalize(lightDirN + viewDirN);
	dist = length(lightPosEye10.xyz - fPosEye.xyz);
	att = 1.0f / (constant + linear*dist + quadratic*(dist*dist));
	ambientPoint10 = att * ambientPointStrength * lightColor10;
	ambientPoint10 *= (texture(diffuseTexture, fTexCoords)).xyz;
	diffusePoint10 = att * max(dot(normalEye, lightDirN), 0.0f) * lightColor10;
	diffusePoint10 *= (texture(diffuseTexture, fTexCoords)).xyz;
	specCoeff = pow(max(dot(normalEye, halfVector), 0.0f), shininess);
	specularPoint10 = att * specularPointStrength * specCoeff * lightColor10;
	specularPoint10 *= (texture(specularTexture, fTexCoords)).xyz;
	
	//POINT11
	lightDirN = normalize(lightPosEye11.xyz - fPosEye.xyz);
	viewDirN = normalize(cameraPosEye - fPosEye.xyz);
	halfVector = normalize(lightDirN + viewDirN);
	dist = length(lightPosEye11.xyz - fPosEye.xyz);
	att = 1.0f / (constant + linear*dist + quadratic*(dist*dist));
	ambientPoint11 = att * ambientPointStrength * lightColor11;
	ambientPoint11 *= (texture(diffuseTexture, fTexCoords)).xyz;
	diffusePoint11 = att * max(dot(normalEye, lightDirN), 0.0f) * lightColor11;
	diffusePoint11 *= (texture(diffuseTexture, fTexCoords)).xyz;
	specCoeff = pow(max(dot(normalEye, halfVector), 0.0f), shininess);
	specularPoint11 = att * specularPointStrength * specCoeff * lightColor11;
	specularPoint11 *= (texture(specularTexture, fTexCoords)).xyz;
	
	//POINT12
	lightDirN = normalize(lightPosEye12.xyz - fPosEye.xyz);
	viewDirN = normalize(cameraPosEye - fPosEye.xyz);
	halfVector = normalize(lightDirN + viewDirN);
	dist = length(lightPosEye12.xyz - fPosEye.xyz);
	att = 1.0f / (constant + linear*dist + quadratic*(dist*dist));
	ambientPoint12 = att * ambientPointStrength * lightColor12;
	ambientPoint12 *= (texture(diffuseTexture, fTexCoords)).xyz;
	diffusePoint12 = att * max(dot(normalEye, lightDirN), 0.0f) * lightColor12;
	diffusePoint12 *= (texture(diffuseTexture, fTexCoords)).xyz;
	specCoeff = pow(max(dot(normalEye, halfVector), 0.0f), shininess);
	specularPoint12 = att * specularPointStrength * specCoeff * lightColor12;
	specularPoint12 *= (texture(specularTexture, fTexCoords)).xyz;
	
	//POINT13
	lightDirN = normalize(lightPosEye13.xyz - fPosEye.xyz);
	viewDirN = normalize(cameraPosEye - fPosEye.xyz);
	halfVector = normalize(lightDirN + viewDirN);
	dist = length(lightPosEye13.xyz - fPosEye.xyz);
	att = 1.0f / (constant + linear*dist + quadratic*(dist*dist));
	ambientPoint13 = att * ambientPointStrength * lightColor13;
	ambientPoint13 *= (texture(diffuseTexture, fTexCoords)).xyz;
	diffusePoint13 = att * max(dot(normalEye, lightDirN), 0.0f) * lightColor13;
	diffusePoint13 *= (texture(diffuseTexture, fTexCoords)).xyz;
	specCoeff = pow(max(dot(normalEye, halfVector), 0.0f), shininess);
	specularPoint13 = att * specularPointStrength * specCoeff * lightColor13;
	specularPoint13 *= (texture(specularTexture, fTexCoords)).xyz;
}


void computeLightComponents()
{		
	vec3 cameraPosEye = vec3(0.0f);//in eye coordinates, the viewer is situated at the origin
	
	//transform normal
	vec3 normalEye = normalize(fNormal);	
	
	//compute light direction
	vec3 lightDirN = normalize(lightDir);
	
	//compute view direction 
	vec3 viewDirN = normalize(cameraPosEye - fPosEye.xyz);
		
	//compute ambient light
	ambient = ambientStrength * lightColor;
	
	//compute diffuse light
	diffuse = max(dot(normalEye, lightDirN), 0.0f) * lightColor;
	
	//compute specular light
	vec3 reflection = reflect(-lightDirN, normalEye);
	float specCoeff = pow(max(dot(viewDirN, reflection), 0.0f), shininess);
	specular = specularStrength * specCoeff * lightColor;
}

void computeLightSpotComponents() {

	vec3 cameraPosEye = vec3(0.0f);
	vec3 lightDir = normalize(spotPos - fPos);
	vec3 lightDirN = normalize(lightDir);
	vec3 viewDirN = normalize(cameraPosEye - fPosEye.xyz);
	vec3 halfVector = normalize(lightDirN + viewDirN);

	vec3 normalEye = normalize(fNormal);
	float diff = max(dot(vecNormal, lightDir), 0.0f);
	float spec = pow(max(dot(normalEye, halfVector), 0.0f), shininess);
	float dist = length(spotPos - fPos);
	float attenuation = 1.0f / (spotConstant + spotLinear * dist + spotQuadratic * dist * dist);

	float theta = dot(lightDir, normalize(-spotDir));
	float epsilon = spotlight1 - spotlight2;
	float intensity = clamp((theta - spotlight2)/epsilon, 0.0, 1.0);

	ambientSpot = spotLightColor * spotLightAmbient * vec3(texture(diffuseTexture, fTexCoords));
	diffuseSpot = spotLightColor * spotLightSpecular * diff * vec3(texture(diffuseTexture, fTexCoords));
	specularSpot = spotLightColor * spotLightSpecular * spec * vec3(texture(specularTexture, fTexCoords));
	ambientSpot *= attenuation * intensity;
	diffuseSpot *= attenuation * intensity;
	specularSpot *= attenuation * intensity;
	
}

float computeFog()
{
	float fogDensity = 0.02f;
	float fragmentDistance = length(fPosEye);
	float fogFactor = exp(-pow(fragmentDistance*fogDensity, 2));
	
	return clamp(fogFactor, 0.0f, 1.0f);
}

void main() 
{
	computeLightComponents();
	computePointLightComponents();
	computeLightSpotComponents();
	shadow = computeShadow();
	float fogFactor = computeFog();
	
	vec4 fogColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);
	
	vec4 colorFromTexture = texture(diffuseTexture, fTexCoords);
	if(colorFromTexture.a < 0.1)
		discard;
	
	vec3 baseColor = vec3(0.9f, 0.35f, 0.0f);//orange
	
	ambient *= colorFromTexture.rgb;
	diffuse *= colorFromTexture.rgb;
	specular *= colorFromTexture.rgb;

	ambientPoint1 *= colorFromTexture.rgb;
	diffusePoint1 *= colorFromTexture.rgb;
	specularPoint1 *= colorFromTexture.rgb;
	
	ambientPoint2 *= colorFromTexture.rgb;
	diffusePoint2 *= colorFromTexture.rgb;
	specularPoint2 *= colorFromTexture.rgb;
	
	ambientPoint3 *= colorFromTexture.rgb;
	diffusePoint3 *= colorFromTexture.rgb;
	specularPoint3 *= colorFromTexture.rgb;
	
	ambientPoint4 *= colorFromTexture.rgb;
	diffusePoint4 *= colorFromTexture.rgb;
	specularPoint4 *= colorFromTexture.rgb;
	
	ambientPoint5 *= colorFromTexture.rgb;
	diffusePoint5 *= colorFromTexture.rgb;
	specularPoint5 *= colorFromTexture.rgb;
	
	ambientPoint6 *= colorFromTexture.rgb;
	diffusePoint6 *= colorFromTexture.rgb;
	specularPoint6 *= colorFromTexture.rgb;
	
	ambientPoint7 *= colorFromTexture.rgb;
	diffusePoint7 *= colorFromTexture.rgb;
	specularPoint7 *= colorFromTexture.rgb;
	
	ambientPoint8 *= colorFromTexture.rgb;
	diffusePoint8 *= colorFromTexture.rgb;
	specularPoint8 *= colorFromTexture.rgb;
	
	ambientPoint9 *= colorFromTexture.rgb;
	diffusePoint9 *= colorFromTexture.rgb;
	specularPoint9 *= colorFromTexture.rgb;
	
	ambientPoint10 *= colorFromTexture.rgb;
	diffusePoint10 *= colorFromTexture.rgb;
	specularPoint10 *= colorFromTexture.rgb;
	
	ambientPoint11 *= colorFromTexture.rgb;
	diffusePoint11 *= colorFromTexture.rgb;
	specularPoint11 *= colorFromTexture.rgb;
	
	ambientPoint12 *= colorFromTexture.rgb;
	diffusePoint12 *= colorFromTexture.rgb;
	specularPoint12 *= colorFromTexture.rgb;
	
	ambientPoint13 *= colorFromTexture.rgb;
	diffusePoint13 *= colorFromTexture.rgb;
	specularPoint13 *= colorFromTexture.rgb;
	
	ambientSpot *= colorFromTexture.rgb;
	diffuseSpot *= colorFromTexture.rgb;
	specularSpot *= colorFromTexture.rgb;
	
	vec3 ambientSum = ambient + ambientPoint1 + ambientPoint2 + ambientPoint3 + ambientPoint4 + ambientPoint5 + ambientPoint6 + ambientPoint7 + ambientPoint8 + ambientPoint9 + ambientPoint10 + ambientPoint11 + ambientPoint12 + ambientPoint13;
	vec3 diffuseSum = diffuse + diffusePoint1 + diffusePoint2 + diffusePoint3 + diffusePoint4 + diffusePoint5 + diffusePoint6 + diffusePoint7 + diffusePoint8 + diffusePoint9 + diffusePoint10 + diffusePoint11 + diffusePoint12 + diffusePoint13;
	vec3 specularSum = specular + specularPoint1 + specularPoint2 + specularPoint3 + specularPoint4 + specularPoint5 + specularPoint6 + specularPoint7 + specularPoint8 + specularPoint9 + specularPoint10 + specularPoint11 + specularPoint12 + specularPoint13;
	vec3 color;
	
	if(spot == 1) {
		color = min((ambientSpot + diffuseSpot) + specularSpot, 1.0f);
		//color = min((ambientSpot + (1.0f - shadow) * diffuseSpot) + (1.0f - shadow) * specularSpot, 1.0f);	
	}
	else {
		color = min((ambientSum + (1.0f - shadow)*diffuseSum) + (1.0f - shadow)*specularSum, 1.0f);
	}
	
	if(withFog == 1) {
		fColor = fogColor * (1 - fogFactor) + vec4(color, 1.0f) * fogFactor;
	} else {
		fColor = vec4(color, 1.0f);
	}
	
}
