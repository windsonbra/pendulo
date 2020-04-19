#include "Suporte.h"

Suporte::Suporte(float x, float y, float z,int tipoDeMaterial, float largura, float altura,
		float comprimento) :
		Objeto(x, y, z,tipoDeMaterial) {
	this->largura = largura;
	this->altura = altura;
	this->comprimento = comprimento;
}

void Suporte::desenha() {
	glColor3f(0.9f, 0.9f, 0.0f);
	glPushMatrix();
	glTranslatef(this->x, this->y, this->z); //Coordenadas da origem.
		glBegin(GL_QUADS);
			glVertex3d(this->x, this->y, this->z);
			glVertex3d(this->x + comprimento, this->y, this->z);
			glVertex3d(this->x + comprimento, this->y, this->z + largura);
			glVertex3d(this->x, this->y, this->z + largura);
			glEnd();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(this->x, this->y, this->z + largura); //Coordenadas da origem.
		glBegin(GL_QUADS);
			glVertex3d(this->x, this->y, this->z + largura);
			glVertex3d(this->x + comprimento, this->y, this->z + largura);
			glVertex3d(this->x, this->y - altura, this->z + largura);
			glVertex3d(this->x, this->y - altura, this->z + largura);
		glEnd();
	glPopMatrix();

}

void Suporte::recalcularPosicao() {

}

Suporte::~Suporte() {
	// TODO Auto-generated destructor stub
}

