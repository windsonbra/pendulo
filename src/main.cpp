#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>

#include <GL/freeglut.h>
#include <math.h>
#include "Pendulo.h"
#include "Trave.h"
#include "Suporte.h"
#include <string>
#include <time.h>
double xcam=0,ycam=0,zcam=0;
double xzoom=0,yzoom=0,zzoom=0;
int desenha1=1,desenha2=1;
int anguloDeRotacaoDaCamera=2;
double angulo_de_visao = 90;
double z_proximo = 1.0f;
double z_longe = 500.0f;
int tipoDeMaterial=0;
int iteracao=0;
Pendulo pendulo(-3,0,0,tipoDeMaterial,9,0,0,0.02,3);
Pendulo pendulo2(3,0,0,tipoDeMaterial,9,0,0,0.02,3);
Trave trave1(-17.5,0,-4,tipoDeMaterial);
Trave trave2(-17.5,0,4,tipoDeMaterial);
Suporte suporte(-5,-7,0,tipoDeMaterial,5,5,5);
void rotacaoDaCamera() {
	if(xcam>0)
		for(int i=0;i<xcam;i++)
			glRotated(anguloDeRotacaoDaCamera,1,0,0);
	else
		for(int i=0;i>xcam;i--)
			glRotated(-anguloDeRotacaoDaCamera,1,0,0);
	if(ycam>0)
		for(int i=0;i<ycam;i++)
			glRotated(anguloDeRotacaoDaCamera,0,1,0);
	else
		for(int i=0;i>ycam;i--)
			glRotated(-anguloDeRotacaoDaCamera,0,1,0);
	if(zcam>0)
		for(int i=0;i<zcam;i++)
			glRotated(anguloDeRotacaoDaCamera,0,0,1);
	else
		for(int i=0;i>zcam;i--)
			glRotated(-anguloDeRotacaoDaCamera,0,0,1);
}

void zoomCamera() {
	if(xzoom>0)
		for(int i=0;i<xzoom;i++)
			glTranslatef(1,0,0);
	else
		for(int i=0;i>xzoom;i--)
			glTranslatef(-1,0,0);
	if(yzoom>0)
		for(int i=0;i<yzoom;i++)
			glTranslatef(0,1,0);
	else
		for(int i=0;i>yzoom;i--)
			glTranslatef(0,-1,0);
	if(zzoom>0)
		for(int i=0;i<zzoom;i++)
			glTranslatef(0,0,1);
	else
		for(int i=0;i>zzoom;i--)
			glTranslatef(0,0,-1);
}
void choqueEntrePendulos() {
	long double distancia=pendulo.x2+pendulo.raioEsferaMaior-(pendulo2.x2-pendulo2.raioEsferaMaior);
	if(iteracao==0){
		if(distancia<=3 &&distancia>=-3 &&(pendulo.t>=pendulo.periodo/4||pendulo2.t>=pendulo2.periodo/4)
				&& desenha1%2==1 && desenha2%2==1) {
				int aux=pendulo.movimentoSim;
				pendulo.movimentoSim=pendulo2.movimentoSim;
				pendulo2.movimentoSim=aux;
				iteracao++;
				pendulo.angulo=180;
				pendulo2.angulo=0;
		}
	}
	else
		if(distancia<3 &&distancia>=-3 &&(pendulo.t>=pendulo.periodo/2||pendulo2.t>=pendulo2.periodo/2)
				&& desenha1%2==1 && desenha2%2==1) {
				int aux=pendulo.movimentoSim;
				pendulo.movimentoSim=pendulo2.movimentoSim;
				pendulo2.movimentoSim=aux;
		}
}

