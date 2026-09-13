//Previo 4
//González Jiménez Victor Yotecatl
//Fecha de entrega: 12 - 09 - 2026
//Número de cuenta: 313173743

#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"


// ==========================================
// FUNCIONES
// ==========================================

void Inputs(GLFWwindow* window);

void dibujarCubo(
    GLint modelLoc,
    GLuint VAO,
    GLuint VAOlineas,
    GLint colorLineaLoc,
    float x, float y, float z,
    float sx, float sy, float sz
);


// ==========================================
// VARIABLES GENERALES
// ==========================================

const GLint WIDTH = 800, HEIGHT = 600;

// Tamaño base de los bloques
const float B = 0.22f;

float movX = 0.0f;
float movY = 0.0f;
float movZ = -5.0f;
float rot = 0.0f;


// ==========================================
// MAIN
// ==========================================

int main()
{
    glfwInit();

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(
        WIDTH,
        HEIGHT,
        "Victor Yotecatl",
        nullptr,
        nullptr
    );

    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();

        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);

    int screenWidth, screenHeight;

    glfwGetFramebufferSize(
        window,
        &screenWidth,
        &screenHeight
    );


    // ==========================================
    // GLEW
    // ==========================================

    glewExperimental = GL_TRUE;

    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialise GLEW" << std::endl;
        return EXIT_FAILURE;
    }


    glViewport(
        0,
        0,
        screenWidth,
        screenHeight
    );


    // ==========================================
    // OPCIONES OPENGL
    // ==========================================

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);

    glBlendFunc(
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA
    );


    // ==========================================
    // SHADER
    // ==========================================

    Shader ourShader(
        "Shader/core.vs",
        "Shader/core.frag"
    );


    // ==========================================
    // CUBO VERDE
    // ==========================================

    float vertices[] =
    {
        // Frente
        -0.5f,-0.5f, 0.5f,   0.20f,0.75f,0.20f,
         0.5f,-0.5f, 0.5f,   0.20f,0.75f,0.20f,
         0.5f, 0.5f, 0.5f,   0.20f,0.75f,0.20f,

         0.5f, 0.5f, 0.5f,   0.20f,0.75f,0.20f,
        -0.5f, 0.5f, 0.5f,   0.20f,0.75f,0.20f,
        -0.5f,-0.5f, 0.5f,   0.20f,0.75f,0.20f,


        // Atras
        -0.5f,-0.5f,-0.5f,   0.20f,0.75f,0.20f,
         0.5f,-0.5f,-0.5f,   0.20f,0.75f,0.20f,
         0.5f, 0.5f,-0.5f,   0.20f,0.75f,0.20f,

         0.5f, 0.5f,-0.5f,   0.20f,0.75f,0.20f,
        -0.5f, 0.5f,-0.5f,   0.20f,0.75f,0.20f,
        -0.5f,-0.5f,-0.5f,   0.20f,0.75f,0.20f,


        // Derecha
         0.5f,-0.5f, 0.5f,   0.20f,0.75f,0.20f,
         0.5f,-0.5f,-0.5f,   0.20f,0.75f,0.20f,
         0.5f, 0.5f,-0.5f,   0.20f,0.75f,0.20f,

         0.5f, 0.5f,-0.5f,   0.20f,0.75f,0.20f,
         0.5f, 0.5f, 0.5f,   0.20f,0.75f,0.20f,
         0.5f,-0.5f, 0.5f,   0.20f,0.75f,0.20f,


         // Izquierda
         -0.5f, 0.5f, 0.5f,   0.20f,0.75f,0.20f,
         -0.5f, 0.5f,-0.5f,   0.20f,0.75f,0.20f,
         -0.5f,-0.5f,-0.5f,   0.20f,0.75f,0.20f,

         -0.5f,-0.5f,-0.5f,   0.20f,0.75f,0.20f,
         -0.5f,-0.5f, 0.5f,   0.20f,0.75f,0.20f,
         -0.5f, 0.5f, 0.5f,   0.20f,0.75f,0.20f,


         // Abajo
         -0.5f,-0.5f,-0.5f,   0.20f,0.75f,0.20f,
          0.5f,-0.5f,-0.5f,   0.20f,0.75f,0.20f,
          0.5f,-0.5f, 0.5f,   0.20f,0.75f,0.20f,

          0.5f,-0.5f, 0.5f,   0.20f,0.75f,0.20f,
         -0.5f,-0.5f, 0.5f,   0.20f,0.75f,0.20f,
         -0.5f,-0.5f,-0.5f,   0.20f,0.75f,0.20f,


         // Arriba
         -0.5f, 0.5f,-0.5f,   0.20f,0.75f,0.20f,
          0.5f, 0.5f,-0.5f,   0.20f,0.75f,0.20f,
          0.5f, 0.5f, 0.5f,   0.20f,0.75f,0.20f,

          0.5f, 0.5f, 0.5f,   0.20f,0.75f,0.20f,
         -0.5f, 0.5f, 0.5f,   0.20f,0.75f,0.20f,
         -0.5f, 0.5f,-0.5f,   0.20f,0.75f,0.20f
    };


    // ==========================================
    // CUBO NARANJA
    // ==========================================

    float verticesNaranja[] =
    {
        // Frente
        -0.5f,-0.5f, 0.5f,   1.00f,0.55f,0.10f,
         0.5f,-0.5f, 0.5f,   1.00f,0.55f,0.10f,
         0.5f, 0.5f, 0.5f,   1.00f,0.55f,0.10f,

         0.5f, 0.5f, 0.5f,   1.00f,0.55f,0.10f,
        -0.5f, 0.5f, 0.5f,   1.00f,0.55f,0.10f,
        -0.5f,-0.5f, 0.5f,   1.00f,0.55f,0.10f,


        // Atras
        -0.5f,-0.5f,-0.5f,   1.00f,0.55f,0.10f,
         0.5f,-0.5f,-0.5f,   1.00f,0.55f,0.10f,
         0.5f, 0.5f,-0.5f,   1.00f,0.55f,0.10f,

         0.5f, 0.5f,-0.5f,   1.00f,0.55f,0.10f,
        -0.5f, 0.5f,-0.5f,   1.00f,0.55f,0.10f,
        -0.5f,-0.5f,-0.5f,   1.00f,0.55f,0.10f,


        // Derecha
         0.5f,-0.5f, 0.5f,   1.00f,0.55f,0.10f,
         0.5f,-0.5f,-0.5f,   1.00f,0.55f,0.10f,
         0.5f, 0.5f,-0.5f,   1.00f,0.55f,0.10f,

         0.5f, 0.5f,-0.5f,   1.00f,0.55f,0.10f,
         0.5f, 0.5f, 0.5f,   1.00f,0.55f,0.10f,
         0.5f,-0.5f, 0.5f,   1.00f,0.55f,0.10f,


         // Izquierda
         -0.5f, 0.5f, 0.5f,   1.00f,0.55f,0.10f,
         -0.5f, 0.5f,-0.5f,   1.00f,0.55f,0.10f,
         -0.5f,-0.5f,-0.5f,   1.00f,0.55f,0.10f,

         -0.5f,-0.5f,-0.5f,   1.00f,0.55f,0.10f,
         -0.5f,-0.5f, 0.5f,   1.00f,0.55f,0.10f,
         -0.5f, 0.5f, 0.5f,   1.00f,0.55f,0.10f,


         // Abajo
         -0.5f,-0.5f,-0.5f,   1.00f,0.55f,0.10f,
          0.5f,-0.5f,-0.5f,   1.00f,0.55f,0.10f,
          0.5f,-0.5f, 0.5f,   1.00f,0.55f,0.10f,

          0.5f,-0.5f, 0.5f,   1.00f,0.55f,0.10f,
         -0.5f,-0.5f, 0.5f,   1.00f,0.55f,0.10f,
         -0.5f,-0.5f,-0.5f,   1.00f,0.55f,0.10f,


         // Arriba
         -0.5f, 0.5f,-0.5f,   1.00f,0.55f,0.10f,
          0.5f, 0.5f,-0.5f,   1.00f,0.55f,0.10f,
          0.5f, 0.5f, 0.5f,   1.00f,0.55f,0.10f,

          0.5f, 0.5f, 0.5f,   1.00f,0.55f,0.10f,
         -0.5f, 0.5f, 0.5f,   1.00f,0.55f,0.10f,
         -0.5f, 0.5f,-0.5f,   1.00f,0.55f,0.10f
    };

    // ==========================================
