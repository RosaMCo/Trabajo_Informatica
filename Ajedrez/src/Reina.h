#pragma once
#include "Pieza.h"
class Reina:public Pieza
{
public:

	Reina(Color color, int fila, int columna);
	//virtual ~Rey();

	//M�todos p�blicos
	void dibuja(float ix, float iy);
	bool mover(int nc, int nf);
	bool comer(int nc, int nf) { return mover(nc, nf); }
	bool getMovIniLargo() { return 0; } //solo para poder usar su formato virtual en Pieza y para poder comer al paso en los peones
	bool getMovIni() { return 0; } //no usado, s�lo para incluirlo en el virtual de Pieza y aplicarlo en el enroque
	void setMovIni(bool nuevo) {} //no usado, s�lo para incluirlo en el virtual de Pieza y aplicarlo en el enroque
};
