#include "Pendulo.h"

Pendulo::Pendulo(long double x, long double y, long double z,int tipoDeMaterial, long double comprimento,
				long double angulo,int movimentoSim,long double gravidade,
				long double radioEsferaMaior) : Objeto(x,y,z,tipoDeMaterial) {
	this->comprimento=comprimento;
	this->angulo=angulo;
	this->anguloCorrente=angulo;
	this->gravidade=gravidade;
	this->movimentoSim=movimentoSim;
	this->raioEsferaMaior=radioEsferaMaior;
	pausa=1;

}
void Pendulo::desenha(){
		long double numeroDeSegmentosEsferaMaior = 20;
		periodo=2*M_PI*sqrt(comprimento/gravidade);
		velocidadeAngular=2*M_PI/periodo;
		// seta a cor
		glColor3f(0.5f, 0.25f, 0.0f);
		//Desenha a esfera menorFrente.
		glPushMatrix();
			glTranslatef(this->x, this->y, 4);//Coordenadas da origem.
			if(tipoDeMaterial%2==0)
				glutSolidSphere(0.5, 5, 5);//Função para desenhar esfera.
			else
				glutWireSphere(0.5, 5, 5);//Função para desenhar esfera.
		glPopMatrix();
		//Desenha a esfera menorTraz.
		glPushMatrix();
			glTranslatef(this->x, this->y, -4);//Coordenadas da origem.
			if(tipoDeMaterial%2==0)
				glutSolidSphere(0.5, 5, 5);//Função para desenhar esfera.
			else
				glutWireSphere(0.5, 5, 5);//Função para desenhar esfera.

		glPopMatrix();
		if(pausa%2==1) {
			//pega tempo
			if(movimentoSim==1) {
				 t++;
				 sleep(0.1);
			}
			else
				t=0;
			//cout << "t: " << t <<endl;
			//t=0;
		}
		// Calcula novo x2 e y2.
		long double radiano = (angulo * M_PI / 180)+velocidadeAngular*t;
		x2 = (comprimento * sin(radiano)) + this->x;
		//long double y2=(comprimento*cos(radiano) );
	glPopMatrix();
		anguloCorrente=(long double)2*asin((x2-x)/(2*comprimento));
		y2 = comprimento * cos((long double) anguloCorrente+M_PI);
		//cout<< "angulo corrente"<<anguloCorrente<< endl;
		//cout << "y2 "<< y2 << endl;
		// desenha linha1
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINES);
			glVertex3f(x, y, 4);
			glVertex3f(x2, y2,raioEsferaMaior);
		glEnd();
		// desenha linha2
		glBegin(GL_LINES);
			glVertex3f(x, y, -4);
			glVertex3f(x2, y2,-raioEsferaMaior);
		glEnd();

		glColor3f(0.29f, 0.29f, 0.29f);
		//glColor3i(0,0,0);
		//Desenha a esfera maior.
		glPushMatrix();
			glTranslatef(x2, y2, z);
			if(tipoDeMaterial%2==0)
				glutSolidSphere(raioEsferaMaior, numeroDeSegmentosEsferaMaior,
						numeroDeSegmentosEsferaMaior);
			else
					glutWireSphere(raioEsferaMaior, numeroDeSegmentosEsferaMaior,
						numeroDeSegmentosEsferaMaior);
		glPopMatrix();
}

Pendulo::~Pendulo() {
	// TODO Auto-generated destructor stub
}

