//Práctica 2
//González Jiménez Victor Yotecatl
//Fecha de entrega: agosto 2026
//Número de cuenta

#include<iostream>

//#define GLEW_STATIC

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Shaders
#include "Shader.h"

void resize(GLFWwindow* window, int width, int height);

const GLint WIDTH = 800, HEIGHT = 800;


int main()
{
    glfwInit();


    GLFWwindow* window = glfwCreateWindow(
        WIDTH,
        HEIGHT,
        "Victor Yotecatl",
        NULL,
        NULL
    );


    glfwSetFramebufferSizeCallback(window, resize);


    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;

        glfwTerminate();

        return EXIT_FAILURE;
    }


    glfwMakeContextCurrent(window);


    glewExperimental = GL_TRUE;


    if (GLEW_OK != glewInit())
    {
        std::cout << "Failed to initialise GLEW" << std::endl;

        return EXIT_FAILURE;
    }


    std::cout << "> Version: "
        << glGetString(GL_VERSION)
        << std::endl;

    std::cout << "> Vendor: "
        << glGetString(GL_VENDOR)
        << std::endl;

    std::cout << "> Renderer: "
        << glGetString(GL_RENDERER)
        << std::endl;

    std::cout << "> SL Version: "
        << glGetString(GL_SHADING_LANGUAGE_VERSION)
        << std::endl;


    Shader ourShader(
        "Shader/core.vs",
        "Shader/core.frag"
    );


    // =====================================================
    // VERTICES
    // =====================================================

    float vertices[] = {


        // =================================================
        // OREJA IZQUIERDA
        // =================================================

        -0.65f,  0.85f, 0.0f,    1.0f, 0.55f, 0.15f,   // 0
        -0.55f,  0.15f, 0.0f,    1.0f, 0.55f, 0.15f,   // 1
        -0.15f,  0.25f, 0.0f,    1.0f, 0.55f, 0.15f,   // 2


        // =================================================
        // OREJA DERECHA
        // =================================================

         0.65f,  0.85f, 0.0f,    1.0f, 0.0f, 0.0f,     // 3
         0.15f,  0.25f, 0.0f,    1.0f, 0.1f, 0.1f,     // 4
         0.55f,  0.15f, 0.0f,    1.0f, 0.3f, 0.0f,     // 5


         // =================================================
         // TRIANGULO CENTRAL ROJO
         // =================================================

         -0.10f,  0.22f, 0.0f,    1.0f, 0.0f, 0.0f,     // 6
          0.10f,  0.22f, 0.0f,    1.0f, 0.0f, 0.0f,     // 7
          0.00f, -0.55f, 0.0f,    1.0f, 0.0f, 0.0f,     // 8


          // =================================================
          // OJO IZQUIERDO
          // =================================================

          -0.52f, -0.05f, 0.0f,    1.0f, 1.0f, 1.0f,     // 9
          -0.30f,  0.11f, 0.0f,    1.0f, 1.0f, 1.0f,     // 10
          -0.10f, -0.05f, 0.0f,    1.0f, 1.0f, 1.0f,     // 11
          -0.30f, -0.28f, 0.0f,    1.0f, 1.0f, 1.0f,     // 12


          // =================================================
          // OJO DERECHO
          // =================================================

           0.52f, -0.05f, 0.0f,    1.0f, 1.0f, 1.0f,     // 13
           0.30f,  0.07f, 0.0f,    1.0f, 1.0f, 1.0f,     // 14
           0.10f, -0.05f, 0.0f,    1.0f, 1.0f, 1.0f,     // 15
           0.30f, -0.28f, 0.0f,    1.0f, 1.0f, 1.0f,     // 16


           // =================================================
           // LINEAS CABEZA DERECHA
           // =================================================

           0.58f,  0.12f, 0.0f,    0.0f, 0.0f, 0.0f,    // 17
           0.58f, -0.45f, 0.0f,    0.0f, 0.0f, 0.0f,    // 18

           0.58f, -0.45f, 0.0f,    0.0f, 0.0f, 0.0f,    // 19
           0.00f, -0.45f, 0.0f,    0.0f, 0.0f, 0.0f,    // 20


           // =================================================
           // LINEAS CABEZA IZQUIERDA
           // =================================================

           -0.58f,  0.12f, 0.0f,    0.0f, 0.0f, 0.0f,    // 21
           -0.62f, -0.15f, 0.0f,    0.0f, 0.0f, 0.0f,    // 22

           -0.62f, -0.15f, 0.0f,    0.0f, 0.0f, 0.0f,    // 23
           -0.58f, -0.45f, 0.0f,    0.0f, 0.0f, 0.0f,    // 24

           -0.58f, -0.45f, 0.0f,    0.0f, 0.0f, 0.0f,    // 25
           0.00f, -0.45f, 0.0f,     0.0f, 0.0f, 0.0f,    // 26


             // =================================================
             // ZONA VERDE IZQUIERDA
             // =================================================

             -0.32f, -0.08f, 0.0f,    0.0f, 0.8f, 0.2f,     // 27 centro

             -0.55f,  0.15f, 0.0f,    0.0f, 0.8f, 0.2f,     // 28
             -0.15f,  0.25f, 0.0f,    0.0f, 0.8f, 0.2f,     // 29
             -0.10f,  0.22f, 0.0f,    0.0f, 0.8f, 0.2f,     // 30
             -0.01f, -0.45f, 0.0f,    0.0f, 0.8f, 0.2f,     // 31
             -0.58f, -0.45f, 0.0f,    0.0f, 0.8f, 0.2f,     // 32
             -0.62f, -0.15f, 0.0f,    0.0f, 0.8f, 0.2f,     // 33
             -0.55f,  0.15f, 0.0f,    0.0f, 0.8f, 0.2f,     // 34


             // =================================================
             // ZONA AZUL DERECHA
             // =================================================

              0.32f, -0.08f, 0.0f,    0.0f, 0.4f, 1.0f,     // 35 centro

              0.55f,  0.15f, 0.0f,    0.0f, 0.4f, 1.0f,     // 36
              0.15f,  0.25f, 0.0f,    0.0f, 0.4f, 1.0f,     // 37
              0.10f,  0.22f, 0.0f,    0.0f, 0.4f, 1.0f,     // 38
              0.01f, -0.45f, 0.0f,    0.0f, 0.4f, 1.0f,     // 39
              0.58f, -0.45f, 0.0f,    0.0f, 0.4f, 1.0f,     // 40
              0.58f,  0.12f, 0.0f,    0.0f, 0.4f, 1.0f,     // 41
              0.55f,  0.15f, 0.0f,    0.0f, 0.4f, 1.0f,     // 42


              // =================================================
              // IRIS IZQUIERDO
              // =================================================

              -0.30f, -0.05f, 0.0f,    0.2f, 1.0f, 0.1f,     // 43 centro
              -0.30f,  0.06f, 0.0f,    0.2f, 1.0f, 0.1f,     // 44
              -0.22f,  0.02f, 0.0f,    0.2f, 1.0f, 0.1f,     // 45
              -0.22f, -0.10f, 0.0f,    0.2f, 1.0f, 0.1f,     // 46
              -0.30f, -0.15f, 0.0f,    0.2f, 1.0f, 0.1f,     // 47
              -0.38f, -0.10f, 0.0f,    0.2f, 1.0f, 0.1f,     // 48
              -0.38f,  0.02f, 0.0f,    0.2f, 1.0f, 0.1f,     // 49
              -0.30f,  0.06f, 0.0f,    0.2f, 1.0f, 0.1f,     // 50


              // =================================================
              // PUPILA IZQUIERDA
              // =================================================

              -0.315f,  0.03f, 0.0f,    0.0f, 0.0f, 0.0f,    // 51
              -0.285f,  0.03f, 0.0f,    0.0f, 0.0f, 0.0f,    // 52
              -0.285f, -0.12f, 0.0f,    0.0f, 0.0f, 0.0f,    // 53
              -0.315f, -0.12f, 0.0f,    0.0f, 0.0f, 0.0f,    // 54


              // =================================================
              // IRIS DERECHO
              // =================================================

               0.30f, -0.05f, 0.0f,    0.2f, 1.0f, 0.1f,     // 55 centro
               0.30f,  0.06f, 0.0f,    0.2f, 1.0f, 0.1f,     // 56
               0.22f,  0.02f, 0.0f,    0.2f, 1.0f, 0.1f,     // 57
               0.22f, -0.10f, 0.0f,    0.2f, 1.0f, 0.1f,     // 58
               0.30f, -0.15f, 0.0f,    0.2f, 1.0f, 0.1f,     // 59
               0.38f, -0.10f, 0.0f,    0.2f, 1.0f, 0.1f,     // 60
               0.38f,  0.02f, 0.0f,    0.2f, 1.0f, 0.1f,     // 61
               0.30f,  0.06f, 0.0f,    0.2f, 1.0f, 0.1f,     // 62


               // =================================================
               // PUPILA DERECHA
               // =================================================

                0.285f,  0.03f, 0.0f,    0.0f, 0.0f, 0.0f,    // 63
                0.315f,  0.03f, 0.0f,    0.0f, 0.0f, 0.0f,    // 64
                0.315f, -0.12f, 0.0f,    0.0f, 0.0f, 0.0f,    // 65
                0.285f, -0.12f, 0.0f,    0.0f, 0.0f, 0.0f,    // 66


               // =================================================
               // CONTORNO DEL MENTON
               // =================================================

               -0.58f, -0.45f, 0.0f, 0.0f, 0.0f, 0.0f,    // 67
               -0.51f, -0.75f, 0.0f, 0.0f, 0.0f, 0.0f,    // 68

               -0.51f, -0.75f, 0.0f, 0.0f, 0.0f, 0.0f,    // 69
               -0.29f, -0.98f, 0.0f, 0.0f, 0.0f, 0.0f,    // 70

               0.58f, -0.45f, 0.0f, 0.0f, 0.0f, 0.0f,    // 71
               0.51f, -0.75f, 0.0f, 0.0f, 0.0f, 0.0f,    // 72

               0.51f, -0.75f, 0.0f, 0.0f, 0.0f, 0.0f,    // 73
               0.29f, -0.98f, 0.0f, 0.0f, 0.0f, 0.0f,    // 74

               -0.29f, -0.98f, 0.0f, 0.0f, 0.0f, 0.0f,    // 75
               0.29f, -0.98f, 0.0f, 0.0f, 0.0f, 0.0f,    // 76


                 // =================================================
                 // BOCA
                 // =================================================

                 // blanco
                 -0.10f, -0.45f, 0.0f,    0.90f, 0.90f, 0.90f,  // 77
                  0.10f, -0.45f, 0.0f,    0.90f, 0.90f, 0.90f,  // 78
                  0.00f, -0.62f, 0.0f,    0.90f, 0.90f, 0.90f,  // 79

                  // azul izquierdo
                  -0.10f, -0.45f, 0.0f,    0.05f, 0.25f, 0.70f,  // 80
                   0.00f, -0.62f, 0.0f,    0.05f, 0.25f, 0.70f,  // 81
                  -0.10f, -0.78f, 0.0f,    0.05f, 0.25f, 0.70f,  // 82

                  // azul derecho
                   0.10f, -0.45f, 0.0f,    0.05f, 0.25f, 0.70f,  // 83
                   0.10f, -0.78f, 0.0f,    0.05f, 0.25f, 0.70f,  // 84
                   0.00f, -0.62f, 0.0f,    0.05f, 0.25f, 0.70f,  // 85

                   // rojo inferior
                   -0.10f, -0.78f, 0.0f,    1.0f, 0.05f, 0.05f,   // 86
                    0.10f, -0.78f, 0.0f,    1.0f, 0.05f, 0.05f,   // 87
                    0.00f, -0.94f, 0.0f,    1.0f, 0.05f, 0.05f,   // 88

                    // rojo superior
                     0.00f, -0.62f, 0.0f,    1.0f, 0.05f, 0.05f,   // 89
                    -0.10f, -0.78f, 0.0f,    1.0f, 0.05f, 0.05f,   // 90
                     0.10f, -0.78f, 0.0f,    1.0f, 0.05f, 0.05f,   // 91


                     // =================================================
                     // CACHETE DERECHO NARANJA
                     // =================================================

                      0.34f, -0.68f, 0.0f,    1.0f, 0.45f, 0.12f,   // 92 centro
                      0.58f, -0.45f, 0.0f,    1.0f, 0.45f, 0.12f,   // 93
                      0.51f, -0.75f, 0.0f,    1.0f, 0.45f, 0.12f,   // 94
                      0.29f, -0.98f, 0.0f,    1.0f, 0.45f, 0.12f,   // 95
                      0.10f, -0.78f, 0.0f,    1.0f, 0.45f, 0.12f,   // 96
                      0.10f, -0.45f, 0.0f,    1.0f, 0.45f, 0.12f,   // 97
                      0.58f, -0.45f, 0.0f,    1.0f, 0.45f, 0.12f,   // 98


                      // =================================================
                      // CACHETE IZQUIERDO ROJO
                      // =================================================

                      -0.34f, -0.68f, 0.0f,    1.0f, 0.12f, 0.18f,   // 99 centro
                      -0.10f, -0.45f, 0.0f,    1.0f, 0.12f, 0.18f,   // 100
                      -0.10f, -0.78f, 0.0f,    1.0f, 0.12f, 0.18f,   // 101
                      -0.29f, -0.98f, 0.0f,    1.0f, 0.12f, 0.18f,   // 102
                      -0.51f, -0.75f, 0.0f,    1.0f, 0.12f, 0.18f,   // 103
                      -0.58f, -0.45f, 0.0f,    1.0f, 0.12f, 0.18f,   // 104
                      -0.10f, -0.45f, 0.0f,    1.0f, 0.12f, 0.18f,   // 105


                      // =================================================
                      // CUERPO IZQUIERDO AMARILLO
                      // =================================================

                      -0.29f, -0.98f, 0.0f,    1.0f, 0.90f, 0.05f,   // 106
                       0.00f, -0.98f, 0.0f,    1.0f, 0.90f, 0.05f,   // 107
                       0.00f, -1.45f, 0.0f,    1.0f, 0.90f, 0.05f,   // 108
                      -0.42f, -1.45f, 0.0f,    1.0f, 0.90f, 0.05f,   // 109


                      // =================================================
                      // CUERPO DERECHO VERDE
                      // =================================================

                       0.00f, -0.98f, 0.0f,    0.10f, 0.80f, 0.35f,  // 110
                       0.29f, -0.98f, 0.0f,    0.10f, 0.80f, 0.35f,  // 111
                       0.34f, -1.45f, 0.0f,    0.10f, 0.80f, 0.35f,  // 112
                       0.00f, -1.45f, 0.0f,    0.10f, 0.80f, 0.35f,  // 113


                       // =================================================
                       // BRAZO DERECHO AMARILLO
                       // =================================================

                        0.29f, -0.98f, 0.0f,    1.0f, 0.85f, 0.05f,   // 114
                        0.37f, -1.03f, 0.0f,    1.0f, 0.85f, 0.05f,   // 115
                        0.50f, -1.45f, 0.0f,    1.0f, 0.85f, 0.05f,   // 116
                        0.34f, -1.45f, 0.0f,    1.0f, 0.85f, 0.05f,    // 117

                        // =================================================
                        // CONTORNO NEGRO OREJA IZQUIERDA
                        // =================================================

                        // 118 - punta
                    -0.65f, 0.85f, 0.0f, 0.0f, 0.0f, 0.0f,

                    // 119 - abajo izquierda
                    -0.55f, 0.15f, 0.0f, 0.0f, 0.0f, 0.0f,

                    // 120 - abajo derecha
                    -0.15f, 0.25f, 0.0f, 0.0f, 0.0f, 0.0f,


                    // =================================================
                    // CONTORNO NEGRO OREJA DERECHA
                    // =================================================

                    // 121 - punta
                    0.65f, 0.85f, 0.0f, 0.0f, 0.0f, 0.0f,

                    // 122 - abajo izquierda
                    0.15f, 0.25f, 0.0f, 0.0f, 0.0f, 0.0f,

                    // 123 - abajo derecha
                    0.55f, 0.15f, 0.0f, 0.0f, 0.0f, 0.0f,

                    // =================================================
                    // CONTORNO NEGRO OJO IZQUIERDO
                    // =================================================

                    // 124 - izquierda
                      -0.52f, -0.05f, 0.0f, 0.0f, 0.0f, 0.0f,

                      // 125 - arriba
                      -0.30f, 0.11f, 0.0f, 0.0f, 0.0f, 0.0f,

                      // 126 - derecha
                      -0.10f, -0.05f, 0.0f, 0.0f, 0.0f, 0.0f,

                      // 127 - abajo
                      -0.30f, -0.28f, 0.0f, 0.0f, 0.0f, 0.0f,


                      // =================================================
                      // CONTORNO NEGRO OJO DERECHO
                      // =================================================

                      // 128 - derecha
                      0.52f, -0.05f, 0.0f, 0.0f, 0.0f, 0.0f,

                      // 129 - arriba
                      0.30f, 0.07f, 0.0f, 0.0f, 0.0f, 0.0f,

                      // 130 - izquierda
                      0.10f, -0.05f, 0.0f, 0.0f, 0.0f, 0.0f,

                      // 131 - abajo
                      0.30f, -0.28f, 0.0f, 0.0f, 0.0f, 0.0f,


            // =================================================
            // CONTORNO NEGRO DEL CUERPO
            // =================================================

            // 132 - arriba izquierda
            -0.29f, -0.98f, 0.0f, 0.0f, 0.0f, 0.0f,

            // 133 - arriba centro
            0.00f, -0.98f, 0.0f, 0.0f, 0.0f, 0.0f,

            // 134 - arriba derecha
            0.29f, -0.98f, 0.0f, 0.0f, 0.0f, 0.0f,

            // 135 - inicio brazo exterior
            0.37f, -1.03f, 0.0f, 0.0f, 0.0f, 0.0f,

            // 136 - abajo derecha exterior
            0.50f, -1.45f, 0.0f, 0.0f, 0.0f, 0.0f,

            // 137 - abajo centro derecho
            0.34f, -1.45f, 0.0f, 0.0f, 0.0f, 0.0f,

            // 138 - abajo centro
            0.00f, -1.45f, 0.0f, 0.0f, 0.0f, 0.0f,

            // 139 - abajo izquierda
            -0.42f, -1.45f, 0.0f, 0.0f, 0.0f, 0.0f,

            // 140 - cerrar arriba izquierda
            -0.29f, -0.98f, 0.0f, 0.0f, 0.0f, 0.0f,

            // =================================================
            // LINEAS INTERNAS DEL CUERPO
            // =================================================

            // 141 - división amarillo / verde
            0.00f, -0.98f, 0.0f, 0.0f, 0.0f, 0.0f,

            // 142
            0.00f, -1.45f, 0.0f, 0.0f, 0.0f, 0.0f,


            // 143 - división verde / brazo amarillo
            0.29f, -0.98f, 0.0f, 0.0f, 0.0f, 0.0f,

            // 144
            0.34f, -1.45f, 0.0f, 0.0f, 0.0f, 0.0f,

            // =================================================
            // CONTORNO NEGRO TRIANGULO ROJO CENTRAL / NARIZ
            // =================================================

            // 145 - arriba izquierda
            -0.10f, 0.22f, 0.0f, 0.0f, 0.0f, 0.0f,

            // 146 - arriba derecha
            0.10f, 0.22f, 0.0f, 0.0f, 0.0f, 0.0f,

            // 147 - punta inferior
            0.00f, -0.55f, 0.0f, 0.0f, 0.0f, 0.0f,

            // =================================================
            // LINEA VERTICAL CENTRAL DEL HOCICO
            // =================================================

            // 148 - arriba, centro de la base del triángulo blanco
            0.00f, -0.45f, 0.0f, 0.0f, 0.0f, 0.0f,

            // 149 - abajo, punta del rombo rojo
            0.00f, -0.94f, 0.0f, 0.0f, 0.0f, 0.0f,

            // =================================================
            // BIGOTES IZQUIERDOS
            // =================================================

            // Bigote izquierdo 1 - corto
                -0.38f, -0.54f, 0.0f, 0.0f, 0.0f, 0.0f,   // 150
                -0.66f, -0.50f, 0.0f, 0.0f, 0.0f, 0.0f,   // 151

                // Bigote izquierdo 2 - más largo
                -0.38f, -0.59f, 0.0f, 0.0f, 0.0f, 0.0f,   // 152
                -0.82f, -0.57f, 0.0f, 0.0f, 0.0f, 0.0f,   // 153

                // Bigote izquierdo 3 - más largo
                -0.38f, -0.64f, 0.0f, 0.0f, 0.0f, 0.0f,   // 154
                -0.84f, -0.65f, 0.0f, 0.0f, 0.0f, 0.0f,   // 155

                // Bigote izquierdo 4 - más largo
                -0.38f, -0.69f, 0.0f, 0.0f, 0.0f, 0.0f,   // 156
                -0.82f, -0.74f, 0.0f, 0.0f, 0.0f, 0.0f,   // 157

                // Bigote izquierdo 5 - inferior, largo
                -0.38f, -0.74f, 0.0f, 0.0f, 0.0f, 0.0f,   // 158
                -0.78f, -0.84f, 0.0f, 0.0f, 0.0f, 0.0f,   // 159


                // =================================================
                // BIGOTES DERECHOS
                // =================================================

                // Bigote derecho 1 - corto
                0.38f, -0.54f, 0.0f, 0.0f, 0.0f, 0.0f,   // 160
                0.66f, -0.50f, 0.0f, 0.0f, 0.0f, 0.0f,   // 161

                // Bigote derecho 2 - más largo
                0.38f, -0.59f, 0.0f, 0.0f, 0.0f, 0.0f,   // 162
                0.82f, -0.57f, 0.0f, 0.0f, 0.0f, 0.0f,   // 163

                // Bigote derecho 3 - más largo
                0.38f, -0.64f, 0.0f, 0.0f, 0.0f, 0.0f,   // 164
                0.84f, -0.65f, 0.0f, 0.0f, 0.0f, 0.0f,   // 165

                // Bigote derecho 4 - más largo
                0.38f, -0.69f, 0.0f, 0.0f, 0.0f, 0.0f,   // 166
                0.82f, -0.74f, 0.0f, 0.0f, 0.0f, 0.0f,   // 167

                // Bigote derecho 5 - inferior, largo
                0.38f, -0.74f, 0.0f, 0.0f, 0.0f, 0.0f,   // 168
                0.78f, -0.84f, 0.0f, 0.0f, 0.0f, 0.0f    // 169


    };


    // =====================================================
    // INDICES
    // =====================================================

    unsigned int indices[] = {

        // Orejas
        0, 1, 2,
        3, 4, 5,

        // Triangulo central
        6, 7, 8,

        // Ojo izquierdo
        9, 10, 11,
        9, 11, 12,

        // Ojo derecho
        13, 14, 15,
        13, 15, 16,

        // Pupila izquierda
        51, 52, 53,
        51, 53, 54,

        // Pupila derecha
        63, 64, 65,
        63, 65, 66,

        // Boca
        77, 78, 79,

        80, 81, 82,

        83, 84, 85,

        86, 87, 88,

        89, 90, 91
    };


    // =====================================================
    // VAO - VBO - EBO
    // =====================================================

    GLuint VBO, VAO, EBO;


    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);

    glGenBuffers(1, &EBO);


    glBindVertexArray(VAO);


    glBindBuffer(
        GL_ARRAY_BUFFER,
        VBO
    );


    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(vertices),
        vertices,
        GL_STATIC_DRAW
    );


    glBindBuffer(
        GL_ELEMENT_ARRAY_BUFFER,
        EBO
    );


    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(indices),
        indices,
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


    glBindBuffer(
        GL_ARRAY_BUFFER,
        0
    );


    glBindVertexArray(0);


    // =====================================================
    // CICLO PRINCIPAL
    // =====================================================

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();


        // Fondo azul marino
        glClearColor(
            0.06f,
            0.12f,
            0.32f,
            1.0f
        );


        glClear(GL_COLOR_BUFFER_BIT);


        ourShader.Use();

        glBindVertexArray(VAO);


        // =================================================
        // CARA SUPERIOR
        // =================================================

        glDrawArrays(
            GL_TRIANGLE_FAN,
            27,
            8
        );


        glDrawArrays(
            GL_TRIANGLE_FAN,
            35,
            8
        );


        // =================================================
        // CACHETES
        // =================================================

        glDrawArrays(
            GL_TRIANGLE_FAN,
            92,
            7
        );


        glDrawArrays(
            GL_TRIANGLE_FAN,
            99,
            7
        );


        // =================================================
        // CUERPO
        // =================================================

        // Amarillo
        glDrawArrays(
            GL_TRIANGLE_FAN,
            106,
            4
        );


        // Verde
        glDrawArrays(
            GL_TRIANGLE_FAN,
            110,
            4
        );


        // Brazo derecho amarillo
        glDrawArrays(
            GL_TRIANGLE_FAN,
            114,
            4
        );


        // =================================================
        // OREJAS + CENTRO + OJOS
        // =================================================

        glDrawElements(
            GL_TRIANGLES,
            21,
            GL_UNSIGNED_INT,
            0
        );


        // =================================================
        // IRIS
        // =================================================

        glDrawArrays(
            GL_TRIANGLE_FAN,
            43,
            8
        );


        glDrawArrays(
            GL_TRIANGLE_FAN,
            55,
            8
        );


        // =================================================
        // PUPILAS
        // =================================================

        glDrawElements(
            GL_TRIANGLES,
            6,
            GL_UNSIGNED_INT,
            (void*)(21 * sizeof(unsigned int))
        );


        glDrawElements(
            GL_TRIANGLES,
            6,
            GL_UNSIGNED_INT,
            (void*)(27 * sizeof(unsigned int))
        );

        // =================================================
        // CONTORNO NEGRO DE LOS OJOS
        // =================================================

        glLineWidth(7.0f);


        // OJO IZQUIERDO
        glDrawArrays(
            GL_LINE_LOOP,
            124,
            4
        );


        // OJO DERECHO
        glDrawArrays(
            GL_LINE_LOOP,
            128,
            4
        );
        // =================================================
        // CONTORNO NEGRO DEL CUERPO
        // =================================================

        glLineWidth(7.0f);

        glDrawArrays(
            GL_LINE_STRIP,
            132,
            9
        );


        // =================================================
        // LINEAS INTERNAS DEL CUERPO
        // =================================================

        glDrawArrays(
            GL_LINES,
            141,
            4
        );

        // =================================================
        // BOCA
        // =================================================

        glDrawElements(
            GL_TRIANGLES,
            15,
            GL_UNSIGNED_INT,
            (void*)(33 * sizeof(unsigned int))
        );


        // =================================================
        // TRIANGULO ROJO CENTRAL ENCIMA
        // =================================================

        glDrawElements(
            GL_TRIANGLES,
            3,
            GL_UNSIGNED_INT,
            (void*)(6 * sizeof(unsigned int))
        );


        // =================================================
        // LINEAS DE LA CABEZA
        // =================================================

        glDrawArrays(
            GL_LINES,
            17,
            4
        );


        glDrawArrays(
            GL_LINES,
            21,
            6
        );


        // =================================================
        // CONTORNO DEL MENTON
        // =================================================

        glDrawArrays(
            GL_LINES,
            67,
            10
        );

        // =================================================
        // CONTORNO NEGRO DE LAS OREJAS
        // =================================================

        glLineWidth(8.0f);

        // Oreja izquierda
        glDrawArrays(
            GL_LINE_LOOP,
            118,
            3
        );

        // Oreja derecha
        glDrawArrays(
            GL_LINE_LOOP,
            121,
            3
        );
        // =================================================
        // CONTORNO NEGRO DE LA NARIZ
        // =================================================

        glLineWidth(7.0f);

        glDrawArrays(
            GL_LINE_LOOP,
            145,
            3
        );

        // =================================================
        // LINEA NEGRA HORIZONTAL DEL HOCICO
        // =================================================

        glLineWidth(7.0f);

        glDrawArrays(
            GL_LINES,
            148,
            2
        );

        // =================================================
        // BIGOTES NEGROS
        // =================================================

        glLineWidth(7.0f);

        // 5 bigotes izquierdos
        glDrawArrays(
            GL_LINES,
            150,
            10
        );

        // 5 bigotes derechos
        glDrawArrays(
            GL_LINES,
            160,
            10
        );

        glBindVertexArray(0);


        glfwSwapBuffers(window);
    }


    glfwTerminate();

    return EXIT_SUCCESS;
}


// =========================================================
// RESIZE
// =========================================================

void resize(
    GLFWwindow* window,
    int width,
    int height)
{
    glViewport(
        0,
        0,
        width,
        height
    );
}