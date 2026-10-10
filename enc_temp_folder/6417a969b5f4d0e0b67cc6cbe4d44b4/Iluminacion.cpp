//Prárctica 6
//González Jiménez Victor Yotecatl
//Fecha de entrega: 27 - 09 - 2026
//Número de cuenta: 31317374-3

// Std. Includes
#include <string>
#include <vector>
#include <iostream>

// GLEW
#include <GL/glew.h>

// GLFW
#include <GLFW/glfw3.h>

// GL includes
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Other Libs
#include "SOIL2/SOIL2.h"
#include "stb_image.h"


// ============================================================ textures
// VENTANA
// ============================================================

const GLuint WIDTH = 800;
const GLuint HEIGHT = 600;

int SCREEN_WIDTH;
int SCREEN_HEIGHT;


// ============================================================
// PROTOTIPOS
// ============================================================ LIBRO NUEVO

void BuildSphere(
    std::vector<float>& vertices,
    std::vector<unsigned int>& indices,
    float radius,
    unsigned int sectors,
    unsigned int stacks
);

void KeyCallback(
    GLFWwindow* window,
    int key,
    int scancode,
    int action,
    int mode
);

void DoMovement();


// ============================================================
// CAMARA
// ============================================================

Camera camera(
    glm::vec3(0.0f, 0.0f, 3.0f)
);

bool keys[1024];

GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;


// ============================================================
// AJUSTES DE LA ESCENA Load
// ============================================================

// ------------------------------------------------------------
// PISO
// ------------------------------------------------------------

const GLfloat FLOOR_Y = -1.0f;


// ------------------------------------------------------------
// PERRO
//
// Cambiar DOG_Y para subirlo o bajarlo.
// ------------------------------------------------------------

const GLfloat DOG_X = 0.0f;
const GLfloat DOG_Y = -0.60f;
const GLfloat DOG_Z = 0.0f;


// ------------------------------------------------------------
// SOFA
// ------------------------------------------------------------

const GLfloat SOFA_X = 0.0f;
const GLfloat SOFA_Y = -0.95f;
const GLfloat SOFA_Z = -2.0f;

const GLfloat SOFA_SCALE = 0.009f;


// ------------------------------------------------------------
// LIBREROS
// ------------------------------------------------------------

const float BOOK_SCALE = 0.58f; //---------------- ultima coonstante agregada

const GLfloat BOOKCASE_SCALE = 0.20f;

// Distancia de las paredes laterales al centro.
// Menor valor = habitación más estrecha.
const GLfloat WALL_X = 3.2f;

// Separación entre libreros laterales.
const GLfloat BOOKCASE_DISTANCE = 1.4f;

// Altura de los libreros.
const GLfloat BOOKCASE_Y = -1.0f;

// Posición de la pared del fondo.
const GLfloat BACK_WALL_Z = -5.0f;

// Separación de los libreros del fondo.
const GLfloat BACK_BOOKCASE_DISTANCE = 1.4f;

// ============================================================
// MESA
// ============================================================

// Posicion de la mesa
const GLfloat TABLE_X = 0.0f;
const GLfloat TABLE_Y = -1.25f;
const GLfloat TABLE_Z = 1.4f;

// Tamaño de la mesa
const GLfloat TABLE_SCALE = 0.006f;
// ============================================================
// LAMPARA
// ============================================================


const GLfloat LAMP_X = 0.0f;
const GLfloat LAMP_Y = 1.0f;
const GLfloat LAMP_Z = -0.5f;

const GLfloat LAMP_SCALE = 0.002f;

// ============================================================
// LIBROS
// ============================================================

const GLfloat BOOKS_X = 0.4f;
const GLfloat BOOKS_Y = -0.53f;
const GLfloat BOOKS_Z = 1.4f;

const GLfloat BOOKS_SCALE = 0.009f;

// ============================================================
// SOFA 2 - PHOENIX
// ============================================================

const GLfloat SOFA2_X = -8.5f;
const GLfloat SOFA2_Y = -0.95f;
const GLfloat SOFA2_Z = -11.0f;

const GLfloat SOFA2_SCALE = 0.030f;

// ============================================================ Model 
// ORBITA SOL - LUNA
// ============================================================

float orbitAngle = 90.0f;

const float ORBIT_RADIUS = 8.0f;

const float ORBIT_CENTER_X = 0.0f;
const float ORBIT_CENTER_Y = 4.0f;
const float ORBIT_CENTER_Z = -2.0f;

// ============================================================
// MAIN
// ============================================================

