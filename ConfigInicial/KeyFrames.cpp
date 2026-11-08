//Práctica 12
//González Jiménez Victor Yotecatl
//Fecha de entrega: 08 - 11 - 2026
//Número de cuenta: 31317374 - 3

#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <string>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// Other Libs
#include "stb_image.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

//Load Models
#include "SOIL2/SOIL2.h"


// Other includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"


// Function prototypes
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void DoMovement();
void Animation();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
bool keys[1024];
// Light attributes
glm::vec3 lightPos(0.0f, 0.0f, 0.0f);
bool active;

// Positions of the point lights
glm::vec3 pointLightPositions[] = {
	glm::vec3(0.0f,2.0f, 0.0f),
	glm::vec3(0.0f,0.0f, 0.0f),
	glm::vec3(0.0f,0.0f,  0.0f),
	glm::vec3(0.0f,0.0f, 0.0f)
};

float vertices[] = {
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	   -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	   -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};


glm::vec3 Light1 = glm::vec3(0);
//Anim
float rotBall = 0.0f;
float rotDog = 0.0f;
int dogAnim = 0;
float FLeftLeg = 0.0f;
float FRightLeg = 0.0f;
float BLeftLeg = 0.0f;
float BRightLeg = 0.0f;
float head = 0.0f;
float tail = 0.0f;
float sitPitch = 0.0f;
float bodyRoll = 0.0f;



//KeyFrames
float dogPosX, dogPosY, dogPosZ;

#define MAX_FRAMES 20
int i_max_steps = 65; // Duracion de cada tramo en pasos a 60 Hz
float i_curr_steps = 0.0f;
typedef struct _frame {
	float rotDog, rotDogInc;
	float dogPosX, dogPosY, dogPosZ;
	float incX, incY, incZ;
	float head, headInc;
	float tail, tailInc;
	float FLeftLeg, FLeftLegInc;
	float FRightLeg, FRightLegInc;
	float BLeftLeg, BLeftLegInc;
	float BRightLeg, BRightLegInc;
	float sitPitch, sitPitchInc;
	float bodyRoll, bodyRollInc;
} FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;
bool play = false;
int playIndex = 0;
// Mantener el nombre original en la primera ranura conserva la animacion existente.
const char* ANIMATION_FILES[3] = {
	"animacion_perro.txt",
	"animacion_perro_2.txt",
	"animacion_perro_3.txt"
};

void saveFrame(void)
{
	if (FrameIndex >= MAX_FRAMES) return;

	KeyFrame[FrameIndex].dogPosX = dogPosX;
	KeyFrame[FrameIndex].dogPosY = dogPosY;
	KeyFrame[FrameIndex].dogPosZ = dogPosZ;
	KeyFrame[FrameIndex].rotDog = rotDog;
	KeyFrame[FrameIndex].head = head;
	KeyFrame[FrameIndex].tail = tail;
	KeyFrame[FrameIndex].FLeftLeg = FLeftLeg;
	KeyFrame[FrameIndex].FRightLeg = FRightLeg;
	KeyFrame[FrameIndex].BLeftLeg = BLeftLeg;
	KeyFrame[FrameIndex].BRightLeg = BRightLeg;
	KeyFrame[FrameIndex].sitPitch = sitPitch;
	KeyFrame[FrameIndex].bodyRoll = bodyRoll;

	printf("frameindex %d\n", FrameIndex);
	FrameIndex++;
}

void resetElements(void)
{
	if (FrameIndex == 0) return;

	dogPosX = KeyFrame[0].dogPosX;
	dogPosY = KeyFrame[0].dogPosY;
	dogPosZ = KeyFrame[0].dogPosZ;
	rotDog = KeyFrame[0].rotDog;
	head = KeyFrame[0].head;
	tail = KeyFrame[0].tail;
	FLeftLeg = KeyFrame[0].FLeftLeg;
	FRightLeg = KeyFrame[0].FRightLeg;
	BLeftLeg = KeyFrame[0].BLeftLeg;
	BRightLeg = KeyFrame[0].BRightLeg;
	sitPitch = KeyFrame[0].sitPitch;
	bodyRoll = KeyFrame[0].bodyRoll;
}

