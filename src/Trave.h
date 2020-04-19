#ifndef CILINDRO_H_
#define CILINDRO_H_
#include "Objeto.h"

class Trave : public Objeto  {
public:
	Trave(float x, float y, float z,int tipoDeMaterial);
	void desenha();
	void recalcularPosicao();
	virtual ~Trave();
};

#endif /* CILINDRO_H_ */
