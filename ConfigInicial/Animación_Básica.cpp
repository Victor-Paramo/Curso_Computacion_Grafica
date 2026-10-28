//Práctica 10 
//González Jiménez Victor Yotecatl
//Fecha de entrega: 25 - 10 - 2026
//Número de cuenta: 31317374 - 3

#include <iostream>
#include <cmath>

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
void MouseCallback(GLFWwindow* window, double xPos, double yPos);
void DoMovement();
void Animation();

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;
int SCREEN_WIDTH, SCREEN_HEIGHT;

// Camera
Camera  camera(glm::vec3(0.0f, 0.0f, 3.0f));
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
bool keys[1024];
bool firstMouse = true;
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

bool AnimBall = false;
bool pelotaSubiendo = true;         // Conservada del previo; sin uso en trayectoria circular
GLfloat desplazamientoPelota = 0.0f;
// La pelota avanza en sentido opuesto sobre el Primer circulo.
GLfloat posicionXPelota = 0.0f;
GLfloat posicionZPelota = 0.0f;
// Centro de ball.obj: X=-0.0009, Y=0.31245, Z=0.4702.
const GLfloat centroPelotaX = -0.0009f;
const GLfloat centroPelotaY = 0.31245f;
const GLfloat centroPelotaZ = 0.4702f;

// PRACTICA 10: Primer circulo en XZ, con saltos senoidales y tramos sobre el suelo.
// Gira sobre Y para orientar la cabeza y se inclina solo unos grados.
GLfloat tiempoPerro = 0.0f;
GLfloat posicionXPerro = 0.0f;
GLfloat posicionZPerro = 0.0f;
GLfloat alturaSenoidalPerro = 0.0f;
GLfloat inclinacionPerro = 0.0f;
GLfloat anguloPerro = 0.0f;
const GLfloat radioPrimerCirculo = 1.5f; // Radio unico para perro y pelota
const GLfloat amplitudSenoidalPerro = 1.20f; // Altura maxima del salto sobre el piso
const GLfloat ondasPorVueltaPerro = 2.0f; // Dos saltos por vuelta, separados por tramos en el suelo
const GLfloat velocidadAngularPerro = 0.90f; // radianes por segundo
// Ajusta solo este angulo si la cabeza no mira hacia donde avanza.
const GLfloat orientacionInicialPerro = 0.0f; // probar 90, -90 o 180


// Deltatime
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

