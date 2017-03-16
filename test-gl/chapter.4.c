#include "Utils.h"

#define WINDOW_TITLE_PREFIX "Chapter 4"

int CurrentWidth = 800;
int CurrentHeight = 600;
int WindowHandle = 0;

unsigned FrameCount = 0;
GLuint ProjectionMatrixUniformLocation;
GLuint ViewMatrixUniformLocation;
GLuint ModelMatrixUniformLocation;
GLuint BufferIds[3] = { 0 };
GLuint ShaderIds[3] = { 0 };

Matrix ProjectionMatrix;
Matrix ViewMatrix;
Matrix ModelMatrix;

float CubeRotation;
clock_t LastTime;

void Initialize(int, char*[]);
void InitWindow(int, char*[]);
void ResizeFunction(int, int);
void RenderFunction(void);
void TimerFunction(int);
void IdleFunction(void);
void CreateCube(void);
void Destroy(void);
void DrawCube(void);

int main(int argc, char *argv[]) {
	Initialize(argc, argv);

	glutMainLoop();

	exit(EXIT_SUCCESS);
}

void Initialize(int argc, char *argv[]) {
	GLenum GlewInitResult;

	InitWindow(argc, argv);

	GlewInitResult = glewInit();

	if (GLEW_OK != GlewInitResult) {
		fprintf(stderr, "ERROR: %s\n", glewGetErrorString(GlewInitResult));

		exit(EXIT_FAILURE);
	}

	fprintf(stdout, "INFO: OpenGL version: %s\n", glGetString(GL_VERSION));

	glGetError();

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void InitWindow(int argc, char *argv[]) {
	glutInit(&argc, argv);

	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutInitWindowSize(CurrentWidth, CurrentHeight);

	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	WindowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);

	if (WindowHandle < 1) {
		fprintf(stderr, "ERROR: Could not create a new rendering window.\n");
		exit(EXIT_FAILURE);
	}

	glutReshapeFunc(ResizeFunction);
	glutDisplayFunc(RenderFunction);
	glutIdleFunc(IdleFunction);
	glutTimerFunc(0, TimerFunction, 0);
}

void ResizeFunction(int Width, int Height) {
	CurrentWidth = Width;
	CurrentHeight = Height;
	glViewport(0, 0, CurrentWidth, CurrentHeight);
}

void RenderFunction(void) {
	++FrameCount;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glutSwapBuffers();
	glutPostRedisplay();
}

void IdleFunction(void) {
	glutPostRedisplay();
}

void TimerFunction(int value) {
	if (0 != value) {
		char *TempString = (char*)malloc(512 + strlen(WINDOW_TITLE_PREFIX));

		sprintf(TempString, "%s: %d Frames PerSecond @ %d x %d", WINDOW_TITLE_PREFIX, FrameCount * 4, CurrentWidth, CurrentHeight);

		glutSetWindowTitle(TempString);
		free(TempString);
	}

	FrameCount = 0;
	glutTimerFunc(250, TimerFunction, 1);
}
