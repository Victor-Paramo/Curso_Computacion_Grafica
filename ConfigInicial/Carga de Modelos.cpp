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


// ============================================================
// VENTANA
// ============================================================

const GLuint WIDTH = 800;
const GLuint HEIGHT = 600;

int SCREEN_WIDTH;
int SCREEN_HEIGHT;


// ============================================================
// PROTOTIPOS
// ============================================================

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
// AJUSTES DE LA ESCENA
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
const GLfloat DOG_Y = -0.50f;
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
const GLfloat TABLE_Y = -1.09f;
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
const GLfloat BOOKS_Y = -0.37f;
const GLfloat BOOKS_Z = 1.4f;

const GLfloat BOOKS_SCALE = 0.009f;

// ============================================================
// SOFA 2 - PHOENIX
// ============================================================

const GLfloat SOFA2_X = -8.5f;
const GLfloat SOFA2_Y = -0.95f;
const GLfloat SOFA2_Z = -11.0f;

const GLfloat SOFA2_SCALE = 0.030f;
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


    // ========================================================
    // CREAR PISO BEIGE
    //
    // Plano horizontal formado por dos triángulos.
    // ========================================================

    GLfloat floorVertices[] =
    {
        // X       Y         Z

        -20.0f, FLOOR_Y, -20.0f,
         20.0f, FLOOR_Y, -20.0f,
         20.0f, FLOOR_Y,  20.0f,

        -20.0f, FLOOR_Y, -20.0f,
         20.0f, FLOOR_Y,  20.0f,
        -20.0f, FLOOR_Y,  20.0f
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
    // ========================================================

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
        // FONDO GRIS CLARO
        //
        // Este es el color que aparecerá por encima del piso.
        // ====================================================

        glClearColor(
            0.75f,
            0.75f,
            0.75f,
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


        // ====================================================
        // MATRIZ VIEW
        // ====================================================

        glm::mat4 view =
            camera.GetViewMatrix();


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
        // PISO BEIGE
        // ====================================================

        glUniform1i(
            glGetUniformLocation(
                shader.Program,
                "useSolidColor"
            ),
            GL_TRUE
        );


        // Beige ligeramente oscuro
        glUniform4f(
            glGetUniformLocation(
                shader.Program,
                "solidColor"
            ),
            0.62f,
            0.57f,
            0.49f,
            1.0f
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


        // ====================================================
        // CUADRICULA NEGRA
        // ====================================================

        glUniform1i(
            glGetUniformLocation(
                shader.Program,
                "useSolidColor"
            ),
            GL_TRUE
        );


        glUniform4f(
            glGetUniformLocation(
                shader.Program,
                "solidColor"
            ),
            0.0f,
            0.0f,
            0.0f,
            1.0f
        );


        model =
            glm::mat4(1.0f);


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
            gridVAO
        );


        glDrawArrays(
            GL_LINES,
            0,
            (GLsizei)(
                gridVertices.size() / 3
                )
        );


        glBindVertexArray(0);


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
            model =
                glm::mat4(1.0f);


            model = glm::translate(
                model,
                glm::vec3(
                    -WALL_X,
                    BOOKCASE_Y,
                    0.5f -
                    (i * BOOKCASE_DISTANCE)
                )
            );


            // Girar el librero hacia el interior

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
        }


        // ====================================================
        // PARED DERECHA DE LIBREROS
        // ====================================================

        for (int i = 0; i < 4; i++)
        {
            model =
                glm::mat4(1.0f);


            model = glm::translate(
                model,
                glm::vec3(
                    WALL_X,
                    BOOKCASE_Y,
                    0.5f -
                    (i * BOOKCASE_DISTANCE)
                )
            );


            // Girar el librero hacia el interior

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
        }


        // ====================================================
        // PARED DEL FONDO
        //
        // Tres libreros:
        //
        // ====================================================

        for (int i = -1; i <= 1; i++)
        {
            model =
                glm::mat4(1.0f);


            model = glm::translate(
                model,
                glm::vec3(
                    i *
                    BACK_BOOKCASE_DISTANCE,

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
        }


        // ====================================================
        // MOSTRAR FRAME
        // ====================================================

        glfwSwapBuffers(
            window
        );
    }


    // ========================================================
    // LIMPIAR MEMORIA
    // ========================================================

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
    // VELOCIDAD DE GIRO CON LAS FLECHAS
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
    // FLECHA ABAJO
    // ========================================================

    if (keys[GLFW_KEY_DOWN])
    {
        camera.ProcessMouseMovement(
            0.0f,
            -velocidadGiro *
            deltaTime
        );
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