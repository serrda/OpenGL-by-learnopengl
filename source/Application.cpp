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

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


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

	glViewport(0, 0, 800, 600);  
	/* Telling OpenGL the size of our rendering window so it knows how we
	want to display the data and coordinates with respect to the window.
	Args: first 2 params - location of lower left corner of the window;
	last 2 params - location of the top right corner of window. */
	/* Function configures how primitives are drawn

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	*/

	Shader shader("shaders/vertex.shader", "shaders/fragment.shader");

	float vertices[] = {	
		 // positions         // colors			   // texture coords
		 0.5f,  0.5f,  0.0f,  1.0f, 0.0f, 0.0f,    1.0f,  1.0f,	// top right	#0
		 0.5f, -0.5f,  0.0f,  0.0f, 1.0f, 0.0f,    1.0f,  0.0f,	// bottom right	#1
		-0.5f, -0.5f,  0.0f,  0.0f, 0.0f, 1.0f,    0.0f,  0.0f,	// bottom left	#2
		-0.5f,  0.5f,  0.0f,  1.0f, 1.0f, 0.0f,    0.0f,  1.0f	// top left		#3
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	VertexArray va;														// Generating vertex array object
	VertexBuffer vb(vertices, sizeof(vertices));						// Generating vertex buffer object
	ElementBuffer eb(indices, 6);										// Generating element buffer object

	Texture texture1("textures/delogo.png", GL_RGB);					// Generating texture objects:	#1
	Texture texture2("textures/awesomeface.png", GL_RGBA);				//								#2
	//glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	//glm::mat4 trans;
	//trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
	//vec = trans * vec;
	//std::cout << vec.x << vec.y << vec.z << std::endl;

	
	
	
	
	VertexBufferLayout layout;
	layout.Push<float>(3);
	layout.Push<float>(3);
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	
	
	
	shader.use();
	shader.setUniform1i("texture1", 0);
	shader.setUniform1i("texture2", 1);

	Renderer engine;

	texture1.Bind(0);
	texture2.Bind(1);
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		engine.Clear();
		engine.Draw(va, eb, shader);
		
		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));

		shader.setUniformMatrix4fv("transform", trans);


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
}