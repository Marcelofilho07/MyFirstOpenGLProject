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
	Shader lightShader("lightShader.vs", "fragmentLight.fs");
	Shader lightSourceShader("lightShader.vs", "lightSourceFragment.fs");

	constexpr float verticesSquare[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, 
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f,  
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,  
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f,  
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f,  
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f,  

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f, 0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f
   };
	
	glm::vec3 lightPos(1.2f, 1.0f, -2.0f);
	/*
	 * VERTEX BUFFER OBJECT:
	 * An OpenGL object responsible to store Vertex data in the GPU's memory
	 * we can send large batches of data all at once to the graphics card,
	 * and keep it there if there's enough memory left,
	 * without having to send data one vertex at a time.
	 * Sending data to the graphics card from the CPU is relatively slow,
	 * so wherever we can we try to send as much data as possible at once.
	 * Once the data is in the graphics card's memory the vertex shader
	 * has almost instant access to the vertices making it extremely fast
	*/

	/*
	 * VERTEX ARRAY OBJECT:
	 * An OpenGL object used to store VBOs.
	 * Whenever you bind a VBO using "glBindBuffer" inside the scope
	 * of "glBindVertexArray" it will bind the VBO to the VAO.
	 */
	
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesSquare), verticesSquare, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 8 * sizeof(float), static_cast<void*>(nullptr));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6* sizeof(float)));
	glEnableVertexAttribArray(2);
	
	glBindVertexArray(0);
	
	
	const Texture textureContainer(R"(E:\CppProjects\MyFirstOpenGLProject\MyFirstOpenGLProject\container.jpg)", 0, false);
	const Texture textureAwesomeface(R"(E:\CppProjects\MyFirstOpenGLProject\MyFirstOpenGLProject\awesomeface.png)", 0, true);
	
	shader00.use();
	shader00.setInt("ourTexture0", 0);
	shader00.setInt("ourTexture1", 1);
	shader00.setFloat("visibility", 0.2f);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureContainer.GetId());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureAwesomeface.GetId());

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::perspective(glm::radians(75.f), (800.f/600.f), 0.1f, 100.0f);
	
	shader00.setMat4("model", model);
	shader00.setMat4("view", view);
	shader00.setMat4("projection", projection);

	shader00.setVec3("objectColor", glm::vec3( 1.0f, 0.5f, 0.31f));
	shader00.setVec3("lightColor", glm::vec3( 1.0f, 1.0f, 1.0f));

	shader00.setVec3("lightPos", lightPos);
	shader00.setVec3("viewPos", fpsCamera.Position);
	
	lightSourceShader.use();
	lightSourceShader.setMat4("model", model);
	lightSourceShader.setMat4("view", view);
	lightSourceShader.setMat4("projection", projection);
	

	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  -1.0f)//,
		// glm::vec3( 2.0f,  5.0f, -15.0f), 
		// glm::vec3(-1.5f, -2.2f, -2.5f),  
		// glm::vec3(-3.8f, -2.0f, -12.3f),  
		// glm::vec3( 2.4f, -0.4f, -3.5f),  
		// glm::vec3(-1.7f,  3.0f, -7.5f),  
		// glm::vec3( 1.3f, -2.0f, -2.5f),  
		// glm::vec3( 1.5f,  2.0f, -2.5f), 
		// glm::vec3( 1.5f,  0.2f, -1.5f), 
		// glm::vec3(-1.3f,  1.0f, -1.5f)  
	};
	
	// LIGHT

	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 8 * sizeof(float), static_cast<void*>(nullptr));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	lightShader.use();
	lightShader.setVec3("objectColor", glm::vec3( 1.0f, 0.5f, 0.31f));
	lightShader.setVec3("lightColor", glm::vec3( 1.0f, 1.0f, 1.0f));
	
	
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
		shader00.setMat4("view", view);


		glBindVertexArray(VAO);

		for(auto cube : cubePositions)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model, cube);
			model = glm::rotate(model, static_cast<float>(glfwGetTime()), glm::vec3(1.0f, 0.5f, 0.0f));
			model = glm::scale(model, glm::vec3(1.0f));
			shader00.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);
		
		
		lightSourceShader.use();
		lightSourceShader.setMat4("view", view);
		model = glm::mat4(1.0f);
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2f));
		lightSourceShader.setMat4("model", model);
		glBindVertexArray(lightVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		
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