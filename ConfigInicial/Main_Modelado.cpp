//Previo 4
//González Jiménez Victor Yotecatl
//Fecha de entrega: 08 - 09 - 2026
//Número de cuenta: 313173743


#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>



// Shaders
#include "Shader.h"

void Inputs(GLFWwindow *window);
void dibujarCubo(
	GLint modelLoc,
	GLuint VAO,
	GLuint VAOlineas,
	GLint colorLineaLoc,
	float x, float y, float z,
	float sx, float sy, float sz
);


const GLint WIDTH = 800, HEIGHT = 600;

// Tamaño base de los bloques del dinosaurio
const float B = 0.22f;

float movX=0.0f;
float movY=0.0f;
float movZ=-5.0f;
float rot = 0.0f;
int main() {
	glfwInit();

	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, "Victor Yotecatl", nullptr, nullptr);

	int screenWidth, screenHeight;

	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	//Verificación de errores de creacion  ventana
	if (nullptr == window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();

		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

	//Verificación de errores de inicialización de glew

	if (GLEW_OK != glewInit()) {
		std::cout << "Failed to initialise GLEW" << std::endl;
		return EXIT_FAILURE;
	}


	// Define las dimensiones del viewport
	glViewport(0, 0, screenWidth, screenHeight);


	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	// enable alpha support
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	// Build and compile our shader program
	Shader ourShader("Shader/core.vs", "Shader/core.frag");


	float vertices[] = {

		// Frente
		-0.5f, -0.5f,  0.5f,   0.20f, 0.75f, 0.20f,
		 0.5f, -0.5f,  0.5f,   0.20f, 0.75f, 0.20f,
		 0.5f,  0.5f,  0.5f,   0.20f, 0.75f, 0.20f,
		 0.5f,  0.5f,  0.5f,   0.20f, 0.75f, 0.20f,
		-0.5f,  0.5f,  0.5f,   0.20f, 0.75f, 0.20f,
		-0.5f, -0.5f,  0.5f,   0.20f, 0.75f, 0.20f,

		// Atrás
		-0.5f, -0.5f, -0.5f,   0.20f, 0.75f, 0.20f,
		 0.5f, -0.5f, -0.5f,   0.20f, 0.75f, 0.20f,
		 0.5f,  0.5f, -0.5f,   0.20f, 0.75f, 0.20f,
		 0.5f,  0.5f, -0.5f,   0.20f, 0.75f, 0.20f,
		-0.5f,  0.5f, -0.5f,   0.20f, 0.75f, 0.20f,
		-0.5f, -0.5f, -0.5f,   0.20f, 0.75f, 0.20f,

		// Derecha
		 0.5f, -0.5f,  0.5f,   0.20f, 0.75f, 0.20f,
		 0.5f, -0.5f, -0.5f,   0.20f, 0.75f, 0.20f,
		 0.5f,  0.5f, -0.5f,   0.20f, 0.75f, 0.20f,
		 0.5f,  0.5f, -0.5f,   0.20f, 0.75f, 0.20f,
		 0.5f,  0.5f,  0.5f,   0.20f, 0.75f, 0.20f,
		 0.5f, -0.5f,  0.5f,   0.20f, 0.75f, 0.20f,

		 // Izquierda
		 -0.5f,  0.5f,  0.5f,   0.20f, 0.75f, 0.20f,
		 -0.5f,  0.5f, -0.5f,   0.20f, 0.75f, 0.20f,
		 -0.5f, -0.5f, -0.5f,   0.20f, 0.75f, 0.20f,
		 -0.5f, -0.5f, -0.5f,   0.20f, 0.75f, 0.20f,
		 -0.5f, -0.5f,  0.5f,   0.20f, 0.75f, 0.20f,
		 -0.5f,  0.5f,  0.5f,   0.20f, 0.75f, 0.20f,

		 // Abajo
		 -0.5f, -0.5f, -0.5f,   0.20f, 0.75f, 0.20f,
		  0.5f, -0.5f, -0.5f,   0.20f, 0.75f, 0.20f,
		  0.5f, -0.5f,  0.5f,   0.20f, 0.75f, 0.20f,
		  0.5f, -0.5f,  0.5f,   0.20f, 0.75f, 0.20f,
		 -0.5f, -0.5f,  0.5f,   0.20f, 0.75f, 0.20f,
		 -0.5f, -0.5f, -0.5f,   0.20f, 0.75f, 0.20f,

		 // Arriba
		 -0.5f,  0.5f, -0.5f,   0.20f, 0.75f, 0.20f,
		  0.5f,  0.5f, -0.5f,   0.20f, 0.75f, 0.20f,
		  0.5f,  0.5f,  0.5f,   0.20f, 0.75f, 0.20f,
		  0.5f,  0.5f,  0.5f,   0.20f, 0.75f, 0.20f,
		 -0.5f,  0.5f,  0.5f,   0.20f, 0.75f, 0.20f,
		 -0.5f,  0.5f, -0.5f,   0.20f, 0.75f, 0.20f
	};

	float verticesNaranja[] = {

		// Frente
		-0.5f, -0.5f,  0.5f,   1.00f, 0.55f, 0.10f,
		 0.5f, -0.5f,  0.5f,   1.00f, 0.55f, 0.10f,
		 0.5f,  0.5f,  0.5f,   1.00f, 0.55f, 0.10f,
		 0.5f,  0.5f,  0.5f,   1.00f, 0.55f, 0.10f,
		-0.5f,  0.5f,  0.5f,   1.00f, 0.55f, 0.10f,
		-0.5f, -0.5f,  0.5f,   1.00f, 0.55f, 0.10f,

		// Atrás
		-0.5f, -0.5f, -0.5f,   1.00f, 0.55f, 0.10f,
		 0.5f, -0.5f, -0.5f,   1.00f, 0.55f, 0.10f,
		 0.5f,  0.5f, -0.5f,   1.00f, 0.55f, 0.10f,
		 0.5f,  0.5f, -0.5f,   1.00f, 0.55f, 0.10f,
		-0.5f,  0.5f, -0.5f,   1.00f, 0.55f, 0.10f,
		-0.5f, -0.5f, -0.5f,   1.00f, 0.55f, 0.10f,

		// Derecha
		 0.5f, -0.5f,  0.5f,   1.00f, 0.55f, 0.10f,
		 0.5f, -0.5f, -0.5f,   1.00f, 0.55f, 0.10f,
		 0.5f,  0.5f, -0.5f,   1.00f, 0.55f, 0.10f,
		 0.5f,  0.5f, -0.5f,   1.00f, 0.55f, 0.10f,
		 0.5f,  0.5f,  0.5f,   1.00f, 0.55f, 0.10f,
		 0.5f, -0.5f,  0.5f,   1.00f, 0.55f, 0.10f,

		 // Izquierda
		 -0.5f,  0.5f,  0.5f,   1.00f, 0.55f, 0.10f,
		 -0.5f,  0.5f, -0.5f,   1.00f, 0.55f, 0.10f,
		 -0.5f, -0.5f, -0.5f,   1.00f, 0.55f, 0.10f,
		 -0.5f, -0.5f, -0.5f,   1.00f, 0.55f, 0.10f,
		 -0.5f, -0.5f,  0.5f,   1.00f, 0.55f, 0.10f,
		 -0.5f,  0.5f,  0.5f,   1.00f, 0.55f, 0.10f,

		 // Abajo
		 -0.5f, -0.5f, -0.5f,   1.00f, 0.55f, 0.10f,
		  0.5f, -0.5f, -0.5f,   1.00f, 0.55f, 0.10f,
		  0.5f, -0.5f,  0.5f,   1.00f, 0.55f, 0.10f,
		  0.5f, -0.5f,  0.5f,   1.00f, 0.55f, 0.10f,
		 -0.5f, -0.5f,  0.5f,   1.00f, 0.55f, 0.10f,
		 -0.5f, -0.5f, -0.5f,   1.00f, 0.55f, 0.10f,

		 // Arriba
		 -0.5f,  0.5f, -0.5f,   1.00f, 0.55f, 0.10f,
		  0.5f,  0.5f, -0.5f,   1.00f, 0.55f, 0.10f,
		  0.5f,  0.5f,  0.5f,   1.00f, 0.55f, 0.10f,
		  0.5f,  0.5f,  0.5f,   1.00f, 0.55f, 0.10f,
		 -0.5f,  0.5f,  0.5f,   1.00f, 0.55f, 0.10f,
		 -0.5f,  0.5f, -0.5f,   1.00f, 0.55f, 0.10f
	};

	float verticesLineas[] = {

		// Frente
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,

		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,


		// Atrás
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,

		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,

		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,


		// Uniones frente-atras
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f, -0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
	};



	GLuint VBO, VAO;
	GLuint VBOlineas, VAOlineas;
	GLuint VBOnaranja, VAOnaranja; 
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	// Enlazar  Vertex Array Object
	glBindVertexArray(VAO);

	//2.- Copiamos nuestros arreglo de vertices en un buffer de vertices para que OpenGL lo use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3.Copiamos nuestro arreglo de indices en  un elemento del buffer para que OpenGL lo use
	/*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	// 4. Despues colocamos las caracteristicas de los vertices

	//Posicion
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)0);
	glEnableVertexAttribArray(0);

	//Color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid *)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


	glBindVertexArray(0); // Unbind VAO (it's always a good thing to unbind any buffer/array to prevent strange bugs)

	// ==========================================
// VAO PARA CUBOS NARANJAS
// ==========================================

	GLuint VBOnaranja, VAOnaranja;

	glGenVertexArrays(1, &VAOnaranja);
	glGenBuffers(1, &VBOnaranja);

	glBindVertexArray(VAOnaranja);

	glBindBuffer(GL_ARRAY_BUFFER, VBOnaranja);
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(verticesNaranja),
		verticesNaranja,
		GL_STATIC_DRAW
	);

	// Posición
	glVertexAttribPointer(
		0, 3, GL_FLOAT, GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*)0
	);
	glEnableVertexAttribArray(0);

	// Color
	glVertexAttribPointer(
		1, 3, GL_FLOAT, GL_FALSE,
		6 * sizeof(GLfloat),
		(GLvoid*)(3 * sizeof(GLfloat))
	);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);


	// ==========================================
	// VAO PARA LAS ARISTAS DEL CUBO
	// ==========================================

	glGenVertexArrays(1, &VAOlineas);
	glGenBuffers(1, &VBOlineas);

	// ... lo que ya tienes

	// ==========================================
// VAO PARA LAS ARISTAS DEL CUBO
// ==========================================

	glGenVertexArrays(1, &VAOlineas);
	glGenBuffers(1, &VBOlineas);

	glBindVertexArray(VAOlineas);

	glBindBuffer(GL_ARRAY_BUFFER, VBOlineas);

	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(verticesLineas),
		verticesLineas,
		GL_STATIC_DRAW
	);

	// Posicion XYZ de las lineas
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(GLfloat),
		(GLvoid*)0
	);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);


	// ==========================================
	// PROYECCION
	// ==========================================

	glm::mat4 projection = glm::mat4(1);

	projection = glm::perspective(
		glm::radians(45.0f),
		(GLfloat)screenWidth / (GLfloat)screenHeight,
		0.1f,
		100.0f
	);
	

	while (!glfwWindowShouldClose(window))
	{
		
		Inputs(window);
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClearColor(0.55f, 0.55f, 0.55f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);


		// Draw our first triangle
		ourShader.Use();
		glm::mat4 model=glm::mat4(1);
		glm::mat4 view=glm::mat4(1);
	

		view = glm::translate(view, glm::vec3(movX,movY, movZ));
		view = glm::rotate(view, glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f));

		GLint modelLoc = glGetUniformLocation(ourShader.Program, "model");
		GLint colorLineaLoc =
			glGetUniformLocation(ourShader.Program, "usarColorLinea");
		GLint viewLoc = glGetUniformLocation(ourShader.Program, "view");
		GLint projecLoc = glGetUniformLocation(ourShader.Program, "projection");


		glUniformMatrix4fv(projecLoc, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
	

		glBindVertexArray(VAO);

		// Posición general de la pata derecha
		float pataDerX = 0.0f;
		float pataDerY = -1.0f;
		float pataDerZ = 0.0f;

		// Pata derecha
		// Cubo extra arriba
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX, pataDerY + B, pataDerZ,
			B, B, B);

		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX, pataDerY, pataDerZ,
			B, B, B);

		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX, pataDerY - B, pataDerZ,
			B, B, B);

		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX, pataDerY - 2 * B, pataDerZ,
			B, B, B);

		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX, pataDerY - 3 * B, pataDerZ,
			B, B, B);

		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX + B, pataDerY - 3 * B, pataDerZ,
			B, B, B);

		// ==========================================
// VOLUMEN FRENTE Y ATRÁS - CUBOS 2 Y 3
// ==========================================

// ==========================================
// CUBOS LATERALES - NIVELES 2 Y 3
// ==========================================

// Lateral derecho - nivel del cubo 2
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX + B, pataDerY, pataDerZ,
			B, B, B);

		// Lateral izquierdo - nivel del cubo 2
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX - B, pataDerY, pataDerZ,
			B, B, B);


		// Lateral derecho - nivel del cubo 3
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX + B, pataDerY - B, pataDerZ,
			B, B, B);

		// Lateral izquierdo - nivel del cubo 3
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX - B, pataDerY - B, pataDerZ,
			B, B, B);
		//Cubo superior trasero
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX - B, pataDerY + B, pataDerZ,
			B, B, B);
		//Cubo inferior trasero 

		//dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
		//	pataDerX, pataDerY - 3 * B, pataDerZ - B,
		//	B, B, B);

		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX - 1 * B, pataDerY - 3 * B, pataDerZ ,
			B, B, B);

		// Medio cubo de la pierna
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX - B, pataDerY - 2.25f * B, pataDerZ,
			B, B / 2.0f, B);

		// ==========================================
		// CAPA INTERMEDIA - GROSOR DE 1/4 DE CUBO
		// Duplica exactamente los 13 elementos
		// ==========================================

		float interZ = pataDerZ - 0.625f * B;


		// 1. Cubo superior
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX, pataDerY + B, interZ,
			B, B, B / 4.0f);


		// 2. Cubo principal
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX, pataDerY, interZ,
			B, B, B / 4.0f);


		// 3. Cubo debajo
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX, pataDerY - B, interZ,
			B, B, B / 4.0f);


		// 4. Cubo inferior de la columna
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX, pataDerY - 2 * B, interZ,
			B, B, B / 4.0f);


		// 5. Cubo inferior central
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX, pataDerY - 3 * B, interZ,
			B, B, B / 4.0f);


		// 6. Cubo inferior derecho
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX + B, pataDerY - 3 * B, interZ,
			B, B, B / 4.0f);


		// 7. Lateral derecho - nivel cubo 2
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX + B, pataDerY, interZ,
			B, B, B / 4.0f);


		// 8. Lateral izquierdo - nivel cubo 2
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX - B, pataDerY, interZ,
			B, B, B / 4.0f);


		// 9. Lateral derecho - nivel cubo 3
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX + B, pataDerY - B, interZ,
			B, B, B / 4.0f);


		// 10. Lateral izquierdo - nivel cubo 3
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX - B, pataDerY - B, interZ,
			B, B, B / 4.0f);


		// 11. Cubo superior izquierdo
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX - B, pataDerY + B, interZ,
			B, B, B / 4.0f);


		// 12. Cubo inferior izquierdo
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX - B, pataDerY - 3 * B, interZ,
			B, B, B / 4.0f);


		// 13. Medio cubo de la pierna
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX - B, pataDerY - 2.25f * B, interZ,
			B, B / 2.0f, B / 4.0f);

		// ==========================================
		// SEGUNDA PARED - 13 ELEMENTOS
		// ==========================================

		float pared2Z = pataDerZ - 1.25f * B;


		// 1. Cubo superior
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX, pataDerY + B, pared2Z,
			B, B, B);


		// 2. Cubo principal
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX, pataDerY, pared2Z,
			B, B, B);


		// 3. Cubo debajo
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX, pataDerY - B, pared2Z,
			B, B, B);


		// 4. Cubo inferior de la columna
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX, pataDerY - 2 * B, pared2Z,
			B, B, B);


		// 5. Cubo inferior central
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX, pataDerY - 3 * B, pared2Z,
			B, B, B);


		// 6. Cubo inferior derecho
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX + B, pataDerY - 3 * B, pared2Z,
			B, B, B);


		// 7. Lateral derecho - nivel cubo 2
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX + B, pataDerY, pared2Z,
			B, B, B);


		// 8. Lateral izquierdo - nivel cubo 2
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX - B, pataDerY, pared2Z,
			B, B, B);


		// 9. Lateral derecho - nivel cubo 3
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX + B, pataDerY - B, pared2Z,
			B, B, B);


		// 10. Lateral izquierdo - nivel cubo 3
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX - B, pataDerY - B, pared2Z,
			B, B, B);


		// 11. Cubo superior izquierdo
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX - B, pataDerY + B, pared2Z,
			B, B, B);


		// 12. Cubo inferior izquierdo
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX - B, pataDerY - 3 * B, pared2Z,
			B, B, B);


		// 13. Medio cubo de la pierna
		dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
			pataDerX - B, pataDerY - 2.25f * B, pared2Z,
			B, B / 2.0f, B);


		glBindVertexArray(0);

		// Swap the screen buffers
		glfwSwapBuffers(window);
	
	}
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAOlineas);
	glDeleteBuffers(1, &VBOlineas);


	glfwTerminate();
	return EXIT_SUCCESS;
 }

 void Inputs(GLFWwindow *window) {
	 if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
		 glfwSetWindowShouldClose(window, true);
	 if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		 movX += 0.03f;
	 if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		 movX -= 0.03f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		 movY += 0.03f;
	 if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		 movY -= 0.03f;
	 if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		 movZ -= 0.03f;
	 if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		 movZ += 0.03f;
	 if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		 rot += 0.1f;
	 if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		 rot -= 0.1f;
 }
 void dibujarCubo(
	 GLint modelLoc,
	 GLuint VAOnaranja,
	 GLuint VAOlineas,
	 GLint colorLineaLoc,
	 float x, float y, float z,
	 float sx, float sy, float sz
 )
 {
	 glm::mat4 model = glm::mat4(1.0f);

	 model = glm::translate(model, glm::vec3(x, y, z));
	 model = glm::scale(model, glm::vec3(sx, sy, sz));

	 glUniformMatrix4fv(
		 modelLoc,
		 1,
		 GL_FALSE,
		 glm::value_ptr(model)
	 );


	 // =========================
	 // CARAS
	 // =========================

	 glUniform1i(colorLineaLoc, GL_FALSE);

	 glBindVertexArray(VAO);

	 glDrawArrays(
		 GL_TRIANGLES,
		 0,
		 36
	 );


	 // =========================
	 // ARISTAS
	 // =========================

	 glUniform1i(colorLineaLoc, GL_TRUE);

	 glBindVertexArray(VAOlineas);

	 glLineWidth(2.0f);

	 glDrawArrays(
		 GL_LINES,
		 0,
		 24
	 );


	 glBindVertexArray(0);

	 glUniform1i(colorLineaLoc, GL_FALSE);
 }
