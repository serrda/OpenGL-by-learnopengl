#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "stb_image.h"
#include <string>

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

	float texCoords[] = {
		 1.0f,  1.0f,
		 1.0f, -1.0f,
		-1.0f, -1.0f,
		-1.0f,  1.0f
	};

	unsigned int VBO, VAO, EBO, texture1, texture2;

	glGenVertexArrays(1, &VAO);		// Generating vertex array object
	glGenBuffers(1, &VBO);			// Generating vertex buffer object
	glGenBuffers(1, &EBO);			// Generating element buffer object

	glGenTextures(1, &texture1);		// Generating texture object
	glBindTexture(GL_TEXTURE_2D, texture1);
	// Setting the texture wrapping/filtering options(on currently bount texture oject)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);
	
	int width, height, nrChannels;
	std::string path = "textures/delogo.png";
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		/* Previous func args:
		1. Texture target
		2. Mipmap level - manual setting
		3. Format to store the texture - image has only rgb values so rgb values are stored (!!! Change for maps)
		4,5. Width, height - correspondingly
		6. Should always be 0 - legacy staff
		7,8. Format and datatype of source image - we loaded RGB values and stored as chars(bytes) (!!! Change for maps)
		9. Actual image data (pointer)
		*/
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << path << std::endl;
	}
	stbi_image_free(data);
		
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_REPEAT);
	path = "textures/awesomeface.png";
	data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		/* Previous func args:
		1. Texture target
		2. Mipmap level - manual setting
		3. Format to store the texture - image has only rgb values so rgb values are stored (!!! Change for maps)
		4,5. Width, height - correspondingly
		6. Should always be 0 - legacy staff
		7,8. Format and datatype of source image - we loaded RGB values and stored as chars(bytes) (!!! Change for maps)
		9. Actual image data (pointer)
		*/
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << path << std::endl;
	}
	stbi_image_free(data);


	// 1. Bind vertex array object
	glBindVertexArray(VAO);
	// 2. Copy our vertices array in a vertex buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. Copy our index array in an element buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 4. Then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	
	shader.use();
	shader.setUniform1i("texture1", 0);
	shader.setUniform1i("texture2", 1);

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); /* Sets a color to clear screen with. Function is a state-setting function*/
		glClear(GL_COLOR_BUFFER_BIT); /* Actually clears the screen. Function is a state using function. */

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture2);

		shader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		

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