void interpolation(void)
{
	if (playIndex + 1 >= FrameIndex) return;

	FRAME& current = KeyFrame[playIndex];
	const FRAME& next = KeyFrame[playIndex + 1];
	const float steps = static_cast<float>(i_max_steps);

	current.incX = (next.dogPosX - current.dogPosX) / steps;
	current.incY = (next.dogPosY - current.dogPosY) / steps;
	current.incZ = (next.dogPosZ - current.dogPosZ) / steps;
	current.rotDogInc = (next.rotDog - current.rotDog) / steps;
	current.headInc = (next.head - current.head) / steps;
	current.tailInc = (next.tail - current.tail) / steps;
	current.FLeftLegInc = (next.FLeftLeg - current.FLeftLeg) / steps;
	current.FRightLegInc = (next.FRightLeg - current.FRightLeg) / steps;
	current.BLeftLegInc = (next.BLeftLeg - current.BLeftLeg) / steps;
	current.BRightLegInc = (next.BRightLeg - current.BRightLeg) / steps;
	current.sitPitchInc = (next.sitPitch - current.sitPitch) / steps;
	current.bodyRollInc = (next.bodyRoll - current.bodyRoll) / steps;
}

// Guardado y carga de los KeyFrames grabados.
bool saveAnimationToFile(int slot)
{
	if (slot < 0 || slot >= 3) return false;
	const char* filename = ANIMATION_FILES[slot];
	if (FrameIndex == 0)
	{
		printf("No hay KeyFrames para guardar\n");
		return false;
	}

	std::ofstream file(filename);
	if (!file)
	{
		printf("No se pudo abrir el archivo para guardar: %s\n", filename);
		return false;
	}

	file << "DOG_KEYFRAMES_V2 " << FrameIndex << ' ' << i_max_steps << '\n';
	file << std::setprecision(9);
	for (int i = 0; i < FrameIndex; ++i)
	{
		const FRAME& f = KeyFrame[i];
		file << f.dogPosX << ' ' << f.dogPosY << ' ' << f.dogPosZ << ' '
			<< f.rotDog << ' ' << f.head << ' ' << f.tail << ' '
			<< f.FLeftLeg << ' ' << f.FRightLeg << ' '
			<< f.BLeftLeg << ' ' << f.BRightLeg << ' '
			<< f.sitPitch << ' ' << f.bodyRoll << '\n';
	}

	file.flush();
	if (!file)
	{
		printf("Error al escribir la animacion\n");
		return false;
	}

	printf("Guardados %d KeyFrames en %s\n", FrameIndex, filename);
	return true;
}

bool loadAnimationFromFile(int slot, bool silentIfMissing = false)
{
	if (slot < 0 || slot >= 3) return false;
	const char* filename = ANIMATION_FILES[slot];
	std::ifstream file(filename);
	if (!file)
	{
		if (!silentIfMissing) printf("No se encontro %s\n", filename);
		return false;
	}

	std::string version;
	int count = 0;
	int steps = 0;
	if (!(file >> version >> count >> steps) ||
		(version != "DOG_KEYFRAMES_V1" && version != "DOG_KEYFRAMES_V2") ||
		count < 1 || count > MAX_FRAMES || steps < 1 || steps > 100000)
	{
		printf("Formato de animacion no valido\n");
		return false;
	}

	FRAME loaded[MAX_FRAMES] = {};
	for (int i = 0; i < count; ++i)
	{
		FRAME& f = loaded[i];
		if (!(file >> f.dogPosX >> f.dogPosY >> f.dogPosZ
			>> f.rotDog >> f.head >> f.tail
			>> f.FLeftLeg >> f.FRightLeg
			>> f.BLeftLeg >> f.BRightLeg >> f.sitPitch))
		{
			printf("Archivo incompleto o danado\n");
			return false;
		}
		// Las animaciones antiguas no contienen el giro lateral.
		if (version == "DOG_KEYFRAMES_V2" && !(file >> f.bodyRoll))
		{
			printf("Archivo incompleto o danado\n");
			return false;
		}

		const float values[] = {
			f.dogPosX, f.dogPosY, f.dogPosZ, f.rotDog, f.head, f.tail,
			f.FLeftLeg, f.FRightLeg, f.BLeftLeg, f.BRightLeg, f.sitPitch, f.bodyRoll
		};
		for (float value : values)
		{
			if (!std::isfinite(value))
			{
				printf("Archivo de animacion contiene valores invalidos\n");
				return false;
			}
		}
	}

	play = false;
	playIndex = 0;
	i_curr_steps = 0.0f;
	FrameIndex = count;
	i_max_steps = steps;
	for (int i = 0; i < count; ++i) KeyFrame[i] = loaded[i];
	resetElements();
	printf("Cargados %d KeyFrames desde %s\n", FrameIndex, filename);
	return true;
}

