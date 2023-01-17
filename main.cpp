//
//  main.cpp
//  OpenGL Advances Lighting
//
//  Created by CGIS on 28/11/16.
//  Copyright � 2016 CGIS. All rights reserved.
//

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"
#include "Model3D.hpp"
#include "Camera.hpp"
#include "SkyBox.hpp"
#include "CarMovement.hpp"

#include <iostream>
#include <math.h>
#include <string>
#include <ctime>
#include <cstdlib>
#include <Windows.h>
#include <future>
#pragma comment(lib, "Winmm.lib")

//#ifdef __cplusplus
//extern "C" {
//#endif
//
//	__declspec(dllexport) int NvOptimusEnablement = 1;
//	__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;
//
//#ifdef __cplusplus
//}
//#endif

int glWindowWidth = 1920;
int glWindowHeight = 1080;
int retina_width, retina_height;
GLFWwindow* glWindow = NULL;

const unsigned int SHADOW_WIDTH = 8192;
const unsigned int SHADOW_HEIGHT = 8192;

glm::vec3 sunColor(1.0f, 1.0f, 1.0f);

glm::mat4 model;
GLuint modelLoc;
glm::mat4 view;
GLuint viewLoc;
glm::mat4 projection;
GLuint projectionLoc;
glm::mat3 normalMatrix;
GLuint normalMatrixLoc;
glm::mat4 lightRotation;

glm::vec3 lightDir;
GLuint lightDirLoc;
glm::vec3 lightColor;
GLuint lightColorLoc;

glm::vec3 lightPos1;
GLuint lightPos1Loc;
glm::vec3 lightColor1;
GLuint lightColor1Loc;

glm::vec3 lightPos2;
GLuint lightPos2Loc;
glm::vec3 lightColor2;
GLuint lightColor2Loc;

glm::vec3 lightPos3;
GLuint lightPos3Loc;
glm::vec3 lightColor3;
GLuint lightColor3Loc;

glm::vec3 lightPos4;
GLuint lightPos4Loc;
glm::vec3 lightColor4;
GLuint lightColor4Loc;

glm::vec3 lightPos5;
GLuint lightPos5Loc;
glm::vec3 lightColor5;
GLuint lightColor5Loc;

glm::vec3 lightPos6;
GLuint lightPos6Loc;
glm::vec3 lightColor6;
GLuint lightColor6Loc;

glm::vec3 lightPos7;
GLuint lightPos7Loc;
glm::vec3 lightColor7;
GLuint lightColor7Loc;

glm::vec3 lightPos8;
GLuint lightPos8Loc;
glm::vec3 lightColor8;
GLuint lightColor8Loc;

glm::vec3 lightPos9;
GLuint lightPos9Loc;
glm::vec3 lightColor9;
GLuint lightColor9Loc;

glm::vec3 lightPos10;
GLuint lightPos10Loc;
glm::vec3 lightColor10;
GLuint lightColor10Loc;

glm::vec3 lightPos11;
GLuint lightPos11Loc;
glm::vec3 lightColor11;
GLuint lightColor11Loc;

glm::vec3 lightPos12;
GLuint lightPos12Loc;
glm::vec3 lightColor12;
GLuint lightColor12Loc;

glm::vec3 lightPos13;
GLuint lightPos13Loc;
glm::vec3 lightColor13;
GLuint lightColor13Loc;

gps::Camera myCamera(
	glm::vec3(55.0f, 2.2176f, -107.08f),
	glm::vec3(29.102f, 2.31463f, -85.542f),
	glm::vec3(0.0f, 1.0f, 0.0f));
float cameraSpeed = 0.2f;
float animCameraSpeed = 0.05f;

gps::Camera preAnimCamera(
	glm::vec3(0.0f, 2.0f, 5.5f),
	glm::vec3(0.0f, 0.0f, 0.0f),
	glm::vec3(0.0f, 1.0f, 0.0f));

gps::Camera animCamera(
	glm::vec3(55.0f, 2.2176f, -107.08f),
	glm::vec3(31.102f, 2.31463f, -85.542f),
	glm::vec3(0.0f, 1.0f, 0.0f));
glm::vec3 currentPosition = myCamera.getPosition();
glm::vec3 nextPosition = glm::vec3(29.102f, 2.31463f, -85.542f);

bool done1 = false;
bool done2 = false;
bool first = true;
float increment = 0.01f;


bool pressedKeys[1024];
float angleY = 0.0f;
float carUp = 0.0f;
float carLeft = 0.0f;
float carX = 30.795;
float carY = 1.2386;
float carZ = -106.93;

glm::vec3 carTarget = glm::vec3(13.342f, 1.2386, -106.93);
gps::Car myCar(
	glm::vec3(carX, carY, carZ),
	carTarget,
	glm::vec3(0.0f, 1.0f, 0.0f));

float butt2Angle = 0.0f;
float rightGateAngle = 0.0f;
float leftGateAngle = 0.0f;

float offsetY[350] = { 26.0 };
float offsetX[350] = { 0.0f };
float offsetZ[350] = { 0.0f };
float highX = 127.36f;
float lowX = -256.59f;
float lowZ = 22.046;
float highZ = -265.67;