void display(void) {
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0, 12, -30);
	glColor3f(1, 1, 1);

	choqueEntrePendulos();
	/glPushMatrix();
		rotacaoDaCamera();
		zoomCamera();

		if(desenha1%2==1)
			pendulo.desenha();
		if(desenha2%2==1)
			pendulo2.desenha();
		trave1.desenha();
		trave2.desenha();
		//suporte.desenha();
		//chao

		{
			glPushMatrix();
			glColor3f(0,0.5,0);
			glTranslated(0,-16,0);
			glRotated(-90,1,0,0);
			if(tipoDeMaterial%2==0) {
				glBegin(GL_QUADS);
					glNormal3f(0.0, 0.0, 1.0);
					glVertex3f(50, 50, 0);
					glVertex3f(-50, 50,0);
					glVertex3f(-50, -50, 0);
					glVertex3f(50, -50, 0);
				glEnd();
			}
			else  {
				glBegin(GL_LINE_LOOP);
					glVertex3f(50, 50, 0);
					glVertex3f(-50, 50,0);
					glVertex3f(-50, -50, 0);
					glVertex3f(50, -50, 0);
				glEnd();
				for(int i=-50;i<50;i+=2) {
					glBegin(GL_LINES);
						glVertex3f(50, i, 0);
						glVertex3f(-50, i, 0);
					glEnd();
					glBegin(GL_LINES);
						glVertex3f(i, 50, 0);
						glVertex3f(i, -50, 0);
					glEnd();
				}
			}
		}
			glPopMatrix();
		//glPopMatrix();


		//pendulo.recalcularPosicao();
		//pendulo2.recalcularPosicao();
	glutSwapBuffers();

}

void reshape(int w, int h) {
	glMatrixMode(GL_PROJECTION);												// seleciona a matriz de projeção
	glViewport(0, 0, w, h);									// modifica a viewport
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();															// reseta a matriz de projeção
	GLdouble aspacto = (GLdouble) w / h;
	gluPerspective(angulo_de_visao, aspacto, z_proximo, z_longe);		// modifica a perspectiva
	glMatrixMode(GL_MODELVIEW);
	glShadeModel( GL_SMOOTH );
	glClearDepth( 1.0f );
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'e':
		exit(0);
		break;

	case 'w':
		xcam++;
		break;

	case 's':
		xcam--;
		break;

	case 'a':
		ycam--;
		break;

	case 'd':
		ycam++;
		break;
	case 'z':
		zcam--;
		break;
	case 'x':
		zcam++;
		break;

	case 'h':
			zzoom++;
			break;

		case 'n':
			zzoom--;
			break;

		case 'b':
			xzoom++;
			break;

		case 'm':
			xzoom--;
			break;
		case 'j':
			yzoom++;
			break;
		case 'k':
			yzoom--;
			break;
		case 'c':
			desenha1++;
			pendulo.gravidade=pendulo2.gravidade;
			break;
		case 'v':
			desenha2++;
			pendulo2.gravidade=pendulo.gravidade;
			break;
		case 'p':
			if(pendulo.gravidade<2) {
				pendulo.gravidade++;
				pendulo2.gravidade++;
			}
			break;
		case 'l':
			if(pendulo.gravidade>1) {
			pendulo.gravidade--;
			pendulo2.gravidade--;
			}
			break;
		case 'f':
			pendulo.pausa++;
			pendulo2.pausa++;
			break;
	case 'u':
		pendulo.movimentoSim=1;
		pendulo2.movimentoSim=0;
		pendulo.angulo=-90;
		pendulo2.angulo=0;
		iteracao=0;
		break;
	case 'i':
		pendulo.movimentoSim=0;
		pendulo2.movimentoSim=0;
		pendulo.angulo=0;
		pendulo2.angulo=0;
		break;
	case 'o':
		pendulo.movimentoSim=0;
		pendulo2.movimentoSim=1;
		pendulo.angulo=0;
		pendulo2.angulo=90;
		iteracao=0;
		break;
	case 't':
		pendulo.tipoDeMaterial++;
		pendulo2.tipoDeMaterial++;
		trave1.tipoDeMaterial++;
		trave2.tipoDeMaterial++;
		tipoDeMaterial++;
		break;
	}
	glutPostRedisplay();
}


void inicializaIluminacao (void)
{
	GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};	   // "cor"
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho"
	GLfloat posicaoLuz[4]={0.0, 50.0, 50.0, 1.0};

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0};
	GLint especMaterial = 60;

 	// Especifica que a cor de fundo da janela será preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Habilita o modelo de colorização de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a refletância do material
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os parâmetros da luz de número 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);
	// Habilita o depth-buffering
	glEnable(GL_DEPTH_TEST);

}

// Função callback chamada para gerenciar eventos do mouse
void GerenciaMouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON) {
         if (state == GLUT_DOWN) {
        	 cout<<"d";
         }
         if (state == GLUT_UP){
        	 cout<<"U";
         }
}
    glutPostRedisplay();
}

int main(int argc, char **argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Pendulo");
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
    glutMouseFunc(GerenciaMouse);
    inicializaIluminacao();
	glutMainLoop();
	return 0;
}