// CUBO VERDE OSCURO - CRESTAS
// ==========================================

    float verticesVerdeOscuro[] =
    {
        // Frente
        -0.5f,-0.5f, 0.5f,   0.05f,0.35f,0.08f,
         0.5f,-0.5f, 0.5f,   0.05f,0.35f,0.08f,
         0.5f, 0.5f, 0.5f,   0.05f,0.35f,0.08f,

         0.5f, 0.5f, 0.5f,   0.05f,0.35f,0.08f,
        -0.5f, 0.5f, 0.5f,   0.05f,0.35f,0.08f,
        -0.5f,-0.5f, 0.5f,   0.05f,0.35f,0.08f,

        // Atras
        -0.5f,-0.5f,-0.5f,   0.05f,0.35f,0.08f,
         0.5f,-0.5f,-0.5f,   0.05f,0.35f,0.08f,
         0.5f, 0.5f,-0.5f,   0.05f,0.35f,0.08f,

         0.5f, 0.5f,-0.5f,   0.05f,0.35f,0.08f,
        -0.5f, 0.5f,-0.5f,   0.05f,0.35f,0.08f,
        -0.5f,-0.5f,-0.5f,   0.05f,0.35f,0.08f,

        // Derecha
         0.5f,-0.5f, 0.5f,   0.05f,0.35f,0.08f,
         0.5f,-0.5f,-0.5f,   0.05f,0.35f,0.08f,
         0.5f, 0.5f,-0.5f,   0.05f,0.35f,0.08f,

         0.5f, 0.5f,-0.5f,   0.05f,0.35f,0.08f,
         0.5f, 0.5f, 0.5f,   0.05f,0.35f,0.08f,
         0.5f,-0.5f, 0.5f,   0.05f,0.35f,0.08f,

         // Izquierda
         -0.5f, 0.5f, 0.5f,   0.05f,0.35f,0.08f,
         -0.5f, 0.5f,-0.5f,   0.05f,0.35f,0.08f,
         -0.5f,-0.5f,-0.5f,   0.05f,0.35f,0.08f,

         -0.5f,-0.5f,-0.5f,   0.05f,0.35f,0.08f,
         -0.5f,-0.5f, 0.5f,   0.05f,0.35f,0.08f,
         -0.5f, 0.5f, 0.5f,   0.05f,0.35f,0.08f,

         // Abajo
         -0.5f,-0.5f,-0.5f,   0.05f,0.35f,0.08f,
          0.5f,-0.5f,-0.5f,   0.05f,0.35f,0.08f,
          0.5f,-0.5f, 0.5f,   0.05f,0.35f,0.08f,

          0.5f,-0.5f, 0.5f,   0.05f,0.35f,0.08f,
         -0.5f,-0.5f, 0.5f,   0.05f,0.35f,0.08f,
         -0.5f,-0.5f,-0.5f,   0.05f,0.35f,0.08f,

         // Arriba
         -0.5f, 0.5f,-0.5f,   0.05f,0.35f,0.08f,
          0.5f, 0.5f,-0.5f,   0.05f,0.35f,0.08f,
          0.5f, 0.5f, 0.5f,   0.05f,0.35f,0.08f,

          0.5f, 0.5f, 0.5f,   0.05f,0.35f,0.08f,
         -0.5f, 0.5f, 0.5f,   0.05f,0.35f,0.08f,
         -0.5f, 0.5f,-0.5f,   0.05f,0.35f,0.08f
    };


    // ==========================================
    // 12 ARISTAS DEL CUBO
    // ==========================================

    // ==========================================
// CUBO BLANCO - OJOS
// ==========================================

    float verticesBlanco[] =
    {
        // Frente
        -0.5f,-0.5f, 0.5f,   1.0f,1.0f,1.0f,
         0.5f,-0.5f, 0.5f,   1.0f,1.0f,1.0f,
         0.5f, 0.5f, 0.5f,   1.0f,1.0f,1.0f,

         0.5f, 0.5f, 0.5f,   1.0f,1.0f,1.0f,
        -0.5f, 0.5f, 0.5f,   1.0f,1.0f,1.0f,
        -0.5f,-0.5f, 0.5f,   1.0f,1.0f,1.0f,

        // Atras
        -0.5f,-0.5f,-0.5f,   1.0f,1.0f,1.0f,
         0.5f,-0.5f,-0.5f,   1.0f,1.0f,1.0f,
         0.5f, 0.5f,-0.5f,   1.0f,1.0f,1.0f,

         0.5f, 0.5f,-0.5f,   1.0f,1.0f,1.0f,
        -0.5f, 0.5f,-0.5f,   1.0f,1.0f,1.0f,
        -0.5f,-0.5f,-0.5f,   1.0f,1.0f,1.0f,

        // Derecha
         0.5f,-0.5f, 0.5f,   1.0f,1.0f,1.0f,
         0.5f,-0.5f,-0.5f,   1.0f,1.0f,1.0f,
         0.5f, 0.5f,-0.5f,   1.0f,1.0f,1.0f,

         0.5f, 0.5f,-0.5f,   1.0f,1.0f,1.0f,
         0.5f, 0.5f, 0.5f,   1.0f,1.0f,1.0f,
         0.5f,-0.5f, 0.5f,   1.0f,1.0f,1.0f,

         // Izquierda
         -0.5f, 0.5f, 0.5f,   1.0f,1.0f,1.0f,
         -0.5f, 0.5f,-0.5f,   1.0f,1.0f,1.0f,
         -0.5f,-0.5f,-0.5f,   1.0f,1.0f,1.0f,

         -0.5f,-0.5f,-0.5f,   1.0f,1.0f,1.0f,
         -0.5f,-0.5f, 0.5f,   1.0f,1.0f,1.0f,
         -0.5f, 0.5f, 0.5f,   1.0f,1.0f,1.0f,

         // Abajo
         -0.5f,-0.5f,-0.5f,   1.0f,1.0f,1.0f,
          0.5f,-0.5f,-0.5f,   1.0f,1.0f,1.0f,
          0.5f,-0.5f, 0.5f,   1.0f,1.0f,1.0f,

          0.5f,-0.5f, 0.5f,   1.0f,1.0f,1.0f,
         -0.5f,-0.5f, 0.5f,   1.0f,1.0f,1.0f,
         -0.5f,-0.5f,-0.5f,   1.0f,1.0f,1.0f,

         // Arriba
         -0.5f, 0.5f,-0.5f,   1.0f,1.0f,1.0f,
          0.5f, 0.5f,-0.5f,   1.0f,1.0f,1.0f,
          0.5f, 0.5f, 0.5f,   1.0f,1.0f,1.0f,

          0.5f, 0.5f, 0.5f,   1.0f,1.0f,1.0f,
         -0.5f, 0.5f, 0.5f,   1.0f,1.0f,1.0f,
         -0.5f, 0.5f,-0.5f,   1.0f,1.0f,1.0f
    };


    // ==========================================
    // CUBO NEGRO - PUPILA
    // ==========================================

    float verticesNegro[] =
    {
        // Frente
        -0.5f,-0.5f, 0.5f,   0.0f,0.0f,0.0f,
         0.5f,-0.5f, 0.5f,   0.0f,0.0f,0.0f,
         0.5f, 0.5f, 0.5f,   0.0f,0.0f,0.0f,

         0.5f, 0.5f, 0.5f,   0.0f,0.0f,0.0f,
        -0.5f, 0.5f, 0.5f,   0.0f,0.0f,0.0f,
        -0.5f,-0.5f, 0.5f,   0.0f,0.0f,0.0f,

        // Atras
        -0.5f,-0.5f,-0.5f,   0.0f,0.0f,0.0f,
         0.5f,-0.5f,-0.5f,   0.0f,0.0f,0.0f,
         0.5f, 0.5f,-0.5f,   0.0f,0.0f,0.0f,

         0.5f, 0.5f,-0.5f,   0.0f,0.0f,0.0f,
        -0.5f, 0.5f,-0.5f,   0.0f,0.0f,0.0f,
        -0.5f,-0.5f,-0.5f,   0.0f,0.0f,0.0f,

        // Derecha
         0.5f,-0.5f, 0.5f,   0.0f,0.0f,0.0f,
         0.5f,-0.5f,-0.5f,   0.0f,0.0f,0.0f,
         0.5f, 0.5f,-0.5f,   0.0f,0.0f,0.0f,

         0.5f, 0.5f,-0.5f,   0.0f,0.0f,0.0f,
         0.5f, 0.5f, 0.5f,   0.0f,0.0f,0.0f,
         0.5f,-0.5f, 0.5f,   0.0f,0.0f,0.0f,

         // Izquierda
         -0.5f, 0.5f, 0.5f,   0.0f,0.0f,0.0f,
         -0.5f, 0.5f,-0.5f,   0.0f,0.0f,0.0f,
         -0.5f,-0.5f,-0.5f,   0.0f,0.0f,0.0f,

         -0.5f,-0.5f,-0.5f,   0.0f,0.0f,0.0f,
         -0.5f,-0.5f, 0.5f,   0.0f,0.0f,0.0f,
         -0.5f, 0.5f, 0.5f,   0.0f,0.0f,0.0f,

         // Abajo
         -0.5f,-0.5f,-0.5f,   0.0f,0.0f,0.0f,
          0.5f,-0.5f,-0.5f,   0.0f,0.0f,0.0f,
          0.5f,-0.5f, 0.5f,   0.0f,0.0f,0.0f,

          0.5f,-0.5f, 0.5f,   0.0f,0.0f,0.0f,
         -0.5f,-0.5f, 0.5f,   0.0f,0.0f,0.0f,
         -0.5f,-0.5f,-0.5f,   0.0f,0.0f,0.0f,

         // Arriba
         -0.5f, 0.5f,-0.5f,   0.0f,0.0f,0.0f,
          0.5f, 0.5f,-0.5f,   0.0f,0.0f,0.0f,
          0.5f, 0.5f, 0.5f,   0.0f,0.0f,0.0f,

          0.5f, 0.5f, 0.5f,   0.0f,0.0f,0.0f,
         -0.5f, 0.5f, 0.5f,   0.0f,0.0f,0.0f,
         -0.5f, 0.5f,-0.5f,   0.0f,0.0f,0.0f
    };

    // ==========================================