int main()
{
    // ========================================================
    // INICIALIZAR GLFW
    // ========================================================

    glfwInit();

    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MAJOR,
        3
    );

    glfwWindowHint(
        GLFW_CONTEXT_VERSION_MINOR,
        3
    );

    glfwWindowHint(
        GLFW_OPENGL_PROFILE,
        GLFW_OPENGL_CORE_PROFILE
    );

    glfwWindowHint(
        GLFW_OPENGL_FORWARD_COMPAT,
        GL_TRUE
    );

    glfwWindowHint(
        GLFW_RESIZABLE,
        GL_FALSE
    );


    // ========================================================
    // CREAR VENTANA
    // ========================================================

    GLFWwindow* window = glfwCreateWindow(
        WIDTH,
        HEIGHT,
        "Victor Yotecatl",
        nullptr,
        nullptr
    );


    if (window == nullptr)
    {
        std::cout
            << "Failed to create GLFW window"
            << std::endl;

        glfwTerminate();

        return EXIT_FAILURE;
    }


    glfwMakeContextCurrent(window);


    glfwGetFramebufferSize(
        window,
        &SCREEN_WIDTH,
        &SCREEN_HEIGHT
    );


    // ========================================================
    // CALLBACK DE TECLADO
    // ========================================================

    glfwSetKeyCallback(
        window,
        KeyCallback
    );


    // ========================================================
    // NO USAMOS EL MOUSE PARA MOVER LA CAMARA
    // ========================================================

    // No se utiliza:
    //
    // glfwSetCursorPosCallback(...)
    //
    // Las flechas controlan la dirección de la cámara.


    // ========================================================
    // INICIALIZAR GLEW
    // ========================================================

    glewExperimental = GL_TRUE;


    if (GLEW_OK != glewInit())
    {
        std::cout
            << "Failed to initialize GLEW"
            << std::endl;

        return EXIT_FAILURE;
    }


    // ========================================================
    // VIEWPORT
    // ========================================================

    glViewport(
        0,
        0,
        SCREEN_WIDTH,
        SCREEN_HEIGHT
    );


    // ========================================================
    // DEPTH TEST
    // ========================================================

    glEnable(GL_DEPTH_TEST);


    // ========================================================
    // SHADER
    // ========================================================

    Shader shader(
        "Shader/modelLoading.vs",
        "Shader/modelLoading.frag"
    );


    // Shader de la Luna blanca. Se conserva tal como funcionaba.
    Shader sphereShader(
        "Shader/lamp.vs",
        "Shader/lamp.frag"
    );

    // Shader exclusivo para la esfera texturizada del Sol.
    // Usa archivos propios para asegurar que la matriz model
    // se aplique a la traslacion del Sol.
    Shader sunShader(
        "Shader/sun.vs",
        "Shader/sun.frag"
    );
    Shader moonShader(
        "Shader/moon.vs",
        "Shader/moon.frag"
    );


    // ========================================================
    // CREAR PISO BEIGE
    //
    // Plano horizontal formado por dos triángulos.
    // ======================================================== sunTexture  sunLight

    GLfloat floorVertices[] =
    {
        // Posicion                  // Normal            // UV
        -20.0f, FLOOR_Y, -20.0f,     0.0f, 1.0f, 0.0f,    0.0f,  0.0f,
         20.0f, FLOOR_Y, -20.0f,     0.0f, 1.0f, 0.0f,   12.0f,  0.0f,
         20.0f, FLOOR_Y,  20.0f,     0.0f, 1.0f, 0.0f,   12.0f, 12.0f,

        -20.0f, FLOOR_Y, -20.0f,     0.0f, 1.0f, 0.0f,    0.0f,  0.0f,
         20.0f, FLOOR_Y,  20.0f,     0.0f, 1.0f, 0.0f,   12.0f, 12.0f,
        -20.0f, FLOOR_Y,  20.0f,     0.0f, 1.0f, 0.0f,    0.0f, 12.0f
    };


    GLuint floorVAO;
    GLuint floorVBO;


    glGenVertexArrays(
        1,
        &floorVAO
    );


    glGenBuffers(
        1,
        &floorVBO
    );


    glBindVertexArray(
        floorVAO
    );


    glBindBuffer(
        GL_ARRAY_BUFFER,
        floorVBO
    );


    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(floorVertices),
        floorVertices,
        GL_STATIC_DRAW
    );


    // Posicion
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GLfloat),
        (GLvoid*)0
    );
    glEnableVertexAttribArray(0);

    // Normal
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GLfloat),
        (GLvoid*)(3 * sizeof(GLfloat))
    );
    glEnableVertexAttribArray(1);

    // Coordenadas de textura
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(GLfloat),
        (GLvoid*)(6 * sizeof(GLfloat))
    );
    glEnableVertexAttribArray(2);


    glBindVertexArray(0);


    // ========================================================
    // CREAR CUADRICULA
    //
    // Se coloca ligeramente ARRIBA del piso para evitar
    // Z-fighting.
    // ========================================================

    std::vector<GLfloat> gridVertices;


    const int gridSize = 20;


    // La cuadrícula está apenas por encima del piso.
    const GLfloat GRID_Y =
        FLOOR_Y + 0.002f;


    for (int i = -gridSize; i <= gridSize; i++)
    {
        // ----------------------------------------------------
        // LINEA PARALELA AL EJE Z
        // ----------------------------------------------------

        gridVertices.push_back(
            (GLfloat)i
        );

        gridVertices.push_back(
            GRID_Y
        );

        gridVertices.push_back(
            (GLfloat)-gridSize
        );


        gridVertices.push_back(
            (GLfloat)i
        );

        gridVertices.push_back(
            GRID_Y
        );

        gridVertices.push_back(
            (GLfloat)gridSize
        );


        // ----------------------------------------------------
        // LINEA PARALELA AL EJE X
        // ----------------------------------------------------

        gridVertices.push_back(
            (GLfloat)-gridSize
        );

        gridVertices.push_back(
            GRID_Y
        );

        gridVertices.push_back(
            (GLfloat)i
        );


        gridVertices.push_back(
            (GLfloat)gridSize
        );

        gridVertices.push_back(
            GRID_Y
        );

        gridVertices.push_back(
            (GLfloat)i
        );
    }


    // ========================================================
    // VAO Y VBO DE LA CUADRICULA
    // ========================================================

    GLuint gridVAO;
    GLuint gridVBO;


    glGenVertexArrays(
        1,
        &gridVAO
    );


    glGenBuffers(
        1,
        &gridVBO
    );


    glBindVertexArray(
        gridVAO
    );


    glBindBuffer(
        GL_ARRAY_BUFFER,
        gridVBO
    );


    glBufferData(
        GL_ARRAY_BUFFER,
        gridVertices.size() * sizeof(GLfloat),
        gridVertices.data(),
        GL_STATIC_DRAW
    );


    glEnableVertexAttribArray(0);


    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(GLfloat),
        (GLvoid*)0
    );


    glBindVertexArray(0);


    // ========================================================
    // PROYECCION
    // ========================================================

    glm::mat4 projection =
        glm::perspective(
            camera.GetZoom(),
            (float)SCREEN_WIDTH /
            (float)SCREEN_HEIGHT,
            0.1f,
            100.0f
        );


    // ========================================================
    // CARGAR MODELOS
    // ======================================================== books

    Model dog(
        (char*)"Models/RedDog.obj"
    );


    Model sofa(
        (char*)"Models/3DSTYLISH-fsb001.obj"
    );
    Model sofa2(
        (char*)"Models/Sofa_Phoenix_OBJ.obj"
    );

    Model bookcase(
        (char*)"Models/bookshelf_OBJ.obj"
    );

    Model table((char*)"Models/diningtable.obj");
    Model lamp((char*)"Models/pendant light Wooden LED_focos_amarillos_CORREGIDO.obj");
    Model books((char*)"Models/Hard_Cover_Books_OBJ.obj");

    Model book(
        (char*)"Models/1book.obj"
    );

    // ========================================================
    // CREAR GEOMETRIA DE LAS ESFERAS
    // ========================================================

    std::vector<float> sphereVertices;
    std::vector<unsigned int> sphereIndices;

    BuildSphere(
        sphereVertices,
        sphereIndices,
        1.0f,
        36,
        18
    );

    GLuint sphereVAO;
    GLuint sphereVBO;
    GLuint sphereEBO;

    glGenVertexArrays(1, &sphereVAO);
    glGenBuffers(1, &sphereVBO);
    glGenBuffers(1, &sphereEBO);

    glBindVertexArray(sphereVAO);

    glBindBuffer(
        GL_ARRAY_BUFFER,
        sphereVBO
    );

    glBufferData(
        GL_ARRAY_BUFFER,
        sphereVertices.size() * sizeof(float),
        sphereVertices.data(),
        GL_STATIC_DRAW
    );

    glBindBuffer(
        GL_ELEMENT_ARRAY_BUFFER,
        sphereEBO
    );

    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sphereIndices.size() * sizeof(unsigned int),
        sphereIndices.data(),
        GL_STATIC_DRAW
    );

    // Posicion
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(0);

    // Normal
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)(3 * sizeof(float))
    );
    glEnableVertexAttribArray(1);

    // Coordenadas UV preparadas para texturas posteriores
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)(6 * sizeof(float))
    );
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);


    // ========================================================
    // CARGAR TEXTURA DEL SOL
    //
    // Solo cambia la apariencia de la esfera.
    // NO modifica sunPosition ni sunLight.position.
    // ========================================================

    GLuint sunTexture =
        SOIL_load_OGL_texture(
            "images/sol.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS |
            SOIL_FLAG_INVERT_Y
        );

    if (sunTexture == 0)
    {
        std::cout
            << "ERROR cargando images/sol.png: "
            << SOIL_last_result()
            << std::endl;
    }

    glBindTexture(
        GL_TEXTURE_2D,
        sunTexture
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S,
        GL_REPEAT
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T,
        GL_REPEAT
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR_MIPMAP_LINEAR
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_LINEAR
    );

    glBindTexture(
        GL_TEXTURE_2D,
        0
    );
    GLuint moonTexture =
        SOIL_load_OGL_texture(
            "images/luna.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS |
            SOIL_FLAG_INVERT_Y
        );

    if (moonTexture == 0)
    {
        std::cout
            << "ERROR cargando images/luna.png: "
            << SOIL_last_result()
            << std::endl;
    }

    glBindTexture(
        GL_TEXTURE_2D,
        moonTexture
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S,
        GL_REPEAT
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T,
        GL_REPEAT
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR_MIPMAP_LINEAR
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_LINEAR
    );

    glBindTexture(
        GL_TEXTURE_2D,
        0
    );

    // ========================================================
    // CARGAR TEXTURA DE LA ALFOMBRA
    // ========================================================

    GLuint floorTexture =
        SOIL_load_OGL_texture(
            "images/alfombra.png",
            SOIL_LOAD_AUTO,
            SOIL_CREATE_NEW_ID,
            SOIL_FLAG_MIPMAPS |
            SOIL_FLAG_INVERT_Y
        );

    if (floorTexture == 0)
    {
        std::cout
            << "ERROR cargando images/alfombra.png: "
            << SOIL_last_result()
            << std::endl;
    }

    glBindTexture(
        GL_TEXTURE_2D,
        floorTexture
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S,
        GL_REPEAT
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T,
        GL_REPEAT
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR_MIPMAP_LINEAR
    );

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_LINEAR
    );

    glBindTexture(
        GL_TEXTURE_2D,
        0
    );


    // ========================================================
    // GAME LOOP
    // ========================================================

    while (!glfwWindowShouldClose(window))
    {
        // ====================================================
        // TIEMPO ENTRE FRAMES
        // ====================================================

        GLfloat currentFrame =
            glfwGetTime();


        deltaTime =
            currentFrame -
            lastFrame;


        lastFrame =
            currentFrame;


        // ====================================================
        // EVENTOS
        // ====================================================

        glfwPollEvents();


        // ====================================================
        // MOVIMIENTO DE CAMARA
        // ====================================================

        DoMovement();


        // ====================================================
        // FONDO negro
        //
        // Este es el color que aparecerá por encima del piso.
        // ====================================================

        glClearColor(
            0.0f,
            0.0f,
            0.0f,
            1.0f
        );


        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT
        );


        // ====================================================
        // ACTIVAR SHADER
        // ====================================================

        shader.Use();
        // ============================================================
