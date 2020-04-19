#ifndef OBJETO_H_
#define OBJETO_H_
#include <GL/freeglut.h>
#include <math.h>

class Objeto {
protected:
	float x;
	float y;
	float z;
public:
	int tipoDeMaterial;
	Objeto(float x, float y, float z,int tipoDeMaterial);
	virtual void desenha() = 0;
	virtual ~Objeto();
};

#endif /* OBJETO_H_ */
