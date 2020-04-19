#ifndef SUPORTE_H_
#define SUPORTE_H_

#include "Objeto.h"

class Suporte: public Objeto {
private:
	float largura;
	float altura;
	float comprimento;
public:
	Suporte(float x, float y, float z,int tipoDeMaterial, float largura, float altura, float comprimento);
	void desenha();
	void recalcularPosicao();
	virtual ~Suporte();
};

#endif /* SUPORTE_H_ */