// Deltatime
GLfloat deltaTime = 0.0f;	// Time between current frame and last frame
GLfloat lastFrame = 0.0f;  	// Time of last frame

int main()
{
	// Init GLFW
	glfwInit();
	// Set all the required options for GLFW
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);*/

	// Create a GLFWwindow object that we can use for GLFW's functions
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Victor Yotecatl", nullptr, nullptr);

	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glfwGetFramebufferSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);

	// Set the required callback functions
	glfwSetKeyCallback(window, KeyCallback);


	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return EXIT_FAILURE;
	}

	// Define the viewport dimensions
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);



	Shader lightingShader("Shader/lighting.vs", "Shader/lighting.frag");
	Shader lampShader("Shader/lamp.vs", "Shader/lamp.frag");


	//models
	Model DogBody((char*)"Models/DogBody.obj");
	Model HeadDog((char*)"Models/HeadDog.obj");
	Model DogTail((char*)"Models/TailDog.obj");
	Model F_RightLeg((char*)"Models/F_RightLegDog.obj");
	Model F_LeftLeg((char*)"Models/F_LeftLegDog.obj");
	Model B_RightLeg((char*)"Models/B_RightLegDog.obj");
	Model B_LeftLeg((char*)"Models/B_LeftLegDog.obj");
	Model Piso((char*)"Models/piso.obj");
	Model Ball((char*)"Models/ball.obj");

	// La postura inicial se conserva; las animaciones se cargan con O, P o Q.


	// First, set the container's VAO (and VBO)
	GLuint VBO, VAO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);


	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	// normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Set texture units
	lightingShader.Use();
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.difuse"), 0);
	glUniform1i(glGetUniformLocation(lightingShader.Program, "Material.specular"), 1);


	glm::mat4 projection = glm::perspective(camera.GetZoom(), (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.1f, 100.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{

		// Calculate deltatime of current frame
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		DoMovement();
		Animation();

		// Clear the colorbuffer
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// OpenGL options
		glEnable(GL_DEPTH_TEST);


		glm::mat4 modelTemp = glm::mat4(1.0f); //Temp



		// Use cooresponding shader when setting uniforms/drawing objects
		lightingShader.Use();

		glUniform1i(glGetUniformLocation(lightingShader.Program, "diffuse"), 0);
		//glUniform1i(glGetUniformLocation(lightingShader.Program, "specular"),1);

		GLint viewPosLoc = glGetUniformLocation(lightingShader.Program, "viewPos");
		glUniform3f(viewPosLoc, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);


		// Directional light
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.ambient"), 0.6f, 0.6f, 0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.diffuse"), 0.6f, 0.6f, 0.6f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "dirLight.specular"), 0.3f, 0.3f, 0.3f);


		// Point light 1
		glm::vec3 lightColor;
		lightColor.x = abs(sin(glfwGetTime() * Light1.x));
		lightColor.y = abs(sin(glfwGetTime() * Light1.y));
		lightColor.z = sin(glfwGetTime() * Light1.z);


		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].ambient"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].diffuse"), lightColor.x, lightColor.y, lightColor.z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "pointLights[0].specular"), 1.0f, 0.2f, 0.2f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].linear"), 0.045f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "pointLights[0].quadratic"), 0.075f);


		// SpotLight
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.position"), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.direction"), camera.GetFront().x, camera.GetFront().y, camera.GetFront().z);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.ambient"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.diffuse"), 0.2f, 0.2f, 0.8f);
		glUniform3f(glGetUniformLocation(lightingShader.Program, "spotLight.specular"), 0.0f, 0.0f, 0.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.constant"), 1.0f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.linear"), 0.3f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.quadratic"), 0.7f);
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.cutOff"), glm::cos(glm::radians(12.0f)));
		glUniform1f(glGetUniformLocation(lightingShader.Program, "spotLight.outerCutOff"), glm::cos(glm::radians(18.0f)));


		// Set material properties
		glUniform1f(glGetUniformLocation(lightingShader.Program, "material.shininess"), 5.0f);

		// Create camera transformations
		glm::mat4 view;
		view = camera.GetViewMatrix();

		// Get the uniform locations
		GLint modelLoc = glGetUniformLocation(lightingShader.Program, "model");
		GLint viewLoc = glGetUniformLocation(lightingShader.Program, "view");
		GLint projLoc = glGetUniformLocation(lightingShader.Program, "projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


		glm::mat4 model(1);



		//Carga de modelo 
		view = camera.GetViewMatrix();
		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Piso.Draw(lightingShader);

		model = glm::mat4(1);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		//Body
		modelTemp = glm::translate(model, glm::vec3(dogPosX, dogPosY, dogPosZ));
		modelTemp = glm::rotate(modelTemp, glm::radians(rotDog), glm::vec3(0.0f, 1.0f, 0.0f));
		// Inclinacion al sentarse: pivote cerca de las patas delanteras.
		modelTemp = glm::translate(modelTemp, glm::vec3(0.0f, -0.28f, 0.15f));
		modelTemp = glm::rotate(modelTemp, glm::radians(sitPitch), glm::vec3(1.0f, 0.0f, 0.0f));
		modelTemp = glm::translate(modelTemp, glm::vec3(0.0f, 0.28f, -0.15f));
		// Giro longitudinal del perro para quedar boca arriba.
		modelTemp = glm::rotate(modelTemp, glm::radians(bodyRoll), glm::vec3(0.0f, 0.0f, 1.0f));
		model = modelTemp;
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		DogBody.Draw(lightingShader);
		//Head
		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.0f, 0.093f, 0.208f));
		model = glm::rotate(model, glm::radians(head), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		HeadDog.Draw(lightingShader);
		//Tail 
		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.0f, 0.026f, -0.288f));
		model = glm::rotate(model, glm::radians(tail), glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		DogTail.Draw(lightingShader);
		//Front Left Leg
		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.112f, -0.044f, 0.074f));
		model = glm::rotate(model, glm::radians(FLeftLeg), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		F_LeftLeg.Draw(lightingShader);
		//Front Right Leg
		model = modelTemp;
		model = glm::translate(model, glm::vec3(-0.111f, -0.055f, 0.074f));
		model = glm::rotate(model, glm::radians(FRightLeg), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		F_RightLeg.Draw(lightingShader);
		//Back Left Leg
		model = modelTemp;
		model = glm::translate(model, glm::vec3(0.082f, -0.046, -0.218));
		model = glm::rotate(model, glm::radians(BLeftLeg), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		B_LeftLeg.Draw(lightingShader);
		//Back Right Leg
		model = modelTemp;
		model = glm::translate(model, glm::vec3(-0.083f, -0.057f, -0.231f));
		model = glm::rotate(model, glm::radians(BRightLeg), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		B_RightLeg.Draw(lightingShader);


		model = glm::mat4(1);
		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);
		model = glm::rotate(model, glm::radians(rotBall), glm::vec3(0.0f, 1.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		Ball.Draw(lightingShader);
		glDisable(GL_BLEND);  //Desactiva el canal alfa 
		glBindVertexArray(0);


		// Also draw the lamp object, again binding the appropriate shader
		lampShader.Use();
		// Get location objects for the matrices on the lamp shader (these could be different on a different shader)
		modelLoc = glGetUniformLocation(lampShader.Program, "model");
		viewLoc = glGetUniformLocation(lampShader.Program, "view");
		projLoc = glGetUniformLocation(lampShader.Program, "projection");

		// Set matrices
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		model = glm::mat4(1);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		// Draw the light object (using light's vertex attributes)

		model = glm::mat4(1);
		model = glm::translate(model, pointLightPositions[0]);
		model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glBindVertexArray(0);


		// Swap the screen buffers
		glfwSwapBuffers(window);
	}




	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();



	return 0;
}

// Moves/alters the camera positions based on user input
void DoMovement()
{
	//Dog Controls
	// Articulaciones independientes: 6/7, 8/9, Z/X, B/N, I/M.
	if (keys[GLFW_KEY_6]) FLeftLeg += 0.06f;
	if (keys[GLFW_KEY_7]) FLeftLeg -= 0.06f;
	if (keys[GLFW_KEY_8]) FRightLeg += 0.06f;
	if (keys[GLFW_KEY_9]) FRightLeg -= 0.06f;
	if (keys[GLFW_KEY_Z]) BLeftLeg += 0.06f;
	if (keys[GLFW_KEY_X]) BLeftLeg -= 0.06f;
	if (keys[GLFW_KEY_B]) BRightLeg += 0.06f;
	if (keys[GLFW_KEY_N]) BRightLeg -= 0.06f;
	if (keys[GLFW_KEY_I]) tail += 0.06f;
	if (keys[GLFW_KEY_M]) tail -= 0.06f;
	if (keys[GLFW_KEY_V]) sitPitch += 0.06f;
	if (keys[GLFW_KEY_F]) sitPitch -= 0.06f;
	// Giro lateral: 180 grados deja el vientre hacia arriba.
	if (keys[GLFW_KEY_COMMA]) bodyRoll -= 60.0f * deltaTime;
	if (keys[GLFW_KEY_PERIOD]) bodyRoll += 60.0f * deltaTime;
	if (keys[GLFW_KEY_4])
	{
		head += 0.06f;
	}

	if (keys[GLFW_KEY_5])
	{
		head -= 0.06f;
	}

	if (keys[GLFW_KEY_1])
	{
		rotDog -= 0.06f;
	}

	if (keys[GLFW_KEY_2])
	{

		rotDog += 0.06f;

	}


	if (keys[GLFW_KEY_H])
	{
		dogPosZ += 0.001f;
	}

	if (keys[GLFW_KEY_Y])
	{
		dogPosZ -= 0.001f;
	}

	if (keys[GLFW_KEY_G])
	{
		dogPosX -= 0.001f;
	}

	if (keys[GLFW_KEY_J])
	{
		dogPosX += 0.001f;
	}

	// Desplazamiento vertical del perro completo
	if (keys[GLFW_KEY_PAGE_UP])
	{
		dogPosY += 0.0004f;
	}

	if (keys[GLFW_KEY_PAGE_DOWN])
	{
		dogPosY -= 0.0004f;
	}

	// Camera controls
	if (keys[GLFW_KEY_W])
	{
		camera.ProcessKeyboard(FORWARD, 0.0002f);
	}

	if (keys[GLFW_KEY_S])
	{
		camera.ProcessKeyboard(BACKWARD, 0.0002f);
	}

	if (keys[GLFW_KEY_A])
	{
		camera.ProcessKeyboard(LEFT, 0.0002f);
	}

	if (keys[GLFW_KEY_D])
	{
		camera.ProcessKeyboard(RIGHT, 0.0002f);
	}

	// Camera orientation
	if (keys[GLFW_KEY_LEFT])
	{
		camera.ProcessMouseMovement(-0.125f, 0.0f);
	}

	if (keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessMouseMovement(0.125f, 0.0f);
	}

	if (keys[GLFW_KEY_UP])
	{
		camera.ProcessMouseMovement(0.0f, 0.125f);
	}

	if (keys[GLFW_KEY_DOWN])
	{
		camera.ProcessMouseMovement(0.0f, -0.125f);
	}

	if (keys[GLFW_KEY_T])
	{
		pointLightPositions[0].x += 0.001f;
	}
	if (keys[GLFW_KEY_F])
	{
		pointLightPositions[0].x -= 0.001f;
	}

	if (keys[GLFW_KEY_R])
	{
		pointLightPositions[0].y += 0.001f;
	}

	if (keys[GLFW_KEY_V])
	{
		pointLightPositions[0].y -= 0.001f;
	}
	if (keys[GLFW_KEY_U])
	{
		pointLightPositions[0].z -= 0.001f;
	}
	if (keys[GLFW_KEY_E])
	{
		pointLightPositions[0].z += 0.001f;
	}

}

// Is called whenever a key is pressed/released via GLFW
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS) keys[key] = true;
		else if (action == GLFW_RELEASE) keys[key] = false;
	}

	if (action != GLFW_PRESS) return;

	if (key == GLFW_KEY_K && !play) saveFrame();
	if (key == GLFW_KEY_F5 && !play) saveAnimationToFile(0);
	if (key == GLFW_KEY_F9 && !play) loadAnimationFromFile(0);

	// Shift + P/Q guardan las animaciones 2 y 3 sin iniciar su reproduccion.
	if ((mode & GLFW_MOD_SHIFT) && (key == GLFW_KEY_P || key == GLFW_KEY_Q))
	{
		if (!play) saveAnimationToFile(key == GLFW_KEY_P ? 1 : 2);
		return;
	}
	if (key == GLFW_KEY_C)
	{
		play = false;
		FrameIndex = 0;
		playIndex = 0;
		i_curr_steps = 0;
		printf("KeyFrames reiniciados\n");
	}
	if (key == GLFW_KEY_O || key == GLFW_KEY_P || key == GLFW_KEY_Q)
	{
		const int slot = (key == GLFW_KEY_O) ? 0 : ((key == GLFW_KEY_P) ? 1 : 2);
		if (loadAnimationFromFile(slot))
		{
			if (FrameIndex >= 2)
			{
				playIndex = 0;
				i_curr_steps = 0.0f;
				resetElements();
				interpolation();
				play = true;
			}
			else
			{
				printf("La animacion %d necesita al menos 2 KeyFrames\n", slot + 1);
			}
		}
	}

	if (key == GLFW_KEY_SPACE)
	{
		active = !active;
		Light1 = active ? glm::vec3(0.2f, 0.8f, 1.0f) : glm::vec3(0.0f);
	}
}