// CALCULAR POSICION DEL SOL Y LA LUNA
// ============================================================

        float angleRad =
            glm::radians(
                orbitAngle
            );

        // Un solo vector orbital controla a los dos cuerpos.
        // La Luna siempre queda exactamente 180 grados opuesta al Sol.
        glm::vec3 orbitCenter(
            ORBIT_CENTER_X,
            ORBIT_CENTER_Y,
            ORBIT_CENTER_Z
        );

        glm::vec3 orbitOffset(
            ORBIT_RADIUS * cos(angleRad),
            ORBIT_RADIUS * sin(angleRad),
            0.0f
        );

        glm::vec3 sunPosition =
            orbitCenter + orbitOffset;

        glm::vec3 moonPosition =
            orbitCenter - orbitOffset;
        // ============================================================
// POSICION DE LA CAMARA
// ============================================================

        glUniform3f(
            glGetUniformLocation(
                shader.Program,
                "viewPos"
            ),
            camera.GetPosition().x,
            camera.GetPosition().y,
            camera.GetPosition().z
        );

        // ============================================================
        // SOL - LUZ CALIDA
        // ============================================================

        glUniform3f(
            glGetUniformLocation(
                shader.Program,
                "sunLight.ambient"
            ),
            0.20f,
            0.15f,
            0.07f
        );

        glUniform3f(
            glGetUniformLocation(
                shader.Program,
                "sunLight.position"
            ),
            sunPosition.x,
            sunPosition.y,
            sunPosition.z
        );

        glUniform3f(
            glGetUniformLocation(
                shader.Program,
                "sunLight.diffuse"
            ),
            1.05f,
            0.65f,
            0.20f
        );

        glUniform3f(
            glGetUniformLocation(
                shader.Program,
                "sunLight.specular"
            ),
            0.75f,
            0.50f,
            0.20f
        );


        // ============================================================ LUNA BLANCA
        // LUNA - LUZ FRIA
        // ============================================================

        glUniform3f(
            glGetUniformLocation(
                shader.Program,
                "moonLight.position"
            ),
            moonPosition.x,
            moonPosition.y,
            moonPosition.z
        );

        glUniform3f(
            glGetUniformLocation(
                shader.Program,
                "moonLight.ambient"
            ),
            0.18f,
            0.22f,
            0.30f
        );

        glUniform3f(
            glGetUniformLocation(
                shader.Program,
                "moonLight.diffuse"
            ),
            0.47f,
            0.7f,
            1.15f
        );

        glUniform3f(
            glGetUniformLocation(
                shader.Program,
                "moonLight.specular"
            ),
            0.53f,
            0.75f,
            1.15f
        );


        // ==================================================== 
        // MATRIZ VIEW
        // ====================================================

        glm::mat4 view =
            camera.GetViewMatrix();

        //light.position
        //    light.ambient
        //    light.diffuse
        //    light.specular
        glUniformMatrix4fv(
            glGetUniformLocation(
                shader.Program,
                "projection"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(projection)
        );


        glUniformMatrix4fv(
            glGetUniformLocation(
                shader.Program,
                "view"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(view)
        );


        // ====================================================
        // PISO CON TEXTURA DE ALFOMBRA
        // ====================================================

        shader.Use();

        // El piso usa una textura, no un color solido.
        glUniform1i(
            glGetUniformLocation(
                shader.Program,
                "useSolidColor"
            ),
            GL_FALSE
        );

        glUniform1i(
            glGetUniformLocation(
                shader.Program,
                "hasDiffuseTexture"
            ),
            GL_TRUE
        );

        glUniform3f(
            glGetUniformLocation(
                shader.Program,
                "diffuseColor"
            ),
            1.0f,
            1.0f,
            1.0f
        );

        glActiveTexture(
            GL_TEXTURE0
        );

        glBindTexture(
            GL_TEXTURE_2D,
            floorTexture
        );

        glUniform1i(
            glGetUniformLocation(
                shader.Program,
                "texture_diffuse1"
            ),
            0
        );

        glm::mat4 model(1.0f);

        glUniformMatrix4fv(
            glGetUniformLocation(
                shader.Program,
                "model"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        glBindVertexArray(
            floorVAO
        );

        glDrawArrays(
            GL_TRIANGLES,
            0,
            6
        );

        glBindVertexArray(0);


        //// ====================================================
        //// CUADRICULA NEGRA
        //// ====================================================

        //glUniform1i(
        //    glGetUniformLocation(
        //        shader.Program,
        //        "useSolidColor"
        //    ),
        //    GL_TRUE
        //);


        //glUniform4f(
        //    glGetUniformLocation(
        //        shader.Program, const GLfloat DOG_Y = -0.50f;
        //        "solidColor"
        //    ),
        //    0.0f,
        //    0.0f,
        //    0.0f,
        //    1.0f
        //);


        //model =
        //    glm::mat4(1.0f);


        //glUniformMatrix4fv(
        //    glGetUniformLocation(
        //        shader.Program,
        //        "model"
        //    ),
        //    1,
        //    GL_FALSE,
        //    glm::value_ptr(model)
        //);


        //glBindVertexArray(
        //    gridVAO
        //);


        //glDrawArrays(
        //    GL_LINES,
        //    0,
        //    (GLsizei)(
        //        gridVertices.size() / 3
        //        )
        //);


        //glBindVertexArray(0);


        //glUniform1i(
        //    glGetUniformLocation(
        //        shader.Program,
        //        "hasDiffuseTexture"
        //    ),
        //    GL_FALSE
        //);


        // ====================================================
        // REGRESAR A MODO TEXTURA
        //
        // Desde aquí se dibujan:
        //
        // perro
        // sofá
        // libreros
        //
        // usando sus texturas originales.
        // ====================================================

        glUniform1i(
            glGetUniformLocation(
                shader.Program,
                "useSolidColor"
            ),
            GL_FALSE
        );


        // ====================================================
        // PERRO
        // ====================================================

        model =
            glm::mat4(1.0f);


        model = glm::translate(
            model,
            glm::vec3(
                DOG_X,
                DOG_Y,
                DOG_Z
            )
        );


        glUniformMatrix4fv(
            glGetUniformLocation(
                shader.Program,
                "model"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );


        dog.Draw(shader);


        // ====================================================
        // SOFA
        // ====================================================

        model =
            glm::mat4(1.0f);


        model = glm::translate(
            model,
            glm::vec3(
                SOFA_X,
                SOFA_Y,
                SOFA_Z
            )
        );


        model = glm::scale(
            model,
            glm::vec3(
                SOFA_SCALE,
                SOFA_SCALE,
                SOFA_SCALE
            )
        );


        glUniformMatrix4fv(
            glGetUniformLocation(
                shader.Program,
                "model"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );


        sofa.Draw(shader);
        // ============================================================
        // MESA
        // ============================================================

        model = glm::mat4(1.0f);

        // Posicion de la mesa
        model = glm::translate(
            model,
            glm::vec3(
                TABLE_X,
                TABLE_Y,
                TABLE_Z
            )
        );

        // Tamaño de la mesa
        model = glm::scale(
            model,
            glm::vec3(
                TABLE_SCALE,
                TABLE_SCALE,
                TABLE_SCALE
            )
        );

        glUniformMatrix4fv(
            glGetUniformLocation(shader.Program, "model"),
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        table.Draw(shader);

        // ============================================================
// LAMPARA
// ============================================================

        model = glm::mat4(1.0f);

        // Posicion de la lampara
        model = glm::translate(
            model,
            glm::vec3(
                LAMP_X,
                LAMP_Y,
                LAMP_Z
            )
        );

        // Tamaño de la lampara
        model = glm::scale(
            model,
            glm::vec3(
                LAMP_SCALE,
                LAMP_SCALE,
                LAMP_SCALE
            )
        );

        glUniformMatrix4fv(
            glGetUniformLocation(shader.Program, "model"),
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        lamp.Draw(shader);
        // ============================================================
        // LIBROS
        // ============================================================

        model = glm::mat4(1.0f);

        // Posicion de los libros
        model = glm::translate(
            model,
            glm::vec3(
                BOOKS_X,
                BOOKS_Y,
                BOOKS_Z
            )
        );

        // Tamaño de los libros
        model = glm::scale(
            model,
            glm::vec3(
                BOOKS_SCALE,
                BOOKS_SCALE,
                BOOKS_SCALE
            )
        );

        glUniformMatrix4fv(
            glGetUniformLocation(
                shader.Program,
                "model"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        books.Draw(shader);




        // ============================================================
        // SOFA 2 - PHOENIX
        // ============================================================

        model = glm::mat4(1.0f);

        // Posicion del sofa Phoenix
        model = glm::translate(
            model,
            glm::vec3(
                SOFA2_X,
                SOFA2_Y,
                SOFA2_Z
            )
        );

        // Girar el sofa 180 grados sobre el eje Y
        model = glm::rotate(
            model,
            glm::radians(180.0f),
            glm::vec3(
                0.0f,
                1.0f,
                0.0f
            )
        );

        // Tamaño del sofa Phoenix
        model = glm::scale(
            model,
            glm::vec3(
                SOFA2_SCALE,
                SOFA2_SCALE,
                SOFA2_SCALE
            )
        );

        glUniformMatrix4fv(
            glGetUniformLocation(
                shader.Program,
                "model"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        sofa2.Draw(shader);


        // ====================================================
        // PARED IZQUIERDA DE LIBREROS
        // ====================================================

        for (int i = 0; i < 4; i++)
        {
            float zPos =
                0.5f -
                (i * BOOKCASE_DISTANCE);


            // ------------------------------------------------
            // LIBRERO
            // ------------------------------------------------

            model =
                glm::mat4(1.0f);

            model = glm::translate(
                model,
                glm::vec3(
                    -WALL_X,
                    BOOKCASE_Y,
                    zPos
                )
            );

            model = glm::rotate(
                model,
                glm::radians(90.0f),
                glm::vec3(
                    0.0f,
                    1.0f,
                    0.0f
                )
            );

            model = glm::scale(
                model,
                glm::vec3(
                    BOOKCASE_SCALE,
                    BOOKCASE_SCALE,
                    BOOKCASE_SCALE
                )
            );

            glUniformMatrix4fv(
                glGetUniformLocation(
                    shader.Program,
                    "model"
                ),
                1,
                GL_FALSE,
                glm::value_ptr(model)
            );

            bookcase.Draw(shader);


            // ------------------------------------------------
            // LIBROS - REPISA INFERIOR
            // PARED IZQUIERDA moonli
            // ------------------------------------------------

            model =
                glm::mat4(1.0f);

            model = glm::translate(
                model,
                glm::vec3(
                    -2.90f,
                    -0.035f,
                    zPos
                )
            );

            model = glm::rotate(
                model,
                glm::radians(180.0f),
                glm::vec3(
                    0.0f,
                    1.0f,
                    0.0f
                )
            );

            model = glm::scale(
                model,
                glm::vec3(
                    BOOK_SCALE,
                    BOOK_SCALE,
                    BOOK_SCALE
                )
            );

            glUniformMatrix4fv(
                glGetUniformLocation(
                    shader.Program,
                    "model"
                ),
                1,
                GL_FALSE,
                glm::value_ptr(model)
            );

            book.Draw(shader);


            // ------------------------------------------------
            // LIBROS - REPISA SUPERIOR
            // PARED IZQUIERDA
            // ------------------------------------------------

            model =
                glm::mat4(1.0f);

            model = glm::translate(
                model,
                glm::vec3(
                    -2.90f,
                    0.31f,
                    zPos
                )
            );

            model = glm::rotate(
                model,
                glm::radians(180.0f),
                glm::vec3(
                    0.0f,
                    1.0f,
                    0.0f
                )
            );

            model = glm::scale(
                model,
                glm::vec3(
                    BOOK_SCALE,
                    BOOK_SCALE,
                    BOOK_SCALE
                )
            );

            glUniformMatrix4fv(
                glGetUniformLocation(
                    shader.Program,
                    "model"
                ),
                1,
                GL_FALSE,
                glm::value_ptr(model)
            );

            book.Draw(shader);
        }


        // ====================================================
        // PARED DERECHA DE LIBREROS
        // ====================================================

        for (int i = 0; i < 4; i++)
        {
            float zPos =
                0.5f -
                (i * BOOKCASE_DISTANCE);


            // ------------------------------------------------
            // LIBRERO
            // ------------------------------------------------

            model =
                glm::mat4(1.0f);

            model = glm::translate(
                model,
                glm::vec3(
                    WALL_X,
                    BOOKCASE_Y,
                    zPos
                )
            );

            model = glm::rotate(
                model,
                glm::radians(-90.0f),
                glm::vec3(
                    0.0f,
                    1.0f,
                    0.0f
                )
            );

            model = glm::scale(
                model,
                glm::vec3(
                    BOOKCASE_SCALE,
                    BOOKCASE_SCALE,
                    BOOKCASE_SCALE
                )
            );

            glUniformMatrix4fv(
                glGetUniformLocation(
                    shader.Program,
                    "model"
                ),
                1,
                GL_FALSE,
                glm::value_ptr(model)
            );

            bookcase.Draw(shader);


            // ------------------------------------------------
            // LIBROS - REPISA INFERIOR
            // PARED DERECHA
            // ------------------------------------------------

            model = glm::mat4(1.0f);

            model = glm::translate(
                model,
                glm::vec3(
                    2.98f,
                    -0.035f,
                    zPos
                )
            );

            model = glm::rotate(
                model,
                glm::radians(0.0f),
                glm::vec3(
                    0.0f,
                    1.0f,
                    0.0f
                )
            );

            model = glm::scale(
                model,
                glm::vec3(
                    BOOK_SCALE,
                    BOOK_SCALE,
                    BOOK_SCALE
                )
            );

            glUniformMatrix4fv(
                glGetUniformLocation(
                    shader.Program,
                    "model"
                ),
                1,
                GL_FALSE,
                glm::value_ptr(model)
            );

            book.Draw(shader);


            // ------------------------------------------------
            // LIBROS - REPISA SUPERIOR
            // PARED DERECHA
            // ------------------------------------------------

            model = glm::mat4(1.0f);

            model = glm::translate(
                model,
                glm::vec3(
                    2.98f,
                    0.31f,
                    zPos
                )
            );

            model = glm::rotate(
                model,
                glm::radians(0.0f),
                glm::vec3(
                    0.0f,
                    1.0f,
                    0.0f
                )
            );

            model = glm::scale(
                model,
                glm::vec3(
                    BOOK_SCALE,
                    BOOK_SCALE,
                    BOOK_SCALE
                )
            );

            glUniformMatrix4fv(
                glGetUniformLocation(
                    shader.Program,
                    "model"
                ),
                1,
                GL_FALSE,
                glm::value_ptr(model)
            );

            book.Draw(shader);
        }


        // ====================================================
        // PARED DEL FONDO
        // ====================================================

        for (int i = -1; i <= 1; i++)
        {
            float xPos =
                i *
                BACK_BOOKCASE_DISTANCE;


            // ------------------------------------------------
            // LIBRERO
            // ------------------------------------------------

            model =
                glm::mat4(1.0f);

            model = glm::translate(
                model,
                glm::vec3(
                    xPos,
                    BOOKCASE_Y,
                    BACK_WALL_Z
                )
            );

            model = glm::scale(
                model,
                glm::vec3(
                    BOOKCASE_SCALE,
                    BOOKCASE_SCALE,
                    BOOKCASE_SCALE
                )
            );

            glUniformMatrix4fv(
                glGetUniformLocation(
                    shader.Program,
                    "model"
                ),
                1,
                GL_FALSE,
                glm::value_ptr(model)
            );

            bookcase.Draw(shader);


            // ------------------------------------------------
            // LIBROS - REPISA INFERIOR
            // PARED DEL FONDO
            // ------------------------------------------------

            model = glm::mat4(1.0f);

            model = glm::translate(
                model,
                glm::vec3(
                    xPos,
                    -0.03f,
                    -4.72f
                )
            );

            model = glm::rotate(
                model,
                glm::radians(90.0f),
                glm::vec3(
                    0.0f,
                    1.0f,
                    0.0f
                )
            );

            model = glm::scale(
                model,
                glm::vec3(
                    BOOK_SCALE,
                    BOOK_SCALE,
                    BOOK_SCALE
                )
            );

            glUniformMatrix4fv(
                glGetUniformLocation(
                    shader.Program,
                    "model"
                ),
                1,
                GL_FALSE,
                glm::value_ptr(model)
            );

            book.Draw(shader);


            // ------------------------------------------------
            // LIBROS - REPISA SUPERIOR
            // PARED DEL FONDO
            // ------------------------------------------------

            model = glm::mat4(1.0f);

            model = glm::translate(
                model,
                glm::vec3(
                    xPos,
                    0.31f,
                    -4.72f
                )
            );

            model = glm::rotate(
                model,
                glm::radians(90.0f),
                glm::vec3(
                    0.0f,
                    1.0f,
                    0.0f
                )
            );

            model = glm::scale(
                model,
                glm::vec3(
                    BOOK_SCALE,
                    BOOK_SCALE,
                    BOOK_SCALE
                )
            );

            glUniformMatrix4fv(
                glGetUniformLocation(
                    shader.Program,
                    "model"
                ),
                1,
                GL_FALSE,
                glm::value_ptr(model)
            );

            book.Draw(shader);
        }


        // ============================================================
        // SOL TEXTURIZADO + LUNA BLANCA
        //
        // IMPORTANTE:
        // sunPosition y moonPosition siguen siendo los mismos de la
        // versión que ya se trasladaba correctamente con O y L.
        //
        // sunPosition también se envía a sunLight.position.
        // moonPosition también se envía a moonLight.position.
        //
        // No hay rotación propia de las esferas.
        // ============================================================

        glBindVertexArray(sphereVAO);


        // ============================================================
        // SOL TEXTURIZADO
        // ============================================================

        sunShader.Use();

        glUniformMatrix4fv(
            glGetUniformLocation(
                sunShader.Program,
                "projection"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(projection)
        );

        glUniformMatrix4fv(
            glGetUniformLocation(
                sunShader.Program,
                "view"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(view)
        );

        glm::mat4 sunModel(1.0f);

        // MISMA posición de la luz cálida.
        sunModel = glm::translate(
            sunModel,
            sunPosition
        );

        // Tamaño reducido a aproximadamente 1/3 del tamaño grande inicial.
        sunModel = glm::scale(
            sunModel,
            glm::vec3(0.67f)
        );

        glUniformMatrix4fv(
            glGetUniformLocation(
                sunShader.Program,
                "model"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(sunModel)
        );

        glActiveTexture(GL_TEXTURE0);

        glBindTexture(
            GL_TEXTURE_2D,
            sunTexture
        );

        glUniform1i(
            glGetUniformLocation(
                sunShader.Program,
                "sunTexture"
            ),
            0
        );

        glDrawElements(
            GL_TRIANGLES,
            (GLsizei)sphereIndices.size(),
            GL_UNSIGNED_INT,
            0
        );


        // ============================================================
        // LUNA CON TEXTURA
        // ============================================================

        moonShader.Use();

        glUniformMatrix4fv(
            glGetUniformLocation(
                moonShader.Program,
                "projection"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(projection)
        );

        glUniformMatrix4fv(
            glGetUniformLocation(
                moonShader.Program,
                "view"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(view)
        );

        glm::mat4 moonModel(1.0f);

        // La esfera está exactamente en el centro de la luz fría
        moonModel = glm::translate(
            moonModel,
            moonPosition
        );

        // Mismo tamaño que el Sol
        moonModel = glm::scale(
            moonModel,
            glm::vec3(0.67f)
        );

        glUniformMatrix4fv(
            glGetUniformLocation(
                moonShader.Program,
                "model"
            ),
            1,
            GL_FALSE,
            glm::value_ptr(moonModel)
        );

        glActiveTexture(GL_TEXTURE0);

        glBindTexture(
            GL_TEXTURE_2D,
            moonTexture
        );

        glUniform1i(
            glGetUniformLocation(
                moonShader.Program,
                "moonTexture"
            ),
            0
        );

        glDrawElements(
            GL_TRIANGLES,
            (GLsizei)sphereIndices.size(),
            GL_UNSIGNED_INT,
            0
        );

        glBindVertexArray(0);


        // ====================================================
        // MOSTRAR FRAME
        // ====================================================

        glfwSwapBuffers(
            window
        );
    }


    // ========================================================
    // LIMPIAR MEMORIA moonShader
    // ========================================================

    glDeleteTextures(
        1,
        &sunTexture
    );

    glDeleteTextures(
        1,
        &floorTexture
    );


    glDeleteVertexArrays(
        1,
        &sphereVAO
    );

    glDeleteBuffers(
        1,
        &sphereVBO
    );

    glDeleteBuffers(
        1,
        &sphereEBO
    );


    glDeleteVertexArrays(
        1,
        &floorVAO
    );


    glDeleteBuffers(
        1,
        &floorVBO
    );


    glDeleteVertexArrays(
        1,
        &gridVAO
    );


    glDeleteBuffers(
        1,
        &gridVBO
    );


    glfwTerminate();


    return 0;
}


// ============================================================
// MOVIMIENTO DE CAMARA
// ============================================================

void DoMovement()
{
    // ========================================================
    // W = AVANZAR / ACERCARSE
    // ========================================================

    if (keys[GLFW_KEY_W])
    {
        camera.ProcessKeyboard(
            FORWARD,
            deltaTime
        );
    }


    // ========================================================
    // S = RETROCEDER / ALEJARSE
    // ========================================================

    if (keys[GLFW_KEY_S])
    {
        camera.ProcessKeyboard(
            BACKWARD,
            deltaTime
        );
    }


    // ========================================================
    // A = IZQUIERDA
    // ========================================================

    if (keys[GLFW_KEY_A])
    {
        camera.ProcessKeyboard(
            LEFT,
            deltaTime
        );
    }


    // ========================================================
    // D = DERECHA
    // ========================================================

    if (keys[GLFW_KEY_D])
    {
        camera.ProcessKeyboard(
            RIGHT,
            deltaTime
        );
    }


    // ========================================================
    // VELOCIDAD DE GIRO CON LAS FLECHAS CUADRICULA NEGRA
    // ========================================================

    const GLfloat velocidadGiro =
        180.0f;


    // ========================================================
    // FLECHA IZQUIERDA
    // ========================================================

    if (keys[GLFW_KEY_LEFT])
    {
        camera.ProcessMouseMovement(
            -velocidadGiro *
            deltaTime,
            0.0f
        );
    }


    // ========================================================
    // FLECHA DERECHA
    // ========================================================

    if (keys[GLFW_KEY_RIGHT])
    {
        camera.ProcessMouseMovement(
            velocidadGiro *
            deltaTime,
            0.0f
        );
    }


    // ========================================================
    // FLECHA ARRIBA
    // ========================================================

    if (keys[GLFW_KEY_UP])
    {
        camera.ProcessMouseMovement(
            0.0f,
            velocidadGiro *
            deltaTime
        );
    }


    // ========================================================
    // FLECHA ABAJO sunShader
    // ========================================================

    if (keys[GLFW_KEY_DOWN])
    {
        camera.ProcessMouseMovement(
            0.0f,
            -velocidadGiro *
            deltaTime
        );
    }
    // ============================================================
// MOVIMIENTO ORBITAL SOL - LUNA
// ============================================================

    const float orbitSpeed =
        50.0f;

    if (keys[GLFW_KEY_O])
    {
        orbitAngle +=
            orbitSpeed *
            deltaTime;
    }

    if (keys[GLFW_KEY_L])
    {
        orbitAngle -=
            orbitSpeed *
            deltaTime;
    }
}


// ============================================================
// TECLADO
// ============================================================

void KeyCallback(
    GLFWwindow* window,
    int key,
    int scancode,
    int action,
    int mode
)
{
    // ========================================================
    // ESC = CERRAR
    // ========================================================

    if (
        key == GLFW_KEY_ESCAPE &&
        action == GLFW_PRESS
        )
    {
        glfwSetWindowShouldClose(
            window,
            GL_TRUE
        );
    }


    // ========================================================
    // ESTADO DE LAS TECLAS
    // ========================================================

    if (
        key >= 0 &&
        key < 1024
        )
    {
        if (
            action == GLFW_PRESS
            )
        {
            keys[key] =
                true;
        }


        else if (
            action == GLFW_RELEASE
            )
        {
            keys[key] =
                false;
        }
    }
}

// ============================================================ sunLight
// CREAR ESFERA
// ============================================================

void BuildSphere(
    std::vector<float>& vertices,
    std::vector<unsigned int>& indices,
    float radius,
    unsigned int sectors,
    unsigned int stacks
)
{
    const float PI = 3.14159265359f;

    float x;
    float y;
    float z;
    float xy;

    float nx;
    float ny;
    float nz;

    float s;
    float t;

    float sectorStep =
        2.0f * PI / sectors;

    float stackStep =
        PI / stacks;

    float sectorAngle;
    float stackAngle;

    vertices.clear();
    indices.clear();

    for (unsigned int i = 0; i <= stacks; ++i)
    {
        stackAngle =
            PI / 2.0f -
            i * stackStep;

        xy =
            radius * cosf(stackAngle);

        z =
            radius * sinf(stackAngle);

        for (unsigned int j = 0; j <= sectors; ++j)
        {
            sectorAngle =
                j * sectorStep;

            x =
                xy * cosf(sectorAngle);

            y =
                xy * sinf(sectorAngle);

            nx = x / radius;
            ny = y / radius;
            nz = z / radius;

            s =
                (float)j / sectors;

            t =
                (float)i / stacks;

            // Posicion
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            // Normal
            vertices.push_back(nx);
            vertices.push_back(ny);
            vertices.push_back(nz);

            // Coordenadas UV
            vertices.push_back(s);
            vertices.push_back(t);
        }
    }

    for (unsigned int i = 0; i < stacks; ++i)
    {
        unsigned int k1 =
            i * (sectors + 1);

        unsigned int k2 =
            k1 + sectors + 1;

        for (
            unsigned int j = 0;
            j < sectors;
            ++j, ++k1, ++k2
            )
        {
            if (i != 0)
            {
                indices.push_back(k1);
                indices.push_back(k2);
                indices.push_back(k1 + 1);
            }

            if (i != (stacks - 1))
            {
                indices.push_back(k1 + 1);
                indices.push_back(k2);
                indices.push_back(k2 + 1);
            }
        }
    }
}