// CUBO VERDE CLARO - PANZA
// ==========================================

    float verticesVerdeClaro[] =
    {
        // Frente
        -0.5f,-0.5f, 0.5f,   0.55f,0.90f,0.30f,
         0.5f,-0.5f, 0.5f,   0.55f,0.90f,0.30f,
         0.5f, 0.5f, 0.5f,   0.55f,0.90f,0.30f,

         0.5f, 0.5f, 0.5f,   0.55f,0.90f,0.30f,
        -0.5f, 0.5f, 0.5f,   0.55f,0.90f,0.30f,
        -0.5f,-0.5f, 0.5f,   0.55f,0.90f,0.30f,

        // Atras
        -0.5f,-0.5f,-0.5f,   0.55f,0.90f,0.30f,
         0.5f,-0.5f,-0.5f,   0.55f,0.90f,0.30f,
         0.5f, 0.5f,-0.5f,   0.55f,0.90f,0.30f,

         0.5f, 0.5f,-0.5f,   0.55f,0.90f,0.30f,
        -0.5f, 0.5f,-0.5f,   0.55f,0.90f,0.30f,
        -0.5f,-0.5f,-0.5f,   0.55f,0.90f,0.30f,

        // Derecha
         0.5f,-0.5f, 0.5f,   0.55f,0.90f,0.30f,
         0.5f,-0.5f,-0.5f,   0.55f,0.90f,0.30f,
         0.5f, 0.5f,-0.5f,   0.55f,0.90f,0.30f,

         0.5f, 0.5f,-0.5f,   0.55f,0.90f,0.30f,
         0.5f, 0.5f, 0.5f,   0.55f,0.90f,0.30f,
         0.5f,-0.5f, 0.5f,   0.55f,0.90f,0.30f,

         // Izquierda
         -0.5f, 0.5f, 0.5f,   0.55f,0.90f,0.30f,
         -0.5f, 0.5f,-0.5f,   0.55f,0.90f,0.30f,
         -0.5f,-0.5f,-0.5f,   0.55f,0.90f,0.30f,

         -0.5f,-0.5f,-0.5f,   0.55f,0.90f,0.30f,
         -0.5f,-0.5f, 0.5f,   0.55f,0.90f,0.30f,
         -0.5f, 0.5f, 0.5f,   0.55f,0.90f,0.30f,

         // Abajo
         -0.5f,-0.5f,-0.5f,   0.55f,0.90f,0.30f,
          0.5f,-0.5f,-0.5f,   0.55f,0.90f,0.30f,
          0.5f,-0.5f, 0.5f,   0.55f,0.90f,0.30f,

          0.5f,-0.5f, 0.5f,   0.55f,0.90f,0.30f,
         -0.5f,-0.5f, 0.5f,   0.55f,0.90f,0.30f,
         -0.5f,-0.5f,-0.5f,   0.55f,0.90f,0.30f,

         // Arriba
         -0.5f, 0.5f,-0.5f,   0.55f,0.90f,0.30f,
          0.5f, 0.5f,-0.5f,   0.55f,0.90f,0.30f,
          0.5f, 0.5f, 0.5f,   0.55f,0.90f,0.30f,

          0.5f, 0.5f, 0.5f,   0.55f,0.90f,0.30f,
         -0.5f, 0.5f, 0.5f,   0.55f,0.90f,0.30f,
         -0.5f, 0.5f,-0.5f,   0.55f,0.90f,0.30f
    };

    float verticesLineas[] =
    {
        // Frente
        -0.5f,-0.5f, 0.5f,    0.5f,-0.5f, 0.5f,
         0.5f,-0.5f, 0.5f,    0.5f, 0.5f, 0.5f,
         0.5f, 0.5f, 0.5f,   -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,   -0.5f,-0.5f, 0.5f,

        // Atras
        -0.5f,-0.5f,-0.5f,    0.5f,-0.5f,-0.5f,
         0.5f,-0.5f,-0.5f,    0.5f, 0.5f,-0.5f,
         0.5f, 0.5f,-0.5f,   -0.5f, 0.5f,-0.5f,
        -0.5f, 0.5f,-0.5f,   -0.5f,-0.5f,-0.5f,

        // Uniones frente-atras
        -0.5f,-0.5f, 0.5f,   -0.5f,-0.5f,-0.5f,
         0.5f,-0.5f, 0.5f,    0.5f,-0.5f,-0.5f,
         0.5f, 0.5f, 0.5f,    0.5f, 0.5f,-0.5f,
        -0.5f, 0.5f, 0.5f,   -0.5f, 0.5f,-0.5f
    };


    // ==========================================
    // VAO Y VBO
    // ==========================================

    GLuint VBO, VAO;
    GLuint VBOnaranja, VAOnaranja;
    GLuint VBOverdeOscuro, VAOverdeOscuro;
    GLuint VBOblanco, VAOblanco;
    GLuint VBOnegro, VAOnegro;
    GLuint VBOverdeClaro, VAOverdeClaro;
    GLuint VBOlineas, VAOlineas;


    // ==========================================
    // VAO VERDE
    // ==========================================

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );

    // Posicion
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(GLfloat),
        (GLvoid*)0
    );

    glEnableVertexAttribArray(0);


    // Color
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(GLfloat),
        (GLvoid*)(3 * sizeof(GLfloat))
    );

    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // ==========================================
    // VAO NARANJA
    // ==========================================

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


    // Posicion
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(GLfloat),
        (GLvoid*)0
    );

    glEnableVertexAttribArray(0);


    // Color
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(GLfloat),
        (GLvoid*)(3 * sizeof(GLfloat))
    );

    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // ==========================================
// VAO VERDE OSCURO
// ==========================================

    glGenVertexArrays(1, &VAOverdeOscuro);
    glGenBuffers(1, &VBOverdeOscuro);

    glBindVertexArray(VAOverdeOscuro);

    glBindBuffer(GL_ARRAY_BUFFER, VBOverdeOscuro);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(verticesVerdeOscuro),
        verticesVerdeOscuro,
        GL_STATIC_DRAW
    );

    // Posicion
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(GLfloat),
        (GLvoid*)0
    );

    glEnableVertexAttribArray(0);

    // Color
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(GLfloat),
        (GLvoid*)(3 * sizeof(GLfloat))
    );

    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // ==========================================
// VAO BLANCO
// ==========================================

    glGenVertexArrays(1, &VAOblanco);
    glGenBuffers(1, &VBOblanco);

    glBindVertexArray(VAOblanco);
    glBindBuffer(GL_ARRAY_BUFFER, VBOblanco);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(verticesBlanco),
        verticesBlanco,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE,
        6 * sizeof(GLfloat),
        (GLvoid*)0
    );

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE,
        6 * sizeof(GLfloat),
        (GLvoid*)(3 * sizeof(GLfloat))
    );

    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    // ==========================================
    // VAO NEGRO
    // ==========================================

    glGenVertexArrays(1, &VAOnegro);
    glGenBuffers(1, &VBOnegro);

    glBindVertexArray(VAOnegro);
    glBindBuffer(GL_ARRAY_BUFFER, VBOnegro);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(verticesNegro),
        verticesNegro,
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0, 3, GL_FLOAT, GL_FALSE,
        6 * sizeof(GLfloat),
        (GLvoid*)0
    );

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1, 3, GL_FLOAT, GL_FALSE,
        6 * sizeof(GLfloat),
        (GLvoid*)(3 * sizeof(GLfloat))
    );

    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // ==========================================