glm::vec3 skateInitial = glm::vec3(30.601f, 0.49772f, -81.018f);
glm::vec3 wheel1Initial = glm::vec3(30.415, 0.38503, -81.451);
glm::vec3 wheel2Initial = glm::vec3(30.415, 0.38608, -80.614);
float wheelsAngle = 0.0f;
float skateOffsetX = 0.0f;
float skateOffsetY = 0.0f;
float skateOffsetZ = 0.0f;
bool goUp = true;
bool makeItRain = false;
bool started = false;

GLfloat lightAngle;

gps::Model3D demo;
gps::Model3D sun;
gps::Model3D screenQuad;

gps::Model3D benches[13]; //done
gps::Model3D stalpi[14]; //done
gps::Model3D rampe[5]; //done
gps::Model3D tree1; //done
gps::Model3D tree2; //done
gps::Model3D flowers; //done
gps::Model3D fence; //done
gps::Model3D ramps_fence; //done
gps::Model3D gate1; //done
gps::Model3D gate2; //done
gps::Model3D car; //done
gps::Model3D motel; //done
gps::Model3D gas_station; //done
gps::Model3D skate; //done
gps::Model3D wheel1;
gps::Model3D wheel2;
gps::Model3D carousel; //done
gps::Model3D flats[8]; //done
gps::Model3D button1; //done
gps::Model3D button2; //done
gps::Model3D bec[14]; //done
gps::Model3D rain[350];

//gps::Model3D leaf;


gps::Shader myCustomShader;

//gps::Shader carouselShader;

gps::Shader lightShader;
gps::Shader screenQuadShader;
gps::Shader depthMapShader;
//gps::Shader leafGroundShader;

GLuint shadowMapFBO;
GLuint depthMapTexture;

bool showDepthMap;

std::vector<const GLchar*> faces;
gps::SkyBox mySkyBox;
gps::Shader skyboxShader;

int withFog = 0;
GLuint withFogLoc;

int withLight = 0;
GLuint withLightLoc;

boolean spot = false;
GLuint spotLoc;

glm::vec3 spotDir(0.0f, -1.0f, 0.0f);
GLuint spotDirLoc;

glm::vec3 spotPos(-66.12f, 8.05f, -123.78f);
GLuint spotPosLoc;

float spotCutOff = 0.9;
GLuint spotCutOffLoc;

float spotLight1 = glm::cos(glm::radians(40.5f));
GLuint spotLight1Loc;

float spotLight2 = glm::cos(glm::radians(100.5f));
GLuint spotLight2Loc;

float Convert(float degree)
{
	double pi = 3.14159265359;
	return (degree * (pi / 180));
}

GLenum glCheckError_(const char *file, int line) {
	GLenum errorCode;
	while ((errorCode = glGetError()) != GL_NO_ERROR)
	{
		std::string error;
		switch (errorCode)
		{
		case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
		case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
		case GL_STACK_OVERFLOW:                error = "STACK_OVERFLOW"; break;
		case GL_STACK_UNDERFLOW:               error = "STACK_UNDERFLOW"; break;
		case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
		}
		std::cout << error << " | " << file << " (" << line << ")" << std::endl;
	}
	return errorCode;
}
#define glCheckError() glCheckError_(__FILE__, __LINE__)

void windowResizeCallback(GLFWwindow* window, int width, int height) {
	fprintf(stdout, "window resized to width: %d , and height: %d\n", width, height);
	//TODO	
}

glm::mat4 computeLightSpaceTrMatrix() {
	//TODO - Return the light-space transformation matrix

	glm::mat4 lightView = glm::lookAt(glm::inverseTranspose(glm::mat3(lightRotation )) * lightDir, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	const GLfloat near_plane = 0.1f, far_plane = 600.0f;
	glm::mat4 lightProjection = glm::ortho(-300.0f, 300.0f, -300.0f, 300.0f, near_plane, far_plane);

	glm::mat4 lightSpaceTrMatrix = lightProjection * lightView;

	return lightSpaceTrMatrix;
}


void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key == GLFW_KEY_M && action == GLFW_PRESS)
		showDepthMap = !showDepthMap;

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			pressedKeys[key] = true;
		else if (action == GLFW_RELEASE)
			pressedKeys[key] = false;
	}
}

float lastX = 400, lastY = 300;
bool firstMouse = true;
float pitch = 0.0f;
float yaw = -90.0f;
void mouse_callback(GLFWwindow* glWindow, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates range from bottom to top
	lastX = xpos;
	lastY = ypos;

	const float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	myCamera.rotate(-pitch, yaw);
}

float carPitch = 0.0f;
float carYaw = -90.0f;


