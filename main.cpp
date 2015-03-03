//NTCU TSCC TEAM , 2015.03
#include "line2f.h"
#include "point2f.h"
#include "MyGLgraphic.h"
#include "color3f.h"
#include "diagram.h"
#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <vector>
#include <cstdio>
/*  diagrams dataptr  */
std::vector<singlediagram *> diagrams;
/* mutex */
pthread_mutex_t mutex;
/*  this function will automatic call Draw  */
static void Repaint()
{
	glutPostRedisplay();
}
/*  opengl critical sectiong  */
static void Draw()
{
    pthread_mutex_lock(&mutex);
    glClear(GL_COLOR_BUFFER_BIT);
	for(int i=0 ; i<diagrams.size() ; i++)
        diagrams.at(i)->draw();
    glutSwapBuffers();
    pthread_mutex_unlock(&mutex);
}
/*  critical sectiong of comuuter1 input  */
void *computer(void * Diagram)
{
	singlediagram *diagram = (singlediagram*)Diagram;
	int i = 0;
	while(true)
	{
        /*  temp ....  random data  */
        pthread_mutex_lock(&mutex);
		i++;
		printf("%d\n",i);
		diagram->addvalue(i);
		pthread_mutex_unlock(&mutex);
		usleep(50000);
	}
}

singlediagram* diagIniter(int x,int y)
{
    singlediagram *diagramptr;   //diagram.h
	diagramptr = new singlediagram(x,y,400,150); //x=50 y=50 width=400 height=150
	diagramptr->setdatacolor(color3f(RED));
	diagramptr->setaxiscolor(color3f(WHITE));
	diagramptr->setdisplayscope(60);
	return diagramptr;
}
/*  main function  */
int main(int argc, char** argv)
{
	pthread_t datareceiver[2];
	pthread_mutex_init(&mutex, NULL);

    singlediagram *diagramptr;   //diagram.h
    int r;
    /*  create first diagram  */
    diagramptr = diagIniter(50,50);
	r = pthread_create(&datareceiver[0], NULL, computer, (void *)diagramptr);
	diagrams.push_back(diagramptr);
     /*  create second diagram  */
    diagramptr = diagIniter(50,300);
	r = pthread_create(&datareceiver[1], NULL, computer, (void *)diagramptr);
	diagrams.push_back(diagramptr);

    /*  init opengl (glu,glut...)  */
    glutInit(&argc, argv);
    glutInitWindowPosition(10,10);
    glutInitWindowSize(500,500);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutCreateWindow("Diagrams");
    glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0,500,0,500);
	glutIdleFunc(Repaint);
    glutDisplayFunc(Draw);
    glutMainLoop(); //nerver return
    pthread_mutex_destroy(&mutex);
	return 0;
}

