#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "stb_image.h"
#include "Shader.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"


int processInput(GLFWwindow* window, int currentInput)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		return 1;
	}
	
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		return 2;
	}

	if(glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		return 3;
	}

	if(glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		return 4;
	}

	return currentInput;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	
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
	
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glEnable(GL_DEPTH_TEST);
	
	float r = 0.f;
	float g = 0.f;
	float b = 0.f;
	
	Shader shader00("shader.vs", "fragment00.fs");
	Shader shader01("shader.vs", "fragment01.fs");
	
	constexpr float vertices[] = {
		// first triangle
		-0.9f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // left 
		-0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right
		-0.45f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // top 
		// second triangle
		 0.0f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, // left
		 0.9f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // right
		 0.45f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f // top 
	};

	float verticesSquare[] = {
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
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	}; 

	unsigned int VBO; //VERTEX BUFFER OBJECT
	unsigned int VAO; //VERTEX ARRAY OBJECT
	//unsigned int EBO; //ELEMENT BUFFER OBJECT
	
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);
	//glGenBuffers(1, &EBO);
	
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesSquare), verticesSquare, GL_STATIC_DRAW);
	

	// glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	// glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 5 * sizeof(float), static_cast<void*>(nullptr));
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(2,2,GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(2);

	// glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(6 * sizeof(float)));
	// glEnableVertexAttribArray(2);

	unsigned int VBO2; //VERTEX BUFFER OBJECT
	unsigned int VAO2; //VERTEX ARRAY OBJECT
	
	glGenBuffers(1, &VBO2);
	glGenVertexArrays(1, &VAO2);
	glBindVertexArray(VAO2);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 6 * sizeof(float), static_cast<void*>(nullptr));
	glEnableVertexAttribArray(0);
	
	glVertexAttribPointer(1,3,GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);

	//UNBINDING
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0);
	int userInput = 0;

	//TEXTURE WORK
	unsigned int texture1;
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	int width, height, nrChannels;
	unsigned char* data = stbi_load("E:\\CppProjects\\MyFirstOpenGLProject\\MyFirstOpenGLProject\\container.jpg", &width, &height, &nrChannels, 0);
	if(data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data);

	unsigned int texture2;
	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	int width2, height2, nrChannels2;
	stbi_set_flip_vertically_on_load(true);  
	unsigned char* data2 = stbi_load("E:\\CppProjects\\MyFirstOpenGLProject\\MyFirstOpenGLProject\\awesomeface.png", &width2, &height2, &nrChannels2, 0);
	if(data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	stbi_image_free(data2);
	
	shader00.use();
	glUniform1i(glGetUniformLocation(shader00.ID, "ourTexture0"), 0); // set it manually
	shader00.setInt("ourTexture1", 1); // or with shader class
	shader00.setFloat("visibility", 0.2f);


	//GOING 3D

	glm::mat4 model = glm::mat4(1.0f);
	//model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.5f, 0.0f)); 
	
	glm::mat4 view = glm::mat4(1.0f);
	view = glm::translate(view, glm::vec3(0.f,0.f,-3.f));
	
	glm::mat4 projection = glm::perspective(glm::radians(75.f), (800.f/600.f), 0.1f, 100.0f);
	//glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, 0.1f, 100.0f);

	
	glUniformMatrix4fv(glGetUniformLocation(shader00.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(shader00.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader00.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	
	shader01.use();
	glUniformMatrix4fv(glGetUniformLocation(shader01.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(glGetUniformLocation(shader01.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader01.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

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

	//CAMERA
	//glm::vec3 cameraPos (0.f,0.f,3.f);
	
	glm::vec3 cameraTarget(0.f,0.f,0.f);
	//glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);

	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f); 
	//glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));

	//glm::vec3 cameraUp = glm::cross(cameraDirection, cameraRight);
	
	const float radius = 10.0f;

	//CREATE CAMERA

	glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

	// glm::vec3 direction;
	// yaw = -90.0f;
	// direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	// direction.y = sin(glm::radians(pitch));
	// direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	
	float deltaTime = 0.0f;	
	float lastFrame = 0.0f; 
	
	float positionZ = -3.f;
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		userInput = processInput(window, userInput);

		glClearColor(r, g, b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shader00.use();
		float camX = sin(glfwGetTime()) * radius;
		float camZ = cos(glfwGetTime()) * radius;
		//view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		
		view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		glUniformMatrix4fv(glGetUniformLocation(shader00.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		//MATRIX TRANSFORMATIONS
		glm::mat4 trans = glm::mat4(1.f);
		//trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.f));
		//trans = glm::rotate(trans, static_cast<float>(glfwGetTime()), glm::vec3(1.0,0.0,0.0));
		//trans = glm::rotate(trans, static_cast<float>(glfwGetTime()), glm::vec3(0.0,0.5,0.0));
		//trans = glm::rotate(trans, static_cast<float>(glfwGetTime()), glm::vec3(0.0,0.0,1.0));
		//trans = glm::scale(trans, glm::vec3(0.5,0.5,0.5));
		
		if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			shader00.use();
			positionZ -= 0.01f;
			view = glm::translate(view, glm::vec3(0.f,0.f,positionZ));
			glUniformMatrix4fv(glGetUniformLocation(shader00.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		}
		
		
		if(userInput == 3)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		if(userInput == 4)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		
		if(userInput == 1)
		{
			shader00.use();
			glUniformMatrix4fv(glGetUniformLocation(shader00.ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
			if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
			{
				shader00.setFloat("visibility", 0.8f);
			}
			else if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
			{
				shader00.setFloat("visibility", 0.2f);
			}
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture1);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, texture2);
			glBindVertexArray(VAO);

			for(auto cube : cubePositions)
			{
				model = glm::mat4(1.0f);
				model = glm::translate(model, cube);
				model = glm::rotate(model, static_cast<float>(glfwGetTime()), glm::vec3(1.0f, 0.5f, 0.0f));
				glUniformMatrix4fv(glGetUniformLocation(shader00.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}
		else
		{
			shader01.use();
			glUniformMatrix4fv(glGetUniformLocation(shader01.ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
			glBindVertexArray(VAO2);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
		glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	shader00.deleteShader();
	shader01.deleteShader();
	glfwTerminate();

	return 0;
}