float t = 0.0f;
bool animate = false;
void processMovement()
{
	if (pressedKeys[GLFW_KEY_Q]) {
		angleY -= 1.0f;
	}

	if (pressedKeys[GLFW_KEY_E]) {
		angleY += 1.0f;
	}

	if (pressedKeys[GLFW_KEY_J]) {
		lightAngle -= 1.0f;
	}

	if (pressedKeys[GLFW_KEY_L]) {
		lightAngle += 1.0f;
	}

	if (pressedKeys[GLFW_KEY_W]) {
		myCamera.move(gps::MOVE_FORWARD, cameraSpeed);
	}

	if (pressedKeys[GLFW_KEY_S]) {
		myCamera.move(gps::MOVE_BACKWARD, cameraSpeed);
	}

	if (pressedKeys[GLFW_KEY_A]) {
		myCamera.move(gps::MOVE_LEFT, cameraSpeed);
	}

	if (pressedKeys[GLFW_KEY_D]) {
		myCamera.move(gps::MOVE_RIGHT, cameraSpeed);
	}

	if (pressedKeys[GLFW_KEY_F]) {
		withFog = 1;
	}

	if (pressedKeys[GLFW_KEY_G]) {
		withFog = 0;
	}

	if (pressedKeys[GLFW_KEY_UP]) {
		myCar.move(false, 0.3f);
	}

	if (pressedKeys[GLFW_KEY_DOWN]) {
		myCar.move(true, 0.3f);
	}

	if (pressedKeys[GLFW_KEY_LEFT]) {
		carYaw += 1.0f;
		carLeft += 1.0f;

		myCar.rotate(-pitch, yaw);
	}

	if (pressedKeys[GLFW_KEY_RIGHT]) {
		carLeft -= 1.0f;
		carYaw -= 1.0f;

		myCar.rotate(-pitch, yaw);
	}

	if (pressedKeys[GLFW_KEY_1]) {
		butt2Angle += 1.0f;
	}

	if (pressedKeys[GLFW_KEY_2]) {
		butt2Angle -= 1.0f;
	}

	if (pressedKeys[GLFW_KEY_Z]) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	if (pressedKeys[GLFW_KEY_X]) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	if (pressedKeys[GLFW_KEY_C]) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}

	if (pressedKeys[GLFW_KEY_5]) {
		rightGateAngle += 1.0f;
	}

	if (pressedKeys[GLFW_KEY_6]) {
		rightGateAngle -= 1.0f;
	}

	if (pressedKeys[GLFW_KEY_7]) {
		leftGateAngle += 1.0f;
	}

	if (pressedKeys[GLFW_KEY_8]) {
		leftGateAngle -= 1.0f;
	}

	if (pressedKeys[GLFW_KEY_9]) {
		makeItRain = true;
	}

	if (pressedKeys[GLFW_KEY_0]) {
		makeItRain = false;
		started = false;
		PlaySound(NULL, NULL, 0);
	}

	if (pressedKeys[GLFW_KEY_O]) {

		animate = true;
	
	}

	if (pressedKeys[GLFW_KEY_P]) {
		animate = false;
		first = true;
		currentPosition = myCamera.getPosition();
		nextPosition = glm::vec3(29.102f, 2.31463f, -85.542f);
		glfwSetCursorPosCallback(glWindow, mouse_callback);
	}

	if (pressedKeys[GLFW_KEY_B]) {
		sunColor = glm::vec3(1.0f, 1.0f, 1.0f);
		myCustomShader.useShaderProgram();
		lightColor = glm::vec3(1.0f, 1.0f, 1.0f); //white light
		lightColorLoc = glGetUniformLocation(myCustomShader.shaderProgram, "lightColor");
		glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));
	}

	if (pressedKeys[GLFW_KEY_N]) {
		sunColor = glm::vec3(0.0f, 0.0f, 0.0f);
		myCustomShader.useShaderProgram();
		lightColor = glm::vec3(0.0f, 0.0f, 0.0f); //no light
		lightColorLoc = glGetUniformLocation(myCustomShader.shaderProgram, "lightColor");
		glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));
	}

	if (pressedKeys[GLFW_KEY_U]) {
		spot = true;
	}

	if (pressedKeys[GLFW_KEY_I]) {
		spot = false;
	}
}



bool initOpenGLWindow()
{
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 4);

	glWindow = glfwCreateWindow(glWindowWidth, glWindowHeight, "OpenGL Shader Example", NULL, NULL);
	if (!glWindow) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return false;
	}

	glfwSetWindowSizeCallback(glWindow, windowResizeCallback);
	glfwSetKeyCallback(glWindow, keyboardCallback);

	//for input from mouse
	glfwSetInputMode(glWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(glWindow, mouse_callback);


	glfwMakeContextCurrent(glWindow);

	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);

	//for RETINA display
	glfwGetFramebufferSize(glWindow, &retina_width, &retina_height);

	//skybox

	faces.push_back("textures/nevada/nevada_rt.tga");
	faces.push_back("textures/nevada/nevada_lf.tga");
	faces.push_back("textures/nevada/nevada_up.tga");
	faces.push_back("textures/nevada/nevada_dn.tga");
	faces.push_back("textures/nevada/nevada_bk.tga");
	faces.push_back("textures/nevada/nevada_ft.tga");

	mySkyBox.Load(faces);

	return true;
}

void initOpenGLState()
{
	glClearColor(0.3, 0.3, 0.3, 1.0);
	glViewport(0, 0, retina_width, retina_height);

	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
	//glEnable(GL_CULL_FACE); // cull face
	//glCullFace(GL_BACK); // cull back face
	glFrontFace(GL_CCW); // GL_CCW for counter clock-wise

	glEnable(GL_FRAMEBUFFER_SRGB);
}

