#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

bool firstMouse = true;
float lastX = 400.f;
float lastY = 300.f;
float yaw = 0.f;
float pitch = 0.f;
float deltaTime = 0.f;
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
Camera fpsCamera;


void processInput(GLFWwindow* window)
{
	
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		fpsCamera.ProcessKeyboard(FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		fpsCamera.ProcessKeyboard(BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		fpsCamera.ProcessKeyboard(LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		fpsCamera.ProcessKeyboard(RIGHT, deltaTime);
	}
}
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
  
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; 
	lastX = xpos;
	lastY = ypos;

	fpsCamera.ProcessMouseMovement(xoffset, yoffset);
}

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", nullptr, nullptr);
	if(window == nullptr)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouse_callback);
	
	if(!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glEnable(GL_DEPTH_TEST);
	
	constexpr float r = 0.f;
	constexpr float g = 0.f;
	constexpr float b = 0.f;
	
	Shader shader00("shader.vs", "fragment00.fs");

	constexpr float verticesSquare[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,  
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 
 
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 
 
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 
 
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 
 
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 
 
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f 
   };

	unsigned int VBO; //VERTEX BUFFER OBJECT
	unsigned int VAO; //VERTEX ARRAY OBJECT
	
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesSquare), verticesSquare, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 5 * sizeof(float), static_cast<void*>(nullptr));
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(2);

	//UNBINDING
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0);

	const Texture txt1(R"(E:\CppProjects\MyFirstOpenGLProject\MyFirstOpenGLProject\container.jpg)", 0, false);
	const Texture txt2(R"(E:\CppProjects\MyFirstOpenGLProject\MyFirstOpenGLProject\awesomeface.png)", 0, true);
	
	shader00.use();
	glUniform1i(glGetUniformLocation(shader00.ID, "ourTexture0"), 0); // set it manually
	shader00.setInt("ourTexture1", 1); // or with shader class
	shader00.setFloat("visibility", 0.2f);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, txt1.GetId());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, txt2.GetId());

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::perspective(glm::radians(75.f), (800.f/600.f), 0.1f, 100.0f);

	
	glUniformMatrix4fv(glGetUniformLocation(shader00.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(shader00.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader00.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	

	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f), 
		glm::vec3( 2.0f,  5.0f, -15.0f), 
		glm::vec3(-1.5f, -2.2f, -2.5f),  
		glm::vec3(-3.8f, -2.0f, -12.3f),  
		glm::vec3( 2.4f, -0.4f, -3.5f),  
		glm::vec3(-1.7f,  3.0f, -7.5f),  
		glm::vec3( 1.3f, -2.0f, -2.5f),  
		glm::vec3( 1.5f,  2.0f, -2.5f), 
		glm::vec3( 1.5f,  0.2f, -1.5f), 
		glm::vec3(-1.3f,  1.0f, -1.5f)  
	};
	
	float lastFrame = 0.0f; 
	
	while (!glfwWindowShouldClose(window))
	{
		const float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glClearColor(0.f, 0.f, 0.f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		processInput(window);
		view = fpsCamera.GetViewMatrix();

		
		shader00.use();
		glUniformMatrix4fv(glGetUniformLocation(shader00.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));


		glBindVertexArray(VAO);

		for(auto cube : cubePositions)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cube);
			model = glm::rotate(model, static_cast<float>(glfwGetTime()), glm::vec3(1.0f, 0.5f, 0.0f));
			glUniformMatrix4fv(glGetUniformLocation(shader00.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	
		glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	shader00.deleteShader();
	glfwTerminate();

	return 0;
}