// VAO VERDE CLARO - PANZA
// ==========================================

    glGenVertexArrays(1, &VAOverdeClaro);
    glGenBuffers(1, &VBOverdeClaro);

    glBindVertexArray(VAOverdeClaro);
    glBindBuffer(GL_ARRAY_BUFFER, VBOverdeClaro);

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(verticesVerdeClaro),
        verticesVerdeClaro,
        GL_STATIC_DRAW
    );

    // Posicion
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
    // VAO PARA LAS ARISTAS
    // ==========================================

    glGenVertexArrays(1, &VAOlineas);
    glGenBuffers(1, &VBOlineas);

    glBindVertexArray(VAOlineas);

    glBindBuffer(
        GL_ARRAY_BUFFER,
        VBOlineas
    );

    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(verticesLineas),
        verticesLineas,
        GL_STATIC_DRAW
    );


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

    glm::mat4 projection = glm::mat4(1.0f);

    projection = glm::perspective(
        glm::radians(45.0f),
        (GLfloat)screenWidth / (GLfloat)screenHeight,
        0.1f,
        100.0f
    );


    // ==========================================
    // CICLO PRINCIPAL
    // ==========================================

    while (!glfwWindowShouldClose(window))
    {
        Inputs(window);

        glfwPollEvents();


        glClearColor(
            0.55f,
            0.55f,
            0.55f,
            1.0f
        );

        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT
        );


        ourShader.Use();


        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);


        view = glm::translate(
            view,
            glm::vec3(
                movX,
                movY,
                movZ
            )
        );

        view = glm::rotate(
            view,
            glm::radians(rot),
            glm::vec3(
                0.0f,
                1.0f,
                0.0f
            )
        );


        GLint modelLoc =
            glGetUniformLocation(
                ourShader.Program,
                "model"
            );

        GLint viewLoc =
            glGetUniformLocation(
                ourShader.Program,
                "view"
            );

        GLint projecLoc =
            glGetUniformLocation(
                ourShader.Program,
                "projection"
            );

        GLint colorLineaLoc =
            glGetUniformLocation(
                ourShader.Program,
                "usarColorLinea"
            );


        glUniformMatrix4fv(
            projecLoc,
            1,
            GL_FALSE,
            glm::value_ptr(projection)
        );

        glUniformMatrix4fv(
            viewLoc,
            1,
            GL_FALSE,
            glm::value_ptr(view)
        );


        // ==========================================
        // POSICION GENERAL DE LA PATA
        // ==========================================

        float pataDerX = -0.5f;
        float pataDerY = -1.0f;
        float pataDerZ = 0.0f;


        // ==========================================
        // PRIMERA  brazos
        // ==========================================

        // 1
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY + B,
            pataDerZ,
            B, B, B
        );


        // 2
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY,
            pataDerZ,
            B, B, B
        );


        // 3
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY - B,
            pataDerZ,
            B, B, B
        );


        // 4
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY - 2.0f * B,
            pataDerZ,
            B, B, B
        );


        // 5
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY - 3.0f * B,
            pataDerZ,
            B, B, B
        );


        // 6
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY - 3.0f * B,
            pataDerZ,
            B, B, B
        );


        // 7
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY,
            pataDerZ,
            B, B, B
        );


        // 8
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY,
            pataDerZ,
            B, B, B
        );


        // 9
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY - B,
            pataDerZ,
            B, B, B
        );


        // 10
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY - B,
            pataDerZ,
            B, B, B
        );


        // 11
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY + B,
            pataDerZ,
            B, B, B
        );


        // 12
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY - 3.0f * B,
            pataDerZ,
            B, B, B
        );


        // 13 - Medio cubo
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY - 2.25f * B,
            pataDerZ,
            B,
            B / 2.0f,
            B
        );


        // ==========================================
        // CAPA INTERMEDIA
        // GROSOR = 1/4 DE CUBO
        // ==========================================

        float interZ =
            pataDerZ - 0.625f * B;


        // 1
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY + B,
            interZ,
            B, B, B / 4.0f
        );


        // 2
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY,
            interZ,
            B, B, B / 4.0f
        );


        // 3
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY - B,
            interZ,
            B, B, B / 4.0f
        );


        // 4
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY - 2.0f * B,
            interZ,
            B, B, B / 4.0f
        );


        // 5
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY - 3.0f * B,
            interZ,
            B, B, B / 4.0f
        );


        // 6
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY - 3.0f * B,
            interZ,
            B, B, B / 4.0f
        );


        // 7
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY,
            interZ,
            B, B, B / 4.0f
        );


        // 8
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY,
            interZ,
            B, B, B / 4.0f
        );


        // 9
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY - B,
            interZ,
            B, B, B / 4.0f
        );


        // 10
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY - B,
            interZ,
            B, B, B / 4.0f
        );


        // 11
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY + B,
            interZ,
            B, B, B / 4.0f
        );


        // 12
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY - 3.0f * B,
            interZ,
            B, B, B / 4.0f
        );


        // 13 - Medio cubo
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY - 2.25f * B,
            interZ,
            B,
            B / 2.0f,
            B / 4.0f
        );
        //PARED INTER ANTES DE GARRA PATA 1 PARED 1
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2 * B,
            pataDerY - 3.0f * B,
            interZ,
            B, B, B / 4.0f
        );

        // ==========================================
        // SEGUNDA PARED
        // ==========================================

        float pared2Z =
            pataDerZ - 1.25f * B;
        // 1
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2 * B,
            pataDerY + -3 * B,
            pared2Z,
            B, B, B
        );

        // 1
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY + B,
            pared2Z,
            B, B, B
        );


        // 2
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY,
            pared2Z,
            B, B, B
        );


        // 3
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY - B,
            pared2Z,
            B, B, B
        );


        // 4
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY - 2.0f * B,
            pared2Z,
            B, B, B
        );


        // 5
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY - 3.0f * B,
            pared2Z,
            B, B, B
        );


        // 6
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY - 3.0f * B,
            pared2Z,
            B, B, B
        );


        // 7
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY,
            pared2Z,
            B, B, B
        );


        // 8
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY,
            pared2Z,
            B, B, B
        );


        // 9
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY - B,
            pared2Z,
            B, B, B
        );


        // 10
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY - B,
            pared2Z,
            B, B, B
        );


        // 11
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY + B,
            pared2Z,
            B, B, B
        );


        // 12
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY - 3.0f * B,
            pared2Z,
            B, B, B
        );


        // 13 - Medio cubo
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY - 2.25f * B,
            pared2Z,
            B,
            B / 2.0f,
            B
        );

        // CUABO ANTES DE GARRA PARED 1 , PATA 1 --------MAL 


        //CUBO PARED 1 
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2 * B,
            pataDerY - 3.0f * B,
            pared2Z + 1.25 * B,
            B, B, B
        );


        // ==========================================
        // GARRAS NARANJAS - PUNTA DEL PIE
        // ==========================================

        // Garra de la primera pared
        dibujarCubo(
            modelLoc,
            VAOnaranja,
            VAOlineas,
            colorLineaLoc,

            pataDerX + 2.625f * B,   // adelante, en +X
            pataDerY - 3.0f * B,     // misma altura del pie
            pataDerZ,                 // primera pared

            B / 4.0f,                // delgada en X
            B,                       // altura completa
            B                        // profundidad completa
        );


        // Garra de la segunda pared
        dibujarCubo(
            modelLoc,
            VAOnaranja,
            VAOlineas,
            colorLineaLoc,

            pataDerX + 2.625f * B,   // misma punta
            pataDerY - 3.0f * B,
            pared2Z,                  // segunda pared

            B / 4.0f,
            B,
            B
        );

        // ==========================================
        // PUENTE HACIA LA PANZA - 4 CUBOS
        // ==========================================

        // Cubo 1
        dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2 * B,
            pataDerY - B,
            pataDerZ - 1.250f * B,
            B, B, B);

        // Cubo 2
        dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2 * B,
            pataDerY - B,
            pataDerZ - 2.250f * B,
            B, B, B);

        // Cubo 3
        dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2 * B,
            pataDerY - B,
            pataDerZ - 3.250f * B,
            B, B, B);

        // Cubo 4
        dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2 * B,
            pataDerY - B,
            pataDerZ - 4.250f * B,
            B, B, B);
        //Panza delantera - 4 cubos---------------------------------------------------
                // Cubo 1
        dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3 * B,
            pataDerY - B,
            pataDerZ - 1.250f * B,
            B, B, B);

        // Cubo 2
        dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3 * B,
            pataDerY - B,
            pataDerZ - 2.250f * B,
            B, B, B);

        // Cubo 3
        dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3 * B,
            pataDerY - B,
            pataDerZ - 3.250f * B,
            B, B, B);

        // Cubo 4
        dibujarCubo(modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3 * B,
            pataDerY - B,
            pataDerZ - 4.250f * B,
            B, B, B);

        //============================================================================================
        //PATA IZQUIERDA
        //============================================================================================

              // ==========================================
            // PRIMERA PARED
            // ==========================================

            // 1
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY + B,
            pataDerZ - 4.250f * B,
            B, B, B
        );


        // 2
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY,
            pataDerZ - 4.250f * B,
            B, B, B
        );


        // 3
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY - B,
            pataDerZ - 4.250f * B,
            B, B, B
        );


        // 4
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY - 2.0f * B,
            pataDerZ - 4.250f * B,
            B, B, B
        );


        // 5
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY - 3.0f * B,
            pataDerZ - 4.250f * B,
            B, B, B
        );


        // 6
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY - 3.0f * B,
            pataDerZ - 4.250f * B,
            B, B, B
        );


        // 7
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY,
            pataDerZ - 4.250f * B,
            B, B, B
        );


        // 8
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY,
            pataDerZ - 4.250f * B,
            B, B, B
        );


        // 9
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY - B,
            pataDerZ - 4.250f * B,
            B, B, B
        );


        // 10
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY - B,
            pataDerZ - 4.250f * B,
            B, B, B
        );


        // 11
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY + B,
            pataDerZ - 4.250f * B,
            B, B, B
        );


        // 12
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY - 3.0f * B,
            pataDerZ - 4.250f * B,
            B, B, B
        );


        // 13 - Medio cubo
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY - 2.25f * B,
            pataDerZ - 4.250f * B,
            B,
            B / 2.0f,
            B
        );
        //__________________________CUBO ANTES DE LA GARRA
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY - 3.0f * B,
            pared2Z - 3.0f * B,
            B, B, B
        );

        //// ==========================================
        //// CAPA INTERMEDIA
        //// GROSOR = 1/4 DE CUBO
        //// ==========================================

        //float interZ =
        //    pataDerZ - 0.625f * B;
