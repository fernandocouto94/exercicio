#include <glad/glad.h>
#include <GLFW/glfw3.h>


#define STB_IMAGE_IMPLEMENTATION

#include "common/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_m.h"

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Cubinho", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    Shader ourShader("C:/Users/Naná/source/repos/folha7/folha7/texture.vs", "C:/Users/Naná/source/repos/folha7/folha7/texture.fs");

    float vertices[] = {

        //offset 0, tamanho 3   offset 3, tamanho 2,      offset 8, tamanho 3
        //Vertices do cubo      // vertices na textura    // cor (último vértice seleciona a textura, valores 0 e 1)
        -1.0f, -1.0f, -1.0f,    0.0f, 0.0f,   1.0f,  1.0f,  1.0f, 0.0f,
        1.0f,  -1.0f, -1.0f,    1.0f, 0.0f,   1.0f,  1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  -1.0f,    1.0f, 1.0f,   1.0f,  1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  -1.0f,    1.0f, 1.0f,   1.0f,  1.0f,  1.0f, 0.0f,
        -1.0f, 1.0f,  -1.0f,    0.0f, 1.0f,   1.0f,  1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f,    0.0f, 0.0f,   1.0f,  1.0f,  1.0f, 0.0f,

        -1.0f, -1.0f, 1.0f,     0.0f, 0.0f,   1.0f,  1.0f,  1.0f, 0.0f,
        1.0f,  -1.0f, 1.0f,     1.0f, 0.0f,   1.0f,  1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f,     1.0f, 1.0f,   1.0f,  1.0f,  1.0f, 0.0f,
        1.0f,  1.0f,  1.0f,     1.0f, 1.0f,   1.0f,  1.0f,  1.0f, 0.0f,
        -1.0f, 1.0f,  1.0f,     0.0f, 1.0f,   1.0f,  1.0f,  1.0f, 0.0f,
        -1.0f, -1.0f, 1.0f,     0.0f, 0.0f,   1.0f,  1.0f,  1.0f, 0.0f,

        -1.0f, 1.0f,  1.0f,     1.0f, 0.0f,   0.00f,  1.0f,  1.0f, 1.0f,
        -1.0f, 1.0f,  -1.0f,    1.0f, 1.0f,   0.00f,  1.0f,  1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,    0.0f, 1.0f,   0.00f,  1.0f,  1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,    0.0f, 1.0f,   0.00f,  1.0f,  1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,     0.0f, 0.0f,   0.00f,  1.0f,  1.0f, 1.0f,
        -1.0f, 1.0f,  1.0f,     1.0f, 0.0f,   0.00f,  1.0f,  1.0f, 1.0f,

        1.0f, 1.0f,  1.0f,      1.0f, 0.0f,   0.00f,  1.0f,  0.0f, 1.0f,
        1.0f, 1.0f,  -1.0f,     1.0f, 1.0f,   0.00f,  1.0f,  0.0f, 1.0f,
        1.0f, -1.0f, -1.0f,     0.0f, 1.0f,   0.00f,  1.0f,  0.0f, 1.0f,
        1.0f, -1.0f, -1.0f,     0.0f, 1.0f,   0.00f,  1.0f,  0.0f, 1.0f,
        1.0f, -1.0f, 1.0f,      0.0f, 0.0f,   0.00f,  1.0f,  0.0f, 1.0f,
        1.0f, 1.0f,  1.0f,      1.0f, 0.0f,   0.00f,  1.0f,  0.0f, 1.0f,

        -1.0f, -1.0f, -1.0f,    0.0f, 1.0f,   0.00f,  1.0f,  1.0f, 1.0f,
        1.0f,  -1.0f, -1.0f,    1.0f, 1.0f,   0.00f,  1.0f,  1.0f, 1.0f,
        1.0f,  -1.0f, 1.0f,     1.0f, 0.0f,   0.00f,  1.0f,  1.0f, 1.0f,
        1.0f,  -1.0f, 1.0f,     1.0f, 0.0f,   0.00f,  1.0f,  1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,     0.0f, 0.0f,   0.00f,  1.0f,  1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,    0.0f, 1.0f,   0.00f,  1.0f,  1.0f, 1.0f,

        -1.0f, 1.0f, -1.0f,     0.0f, 1.0f,   1.00f,  0.0f,  0.0f, 1.0f,
        1.0f,  1.0f, -1.0f,     1.0f, 1.0f,   1.00f,  0.0f,  0.0f, 1.0f,
        1.0f,  1.0f, 1.0f,      1.0f, 0.0f,   1.00f,  0.0f,  0.0f, 1.0f,
        1.0f,  1.0f, 1.0f,      1.0f, 0.0f,   1.00f,  0.0f,  0.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,      0.0f, 0.0f,   1.00f,  0.0f,  0.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,     0.0f, 1.0f,   1.00f,  0.0f,  1.0f, 1.0f
    };
    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //     location, tamanho, ..., ..., tamanho de cada stride (linha), offset


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(5 * sizeof(float)));
    //na localização 2 do vertex shader, ver ficheiro
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(8 * sizeof(float)));
    glEnableVertexAttribArray(3);

    // load and create a texture
    // -------------------------
    unsigned int texture1, texture2;
    // texture 1
    // ---------
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
    unsigned char* data = stbi_load("C:/Users/Naná/source/repos/folha7/folha7/i.jpg", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);



    //textura dois
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load("C:/Users/Naná/source/repos/folha7/folha7/a.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        // note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);





    //pomos as texturas para o fragment shader
    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);


    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f); //cor de fundo branca
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);
        ourShader.use();

        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 0.0f, 0.6f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -10.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");

        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);

        ourShader.setMat4("projection", projection);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
