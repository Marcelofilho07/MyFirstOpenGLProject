#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"

bool firstMouse = true;
float lastX = 400.f;
float lastY = 300.f;
float yaw = 0.f;
float pitch = 0.f;
float deltaTime = 0.f;
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

	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile("", aiProcess_Triangulate | aiProcess_FlipUVs); 

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
	glm::vec3 pointLightPositions[] = {
		glm::vec3( 0.7f,  0.2f,  2.0f),
		glm::vec3( 2.3f, -3.3f, -4.0f),
		glm::vec3(-4.0f,  2.0f, -12.0f),
		glm::vec3( 0.0f,  0.0f, -3.0f)
	};  
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
	
	
	const Texture textureContainer(R"(E:\CppProjects\MyFirstOpenGLProject\MyFirstOpenGLProject\resourcers\container2.png)", 0, true);
	const Texture textureContainerMetalBorder(R"(E:\CppProjects\MyFirstOpenGLProject\MyFirstOpenGLProject\resourcers\container2_specular.png)", 0, true);
	//const Texture textureAwesomeface(R"(E:\CppProjects\MyFirstOpenGLProject\MyFirstOpenGLProject\awesomeface.png)", 0, true);
	
	shader00.use();
	shader00.setInt("material.diffuse", 0);
	shader00.setInt("material.specular", 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureContainer.GetId());
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureContainerMetalBorder.GetId());
	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::perspective(glm::radians(75.f), (800.f/600.f), 0.1f, 100.0f);
	
	shader00.setMat4("model", model);
	shader00.setMat4("view", view);
	shader00.setMat4("projection", projection);

	shader00.setVec3("lightPos", lightPos);
	shader00.setFloat("material.shininess", 32.0f);
	shader00.setVec3("light.ambient",  glm::vec3(0.2f, 0.2f, 0.2f));
	shader00.setVec3("light.diffuse",  glm::vec3(0.5f, 0.5f, 0.5f));
	shader00.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f)); 
	shader00.setVec3("light.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
	shader00.setFloat("light.constant",  1.0f);
	shader00.setFloat("light.linear",    0.09f);
	shader00.setFloat("light.quadratic", 0.032f);
	shader00.setVec3("light.position",  fpsCamera.Position);
	shader00.setVec3("light.direction", fpsCamera.Front);
	shader00.setFloat("light.cutOff",   glm::cos(glm::radians(12.5f)));
	shader00.setFloat("light.outerCutOff",   glm::cos(glm::radians(17.5f)));

	shader00.setVec3("dirLight.direction", glm::vec3(-0.2f, -1.0f, -0.3f));
	shader00.setVec3("dirLight.ambient", glm::vec3(0.05f, 0.05f, 0.05f));
	shader00.setVec3("dirLight.diffuse",glm::vec3(0.4f, 0.4f, 0.4f));
	shader00.setVec3("dirLight.specular", glm::vec3(0.5f, 0.5f, 0.5f));
	/*-------------------------------*/
	shader00.setVec3("pointLights[0].position", glm::vec3( 0.7f,  0.2f,  2.0f));
	shader00.setFloat("pointLights[0].constant", 1.0f);
	shader00.setFloat("pointLights[0].linear", 0.09f);
	shader00.setFloat("pointLights[0].quadratic", 0.032f);
	shader00.setVec3("pointLights[0].ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	shader00.setVec3("pointLights[0].diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	shader00.setVec3("pointLights[0].specular",glm::vec3(1.0f, 1.0f, 1.0f));

	shader00.setVec3("pointLights[1].position", glm::vec3( 2.3f, -3.3f, -4.0f));
	shader00.setFloat("pointLights[1].constant", 1.0f);
	shader00.setFloat("pointLights[1].linear", 0.09f);
	shader00.setFloat("pointLights[1].quadratic", 0.032f);
	shader00.setVec3("pointLights[1].ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	shader00.setVec3("pointLights[1].diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	shader00.setVec3("pointLights[1].specular",glm::vec3(1.0f, 1.0f, 1.0f));

	shader00.setVec3("pointLights[2].position", glm::vec3(-4.0f,  2.0f, -12.0f));
	shader00.setFloat("pointLights[2].constant", 1.0f);
	shader00.setFloat("pointLights[2].linear", 0.09f);
	shader00.setFloat("pointLights[2].quadratic", 0.032f);
	shader00.setVec3("pointLights[2].ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	shader00.setVec3("pointLights[2].diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	shader00.setVec3("pointLights[2].specular",glm::vec3(1.0f, 1.0f, 1.0f));

	shader00.setVec3("pointLights[3].position", glm::vec3( 0.0f,  0.0f, -3.0f));
	shader00.setFloat("pointLights[3].constant", 1.0f);
	shader00.setFloat("pointLights[3].linear", 0.09f);
	shader00.setFloat("pointLights[3].quadratic", 0.032f);
	shader00.setVec3("pointLights[3].ambient", glm::vec3(0.2f, 0.2f, 0.2f));
	shader00.setVec3("pointLights[3].diffuse", glm::vec3(0.5f, 0.5f, 0.5f));
	shader00.setVec3("pointLights[3].specular",glm::vec3(1.0f, 1.0f, 1.0f));
	/*-------------------------------*/
	shader00.setVec3("spotLight.position", fpsCamera.Position);
	shader00.setVec3("spotLight.direction", fpsCamera.Front);
	shader00.setVec3("spotLight.ambient", glm::vec3(0.0f, 0.0f, 0.0f));
	shader00.setVec3("spotLight.diffuse", glm::vec3(1.0f, 1.0f, 1.0f));
	shader00.setVec3("spotLight.specular", glm::vec3(1.0f, 1.0f, 1.0f));
	shader00.setFloat("spotLight.constant", 1.0f);
	shader00.setFloat("spotLight.linear", 0.09f);
	shader00.setFloat("spotLight.quadratic", 0.032f);
	shader00.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
	shader00.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
	
	lightSourceShader.use();
	lightSourceShader.setMat4("model", model);
	lightSourceShader.setMat4("view", view);
	lightSourceShader.setMat4("projection", projection);
	

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
	
	// LIGHT

	unsigned int lightVAO;
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 8 * sizeof(float), static_cast<void*>(nullptr));
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//lightShader.use();
	//lightShader.setVec3("objectColor", glm::vec3( 1.0f, 0.5f, 0.31f));
	//lightShader.setVec3("lightColor", glm::vec3( 1.0f, 1.0f, 1.0f));

	
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
		//shader00.setVec3("viewPos", fpsCamera.Position);
		//shader00.setVec3("lightPos", glm::vec3(glm::sin(static_cast<float>(glfwGetTime())) * 2 * lightPos.x,(glm::sin(static_cast<float>(glfwGetTime()))/2) * lightPos.y,glm::cos(static_cast<float>(glfwGetTime())) * 2 * lightPos.z));
		
		//shader00.setVec3("lightPos", fpsCamera.Position);
		shader00.setVec3("spotLight.position", fpsCamera.Position);
		shader00.setVec3("spotLight.direction", fpsCamera.Front);
		
		glBindVertexArray(VAO);

		for(auto cube : cubePositions)
		{
			model = glm::mat4(1.0f);
			model = glm::translate(model,  cube);
			//model = glm::rotate(model, static_cast<float>(glfwGetTime()), glm::vec3(1.0f, 0.5f, 0.0f));
			//model = glm::scale(model, glm::vec3(1.0f));
			shader00.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		glBindVertexArray(0);

		
		lightSourceShader.use();
		glBindVertexArray(lightVAO);
		
		for(auto LightCubes : pointLightPositions)
		{
			lightSourceShader.setMat4("view", view);
			model = glm::mat4(1.0f);
			//model = glm::translate(model, glm::vec3(glm::sin(static_cast<float>(glfwGetTime())) * 2 * lightPos.x,(glm::sin(static_cast<float>(glfwGetTime()))/2) * lightPos.y, glm::cos(static_cast<float>(glfwGetTime())) * 2 * lightPos.z));
			model = glm::translate(model, LightCubes);
			model = glm::scale(model, glm::vec3(0.2f));
			lightSourceShader.setMat4("model", model);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		
		
		glBindVertexArray(0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	shader00.deleteShader();
	lightSourceShader.deleteShader();
	glfwTerminate();

	return 0;
}


void func(int a)
{

}