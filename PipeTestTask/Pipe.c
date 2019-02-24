#define _USE_MATH_DEFINES
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
	GLfloat r0, r1;
	GLfloat angle, AngleNorm;
	GLint i;
	GLfloat u, v;

	r0 = internal_radius;
	r1 = external_radius;
	AngleNorm = 2.f * (float)M_PI / segments;
	glShadeModel(GL_FLAT);
	glNormal3f(0.f, 0.f, 1.f);

	// Pipe's front face
	glBegin(GL_QUAD_STRIP);
	for (i = 0; i <= segments; i++) {
		angle = i * 2.f * (float)M_PI / segments;
		glVertex3f((float)cos(angle) * r0, (float)sin(angle) * r0, length * 0.5f);
		glVertex3f((float)cos(angle) * r1, (float)sin(angle) * r1, length * 0.5f);
	}
	glEnd();

	// Pipe's back face
	glBegin(GL_QUAD_STRIP);
	for (i = 0; i <= segments; i++) {
		angle = i * 2.f * (float)M_PI / segments;
		glVertex3f((float)cos(angle) * r1, (float)sin(angle) * r1, -length * 0.5f);
		glVertex3f((float)cos(angle) * r0, (float)sin(angle) * r0, -length * 0.5f);
	}
	glEnd();

	// Pipe's inner radius cylinder
	glBegin(GL_QUAD_STRIP);
	for (i = 0; i <= segments; i++) {
		angle = i * 2.f * (float)M_PI / segments;
		glVertex3f((float)cos(angle) * r0, (float)sin(angle) * r0, -length * 0.5f);
		glVertex3f((float)cos(angle) * r0, (float)sin(angle) * r0, length * 0.5f);
		glNormal3f(-(float)cos(angle), -(float)sin(angle), 0.f);
	}
	glEnd();

	// Pipe's outer radius cylinder
	glBegin(GL_QUAD_STRIP);
	for (i = 0; i <= segments; i++) {
		angle = i * 2.f * (float)M_PI / segments;
		u = (float)cos(AngleNorm + angle) * r1 - (float)cos(angle) * r1;
		v = (float)sin(AngleNorm + angle) * r1 - (float)sin(angle) * r1;
		glNormal3f(v, -u, 0.0);
		glVertex3f((float)cos(angle) * r1, (float)sin(angle) * r1, length * 0.5f);
		glVertex3f((float)cos(angle) * r1, (float)sin(angle) * r1, -length * 0.5f);
	}
	glEnd();
}

static GLint pipe1;

//Draw function
static void draw(void)
{
	static GLfloat color[4] = { 0.8f, 0.1f, 0.1f, 1.f };
	pipe1 = glGenLists(1);
	glNewList(pipe1, GL_COMPILE);
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
	pipe(1, 2, 10, 500);
	glEndList();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.0);
	glRotatef(0.0, 0.0, 0.0, 1.0);
	glCallList(pipe1);
	glPopMatrix();	
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
	static GLfloat position[4] = { 0.f, 0.f, 10.f, 0.f };
	glLightfv(GL_LIGHT0, GL_POSITION, position);
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