int main()
{
	// Init GLFW
	glfwInit();

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
	// glfwSetCursorPosCallback(window, MouseCallback); // Control del mouse desactivado

	// GLFW Options
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
	Model Dog((char*)"Models/RedDog.obj");
	Model Piso((char*)"Models/piso.obj");
	Model Ball((char*)"Models/ball.obj");



	// First, set the container's VAO (and VBO) factor
	GLuint VBO, VAO;
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
		// Primer circulo + saltos, con intervalos en el piso. El suelo permanece fijo.
		model = glm::translate(model, glm::vec3(posicionXPerro, alturaSenoidalPerro, posicionZPerro));
		// La cabeza apunta hacia la tangente horizontal del circulo.
		model = glm::rotate(model, anguloPerro + glm::radians(orientacionInicialPerro),
			glm::vec3(0.0f, 1.0f, 0.0f));
		// Pequena inclinacion sobre su eje local X para acompanar la subida/bajada.
		// Se limita a 10 grados: nunca se voltea ni queda patas arriba.
		model = glm::rotate(model, inclinacionPerro, glm::vec3(1.0f, 0.0f, 0.0f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 0);
		Dog.Draw(lightingShader);

		model = glm::mat4(1);
		glEnable(GL_BLEND);//Avtiva la funcionalidad para trabajar el canal alfa
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glUniform1i(glGetUniformLocation(lightingShader.Program, "transparency"), 1);
		// Mueve el CENTRO de la pelota sobre el Primer circulo.
		// Se compensa la posicion con que fue exportada en ball.obj.
		// Correccion lateral CONTINUA: cambia suavemente de signo entre encuentros.
		// En el primer encuentro (fase PI/2) es -0.35; en el segundo
		// (fase 3PI/2) es +0.35. Evita cambios bruscos en la trayectoria.
		const GLfloat faseEncuentros = velocidadAngularPerro * tiempoPerro;
		const GLfloat amplitudAjusteLateral = 0.35f;
		const GLfloat ajusteLateralPelota = -amplitudAjusteLateral * sin(faseEncuentros);
		const GLfloat ajustePelotaX = ajusteLateralPelota * cos(anguloPerro);
		const GLfloat ajustePelotaZ = -ajusteLateralPelota * sin(anguloPerro);
		model = glm::translate(model, glm::vec3(posicionXPelota + ajustePelotaX,
			desplazamientoPelota, posicionZPelota + ajustePelotaZ));
		model = glm::translate(model, glm::vec3(-centroPelotaX, -centroPelotaY, -centroPelotaZ));
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

	// Movimiento de camara: lento normalmente, mas rapido al mantener Shift.
	const GLfloat factorVelocidad = 1.00f;
	const GLfloat deltaMovimiento = deltaTime * factorVelocidad;
	if (keys[GLFW_KEY_W])
	{
		camera.ProcessKeyboard(FORWARD, deltaMovimiento);
	}
	if (keys[GLFW_KEY_S])
	{
		camera.ProcessKeyboard(BACKWARD, deltaMovimiento);
	}
	if (keys[GLFW_KEY_A])
	{
		camera.ProcessKeyboard(LEFT, deltaMovimiento);
	}
	if (keys[GLFW_KEY_D])
	{
		camera.ProcessKeyboard(RIGHT, deltaMovimiento);
	}

	// Las flechas giran la camara suavemente, sin moverla.
	const GLfloat velocidadGiro = 180.0f * deltaTime;
	if (keys[GLFW_KEY_LEFT])
	{
		camera.ProcessMouseMovement(-velocidadGiro, 0.0f);
	}
	if (keys[GLFW_KEY_RIGHT])
	{
		camera.ProcessMouseMovement(velocidadGiro, 0.0f);
	}
	if (keys[GLFW_KEY_UP])
	{
		camera.ProcessMouseMovement(0.0f, velocidadGiro);
	}
	if (keys[GLFW_KEY_DOWN])
	{
		camera.ProcessMouseMovement(0.0f, -velocidadGiro);
	}

	// Velocidad fija y suave para mover la fuente de luz (unidades/segundo).
	const GLfloat velocidadLuz = 0.30f * deltaTime;

	if (keys[GLFW_KEY_T])
	{
		pointLightPositions[0].x += velocidadLuz;
	}
	if (keys[GLFW_KEY_G])
	{
		pointLightPositions[0].x -= velocidadLuz;
	}

	if (keys[GLFW_KEY_Y])
	{
		pointLightPositions[0].y += velocidadLuz;
	}

	if (keys[GLFW_KEY_H])
	{
		pointLightPositions[0].y -= velocidadLuz;
	}
	if (keys[GLFW_KEY_U])
	{
		pointLightPositions[0].z -= velocidadLuz;
	}
	if (keys[GLFW_KEY_J])
	{
		pointLightPositions[0].z += velocidadLuz;
	}

}

// Is called whenever a key is pressed/released via GLFW velocidadLuz 
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (GLFW_KEY_ESCAPE == key && GLFW_PRESS == action)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			keys[key] = false;
		}
	}

	if (keys[GLFW_KEY_SPACE])
	{
		active = !active;
		if (active)
		{
			Light1 = glm::vec3(1.0f, 1.0f, 0.0f);

		}
		else
		{
			Light1 = glm::vec3(0);//Cuado es solo un valor en los 3 vectores pueden dejar solo una componente
		}
	}
	// La tecla N cambia el estado solo una vez por pulsacion.
	if (key == GLFW_KEY_N && action == GLFW_PRESS)
	{
		AnimBall = !AnimBall;
	}
}
void Animation() {
	// Trayectoria de un circulo horizontal sobre el piso (plano XZ).
	tiempoPerro += deltaTime;
	const GLfloat fase = velocidadAngularPerro * tiempoPerro;
	// Ambos modelos se calculan respecto a la misma circunferencia en XZ.
	const auto puntoPrimerCirculo = [](GLfloat angulo) -> glm::vec2 {
		return glm::vec2(radioPrimerCirculo * cos(angulo),
			radioPrimerCirculo * sin(angulo));
		};
	const glm::vec2 puntoPerro = puntoPrimerCirculo(fase);
	posicionXPerro = puntoPerro.x;
	posicionZPerro = puntoPerro.y;

	// Tangente a la trayectoria: derivadas de X y Z respecto al tiempo.
	const GLfloat tangenteX = -sin(fase);
	const GLfloat tangenteZ = cos(fase);
	// Orientacion suponiendo que el frente original del OBJ apunta a +Z.
	anguloPerro = atan2(tangenteX, tangenteZ);

	// Cada ciclo contiene un tramo sobre el piso, un salto y otro tramo sobre el piso.
	// Conservamos dos ciclos por vuelta del Primer circulo.
	const GLfloat pi = 3.14159265358979323846f;
	const GLfloat dosPi = 2.0f * pi;
	const GLfloat ciclo = fmod(ondasPorVueltaPerro * fase, dosPi);
	const GLfloat inicioSalto = 0.25f * dosPi;
	const GLfloat finSalto = 0.75f * dosPi;

	alturaSenoidalPerro = 0.0f;
	GLfloat pendiente = 0.0f;
	if (ciclo >= inicioSalto && ciclo <= finSalto)
	{
		// Una cresta suave que inicia y termina en el suelo sin atravesarlo.
		const GLfloat progreso = (ciclo - inicioSalto) / (finSalto - inicioSalto);
		const GLfloat seno = sin(pi * progreso);
		alturaSenoidalPerro = amplitudSenoidalPerro * seno * seno;

		// Derivada dy/ds, siendo s la distancia recorrida sobre el circulo.
		// La derivada es cero tanto al despegar como al aterrizar.
		pendiente = (amplitudSenoidalPerro * pi * sin(2.0f * pi * progreso)
			* ondasPorVueltaPerro) /
			((finSalto - inicioSalto) * radioPrimerCirculo);
	}

	// Inclinacion discreta a favor de la tangente: nunca patas arriba.
	inclinacionPerro = glm::clamp(atan(pendiente),
		glm::radians(-10.0f), glm::radians(10.0f));

	// El perro gira a favor del angulo +fase; la pelota va en -fase.
	// Desfase PI: coinciden horizontalmente SOLO en fase PI/2 y 3PI/2,
	// justamente las cimas de los dos saltos del perro.
	const GLfloat fasePelota = pi - fase;
	const glm::vec2 puntoPelota = puntoPrimerCirculo(fasePelota);
	posicionXPelota = puntoPelota.x;
	posicionZPelota = puntoPelota.y;

	// Dos periodos verticales por vuelta. La altura de la pelota es
	// su centro en coordenadas del mundo (no la altura de su OBJ).
	// En ambos encuentros el centro esta a Y=2.0, por encima del perro.
	const GLfloat alturaMinimaCentroPelota = 2.00f;
	const GLfloat amplitudVerticalPelota = 0.35f;
	desplazamientoPelota = alturaMinimaCentroPelota +
		amplitudVerticalPelota * (1.0f + cos(2.0f * fasePelota));

}

void MouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	GLfloat xOffset = xPos - lastX;
	GLfloat yOffset = lastY - yPos;  // Reversed since y-coordinates go from bottom to left

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}