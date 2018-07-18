#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

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

	float vertices[] = {
		 0.5f,  0.5f,  0.0f,  // top right		#0
		 0.5f, -0.5f,  0.0f,  // bottom right	#1
		-0.5f, -0.5f,  0.0f,  // bottom left	#2
		-0.5f,  0.5f,  0.0f   // top left		#3
	};

	unsigned int indices[] = {
		0, 1, 3,
		1, 2, 3
	};

	//binding it with variable, initialising it
	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	glGenVertexArrays(1, &VAO);		// Generating vertex array object
	glGenBuffers(1, &VBO);			// Generating vertex buffer object
	glGenBuffers(1, &EBO);			// Generating element buffer object

	// 1. Bind vertex array object
	glBindVertexArray(VAO);
	// 2. Copy our vertices array in a vertex buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// 3. Copy our index array in an element buffer for OpenGL to use
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// 4. Then set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);




	/* Vertex Shader 
	   1. Creating shader
	   2. Attaching it to its source code(stored as const char*)
	   3. Compiling shader
	   4. Shader ready to use */
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	
	/* Fragment Shader
	1. Creating shader
	2. Attaching it to its source code(stored as const char*)
	3. Compiling shader
	4. Shader ready to use */
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	/* Shader Program
	   Is the final linked version of multiple shaders combined.
	   1. Create program
	   2. Attach shaders one by one to this program
	   3. Link them after attaching
	*/
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	
	// To use a program:
	
	// And then delete shaderobjects once they are linked to the program
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	/* Function configures how primitives are drawn
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	*/
	while (!glfwWindowShouldClose(window))
	{
		processInput(window);
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); /* Sets a color to clear screen with. Function is a state-setting function*/
		glClear(GL_COLOR_BUFFER_BIT); /* Actually clears the screen. Function is a state using function. */


		glUseProgram(shaderProgram);
		
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);




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