//----------------------------------------PARED INTER ATRAS DE GARRA SEGUNDA PATA 
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY - 3 * B,
            interZ - 4.250f * B,
            B, B, B / 4.0f
        );
        // 1
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY + B,
            interZ - 4.250f * B,
            B, B, B / 4.0f
        );


        // 2
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY,
            interZ - 4.250f * B,
            B, B, B / 4.0f
        );


        // 3
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY - B,
            interZ - 4.250f * B,
            B, B, B / 4.0f
        );


        // 4
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY - 2.0f * B,
            interZ - 4.250f * B,
            B, B, B / 4.0f
        );


        // 5
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY - 3.0f * B,
            interZ - 4.250f * B,
            B, B, B / 4.0f
        );


        // 6
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY - 3.0f * B,
            interZ - 4.250f * B,
            B, B, B / 4.0f
        );


        // 7
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY,
            interZ - 4.250f * B,
            B, B, B / 4.0f
        );


        // 8
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY,
            interZ - 4.250f * B,
            B, B, B / 4.0f
        );


        // 9
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY - B,
            interZ - 4.250f * B,
            B, B, B / 4.0f
        );


        // 10
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY - B,
            interZ - 4.250f * B,
            B, B, B / 4.0f
        );


        // 11
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY + B,
            interZ - 4.250f * B,
            B, B, B / 4.0f
        );


        // 12
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY - 3.0f * B,
            interZ - 4.250f * B,
            B, B, B / 4.0f
        );


        // 13 - Medio cubo
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY - 2.25f * B,
            interZ - 4.250f * B,
            B,
            B / 2.0f,
            B / 4.0f
        );


        //// ==========================================
        //// SEGUNDA PARED
        //// ==========================================

        //float pared2Z =
        //    pataDerZ - 1.25f * B;


        // 1
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY + B,
            pared2Z - 4.250f * B,
            B, B, B
        );

        //1.55555555555 CUBO ANTES DE GARRAS 
                // 1
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY - 3.0 * B,
            pared2Z - 4.250f * B,
            B, B, B
        );


        //-------------------------------------------------------

        // 2
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY,
            pared2Z - 4.250f * B,
            B, B, B
        );


        // 3
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY - B,
            pared2Z - 4.250f * B,
            B, B, B
        );


        // 4
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY - 2.0f * B,
            pared2Z - 4.250f * B,
            B, B, B
        );


        // 5
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY - 3.0f * B,
            pared2Z - 4.250f * B,
            B, B, B
        );


        // 6
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY - 3.0f * B,
            pared2Z - 4.250f * B,
            B, B, B
        );


        // 7
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY,
            pared2Z - 4.250f * B,
            B, B, B
        );


        // 8
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY,
            pared2Z - 4.250f * B,
            B, B, B
        );


        // 9
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY - B,
            pared2Z - 4.250f * B,
            B, B, B
        );


        // 10
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY - B,
            pared2Z - 4.250f * B,
            B, B, B
        );


        // 11
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY + B,
            pared2Z - 4.250f * B,
            B, B, B
        );


        // 12
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY - 3.0f * B,
            pared2Z - 4.250f * B,
            B, B, B
        );


        // 13 - Medio cubo
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY - 2.25f * B,
            pared2Z - 4.250f * B,
            B,
            B / 2.0f,
            B
        );


        // ==========================================
        // GARRAS NARANJAS - PUNTA DEL PIE
        // ==========================================

        // Garra de la primera pared
        dibujarCubo(
            modelLoc,
            VAOnaranja,
            VAOlineas,
            colorLineaLoc,

            pataDerX + 2.625f * B,   // adelante, en +X
            pataDerY - 3.0f * B,     // misma altura del pie
            pataDerZ - 4.250f * B,                 // primera pared

            B / 4.0f,                // delgada en X
            B,                       // altura completa
            B                        // profundidad completa
        );


        // Garra de la segunda pared
        dibujarCubo(
            modelLoc,
            VAOnaranja,
            VAOlineas,
            colorLineaLoc,

            pataDerX + 2.625f * B,   // misma punta
            pataDerY - 3.0f * B,
            pared2Z - 4.250f * B,                  // segunda pared

            B / 4.0f,
            B,
            B
        );

        // ==========================================
        // PANZA PARTE BAJA 1
        // ==========================================


        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY - 2.0f * B,
            pataDerZ - 2.250f * B,
            B, B, B
        );



        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY - 2.0f * B,
            pataDerZ - 3.250f * B,
            B, B, B
        );


        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY - 2.0f * B,
            pataDerZ - 2.250f * B,
            B, B, B
        );


        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY - 2.0f * B,
            pataDerZ - 3.250f * B,
            B, B, B
        );
        /////POCISIONAR ----------------
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 2.0f * B,
            pataDerY - 2.0f * B,
            pataDerZ - 3.250f * B,
            B, B, B
        );
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 2.0f * B,
            pataDerY - 2.0f * B,
            pataDerZ - 2.250f * B,
            B, B, B
        );

        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 3.0f * B,
            pataDerY - 2.0f * B,
            pataDerZ - 3.250f * B,
            B, B, B
        );
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 3.0f * B,
            pataDerY - 2.0f * B,
            pataDerZ - 2.250f * B,
            B, B, B
        );

        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 4.0f * B,
            pataDerY - 2.0f * B,
            pataDerZ - 3.250f * B,
            B, B, B
        );
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 4.0f * B,
            pataDerY - 2.0f * B,
            pataDerZ - 2.250f * B,
            B, B, B
        );

        // ==========================================
        // PANZA PARTE BAJA 1- lado derecho
        // ==========================================

        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 2.0f * B,
            pataDerY - 1.0f * B,
            pataDerZ - 1.250f * B,
            B, B, B
        );
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 3.0f * B,
            pataDerY - 1.0f * B,
            pataDerZ - 1.250f * B,
            B, B, B
        );
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 4.0f * B,
            pataDerY - 1.0f * B,
            pataDerZ - 1.250f * B,
            B, B, B
        );
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 5.0f * B,
            pataDerY - 1.0f * B,
            pataDerZ - 1.250f * B,
            B, B, B
        );

        // ==========================================
        // PANZA PARTE BAJA 2- lado derecho
        // ==========================================

        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 2.0f * B,
            pataDerY,
            pataDerZ - 1.250f * B,
            B, B, B
        );
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 3.0f * B,
            pataDerY,
            pataDerZ - 1.250f * B,
            B, B, B
        );
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 4.0f * B,
            pataDerY,
            pataDerZ - 1.250f * B,
            B, B, B
        );
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 5.0f * B,
            pataDerY,
            pataDerZ - 1.250f * B,
            B, B, B
        );
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 6.0f * B,
            pataDerY,
            pataDerZ - 1.250f * B,
            B, B, B
        );

        dibujarCubo(//-------------parte delantera
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY,
            pataDerZ - 1.250f * B,
            B, B, B
        );
        dibujarCubo(//------------parte delantera
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY,
            pataDerZ - 1.250f * B,
            B, B, B
        );

        // ==========================================
        // COLA 2 CUBOS 
        // ==========================================

        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 6.0f * B,
            pataDerY + B,
            pataDerZ - 1.250f * B,
            B, B, B
        );
        dibujarCubo(//------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 5.0f * B,
            pataDerY + B,
            pataDerZ - 1.250f * B,
            B, B, B
        );
        dibujarCubo(//------------PUNTA CUBO COLA
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 6.0f * B,
            pataDerY + 2.0f * B,
            pataDerZ - 1.250f * B,
            B, B, B
        );


        // ==========================================
        // 2 lineas pared derecha altura alto pierna der 
        // ==========================================

        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 2.0f * B,
            pataDerY + B,
            pataDerZ - 1.250f * B,
            B, B, B
        );


        dibujarCubo(//------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 1.0f * B,
            pataDerY + B,
            pataDerZ - 1.250f * B,
            B, B, B
        );

        dibujarCubo(//------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY + B,
            pataDerZ - 1.250f * B,
            B, B, B
        );
        dibujarCubo(//------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY + B,
            pataDerZ - 1.250f * B,
            B, B, B
        );
        //pared arriba de la anterior 

        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 2.0f * B,
            pataDerY + 2.0f * B,
            pataDerZ - 1.250f * B,
            B, B, B
        );
        dibujarCubo(//------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 1.0f * B,
            pataDerY + 2.0f * B,
            pataDerZ - 1.250f * B,
            B, B, B
        );
        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY + 2.0f * B,
            pataDerZ - 1.250f * B,
            B, B, B
        );
        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY + 2.0f * B,
            pataDerZ - 1.250f * B,
            B, B, B
        );

        dibujarCubo(//------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY + 2.0f * B,
            pataDerZ - 1.250f * B,
            B, B, B
        );
        dibujarCubo(//------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY + 2.0f * B,
            pataDerZ - 1.250f * B,
            B, B, B
        );
        //pared arriba de la de abajo---donde nace el brazo 
        //dibujarCubo(//-------------
        //    modelLoc, VAO, VAOlineas, colorLineaLoc,
        //    pataDerX - 2.0f * B,
        //    pataDerY + 2.0f * B,
        //    pataDerZ - 1.250f * B,
        //    B, B, B
        //);
        dibujarCubo(//------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 1.0f * B,
            pataDerY + 3.0f * B,
            pataDerZ - 1.250f * B,
            B, B, B
        );
        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY + 3.0f * B,
            pataDerZ - 1.250f * B,
            B, B, B
        );
        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY + 3.0f * B,
            pataDerZ - 1.250f * B,
            B, B, B
        );

        dibujarCubo(//------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY + 3.0f * B,
            pataDerZ - 1.250f * B,
            B, B, B
        );
        dibujarCubo(//------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY + 3.0f * B,
            pataDerZ - 1.250f * B,
            B, B, B
        );
        ////////////-----------------------------------------PARED QUE FORMA LA CABEZA -------------------------------










        /////////////////// LINEA DE LOS OJOS 

        //PARED QUE ANTECEDE LOS OJOS





        //LINEA PANZA LATERAL IZQ
        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY,
            pataDerZ - 4.250f * B,
            B, B, B
        );
        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY + B,
            pataDerZ - 4.250f * B,
            B, B, B
        );
        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY + 2.0f * B,
            pataDerZ - 4.250f * B,
            B, B, B
        );
        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY + 3.0f * B,
            pataDerZ - 4.250f * B,
            B, B, B
        );










        //----------------- LINEA LATERAL DERECHA HOCICO 




        //----------------- LINEA LATERAL IZQUIERA HOCICO 





        //LATERAL CABEZA IZQUIERDA-------------------------------




        //LATERAL CABEZA IZQUIERDA------------------------------- 1ER NIVEL 

        //LATERAL CABEZA IZQUIERDA------------------------------- 2DO NIVEL 

        //LATERAL CABEZA IZQUIERDA------------------------------- 3ER NIVEL 

        //====================================



        //===================================== HACIA EL FRENTE PARA CERRAR EL OJO izq

        //===================================== HACIA EL FRENTE PARA CERRAR EL OJO der 

        //cadena para cerrar frente 

        //hocico delantero =========================================================================


        //LATERAL CABEZA IZQUIERDA------------------------------- HACIA EL FRENTE HOCICO

        //LATERAL CABEZA IZQUIERDA------------------------------- HACIA EL FRENTE HOCICO 1ER NIVEL 

        //LATERAL CABEZA IZQUIERDA------------------------------- HACIA EL FRENTE HOCICO 2 NIVEL 

        //LATERAL CABEZA IZQUIERDA------------------------------- HACIA EL FRENTE HOCICO 3 NIVEL 


        //=======================================================
        //PARED LATERAL IZQUIERDA
        //======================================================
        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY + 3.0f * B,
            pataDerZ - 4.250f * B,
            B, B, B
        );
        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY + 3.0f * B,
            pataDerZ - 4.250f * B,
            B, B, B
        );
        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY + 3.0f * B,
            pataDerZ - 4.250f * B,
            B, B, B
        );
        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 1.0f * B,
            pataDerY + 3.0f * B,
            pataDerZ - 4.250f * B,
            B, B, B
        );
        //////////////-------------------LINEA DENAJO RESTANDO 1 EN Y 
        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY + 2.0f * B,
            pataDerZ - 4.250f * B,
            B, B, B
        );
        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY + 2.0f * B,
            pataDerZ - 4.250f * B,
            B, B, B
        );
        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY + 2.0f * B,
            pataDerZ - 4.250f * B,
            B, B, B
        );
        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 1.0f * B,
            pataDerY + 2.0f * B,
            pataDerZ - 4.250f * B,
            B, B, B
        );

        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 2.0f * B,
            pataDerY + 2.0f * B,
            pataDerZ - 4.250f * B,
            B, B, B
        );
        ///////////////////=========DE AQUI DIBUJO 3 CUBOS HACIA HABAJO EN Y

        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 2.0f * B,
            pataDerY + B,
            pataDerZ - 4.250f * B,
            B, B, B
        );

        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 2.0f * B,
            pataDerY,
            pataDerZ - 4.250f * B,
            B, B, B
        );

        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 2.0f * B,
            pataDerY - 1.0f * B,
            pataDerZ - 4.250f * B,
            B, B, B
        );

        ///////////////////======================================= A PARTIR DEL CUBO DE ABAJO CONSTRUIRE LINEA DE PARED IZQUIERDA PARA IR HACIENDO LA COLA 
        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 3.0f * B,
            pataDerY - 1.0f * B,
            pataDerZ - 4.250f * B,
            B, B, B
        );
        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 4.0f * B,
            pataDerY - 1.0f * B,
            pataDerZ - 4.250f * B,
            B, B, B
        );
        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 5.0f * B,
            pataDerY - 1.0f * B,
            pataDerZ - 4.250f * B,
            B, B, B
        );
        dibujarCubo(//------------- lINE A ARRIBA
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 3.0f * B,
            pataDerY,
            pataDerZ - 4.250f * B,
            B, B, B
        );
        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 4.0f * B,
            pataDerY,
            pataDerZ - 4.250f * B,
            B, B, B
        );
        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 5.0f * B,
            pataDerY,
            pataDerZ - 4.250f * B,
            B, B, B
        );
        dibujarCubo(//------------- CUBO COLA
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 6.0f * B,
            pataDerY,
            pataDerZ - 4.250f * B,
            B, B, B
        );
        //unimos cola 
        dibujarCubo(//------------- CUBO COLA 1er nivel 
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 6.0f * B,
            pataDerY,
            pataDerZ - 3.250f * B,
            B, B, B
        );

        dibujarCubo(//------------- CUBO COLA
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 6.0f * B,
            pataDerY,
            pataDerZ - 2.250f * B,
            B, B, B
        );
        //=========================
        dibujarCubo(//------------- 
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 4.0f * B,
            pataDerY,
            pataDerZ - 3.250f * B,
            B, B, B
        );

        dibujarCubo(//------------- CUBO COLA
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 4.0f * B,
            pataDerY,
            pataDerZ - 2.250f * B,
            B, B, B
        );
        dibujarCubo(//------------- 
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 3.0f * B,
            pataDerY,
            pataDerZ - 3.250f * B,
            B, B, B
        );

        dibujarCubo(//------------- CUBO COLA
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 3.0f * B,
            pataDerY,
            pataDerZ - 2.250f * B,
            B, B, B
        );

        //---------------------
        dibujarCubo(//------------- 
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 2.0f * B,
            pataDerY + B,
            pataDerZ - 3.250f * B,
            B, B, B
        );

        dibujarCubo(//------------- CUBO COLA
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 2.0f * B,
            pataDerY + B,
            pataDerZ - 2.250f * B,
            B, B, B
        );

        dibujarCubo(//------------- 
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 2.0f * B,
            pataDerY + 2.0f * B,
            pataDerZ - 3.250f * B,
            B, B, B
        );

        dibujarCubo(//------------- CUBO COLA
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 2.0f * B,
            pataDerY + 2.0f * B,
            pataDerZ - 2.250f * B,
            B, B, B
        );

        dibujarCubo(//------------- 
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY + 3.0f * B,
            pataDerZ - 3.250f * B,
            B, B, B
        );

        dibujarCubo(//------------- CUBO COLA
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY + 3.0f * B,
            pataDerZ - 2.250f * B,
            B, B, B
        );

        dibujarCubo(//------------- 
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY + 3.0f * B,
            pataDerZ - 3.250f * B,
            B, B, B
        );

        dibujarCubo(//------------- CUBO COLA
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY + 3.0f * B,
            pataDerZ - 2.250f * B,
            B, B, B
        );//Voy aqui arriba

        //==========================
        dibujarCubo(//------------- CUBO COLA 2do nivel 
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 6.0f * B,
            pataDerY + B,
            pataDerZ - 3.250f * B,
            B, B, B
        );

        dibujarCubo(//------------- CUBO COLA
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 6.0f * B,
            pataDerY + B,
            pataDerZ - 2.250f * B,
            B, B, B
        );
        //------------------------------------------------------------------------
        // PARED FRENTE AL SEGUNDO NIVEL 

        dibujarCubo(//------------- CUBO COLA 2do nivel 
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 5.0f * B,
            pataDerY + B,
            pataDerZ - 3.250f * B,
            B, B, B
        );

        dibujarCubo(//------------- CUBO COLA
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 5.0f * B,
            pataDerY + B,
            pataDerZ - 2.250f * B,
            B, B, B
        );

        //------------------------------------------------------------------------
        dibujarCubo(//------------- CUBO COLA 3er nivel 
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 6.0f * B,
            pataDerY + 2.0 * B,
            pataDerZ - 3.250f * B,
            B, B, B
        );

        dibujarCubo(//------------- CUBO COLA
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 6.0f * B,
            pataDerY + 2.0 * B,
            pataDerZ - 2.250f * B,
            B, B, B
        );

        //==================================


        dibujarCubo(//-------------  CUBOS 2 COLA------------------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 5.0f * B,
            pataDerY + B,
            pataDerZ - 4.250f * B,
            B, B, B
        );
        dibujarCubo(//------------- 
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 6.0f * B,
            pataDerY + B,
            pataDerZ - 4.250f * B,
            B, B, B
        );

        dibujarCubo(//-------------  PUNTA COLA
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 6.0f * B,
            pataDerY + 2.0f * B,
            pataDerZ - 4.250f * B,
            B, B, B
        );


        dibujarCubo(//-------------  PUNTA COLA
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 5.0f * B,
            pataDerY - B,
            pataDerZ - 2.250f * B,
            B, B, B
        );
        dibujarCubo(//-------------  PUNTA COLA
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 5.0f * B,
            pataDerY - B,
            pataDerZ - 3.250f * B,
            B, B, B
        );

        //============ 2 CUBOS DEBAJO DE LA SECCIÓN ANTERIOR 
        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY + B,
            pataDerZ - 4.250f * B,
            B, B, B
        );
        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY + B,
            pataDerZ - 4.250f * B,
            B, B, B
        );

        dibujarCubo(//-------------
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY,
            pataDerZ - 4.250f * B,
            B, B, B
        );


        //TAPA CABEZA ==============================





        /////// tapa baja cabeza arriba de la frente -coronilla




        // parte baja boca 2  cubos





            //dibujarCubo(//-------------  
            //    modelLoc, VAO, VAOlineas, colorLineaLoc,
            //    pataDerX + 7.0f * B,
            //    pataDerY + 8.0f * B,
            //    pataDerZ - 1.25f*B,
            //    B, B, B
            //);


    //brazos  
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.25f * B,
            pataDerY + 3.0f * B,
            pataDerZ - 0.25f * B,
            B, B, B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.25f * B,
            pataDerY + 2.0f * B,
            pataDerZ - 0.25f * B,
            B, B, B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3.25f * B,
            pataDerY + 2.0f * B,
            pataDerZ - 0.25f * B,
            B, B, B
        );
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 4.25f * B,
            pataDerY + 2.0f * B,
            pataDerZ - 0.25f * B,
            B, B, B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 4.25f * B,
            pataDerY + 1.25f * B,
            pataDerZ - 0.25f * B,
            B,   // más corta
            B * 0.65,   // más baja
            B
        );

        // brazo izq
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.25f * B,
            pataDerY + 3.0f * B,
            pataDerZ - 5.25f * B,
            B, B, B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.25f * B,
            pataDerY + 2.0f * B,
            pataDerZ - 5.25f * B,
            B, B, B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3.25f * B,
            pataDerY + 2.0f * B,
            pataDerZ - 5.25f * B,
            B, B, B
        );
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 4.25f * B,
            pataDerY + 2.0f * B,
            pataDerZ - 5.25f * B,
            B, B, B
        );


        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 4.25f * B,
            pataDerY + 1.25f * B,
            pataDerZ - 5.25f * B,
            B,   // más corta
            B * 0.65,   // más baja
            B
        );

        //=============== Taapa epalda ===================





        // CABEZA ===================================================================================================================================

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 1.0f * B,
            pataDerY + 4.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY + 4.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 1.0f * B,
            pataDerY + 4.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY + 4.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY + 4.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );


        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 1.0f * B,
            pataDerY + 5.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY + 5.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY + 5.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );


        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 1.0f * B,
            pataDerY + 6.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY + 6.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY + 6.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 1.0f * B,
            pataDerY + 7.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY + 7.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY + 7.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 1.0f * B,
            pataDerY + 8.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY + 8.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );


        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 1.0f * B,
            pataDerY + 9.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY + 9.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );


        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 1.0f * B,
            pataDerY + 10.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY + 10.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY + 10.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 4.0f * B,
            pataDerY + 10.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 5.0f * B,
            pataDerY + 10.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 6.0f * B,
            pataDerY + 10.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 5.0f * B,
            pataDerY + 9.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 6.0f * B,
            pataDerY + 9.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 5.0f * B,
            pataDerY + 8.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 6.0f * B,
            pataDerY + 8.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 4.0f * B,
            pataDerY + 7.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 5.0f * B,
            pataDerY + 7.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 6.0f * B,
            pataDerY + 7.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 4.0f * B,
            pataDerY + 5.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 5.0f * B,
            pataDerY + 5.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 6.0f * B,
            pataDerY + 5.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );


        //espejo
        // CABEZA ===================================================================================================================================

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 1.0f * B,
            pataDerY + 4.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY + 4.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 1.0f * B,
            pataDerY + 4.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY + 4.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY + 4.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );


        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 1.0f * B,
            pataDerY + 5.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY + 5.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY + 5.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );


        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 1.0f * B,
            pataDerY + 6.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY + 6.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY + 6.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );


        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 1.0f * B,
            pataDerY + 7.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY + 7.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY + 7.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );


        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 1.0f * B,
            pataDerY + 8.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY + 8.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );


        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 1.0f * B,
            pataDerY + 9.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY + 9.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );


        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 1.0f * B,
            pataDerY + 10.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY + 10.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY + 10.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 4.0f * B,
            pataDerY + 10.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 5.0f * B,
            pataDerY + 10.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 6.0f * B,
            pataDerY + 10.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );


        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 5.0f * B,
            pataDerY + 9.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 6.0f * B,
            pataDerY + 9.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );


        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 5.0f * B,
            pataDerY + 8.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 6.0f * B,
            pataDerY + 8.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );


        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 4.0f * B,
            pataDerY + 7.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 5.0f * B,
            pataDerY + 7.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 6.0f * B,
            pataDerY + 7.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );


        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 4.0f * B,
            pataDerY + 5.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 5.0f * B,
            pataDerY + 5.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 6.0f * B,
            pataDerY + 5.0f * B,
            pataDerZ - 4.25f * B,
            B,
            B,
            B
        );
        //tapa cabeza 

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY + 11.0f * B,
            pataDerZ - 2.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY + 11.0f * B,
            pataDerZ - 3.25f * B,
            B,
            B,
            B
        );
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY + 11.0f * B,
            pataDerZ - 2.25f * B,
            B,
            B,
            B
        );
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 2.0f * B,
            pataDerY + 11.0f * B,
            pataDerZ - 3.25f * B,
            B,
            B,
            B
        );
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY + 11.0f * B,
            pataDerZ - 2.25f * B,
            B,
            B,
            B
        );
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY + 11.0f * B,
            pataDerZ - 3.25f * B,
            B,
            B,
            B
        );

        //tapa cabeza parte baja 

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 4.0f * B,
            pataDerY + 10.0f * B,
            pataDerZ - 2.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 4.0f * B,
            pataDerY + 10.0f * B,
            pataDerZ - 3.25f * B,
            B,
            B,
            B
        );
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 5.0f * B,
            pataDerY + 10.0f * B,
            pataDerZ - 2.25f * B,
            B,
            B,
            B
        );
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 5.0f * B,
            pataDerY + 10.0f * B,
            pataDerZ - 3.25f * B,
            B,
            B,
            B
        );
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 6.0f * B,
            pataDerY + 10.0f * B,
            pataDerZ - 2.25f * B,
            B,
            B,
            B
        );
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 6.0f * B,
            pataDerY + 10.0f * B,
            pataDerZ - 3.25f * B,
            B,
            B,
            B
        );


        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 6.0f * B,
            pataDerY + 5.0f * B,
            pataDerZ - 2.25f * B,
            B,
            B,
            B
        );
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 6.0f * B,
            pataDerY + 5.0f * B,
            pataDerZ - 3.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY + 4.0f * B,
            pataDerZ - 2.25f * B,
            B,
            B,
            B
        );
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY + 4.0f * B,
            pataDerZ - 3.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY + 6.0f * B,
            pataDerZ - 2.25f * B,
            B,
            B,
            B
        );
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY + 6.0f * B,
            pataDerZ - 3.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 4.0f * B,
            pataDerY + 7.0f * B,
            pataDerZ - 2.25f * B,
            B,
            B,
            B
        );
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 4.0f * B,
            pataDerY + 7.0f * B,
            pataDerZ - 3.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 5.0f * B,
            pataDerY + 7.0f * B,
            pataDerZ - 2.25f * B,
            B,
            B,
            B
        );
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 5.0f * B,
            pataDerY + 7.0f * B,
            pataDerZ - 3.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 6.0f * B,
            pataDerY + 7.0f * B,
            pataDerZ - 2.25f * B,
            B,
            B,
            B
        );
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 6.0f * B,
            pataDerY + 7.0f * B,
            pataDerZ - 3.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY + 10.0f * B,
            pataDerZ - 2.25f * B,
            B,
            B,
            B
        );
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY + 10.0f * B,
            pataDerZ - 3.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY + 8.0f * B,
            pataDerZ - 2.25f * B,
            B,
            B,
            B
        );
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY + 8.0f * B,
            pataDerZ - 3.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY + 6.0f * B,
            pataDerZ - 2.25f * B,
            B,
            B,
            B
        );
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY + 6.0f * B,
            pataDerZ - 3.25f * B,
            B,
            B,
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY + 5.0f * B,
            pataDerZ - 2.25f * B,
            B,
            B,
            B
        );
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY + 5.0f * B,
            pataDerZ - 3.25f * B,
            B,
            B,
            B
        );



        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY + 4.0f * B,
            pataDerZ - 2.25f * B,
            B,
            B,
            B
        );
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY + 4.0f * B,
            pataDerZ - 3.25f * B,
            B,
            B,
            B
        );

        // CRESTA VERDE OSCURO
        dibujarCubo(
            modelLoc,
            VAOverdeOscuro,
            VAOlineas,
            colorLineaLoc,

            pataDerX,
            pataDerY+ 9.0f*B,
            pataDerZ- 2.25f * B,

            B,
            B,
            B
        );
        dibujarCubo(
            modelLoc,
            VAOverdeOscuro,
            VAOlineas,
            colorLineaLoc,

            pataDerX,
            pataDerY + 9.0f * B,
            pataDerZ - 3.25f * B,

            B,
            B,
            B
        );

        dibujarCubo(
            modelLoc,
            VAOverdeOscuro,
            VAOlineas,
            colorLineaLoc,

            pataDerX - B,
            pataDerY + 9.0f * B,
            pataDerZ - 2.25f * B,

            B,
            B,
            B
        );
        dibujarCubo(
            modelLoc,
            VAOverdeOscuro,
            VAOlineas,
            colorLineaLoc,

            pataDerX-B,
            pataDerY + 9.0f * B,
            pataDerZ - 3.25f * B,

            B,
            B,
            B
        );


        dibujarCubo(
            modelLoc,
            VAOverdeOscuro,
            VAOlineas,
            colorLineaLoc,

            pataDerX,
            pataDerY + 7.0f * B,
            pataDerZ - 2.25f * B,

            B,
            B,
            B
        );
        dibujarCubo(
            modelLoc,
            VAOverdeOscuro,
            VAOlineas,
            colorLineaLoc,

            pataDerX,
            pataDerY + 7.0f * B,
            pataDerZ - 3.25f * B,

            B,
            B,
            B
        );

        dibujarCubo(
            modelLoc,
            VAOverdeOscuro,
            VAOlineas,
            colorLineaLoc,

            pataDerX - B,
            pataDerY + 7.0f * B,
            pataDerZ - 2.25f * B,

            B,
            B,
            B
        );
        dibujarCubo(
            modelLoc,
            VAOverdeOscuro,
            VAOlineas,
            colorLineaLoc,

            pataDerX - B,
            pataDerY + 7.0f * B,
            pataDerZ - 3.25f * B,

            B,
            B,
            B
        );

        dibujarCubo(
            modelLoc,
            VAOverdeOscuro,
            VAOlineas,
            colorLineaLoc,

            pataDerX - B,
            pataDerY + 5.0f * B,
            pataDerZ - 2.25f * B,

            B,
            B,
            B
        );
        dibujarCubo(
            modelLoc,
            VAOverdeOscuro,
            VAOlineas,
            colorLineaLoc,

            pataDerX - B,
            pataDerY + 5.0f * B,
            pataDerZ - 3.25f * B,

            B,
            B,
            B
        );


        dibujarCubo(
            modelLoc,
            VAOverdeOscuro,
            VAOlineas,
            colorLineaLoc,

            pataDerX - 2.0f*B,
            pataDerY + 4.0f * B,
            pataDerZ - 2.25f * B,

            B,
            B,
            B
        );
        dibujarCubo(
            modelLoc,
            VAOverdeOscuro,
            VAOlineas,
            colorLineaLoc,

            pataDerX - 2.0f*B,
            pataDerY + 4.0f * B,
            pataDerZ - 3.25f * B,

            B,
            B,
            B
        );


        dibujarCubo(
            modelLoc,
            VAOverdeOscuro,
            VAOlineas,
            colorLineaLoc,

            pataDerX - 2.0f * B,
            pataDerY + 3.0f * B,
            pataDerZ - 2.25f * B,

            B,
            B,
            B
        );
        dibujarCubo(
            modelLoc,
            VAOverdeOscuro,
            VAOlineas,
            colorLineaLoc,

            pataDerX - 2.0f * B,
            pataDerY + 3.0f * B,
            pataDerZ - 3.25f * B,

            B,
            B,
            B
        );

        // CUBO DE ABAJO
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,

            pataDerX - 2.75f * B,   // antes -3.0B
            pataDerY + B,
            pataDerZ - 1.25f * B,

            B / 2.0f,   // mitad en X
            B,          // Y completo
            B
        );

        // CUBO DE ARRIBA - ALTURA 2/3
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 2.75f * B,
            pataDerY + 1.8333f * B,
            pataDerZ - 1.25f * B,

            B / 2.0f,
            B* (2.0f / 3.0f),
            B
        );
        // CUBO DE ABAJO
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,

            pataDerX - 2.75f * B,   // antes -3.0B
            pataDerY + B,
            pataDerZ - 4.25f * B,

            B / 2.0f,   // mitad en X
            B,          // Y completo
            B
        );

        // CUBO DE ARRIBA - ALTURA 2/3
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - 2.75f * B,
            pataDerY + 1.8333f * B,
            pataDerZ - 4.25f * B,

            B / 2.0f,
            B* (2.0f / 3.0f),
            B
        );
        //    regresando a la cresta verde --------------------------------
        dibujarCubo(
            modelLoc,
            VAOverdeOscuro,
            VAOlineas,
            colorLineaLoc,

            pataDerX - 3.0f * B,
            pataDerY + 2.0f * B,
            pataDerZ - 2.25f * B,

            B,
            B,
            B
        );
        dibujarCubo(
            modelLoc,
            VAOverdeOscuro,
            VAOlineas,
            colorLineaLoc,

            pataDerX - 3.0f * B,
            pataDerY + 2.0f * B,
            pataDerZ - 3.25f * B,

            B,
            B,
            B
        );


        dibujarCubo(
            modelLoc,
            VAOverdeOscuro,
            VAOlineas,
            colorLineaLoc,

            pataDerX - 3.0f * B,
            pataDerY + B,
            pataDerZ - 2.25f * B,

            B,
            B,
            B
        );
        dibujarCubo(
            modelLoc,
            VAOverdeOscuro,
            VAOlineas,
            colorLineaLoc,

            pataDerX - 3.0f * B,
            pataDerY + B,
            pataDerZ - 3.25f * B,

            B,
            B,
            B
        );




        /////==============================
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 7.0f * B,
            pataDerY + 7.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 7.0f * B,
            pataDerY + 7.0f * B,
            pataDerZ - 2.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 7.0f * B,
            pataDerY + 7.0f * B,
            pataDerZ - 3.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 7.0f * B,
            pataDerY + 7.0f * B,
            pataDerZ - 4.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 7.0f * B,
            pataDerY + 8.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 7.0f * B,
            pataDerY + 8.0f * B,
            pataDerZ - 2.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 7.0f * B,
            pataDerY + 8.0f * B,
            pataDerZ - 3.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 7.0f * B,
            pataDerY + 8.0f * B,
            pataDerZ - 4.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 6.0f * B,
            pataDerY + 9.0f * B,
            pataDerZ - 2.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 6.0f * B,
            pataDerY + 9.0f * B,
            pataDerZ - 3.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );
        //================================hocico alto
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 7.0f * B,
            pataDerY + 10.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 7.0f * B,
            pataDerY + 10.0f * B,
            pataDerZ - 2.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 7.0f * B,
            pataDerY + 10.0f * B,
            pataDerZ - 3.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 7.0f * B,
            pataDerY + 10.0f * B,
            pataDerZ - 4.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );


        //nariz ----------------------------------------------------

