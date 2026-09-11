//Previo 4
//González Jiménez Victor Yotecatl
//Fecha de entrega: 08 - 09 - 2026
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
    // 12 ARISTAS DEL CUBO
    // ==========================================

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
        // PRIMERA PARED
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


        // ==========================================
        // SEGUNDA PARED
        // ==========================================

        float pared2Z =
            pataDerZ - 1.25f * B;


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


// ==========================================
// GARRAS NARANJAS - PUNTA DEL PIE
// ==========================================

// Garra de la primera pared
        dibujarCubo(
            modelLoc,
            VAOnaranja,
            VAOlineas,
            colorLineaLoc,

            pataDerX + 1.625f * B,   // adelante, en +X
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

            pataDerX + 1.625f * B,   // misma punta
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


        //// ==========================================
        //// CAPA INTERMEDIA
        //// GROSOR = 1/4 DE CUBO
        //// ==========================================

        //float interZ =
        //    pataDerZ - 0.625f * B;


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
            interZ- 4.250f * B,
            B, B, B / 4.0f
        );


        // 3
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY - B,
            interZ- 4.250f * B,
            B, B, B / 4.0f
        );


        // 4
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY - 2.0f * B,
            interZ- 4.250f * B,
            B, B, B / 4.0f
        );


        // 5
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX,
            pataDerY - 3.0f * B,
            interZ- 4.250f * B,
            B, B, B / 4.0f
        );


        // 6
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY - 3.0f * B,
            interZ- 4.250f * B,
            B, B, B / 4.0f
        );


        // 7
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY,
            interZ- 4.250f * B,
            B, B, B / 4.0f
        );


        // 8
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY,
            interZ- 4.250f * B,
            B, B, B / 4.0f
        );


        // 9
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX + B,
            pataDerY - B,
            interZ- 4.250f * B,
            B, B, B / 4.0f
        );


        // 10
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY - B,
            interZ- 4.250f * B,
            B, B, B / 4.0f
        );


        // 11
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY + B,
            interZ- 4.250f * B,
            B, B, B / 4.0f
        );


        // 12
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY - 3.0f * B,
            interZ- 4.250f * B,
            B, B, B / 4.0f
        );


        // 13 - Medio cubo
        dibujarCubo(
            modelLoc, VAO, VAOlineas, colorLineaLoc,
            pataDerX - B,
            pataDerY - 2.25f * B,
            interZ- 4.250f * B,
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

            pataDerX + 1.625f * B,   // adelante, en +X
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

            pataDerX + 1.625f * B,   // misma punta
            pataDerY - 3.0f * B,
            pared2Z - 4.250f * B,                  // segunda pared

            B / 4.0f,
            B,
            B
        );

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