#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

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

	glViewport(0, 0, 800, 600); /* Telling OpenGL the size of our rendering window so it knows how we want to display the data and coordinates with respect to the window. Args: first 2 params - location of lower left corner of the window; last 2 params - location of the top right corner of window. */

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); /* Sets a color to clear screen with. Function is a state-setting function*/
		glClear(GL_COLOR_BUFFER_BIT); /* Actually clears the screen. Function is a state using function. */









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