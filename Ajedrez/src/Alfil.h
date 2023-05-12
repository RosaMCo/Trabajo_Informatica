#pragma once
#include"Pieza.h"

class Alfil :public Pieza
{
public:

    Alfil(Color color, int fila, int columna);

    //true si el movimiento es permitido; nx y ny son los nuevos valores de x e y
    bool mover(int nc, int nf);
    void dibuja(float ix, float iy);
    bool comer(int nc, int nf) { return mover(nc, nf); }
};
