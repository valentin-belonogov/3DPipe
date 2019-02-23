#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

static void
pipe(GLfloat internal_radius, GLfloat external_radius, GLfloat length,
	GLint segments)
{	
}

//Draw function
static void draw(void)
{
}

//Input keys handling
void key_press(GLFWwindow* window, int k, int l, int action)
{
}

//Mouse wheel handling
int scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
}

//Rotating with mouse
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
}

//window
void setwindow(GLFWwindow* window, int width, int height)
{
	GLfloat h = (GLfloat)height / (GLfloat)width;
	GLfloat xmax, znear, zfar;

	znear = 5.0f;
	zfar = 30.0f;
	xmax = znear * 0.5f;

	glViewport(0, 0, (GLint)width, (GLint)height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-xmax, xmax, -xmax*h, xmax*h, znear, zfar);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -20.0);
}

static void init(void)
{	
	//light position
	static GLfloat pos[4] = { 0.f, 0.f, 10.f, 0.f };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
}

int main(int argc, char *argv[])
{
	GLFWwindow* window;
	int width, height;

	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		exit(EXIT_FAILURE);
	}
	
	glfwWindowHint(GLFW_DEPTH_BITS, 16);
	window = glfwCreateWindow(1280, 720, "Pipe", NULL, NULL);

	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	glfwSwapInterval(1);

	glfwGetFramebufferSize(window, &width, &height);
	setwindow(window, width, height);

	init();

	while (!glfwWindowShouldClose(window))
	{
		// Draw the pipe
		draw();
		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

