#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

const GLchar* vertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 position;\n"
"layout(location = 1) in vec3 color;\n"
"out vec3 vertexColor;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"void main()\n"
"{\n"
"    gl_Position = projection * view * model * vec4(position.x, position.y, position.z, 1.0);\n"
"    vertexColor = color;\n"
"}\0";

const GLchar* fragmentShaderSource =
"#version 330 core\n"
"in vec3 vertexColor;\n"
"out vec4 fragmentColor;\n"
"void main()\n"
"{\n"
"    fragmentColor = vec4(vertexColor, 1.0);\n"
"}\0";

GLfloat cubeVertices[] = {
    // Prz�d
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f,    0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f,    0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,

    // Ty�
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,

    // Lewa �ciana
    -0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,

    // Prawa �ciana
    0.5f, 0.5f, 0.5f,    0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f,    0.0f, 0.0f, 1.0f,

    // G�rna �ciana
    -0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, 0.5f,    0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
    0.5f, 0.5f, -0.5f,   0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f, 0.5f, 0.5f,   0.0f, 0.0f, 1.0f,

    // Dolna �ciana
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, 0.5f,  0.0f, 0.0f, 1.0f
};

int main()
{
    // Inicjalizacja GLFW
    if (!glfwInit())
    {
        std::cerr << "Nie uda�o si� zainicjowa� GLFW" << std::endl;
        return -1;
    }

    // Utworzenie okna GLFW
    const unsigned int windowWidth = 800;
    const unsigned int windowHeight = 600;
    GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Sze�cian 3D", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Nie uda�o si� utworzy� okna GLFW" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Ustawienie okna GLFW jako bie��cego kontekstu OpenGL
    glfwMakeContextCurrent(window);

    // Inicjalizacja GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Nie uda�o si� zainicjowa� GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Ustawienie rozmiaru widoku
    glViewport(0, 0, windowWidth, windowHeight);

    // W��czenie testowania g��bi
    glEnable(GL_DEPTH_TEST);

    // Kompilacja i ��czenie shader�w
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLint status;
    GLchar error_message[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(vertexShader, 512, nullptr, error_message);
        std::cout << "B��d (Shader wierzcho�k�w): " << error_message << std::endl;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, error_message);
        std::cout << "B��d (Shader fragment�w): " << error_message << std::endl;
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if (!status)
    {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, error_message);
        std::cout << "B��d (Program shader�w): " << error_message << std::endl;
    }

    glDetachShader(shaderProgram, vertexShader);
    glDetachShader(shaderProgram, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Dane wierzcho�k�w
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    GLint modelLoc = glGetUniformLocation(shaderProgram, "model");
    GLint viewLoc = glGetUniformLocation(shaderProgram, "view");
    GLint projectionLoc = glGetUniformLocation(shaderProgram, "projection");

    // Zmienne kamery i transformacji
    glm::vec3 cameraPosition = glm::vec3(0.0f, 0.0f, 2.5f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

    float pitch = 0.0f;
    float yaw = -90.0f;
    float sensitivity = 0.075f;
    float cameraSpeed = 0.03f;

    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), static_cast<float>(windowWidth) / static_cast<float>(windowHeight), 0.1f, 100.0f);


    // G��wna p�tla
    while (!glfwWindowShouldClose(window))
    {
        // Przetwarzanie wej�cia
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            cameraPosition += cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            cameraPosition -= cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            cameraPosition -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            cameraPosition += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        static float previousX = static_cast<float>(windowWidth) / 2.0f;
        static float previousY = static_cast<float>(windowHeight) / 2.0f;
        float xdifference = xpos - previousX;
        float ydifference = previousY - ypos;
        previousX = xpos;
        previousY = ypos;
        xdifference *= sensitivity;
        ydifference *= sensitivity;
        yaw += xdifference;
        pitch += ydifference;
        if (pitch > 89.0f)
            pitch = 89.0f;
        if (pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 cameraFrontNew;
        cameraFrontNew.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFrontNew.y = sin(glm::radians(pitch));
        cameraFrontNew.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(cameraFrontNew);

        view = glm::lookAt(cameraPosition, cameraPosition + cameraFront, cameraUp);

        // Wyczyszczenie bufor�w koloru i g��bi
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // U�ycie programu shader�w
        glUseProgram(shaderProgram);

        // Ustawienie uniform�w
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        // Powi�zanie VAO i narysowanie sze�cianu
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        // Zamiana bufor�w przednich i tylnych
        glfwSwapBuffers(window);

        // Oczekiwanie na zdarzenia
        glfwPollEvents();
    }

    // Wyczyszczenie zasob�w
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // Zako�czenie GLFW
    glfwTerminate();

    return 0;
}