// CUBO 1
// CUBO 1
        dibujarCubo(//-------------   
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 7.0f * B,
            pataDerY + 9.0f * B,
            pataDerZ - 1.00f * B,
            B,
            B,
            B / 2.0f
        );

        // CUBO 2
        dibujarCubo(//-------------   
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 7.0f * B,
            pataDerY + 9.0f * B,
            pataDerZ - 2.50f * B,
            B,
            B,
            B / 2.0f
        );

        // CUBO 3
        dibujarCubo(//-------------   
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 7.0f * B,
            pataDerY + 9.0f * B,
            pataDerZ - 3.00f * B,
            B,
            B,
            B / 2.0f
        );

        // CUBO 3
// CUBO 4
        dibujarCubo(//-------------   
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 7.0f * B,
            pataDerY + 9.0f * B,
            pataDerZ - 4.50f * B,
            B,
            B,
            B / 2.0f
        );

        // ojos blancos derecha

        dibujarCubo(modelLoc, VAOblanco, VAOlineas, colorLineaLoc,
            pataDerX + 4.0f * B,
            pataDerY + 8.0f*B,
            pataDerZ - 1.250f * B,
            B, B, B);
        dibujarCubo(modelLoc, VAOblanco, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY + 8.0f * B,
            pataDerZ - 1.250f * B,
            B, B, B);

        dibujarCubo(modelLoc, VAOblanco, VAOlineas, colorLineaLoc,
            pataDerX + 4.0f * B,
            pataDerY + 9.0f * B,
            pataDerZ - 1.250f * B,
            B, B, B);
        dibujarCubo(modelLoc, VAOblanco, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY + 9.0f * B,
            pataDerZ - 1.250f * B,
            B, B, B);

        // ojos blancos izquierda

        dibujarCubo(modelLoc, VAOblanco, VAOlineas, colorLineaLoc,
            pataDerX + 4.0f * B,
            pataDerY + 8.0f * B,
            pataDerZ - 4.250f * B,
            B, B, B);
        dibujarCubo(modelLoc, VAOblanco, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY + 8.0f * B,
            pataDerZ - 4.250f * B,
            B, B, B);

        dibujarCubo(modelLoc, VAOblanco, VAOlineas, colorLineaLoc,
            pataDerX + 4.0f * B,
            pataDerY + 9.0f * B,
            pataDerZ - 4.250f * B,
            B, B, B);
        dibujarCubo(modelLoc, VAOblanco, VAOlineas, colorLineaLoc,
            pataDerX + 3.0f * B,
            pataDerY + 9.0f * B,
            pataDerZ - 4.250f * B,
            B, B, B);

        // PUPILA NEGRA
        dibujarCubo(
            modelLoc, VAOnegro, VAOlineas, colorLineaLoc,
            pataDerX + 4.0f * B,
            pataDerY + 8.5f * B,
            pataDerZ - 1.2f * B,
            B ,
            B ,
            B 
        );
        dibujarCubo(
            modelLoc, VAOnegro, VAOlineas, colorLineaLoc,
            pataDerX + 4.0f * B,
            pataDerY + 8.5f * B,
            pataDerZ - 4.3f * B,
            B,
            B,
            B
        );

        //          panza clara 
        dibujarCubo(modelLoc, VAOverdeClaro, VAOlineas, colorLineaLoc,
            pataDerX + 3 * B,
            pataDerY,
            pataDerZ - 2.250f * B,
            B, B, B);

        dibujarCubo(modelLoc, VAOverdeClaro, VAOlineas, colorLineaLoc,
            pataDerX + 3 * B,
            pataDerY,
            pataDerZ - 3.250f * B,
            B, B, B);

        dibujarCubo(modelLoc, VAOverdeClaro, VAOlineas, colorLineaLoc,
            pataDerX + 3 * B,
            pataDerY +B,
            pataDerZ - 2.250f * B,
            B, B, B);

        dibujarCubo(modelLoc, VAOverdeClaro, VAOlineas, colorLineaLoc,
            pataDerX + 3 * B,
            pataDerY +B,
            pataDerZ - 3.250f * B,
            B, B, B);
        dibujarCubo(modelLoc, VAOverdeClaro, VAOlineas, colorLineaLoc,
            pataDerX + 3 * B,
            pataDerY + 2.0f*B,
            pataDerZ - 2.250f * B,
            B, B, B);

        dibujarCubo(modelLoc, VAOverdeClaro, VAOlineas, colorLineaLoc,
            pataDerX + 3 * B,
            pataDerY + 2.0f* B,
            pataDerZ - 3.250f * B,
            B, B, B);

        dibujarCubo(modelLoc, VAOverdeClaro, VAOlineas, colorLineaLoc,
            pataDerX + 3 * B,
            pataDerY + 3.0f * B,
            pataDerZ - 2.250f * B,
            B, B, B);

        dibujarCubo(modelLoc, VAOverdeClaro, VAOlineas, colorLineaLoc,
            pataDerX + 3 * B,
            pataDerY + 3.0f * B,
            pataDerZ - 3.250f * B,
            B, B, B);

        // HOCICO - MEDIO CUBO 1
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,

            pataDerX + 4.0f * B,
            pataDerY + 5.75f * B,   // mitad inferior
            pataDerZ - 1.25f * B,

            B,
            B / 2.0f,
            B
        );

        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,

            pataDerX + 5.0f * B,
            pataDerY + 5.65f * B,   // mitad inferior
            pataDerZ - 1.25f * B,

            B,
            B / 2.0f,
            B
        );
        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 6.0f * B,
            pataDerY + 6.0f * B,
            pataDerZ - 2.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 6.0f * B,
            pataDerY + 6.0f * B,
            pataDerZ - 1.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 6.0f * B,
            pataDerY + 6.0f * B,
            pataDerZ - 3.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        dibujarCubo(//-------------  
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + 6.0f * B,
            pataDerY + 6.0f * B,
            pataDerZ - 4.25f * B,
            B,   // más corta
            B,   // más baja
            B
        );

        // HOCICO - MEDIO CUBO 1
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,

            pataDerX + 4.0f * B,
            pataDerY + 5.75f * B,   // mitad inferior
            pataDerZ - 4.25f * B,

            B,
            B / 2.0f,
            B
        );

        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,

            pataDerX + 5.0f * B,
            pataDerY + 5.65f * B,   // mitad inferior
            pataDerZ - 4.25f * B,

            B,
            B / 2.0f,
            B
        );
        // LENGUA NARANJA - 1/4 DE PROFUNDIDAD HACIA +Z
        dibujarCubo(
            modelLoc, VAOnaranja, VAOlineas, colorLineaLoc,

            pataDerX + 6.0f * B,
            pataDerY + 6.0f * B,
            pataDerZ - 0.75f * B,   // pegada hacia +Z, más cerca de ti

            B,
            B,
            B / 4.0f                 // solo 1/4 de profundidad
        );
        //// HOCICO - MEDIO CUBO 2
        //dibujarCubo(
        //    modelLoc, VAO, VAOlineas, colorLineaLoc,

        //    X,
        //    Y - 0.25f * B,   // mantiene la mitad de abajo
        //    Z,

        //    B,
        //    B / 2.0f,        // mitad de altura
        //    B
        //);

        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }


    // ==========================================
    // LIBERAR MEMORIA
    // ==========================================

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glDeleteVertexArrays(1, &VAOnaranja);
    glDeleteBuffers(1, &VBOnaranja);

    glDeleteVertexArrays(1, &VAOlineas);
    glDeleteBuffers(1, &VBOlineas);


    glfwTerminate();

    return EXIT_SUCCESS;
}