void initObjects() {
	demo.LoadModel("objects/demo/demo.obj");
	
	//init benches and stalpi
	for (int i = 0; i < 13; i++) {
		benches[i].LoadModel("objects/demo/bench" + std::to_string(i + 1) + ".obj");
	}

	for (int i = 0; i < 13; i++) {
		stalpi[i].LoadModel("objects/demo/stalp" + std::to_string(i+1) + ".obj");
		bec[i].LoadModel("objects/demo/bec" + std::to_string(i + 1) + ".obj");
	}

	//init rampe
	for (int i = 0; i < 5; i++) {
		rampe[i].LoadModel("objects/demo/ramp" + std::to_string(i + 1) + ".obj");
	}

	//init rampe_fence
	ramps_fence.LoadModel("objects/demo/ramp_fence.obj");

	//init skate
	skate.LoadModel("objects/demo/skate.obj");

	//init skate_wheels
	//skate_wheels.LoadModel("objects/demo/skate_wheels.obj");
	wheel1.LoadModel("objects/demo/wheel1.obj");
	wheel2.LoadModel("objects/demo/wheel2.obj");

	//init garden
	//tree1.LoadModel("objects/demo/tree1.obj");
	//tree2.LoadModel("objects/demo/tree2.obj");
	fence.LoadModel("objects/demo/fence.obj");
	carousel.LoadModel("objects/demo/carousel.obj");
	gate1.LoadModel("objects/demo/gate1.obj");
	gate2.LoadModel("objects/demo/gate2.obj");
	flowers.LoadModel("objects/demo/flowers.obj");

	//load car
	car.LoadModel("objects/demo/car.obj");

	//load motel
	motel.LoadModel("objects/demo/motel.obj");

	//load gas station
	gas_station.LoadModel("objects/demo/gas_station.obj");

	//load flats
	for (int i = 0; i < 8; i++) {
		flats[i].LoadModel("objects/demo/bloc" + std::to_string(i + 1) + ".obj");
	}

	//load buttons
	button1.LoadModel("objects/demo/button1.obj");
	button2.LoadModel("objects/demo/button2.obj");

	for (int i = 0; i < 350; i++) {
		rain[i].LoadModel("objects/demo/rain.obj");
	}

	//mciSendString(TEXT("open waveaudio!rain.wav alias MyFile"), NULL, 0, 0);
	srand(static_cast <unsigned> (time(0)));

	for (int i = 0; i < 350; i++) {
		offsetX[i] = lowX + (float)(rand()) / (RAND_MAX / (highX - lowX));
	}
	for (int i = 0; i < 350; i++) {
		offsetZ[i] = lowZ + (float)(rand()) / (RAND_MAX / (highZ - lowZ));
	}

	sun.LoadModel("objects/demo/sun.obj");
	screenQuad.LoadModel("objects/quad/quad.obj");
	
}

void initShaders() {
	myCustomShader.loadShader("shaders/shaderStart.vert", "shaders/shaderStart.frag");
	myCustomShader.useShaderProgram();

	lightShader.loadShader("shaders/lightCube.vert", "shaders/lightCube.frag");
	lightShader.useShaderProgram();
	screenQuadShader.loadShader("shaders/screenQuad.vert", "shaders/screenQuad.frag");
	screenQuadShader.useShaderProgram();
	depthMapShader.loadShader("shaders/depthMapShader.vert", "shaders/depthMapShader.frag");
	depthMapShader.useShaderProgram();

	//skybox
	skyboxShader.loadShader("shaders/skyboxShader.vert", "shaders/skyboxShader.frag");
	skyboxShader.useShaderProgram();

}

