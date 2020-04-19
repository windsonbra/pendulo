#ifndef PENDULO_H_
#define PENDULO_H_


#include "Objeto.h"
#include <iostream>
#include <unistd.h>
using namespace std;
class Pendulo : public Objeto{
private:
	long double anguloCorrente;
	long double comprimento;
	long double velocidadeAngular;
	long double y2;

public:
	long double gravidade;
	long double angulo;
	long double periodo;
	int t;
	int movimentoSim;
	long double x2;
	long double raioEsferaMaior;
	int pausa;




	Pendulo(long double x, long double y, long double z,int tipoDeMaterial, long double comprimento, long double angulo,int movimentoSim,long double gravidade,long double radioEsferaMaior);
	void desenha();
	virtual ~Pendulo();
};

#endif /* PENDULO_H_ */