// ==========================================
// INPUTS
// ==========================================

void Inputs(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
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


// ==========================================
// FUNCION DIBUJAR CUBO
// ==========================================

void dibujarCubo(
    GLint modelLoc,
    GLuint VAO,
    GLuint VAOlineas,
    GLint colorLineaLoc,
    float x, float y, float z,
    float sx, float sy, float sz
)
{
    glm::mat4 model = glm::mat4(1.0f);


    model = glm::translate(
        model,
        glm::vec3(x, y, z)
    );

    model = glm::scale(
        model,
        glm::vec3(sx, sy, sz)
    );


    glUniformMatrix4fv(
        modelLoc,
        1,
        GL_FALSE,
        glm::value_ptr(model)
    );


    // ==========================================
    // CARAS
    // ==========================================

    glUniform1i(
        colorLineaLoc,
        GL_FALSE
    );

    glBindVertexArray(VAO);

    glDrawArrays(
        GL_TRIANGLES,
        0,
        36
    );


    // ==========================================
    // ARISTAS NEGRAS
    // ==========================================

    glUniform1i(
        colorLineaLoc,
        GL_TRUE
    );

    glBindVertexArray(VAOlineas);

    glLineWidth(2.0f);

    glDrawArrays(
        GL_LINES,
        0,
        24
    );


    glBindVertexArray(0);

    glUniform1i(
        colorLineaLoc,
        GL_FALSE
    );
}