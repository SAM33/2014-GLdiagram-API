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
/*  diagrams dataptr  */
std::vector<singlediagram *> diagrams;
/*  this function will automatic call Draw  */
static void Repaint()
{
	glutPostRedisplay();
}
/*  opengl critical sectiong  */
static void Draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
	for(int i=0 ; i<diagrams.size() ; i++)
        diagrams.at(i)->draw();
    glutSwapBuffers();
}
/*  critical sectiong of comuuter1 input  */
void *computer1(void * Diagram)
{
	singlediagram *diagram = (singlediagram*)Diagram;
	while(true)
	{
        /*  temp ....  random data  */
		diagram->addvalue(rand()%100);
		usleep(150000);
	}
}
/*  critical sectiong of comuuter2 input  */
void *computer2(void * Diagram)
{
    singlediagram *diagram = (singlediagram*)Diagram;
	while(true)
	{
        /*  temp ....  random data  */
		diagram->addvalue(rand()%100);
		usleep(200000);
	}
}
/*  main function  */
int main(int argc, char** argv)
{
	pthread_t datareceiver1,datareceiver2;
    singlediagram *diagramptr;   //diagram.h
    int r;
    /*  create first diagram  */
    diagramptr = new singlediagram(50,50,400,150); //x=50 y=50 width=400 height=150
	diagramptr->setdatacolor(color3f(RED));
	diagramptr->setaxiscolor(color3f(WHITE));
	diagramptr->setdisplayscope(10);
	r =  pthread_create(&datareceiver1, NULL, computer1, (void *)diagramptr);
	diagrams.push_back(diagramptr);
     /*  create second diagram  */
    diagramptr = new singlediagram(50,300,400,150);  //x=50 y=400 width=400 height=150
	diagramptr->setdatacolor(color3f(BLUE));
	diagramptr->setaxiscolor(color3f(WHITE));
	diagramptr->setdisplayscope(20);
	r =  pthread_create(&datareceiver2, NULL, computer2, (void *)diagramptr);
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
	return 0;
}