void initUniforms() {

	myCustomShader.useShaderProgram();

	model = glm::mat4(1.0f);
	modelLoc = glGetUniformLocation(myCustomShader.shaderProgram, "model");
	withFogLoc = glGetUniformLocation(myCustomShader.shaderProgram, "withFog");
	glUniform1i(withFogLoc, withFog);

	view = myCamera.getViewMatrix();
	viewLoc = glGetUniformLocation(myCustomShader.shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	
	normalMatrix = glm::mat3(glm::inverseTranspose(view*model));
	normalMatrixLoc = glGetUniformLocation(myCustomShader.shaderProgram, "normalMatrix");
	glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
	
	projection = glm::perspective(glm::radians(45.0f), (float)retina_width / (float)retina_height, 0.1f, 1000.0f);
	projectionLoc = glGetUniformLocation(myCustomShader.shaderProgram, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

	//set the light direction (direction towards the light)
	lightDir = glm::vec3(-219.0f, 89.09f, -122.85f);
	lightRotation = glm::rotate(glm::mat4(1.0f), glm::radians(lightAngle), glm::vec3(0.0f, 1.0f, 0.0f));
	lightDirLoc = glGetUniformLocation(myCustomShader.shaderProgram, "lightDir");	
	glUniform3fv(lightDirLoc, 1, glm::value_ptr(glm::inverseTranspose(glm::mat3(lightRotation)) * lightDir));

	//set light color
	lightColor = glm::vec3(1.0f, 1.0f, 1.0f); //white light
	lightColorLoc = glGetUniformLocation(myCustomShader.shaderProgram, "lightColor");
	glUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));

	//point light
	lightPos1 = glm::vec3(-109.2, 3.4108, -113.66);
	lightPos1Loc = glGetUniformLocation(myCustomShader.shaderProgram, "lightPos1");
	glUniform3fv(lightPos1Loc, 1, glm::value_ptr(lightPos1));

	lightColor1 = glm::vec3(1.0f, 1.0f, 1.0f);
	lightColor1Loc = glGetUniformLocation(myCustomShader.shaderProgram, "lightColor1");
	glUniform3fv(lightColor1Loc, 1, glm::value_ptr(lightColor1));

	//point light
	lightPos2 = glm::vec3(-99.936, 3.4108, -109.17);
	lightPos2Loc = glGetUniformLocation(myCustomShader.shaderProgram, "lightPos2");
	glUniform3fv(lightPos2Loc, 1, glm::value_ptr(lightPos2));

	lightColor2 = glm::vec3(1.0f, 1.0f, 1.0f);
	lightColor2Loc = glGetUniformLocation(myCustomShader.shaderProgram, "lightColor2");
	glUniform3fv(lightColor2Loc, 1, glm::value_ptr(lightColor2));

	//point light
	lightPos3 = glm::vec3(-91.782, 3.4109, -104.68);
	lightPos3Loc = glGetUniformLocation(myCustomShader.shaderProgram, "lightPos3");
	glUniform3fv(lightPos3Loc, 1, glm::value_ptr(lightPos3));

	lightColor3 = glm::vec3(1.0f, 1.0f, 1.0f);
	lightColor3Loc = glGetUniformLocation(myCustomShader.shaderProgram, "lightColor3");
	glUniform3fv(lightColor3Loc, 1, glm::value_ptr(lightColor3));

	//point light
	lightPos4 = glm::vec3(-78.526, 3.4108, -102.18);
	lightPos4Loc = glGetUniformLocation(myCustomShader.shaderProgram, "lightPos4");
	glUniform3fv(lightPos4Loc, 1, glm::value_ptr(lightPos4));

	lightColor4 = glm::vec3(1.0f, 1.0f, 1.0f);
	lightColor4Loc = glGetUniformLocation(myCustomShader.shaderProgram, "lightColor4");
	glUniform3fv(lightColor4Loc, 1, glm::value_ptr(lightColor4));

	//point light
	lightPos5 = glm::vec3(-67.485, 3.4116, -99.795);
	lightPos5Loc = glGetUniformLocation(myCustomShader.shaderProgram, "lightPos5");
	glUniform3fv(lightPos5Loc, 1, glm::value_ptr(lightPos5));

	lightColor5 = glm::vec3(1.0f, 1.0f, 1.0f);
	lightColor5Loc = glGetUniformLocation(myCustomShader.shaderProgram, "lightColor5");
	glUniform3fv(lightColor5Loc, 1, glm::value_ptr(lightColor5));

	//point light
	lightPos6 = glm::vec3(-55.61, 3.4109, -99.615);
	lightPos6Loc = glGetUniformLocation(myCustomShader.shaderProgram, "lightPos6");
	glUniform3fv(lightPos6Loc, 1, glm::value_ptr(lightPos6));

	lightColor6 = glm::vec3(1.0f, 1.0f, 1.0f);
	lightColor6Loc = glGetUniformLocation(myCustomShader.shaderProgram, "lightColor6");
	glUniform3fv(lightColor6Loc, 1, glm::value_ptr(lightColor6));

	//point light
	lightPos7 = glm::vec3(-45.699, 3.4109, -100.04);
	lightPos7Loc = glGetUniformLocation(myCustomShader.shaderProgram, "lightPos7");
	glUniform3fv(lightPos7Loc, 1, glm::value_ptr(lightPos7));

	lightColor7 = glm::vec3(1.0f, 1.0f, 1.0f);
	lightColor7Loc = glGetUniformLocation(myCustomShader.shaderProgram, "lightColor7");
	glUniform3fv(lightColor7Loc, 1, glm::value_ptr(lightColor7));

	//point light
	lightPos8 = glm::vec3(-36.702, 3.4109, -99.465);
	lightPos8Loc = glGetUniformLocation(myCustomShader.shaderProgram, "lightPos8");
	glUniform3fv(lightPos8Loc, 1, glm::value_ptr(lightPos8));

	lightColor8 = glm::vec3(1.0f, 1.0f, 1.0f);
	lightColor8Loc = glGetUniformLocation(myCustomShader.shaderProgram, "lightColor8");
	glUniform3fv(lightColor8Loc, 1, glm::value_ptr(lightColor8));

	//point light
	lightPos9 = glm::vec3(-58.735, 3.3908, -92.486);
	lightPos9Loc = glGetUniformLocation(myCustomShader.shaderProgram, "lightPos9");
	glUniform3fv(lightPos9Loc, 1, glm::value_ptr(lightPos9));

	lightColor9 = glm::vec3(1.0f, 1.0f, 1.0f);
	lightColor9Loc = glGetUniformLocation(myCustomShader.shaderProgram, "lightColor9");
	glUniform3fv(lightColor9Loc, 1, glm::value_ptr(lightColor9));

	//point light
	lightPos10 = glm::vec3(-70.908, 3.3909, -92.995);
	lightPos10Loc = glGetUniformLocation(myCustomShader.shaderProgram, "lightPos10");
	glUniform3fv(lightPos10Loc, 1, glm::value_ptr(lightPos10));

	lightColor10 = glm::vec3(1.0f, 1.0f, 1.0f);
	lightColor10Loc = glGetUniformLocation(myCustomShader.shaderProgram, "lightColor10");
	glUniform3fv(lightColor10Loc, 1, glm::value_ptr(lightColor10));

	//point light
	lightPos11 = glm::vec3(-83.258, 3.391, -95.157);
	lightPos11Loc = glGetUniformLocation(myCustomShader.shaderProgram, "lightPos11");
	glUniform3fv(lightPos11Loc, 1, glm::value_ptr(lightPos11));

	lightColor11 = glm::vec3(1.0f, 1.0f, 1.0f);
	lightColor11Loc = glGetUniformLocation(myCustomShader.shaderProgram, "lightColor11");
	glUniform3fv(lightColor11Loc, 1, glm::value_ptr(lightColor11));

	//point light
	lightPos12 = glm::vec3(-95.69, 3.4109, -99.701);
	lightPos12Loc = glGetUniformLocation(myCustomShader.shaderProgram, "lightPos12");
	glUniform3fv(lightPos12Loc, 1, glm::value_ptr(lightPos12));

	lightColor12 = glm::vec3(1.0f, 1.0f, 1.0f);
	lightColor12Loc = glGetUniformLocation(myCustomShader.shaderProgram, "lightColor12");
	glUniform3fv(lightColor12Loc, 1, glm::value_ptr(lightColor12));

	//point light
	lightPos13 = glm::vec3(-106.82, 3.4108, -104.36);
	lightPos13Loc = glGetUniformLocation(myCustomShader.shaderProgram, "lightPos13");
	glUniform3fv(lightPos13Loc, 1, glm::value_ptr(lightPos13));

	lightColor13 = glm::vec3(1.0f, 1.0f, 1.0f);
	lightColor13Loc = glGetUniformLocation(myCustomShader.shaderProgram, "lightColor13");
	glUniform3fv(lightColor13Loc, 1, glm::value_ptr(lightColor13));

	spotPosLoc = glGetUniformLocation(myCustomShader.shaderProgram, "spotPos");
	glUniform3fv(spotPosLoc, 1, glm::value_ptr(spotPos));

	spotDirLoc = glGetUniformLocation(myCustomShader.shaderProgram, "spotDir");
	glUniform3fv(spotDirLoc, 1, glm::value_ptr(spotDir));

	spotLoc = glGetUniformLocation(myCustomShader.shaderProgram, "spot");
	glUniform1i(spotLoc, spot);

	spotLight1Loc = glGetUniformLocation(myCustomShader.shaderProgram, "spotLight1");
	glUniform1f(spotLight1Loc, spotLight1);

	spotLight2Loc = glGetUniformLocation(myCustomShader.shaderProgram, "spotLight2");
	glUniform1f(spotLight2Loc, spotLight2);

	lightShader.useShaderProgram();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));


	depthMapShader.useShaderProgram();
	glm::mat4 lightSpaceTrMatrix = computeLightSpaceTrMatrix();
	glUniformMatrix4fv(glGetUniformLocation(depthMapShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(depthMapShader.shaderProgram, "lightSpaceTrMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceTrMatrix));

	glCheckError();

	skyboxShader.useShaderProgram();
	//skybox
	view = myCamera.getViewMatrix();

	glCheckError();

	glUniformMatrix4fv(glGetUniformLocation(skyboxShader.shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));

	glCheckError();

	projection = glm::perspective(glm::radians(45.0f), (float)retina_width / (float)retina_height, 0.1f, 1000.0f);
	glUniformMatrix4fv(glGetUniformLocation(skyboxShader.shaderProgram, "projection"), 1, GL_FALSE,
		glm::value_ptr(projection));

	

}

void initFBO() {
	//TODO - Create the FBO, the depth texture and attach the depth texture to the FBO
	// 
	//generate FBO ID
	glGenFramebuffers(1, &shadowMapFBO);

	//create depth texture for FBO
	glGenTextures(1, &depthMapTexture);
	glBindTexture(GL_TEXTURE_2D, depthMapTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	//attach depth texture to FBO
	glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMapTexture, 0);

	//nu le vrei active tot timpul
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void drawObjects(gps::Shader shader, bool depthPass) {
	
	shader.useShaderProgram();
	
	//model = glm::rotate(glm::mat4(1.0f), glm::radians(angleY), glm::vec3(0.0f, 1.0f, 0.0f));
	//glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

	// do not send the normal matrix if we are rendering in the depth map
	if (!depthPass) {
		normalMatrix = glm::mat3(glm::inverseTranspose(view * model));
		glUniformMatrix3fv(normalMatrixLoc, 1, GL_FALSE, glm::value_ptr(normalMatrix));
	}

	model = glm::mat4(1.0f);
	glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

	for (int i = 0; i < 13; i++) {
		benches[i].Draw(shader);
	}

	for (int i = 0; i < 5; i++) {
		rampe[i].Draw(shader);
	}

	ramps_fence.Draw(shader);

	//tree1.Draw(shader);
	//tree2.Draw(shader);
	fence.Draw(shader);
	//model = glm::translate(glm::mat4(1.0f), glm::vec3(66.0f, 0.0f, 123.0f));
	//glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
	flowers.Draw(shader);
	//model = glm::mat4(1.0f);
	//glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
	motel.Draw(shader);
	gas_station.Draw(shader);

	for (int i = 0; i < 8; i++) {
		flats[i].Draw(shader);
	}

	for (int i = 0; i < 13; i++) {
		stalpi[i].Draw(shader);
		bec[i].Draw(shader);
	}

	button1.Draw(shader);


	demo.Draw(shader);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-59.403f, 1.5695f, -147.77f)) * glm::rotate(glm::mat4(1.0f), glm::radians(angleY), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(59.403f, -1.5695f, 147.77f));
	//model = glm::rotate(glm::mat4(1.0f), glm::radians(angleY), glm::vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
	carousel.Draw(shader);

	model = glm::translate(glm::mat4(1.0f), myCar.getPosition()) * glm::rotate(glm::mat4(1.0f), glm::radians(carLeft), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(-myCar.getPosition().x, -myCar.getPosition().y, -myCar.getPosition().z));
	model *= glm::translate(glm::mat4(1.0f), glm::vec3(myCar.getPosition().x - carX, myCar.getPosition().y - carY, myCar.getPosition().z - carZ));
	glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
	car.Draw(shader);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-80.698f, 0.85195f, -121.11f)) * glm::rotate(glm::mat4(1.0f), glm::radians(rightGateAngle), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(80.698f, -0.85195f, 121.11f));
	glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
	gate1.Draw(shader);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(-88.373f, 0.84686f, -121.7f)) * glm::rotate(glm::mat4(1.0f), glm::radians(leftGateAngle), glm::vec3(0.0f, 1.0f, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(88.373f, -0.84686f, 121.7f));
	glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
	gate2.Draw(shader);

	model = glm::translate(glm::mat4(1.0f), glm::vec3(skateOffsetX, skateOffsetY, skateOffsetZ));
	glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
	skate.Draw(shader);
	model = glm::translate(glm::mat4(1.0f), glm::vec3(30.415 + skateOffsetX, 0.38503 + skateOffsetY, -81.451 + skateOffsetZ)) * glm::rotate(glm::mat4(1.0f), glm::radians(wheelsAngle), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(-30.415 - skateOffsetX, -0.38503 - skateOffsetY, 81.451 - skateOffsetZ)) * glm::translate(glm::mat4(1.0f), glm::vec3(skateOffsetX, skateOffsetY, skateOffsetZ));
	glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
	wheel1.Draw(shader);
	model = glm::translate(glm::mat4(1.0f), glm::vec3(30.415 + skateOffsetX, 0.38608 + skateOffsetY, -80.614 + skateOffsetZ)) * glm::rotate(glm::mat4(1.0f), glm::radians(wheelsAngle), glm::vec3(1.0f, 0.0f, 0.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(-30.415 - skateOffsetX, -0.38608 - skateOffsetY, 80.614 - skateOffsetZ)) * glm::translate(glm::mat4(1.0f), glm::vec3(skateOffsetX, skateOffsetY, skateOffsetZ));
	glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
	wheel2.Draw(shader);
	
	if (goUp) {
		skateOffsetZ += 0.01f;
		wheelsAngle += 0.5f;
	}
	else {
		skateOffsetZ -= 0.01f;
		wheelsAngle -= 0.5f;
	}
	
	if (skateOffsetZ >= 1.0f) {
		goUp = false;
	}

	if (skateOffsetZ <= -10.0f) {
		goUp = true;
	}

	if (makeItRain) {
		if (!started) {
			started = true;
			PlaySound(TEXT("rain.wav"), NULL, SND_ASYNC);
		}
		srand(time(0));

		for (int i = 0; i < 350; i++) {

			if (offsetY[i] <= -50.0f) {
				offsetX[i] = lowX + (float)(rand()) / (RAND_MAX / (highX - lowX));
				offsetZ[i] = lowZ + (float)(rand()) / (RAND_MAX / (highZ - lowZ));
				offsetY[i] = 26.0f;
			}

			model = glm::translate(glm::mat4(1.0f), glm::vec3(offsetX[i], offsetY[i], offsetZ[i]));
			glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

			offsetY[i]-= (float)rand() / RAND_MAX;
			rain[i].Draw(shader);
		}
	}


	glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f), glm::radians(butt2Angle), glm::vec3(0.8015f, 0.0f, 0.678f));
	model = rotateZ;
	glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
	button2.Draw(shader);
	

	model = glm::mat4(1.0f);
	glUniformMatrix4fv(glGetUniformLocation(shader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

}


//glm::vec3 target = glm::vec3(30.601f, 0.49772f, -81.018f);

void renderScene() {

	// depth maps creation pass
	//TODO - Send the light-space transformation matrix to the depth map creation shader and
	//		 render the scene in the depth map

	myCustomShader.useShaderProgram();
	glUniform1i(withFogLoc, withFog);
	glUniform1i(spotLoc, spot);

	depthMapShader.useShaderProgram();

	glUniformMatrix4fv(glGetUniformLocation(depthMapShader.shaderProgram, "lightSpaceTrMatrix"), 1, GL_FALSE, glm::value_ptr(computeLightSpaceTrMatrix()));

	glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
	glBindFramebuffer(GL_FRAMEBUFFER, shadowMapFBO);
	glClear(GL_DEPTH_BUFFER_BIT);

	
	drawObjects(depthMapShader, true);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	//render scene

	// render depth map on screen - toggled with the M key

	if (showDepthMap) {
		glViewport(0, 0, retina_width, retina_height);

		glClear(GL_COLOR_BUFFER_BIT);

		screenQuadShader.useShaderProgram();

		//bind the depth map
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, depthMapTexture);
		glUniform1i(glGetUniformLocation(screenQuadShader.shaderProgram, "depthMap"), 0);

		glDisable(GL_DEPTH_TEST);
		screenQuad.Draw(screenQuadShader);
		glEnable(GL_DEPTH_TEST);
	}
	else {

		// final scene rendering pass (with shadows)

		glViewport(0, 0, retina_width, retina_height);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		myCustomShader.useShaderProgram();

		view = myCamera.getViewMatrix();
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

		lightRotation = glm::rotate(glm::mat4(1.0f), glm::radians(lightAngle), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniform3fv(lightDirLoc, 1, glm::value_ptr(glm::inverseTranspose(glm::mat3(lightRotation)) * lightDir));

		//bind the shadow map
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, depthMapTexture);
		glUniform1i(glGetUniformLocation(myCustomShader.shaderProgram, "shadowMap"), 3);

		glUniformMatrix4fv(glGetUniformLocation(myCustomShader.shaderProgram, "lightSpaceTrMatrix"),
			1,
			GL_FALSE,
			glm::value_ptr(computeLightSpaceTrMatrix()));


		drawObjects(myCustomShader, false);

		//draw a white cube around the light

		lightShader.useShaderProgram();

		glUniformMatrix4fv(glGetUniformLocation(lightShader.shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniform3fv(glGetUniformLocation(lightShader.shaderProgram, "color"), 1, glm::value_ptr(sunColor));
		model = lightRotation;/*
		model = glm::translate(model, 1.0f * lightDir);
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));*/
		glUniformMatrix4fv(glGetUniformLocation(lightShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));

		sun.Draw(lightShader);
	}

	skyboxShader.useShaderProgram();
	mySkyBox.Draw(skyboxShader, view, projection);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);
	if (animate) {
		glfwSetCursorPosCallback(glWindow, NULL);
		if (first) {
			preAnimCamera = myCamera;
			myCamera = animCamera;
			currentPosition = animCamera.getPosition();
			nextPosition = glm::vec3(31.102f, 2.31463f, -85.542f);
			first = false;
		}
		myCamera.move1((1 - t) * currentPosition + t * nextPosition, 0.001f);

		if (t < 1) t += increment;
		else {
			if (!done1) {
				t = 0;
				myCamera.rotate(0, -90);
				currentPosition = myCamera.getPosition();
				nextPosition = glm::vec3(-63.923f, 2.31463f, -161.67f);
				myCamera.setTarget(glm::vec3(-2.3208, 2.31463f, -59.648f));
				increment = 0.001f;
				done1 = true;
			}
			else {
				if (!done2) {
					t = 0;
					myCamera.rotate(0, -90);
					currentPosition = myCamera.getPosition();
					nextPosition = glm::vec3(-164.63f, 2.31463f, -41.645f);
					myCamera.setTarget(glm::vec3(-48.39f, 2.31463f, -81.813f));
					increment = 0.001f;
					done2 = true;
				}
				else {
					animate = false;
					glfwSetCursorPosCallback(glWindow, mouse_callback);
				}

			}
			

		}

	}


}

void cleanup() {
	glDeleteTextures(1,& depthMapTexture);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDeleteFramebuffers(1, &shadowMapFBO);
	glfwDestroyWindow(glWindow);
	//close GL context and any other GLFW resources
	glfwTerminate();
}

int main(int argc, const char * argv[]) {

	if (!initOpenGLWindow()) {
		glfwTerminate();
		return 1;
	}

	initOpenGLState();
	initObjects();
	initShaders();
	initUniforms();
	initFBO();

	

	while (!glfwWindowShouldClose(glWindow)) {
		processMovement();
		renderScene();		

		glfwPollEvents();
		glfwSwapBuffers(glWindow);
	}

	cleanup();

	return 0;
}