void Animation()
{
	if (!play) return;

	if (i_curr_steps >= static_cast<float>(i_max_steps))
	{
		playIndex++;
		if (playIndex > FrameIndex - 2)
		{
			printf("termina anim\n");
			playIndex = 0;
			play = false;
		}
		else
		{
			i_curr_steps = 0.0f;
			interpolation();
		}
	}
	else
	{
		// Avance proporcional al tiempo real; evita depender de los FPS.
		const float remaining = static_cast<float>(i_max_steps) - i_curr_steps;
		const float advance = glm::min(deltaTime * 60.0f, remaining);
		const FRAME& frame = KeyFrame[playIndex];

		dogPosX += frame.incX * advance;
		dogPosY += frame.incY * advance;
		dogPosZ += frame.incZ * advance;
		rotDog += frame.rotDogInc * advance;
		head += frame.headInc * advance;
		tail += frame.tailInc * advance;
		FLeftLeg += frame.FLeftLegInc * advance;
		FRightLeg += frame.FRightLegInc * advance;
		BLeftLeg += frame.BLeftLegInc * advance;
		BRightLeg += frame.BRightLegInc * advance;
		sitPitch += frame.sitPitchInc * advance;
		bodyRoll += frame.bodyRollInc * advance;
		i_curr_steps += advance;
	}
}
