#include <iostream>

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main(void)
{
	std::cout << "====================================================================================================" << std::endl;
	std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << "====================================================================================================" << std::endl;
	std::cout << std::endl;

	if (!glfwInit())
	{
		std::cout << "====================================================================================================" << std::endl;
		std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "====================================================================================================" << std::endl;
		std::cout << std::endl;

		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	constexpr int DisplayerWindowWidth = 800;
	constexpr int DisplayerWindowHeight = 800;
	const char* DisplayerWindowTitle = "COMPUTER GRAPHICS PROJECT";

	GLFWwindow*  displayerWindowContainer = glfwCreateWindow(DisplayerWindowWidth, DisplayerWindowHeight, DisplayerWindowTitle, NULL, NULL);

	if (!displayerWindowContainer)
	{
		std::cout << "====================================================================================================" << std::endl;
		std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "====================================================================================================" << std::endl;
		std::cout << std::endl;

		glfwTerminate();

		return -1;
	}

	glfwMakeContextCurrent(displayerWindowContainer);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "====================================================================================================" << std::endl;
		std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
		std::cout << "====================================================================================================" << std::endl;
		std::cout << std::endl;

		glfwTerminate();

		return -1;
	}

	glViewport(0, 0, DisplayerWindowWidth, DisplayerWindowHeight);

	glfwSetFramebufferSizeCallback(displayerWindowContainer,
		[](GLFWwindow* paramWindowContainer, int paramWindowWidth, int paramWindowHeight)
		{
			glViewport(0, 0, paramWindowWidth, paramWindowHeight);
		});

	const GLchar* vertexShaderSource =
		"#version 330 core\n"
		"layout (location = 0) in vec4 vertexPosition;\n"
		"layout (location = 1) in vec4 vertexColor;\n"
		"out vec4 g_l_vertexColor;\n"
		"uniform mat4 modelTransform;\n"
		"void main()\n"
		"{\n"
		"\tgl_Position = modelTransform * vec4(vertexPosition.x, vertexPosition.y, vertexPosition.z, vertexPosition.w);\n"
		"\tg_l_vertexColor = vec4(vertexColor.r, vertexColor.g, vertexColor.b, vertexColor.a);\n"
		"}\n\0";

	GLuint vertexShaderIdentifier = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShaderIdentifier, 1, &vertexShaderSource, NULL);

	glCompileShader(vertexShaderIdentifier);

	const GLchar* fragmentShaderSource = 
		"#version 330 core\n"
		"out vec4 fragmentColor;\n"
		"in vec4 g_l_vertexColor;\n"
		"void main()\n"
		"{\n"
		"\tfragmentColor = vec4(g_l_vertexColor.r, g_l_vertexColor.g, g_l_vertexColor.b, g_l_vertexColor.a);\n"
		"}\n\0";

	GLuint fragmentShaderIdentifier = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShaderIdentifier, 1, &fragmentShaderSource, NULL);

	glCompileShader(fragmentShaderIdentifier);

	GLuint shaderProgramIdentifier = glCreateProgram();

	glAttachShader(shaderProgramIdentifier, vertexShaderIdentifier);

	glAttachShader(shaderProgramIdentifier, fragmentShaderIdentifier);

	glLinkProgram(shaderProgramIdentifier);

	glDeleteShader(vertexShaderIdentifier);

	glDeleteShader(fragmentShaderIdentifier);

	GLuint vertexArrayIdentifier;

	GLuint vertexBufferIdentifier;

	GLuint indexBufferIdentifier;

	const GLuint vertexBufferLength = 32;

	GLfloat vertexBufferArray[vertexBufferLength] = {
		-0.75f, -0.75f, +0.0f, +1.0f,
		+1.0f, +0.0f, +0.0f, +1.0f,
		-0.75f, +0.75f, +0.0f, +1.0f,
		+0.0f, +1.0f, +0.0f, +1.0f,
		+0.75f, -0.75f, +0.0f, +1.0f,
		+0.0f, +0.0f, +1.0f, +1.0f,
		+0.75f, +0.75f, +0.0f, +1.0f,
		+1.0f, +1.0f, +1.0f, +1.0f
	};

	const GLuint indexBufferLength = 6;

	GLuint indexBufferArray[indexBufferLength] = {
		0, 1, 2,
		2, 1, 3
	};

	glGenVertexArrays(1, &vertexArrayIdentifier);

	glGenBuffers(1, &vertexBufferIdentifier);

	glGenBuffers(1, &indexBufferIdentifier);

	glBindVertexArray(vertexArrayIdentifier);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferIdentifier);

	glBufferData(GL_ARRAY_BUFFER, vertexBufferLength * sizeof(GLfloat), vertexBufferArray, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferIdentifier);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferLength * sizeof(GLuint), indexBufferArray, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (const GLvoid*)(0 * sizeof(GLfloat)));

	glEnableVertexAttribArray(1);
	
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (const GLvoid*)(4 * sizeof(GLfloat)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	while (!glfwWindowShouldClose(displayerWindowContainer))
	{
		if(glfwGetKey(displayerWindowContainer, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(displayerWindowContainer, GL_TRUE);
		}

		glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgramIdentifier);

		GLuint modelTransformLocation = glGetUniformLocation(shaderProgramIdentifier, "modelTransform");

		glm::mat4 modelTransform = glm::identity<glm::mat4>();
		modelTransform = glm::translate(modelTransform, glm::vec3(0.5f, -0.25f, 0.0));
		modelTransform = glm::rotate(modelTransform, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		modelTransform = glm::scale(modelTransform, glm::vec3(0.5f, 1.0f, 1.0f));

		glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, glm::value_ptr(modelTransform));

		glBindVertexArray(vertexArrayIdentifier);

		glDrawElements(GL_TRIANGLES, indexBufferLength, GL_UNSIGNED_INT, (const void*)0);

		glfwSwapBuffers(displayerWindowContainer);

		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vertexArrayIdentifier);

	glDeleteBuffers(1, &vertexBufferIdentifier);

	glDeleteBuffers(1, &indexBufferIdentifier);

	glDeleteProgram(shaderProgramIdentifier);

	glfwDestroyWindow(displayerWindowContainer);

	glfwTerminate();

	std::cout << std::endl;
	std::cout << "====================================================================================================" << std::endl;
	std::cout << "PRESS [ENTER] KEY TO CLOSE CONSOLE..." << std::endl;
	std::cout << "====================================================================================================" << std::endl;
	std::cout << std::endl;

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::cout << "====================================================================================================" << std::endl;
	std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << "====================================================================================================" << std::endl;

	return std::cin.get();
}
