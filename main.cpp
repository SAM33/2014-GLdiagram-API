//NTCU TSCC TEAM , 2015.03
#include <iostream>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include <vector>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include "infoReceiver.h"
#include "diagram2.h"

void error(const char *msg)
{
	perror(msg);
	exit(1);
}


/*  diagrams dataptr  */
std::vector<diagram2 *> diagrams;
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
    glClear(GL_COLOR_BUFFER_BIT);

    pthread_mutex_lock(&mutex);
    for(int i=0 ; i<diagrams.size() ; i++)
        diagrams.at(i)->draw();
    pthread_mutex_unlock(&mutex);

    glutSwapBuffers();

}
/*  critical sectiong of comuuter1 input  */

void* run(void* Diagram)
{
	diagram2 *diagram = (diagram2*)Diagram;

	int sockfd, newsockfd, portno;
	printf("set port:%d\n",diagram->port);
	portno = diagram->port;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	clilen = sizeof(cli_addr);

	puts("binding");
	if (bind(sockfd, (struct sockaddr *) &serv_addr,
				sizeof(serv_addr)) < 0) 
		error("ERROR on binding");

	puts("listening");
	listen(sockfd,5);

	newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);

	if (newsockfd < 0) 
		error("ERROR on accept");

	int n;
	deque<string> data;
	int chosen = 3;
	int maxSize = 100; //X軸最大的存放項目
	int maxValue = 100; //Y軸最大的值
	infoReceiver r;                    
	diagram->registerItem(&data,maxSize);
	r.registerItem( &data , chosen , maxSize );
	diagram->setmaxvalue(maxValue);   
	diagram->setvistiable(true);    
	while( 1 ) 
	{
        	pthread_mutex_lock(&mutex);
		bzero(buffer,256);
		n = read(newsockfd,buffer,255);
		if (n < 0) error("ERROR reading from socket");
		string tmp( buffer , buffer+n );
		r.updateInfo(tmp);
		r.sync();
		printf("===================================================\n");
		printf("data.size=%lu\n", data.size());
		for( int i = 0 ; i < data.size() ; ++i )
		{
			printf("data[%d]=%s\n",i,data[i].c_str());
		}	
		printf("===================================================\n");
		pthread_mutex_unlock(&mutex);
		usleep(50000);
	}

	close(newsockfd);
	close(sockfd);

	pthread_exit(NULL);
	return NULL;
}


/*  main function  */
int main(int argc, char** argv)
{
    	pthread_t datareceiver[2];
    	pthread_mutex_init(&mutex, NULL);
    	int r;
    	/*  create first diagram  */
	diagram2 *diagramptr = new diagram2(50,50,400,150); //x=50 y=50 width=400 height=150
	diagramptr->settitle("computer1");
	diagramptr->port=4000;   
	r = pthread_create(&datareceiver[0], NULL, run, (void *)diagramptr);
	diagrams.push_back(diagramptr);

    	/*  init opengl (glu,glut...)  */
    	glutInit(&argc, argv);
    	glutInitWindowPosition(10,10);
    	glutInitWindowSize(500,500);
    	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    	glutCreateWindow("TSCC2015");
    	glClearColor(0.0,0.0,0.0,0.0);
    	glMatrixMode(GL_PROJECTION);
    	gluOrtho2D(0,500,0,500);
	glutIdleFunc(Repaint);
    	glutDisplayFunc(Draw);
    	glutMainLoop(); //nerver return
    	pthread_mutex_destroy(&mutex);
	return 0;
}

