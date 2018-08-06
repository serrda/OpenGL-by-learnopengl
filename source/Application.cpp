#include <iostream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image/stb_image.h"

#include "Shader.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Texture.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"
#include "Camera.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// Timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

glm::vec3 lightPos(1.0f, 0.0f, 2.0f);

int main()
{
	// We initialize GLFW. 
	glfwInit(); //Function returns GL_TRUE/GL_FALSE
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Function sets version 3.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // Function sets version .3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Function sets core version

	GLFWwindow * window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Starting OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	
	// Initialising GLAD, that manages function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialise GLAD" << std::endl;
		return -1;
	}

	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glEnable(GL_DEPTH_TEST);

	//glViewport(0, 0, 800, 600);  
	/* Telling OpenGL the size of our rendering window so it knows how we
	want to display the data and coordinates with respect to the window.
	Args: first 2 params - location of lower left corner of the window;
	last 2 params - location of the top right corner of window. */
	/* Function configures how primitives are drawn
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	*/

	Shader shader("shaders/vertex.shader", "shaders/fragment.shader");
	Shader lightShader("shaders/lightV.shader", "shaders/lightF.shader");

	float vertices[] = {
		// positions          // normals           // texture coords
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
	};

	glm::vec3 cubePositions[] = {
		glm::vec3(-1.5f, -2.2f, -2.5f),
	};

	
	VertexArray va;
	VertexBuffer vb(vertices, sizeof(vertices));						
	VertexArray lightVAO;
	VertexBuffer lightVBO(vertices, sizeof(lightPos));	
	
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);

	va.AddBuffer(vb, layout);
	lightVAO.AddBuffer(lightVBO, layout);

	Renderer engine;
	
	Texture box;
	box.LoadImg("textures/container2.png", GL_RGBA);
	
	Texture specular_box;
	specular_box.LoadImg("textures/container2_specular.png", GL_RGBA);
	

	shader.use();
	shader.setUniform1i("material.diffuse", 0);
	shader.setUniform1i("material.specular", 1);

	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = (float)glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		processInput(window);
		
		engine.Clear();

		engine.Draw(va, shader);

		shader.use();
		shader.setUniform3f("light.position", lightPos);
		shader.setUniform3f("viewPos", camera.Position);
		
		shader.setUniform3f("light.ambient", glm::vec3(0.2f, 0.2f, 0.2f));
		shader.setUniform3f("light.diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
		shader.setUniform3f("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));
		
		shader.setUniform1f("material.shininess", 64.0f);
		

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera.Zoom), (float)(SCR_WIDTH / SCR_HEIGHT), 0.1f, 100.0f);
		glm::mat4 view = camera.GetViewMatrix();

		shader.setUniformMatrix4fv("projection", projection);
		shader.setUniformMatrix4fv("view", view);

		glm::mat4 model;
		shader.setUniformMatrix4fv("model", model);
		va.Bind();

		box.Bind(0);
		specular_box.Bind(1);


		lightShader.use();
		
		lightShader.setUniformMatrix4fv("projection", projection);
		lightShader.setUniformMatrix4fv("view", view);
		glm::mat4 lightModel;
		lightModel = glm::translate(lightModel, lightPos);
		lightModel = glm::scale(lightModel, glm::vec3(0.2f));
		lightShader.setUniformMatrix4fv("model", lightModel);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		





		glfwSwapBuffers(window); /* Swaps the color buffer(buffer that contains color values for each pixel in GLFW's window) that has been used to draw in during this iteration and show it as output to the screen */
		glfwPollEvents(); /* Checks if any events are triggered(like keyboard input or mouse movement events), updates window state, and calls corresponding functions(callback methods)*/
	}
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}
	float xoffset = (float)xpos - lastX;
	float yoffset = lastY - (float)ypos;

	lastX = (float)xpos;
	lastY = (float)ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll((float)yoffset);
}