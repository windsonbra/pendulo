#include "Trave.h"

Trave::Trave(float x, float y, float z,int tipoDeMaterial) : Objeto(x,y,z,tipoDeMaterial) {}

void Trave::desenha() {

	glColor3f(0.5f, 0.25f, 0.0f);
	glPushMatrix();
		glTranslatef(this->x, this->y, this->z); //Coordenadas da origem.
		glRotated(90,0,1,0);
		if(tipoDeMaterial%2==0)
			glutSolidCylinder(0.3,35, 10, 20); //Função para desenhar cilindro.
		else
			glutWireCylinder(0.3,35, 10, 20); //Função para desenhar cilindro.
	glPopMatrix();

	glPushMatrix();
		glTranslatef(this->x, this->y, this->z); //Coordenadas da origem.
		glRotated(90,1,0,0);
		if(tipoDeMaterial%2==0)
			glutSolidCylinder(0.3,15, 10, 20); //Função para desenhar cilindro.
		else
			glutWireCylinder(0.3,15, 10, 20); //Função para desenhar cilindro.
	glPopMatrix();

	glPushMatrix();
		glTranslatef(this->x+35, this->y, this->z); //Coordenadas da origem.
		glRotated(90,1,0,0);
		if(tipoDeMaterial%2==0)
			glutSolidCylinder(0.3,15, 10, 20); //Função para desenhar cilindro.
		else
			glutWireCylinder(0.3,15, 10, 20); //Função para desenhar cilindro.
	glPopMatrix();

	glPushMatrix();
		glTranslatef(this->x, this->y, this->z);//Coordenadas da origem.
		if(tipoDeMaterial%2==0)
			glutSolidSphere(0.5, 5, 5);//Função para desenhar esfera.
		else
			glutWireSphere(0.5, 5, 5);//Função para desenhar esfera.

	glPopMatrix();

	glPushMatrix();
		glTranslatef(this->x+35, this->y, this->z);//Coordenadas da origem.
		if(tipoDeMaterial%2==0)
			glutSolidSphere(0.5, 5, 5);//Função para desenhar esfera.
		else
			glutWireSphere(0.5, 5, 5);//Função para desenhar esfera.
	glPopMatrix();

}

 void Trave::recalcularPosicao() {

}

Trave::~Trave() {
// TODO Auto-generated destructor stub
}

