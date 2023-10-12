#include <time.h>
#include <stdio.h>

#include "all.h"

double t_global_begin;

#ifdef _WIN32
int WinMain(HINSTANCE a, HINSTANCE b, char *c, int d)
#else
int main()
#endif
{
	t_global_begin = gettime();
    bin = malloc(8);
	char **argv = (char **)malloc(sizeof(char *));
	*argv = (char *)malloc(sizeof(char));
	**argv = '\0';
	int argc = 1;
	logfile = stderr;

    resetEverything();
	loadModel("sample.obj");
	
	//FIXME
	createModels();
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(400,400);
	glutCreateWindow("Snowman shooter "VERSION);

	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
	glutSpecialFunc(pressKey);
    glutKeyboardFunc(pressNormalKey);
    
    glutSetCursor(GLUT_CURSOR_NONE);
    
	glutIgnoreKeyRepeat(1);
	glutSpecialUpFunc(releaseKey);
    glutKeyboardUpFunc(releaseNormalKey);
	
	glutPassiveMotionFunc(passiveMotionFunc);
	glutMotionFunc(passiveMotionFunc);
	
    t_begin = gettime();

	glEnable(GL_DEPTH_TEST);
 	//~ glEnable(GL_TEXTURE_2D);
    
    logMessage(LOGLEVEL_INFO, "Game initalized successfully!");
    
	glutMainLoop();
 
	return 1;
}
