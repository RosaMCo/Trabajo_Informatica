#pragma once
#include"Pieza.h"

class Torre:public Pieza
{
private:
    bool movIni;
public:

    Torre(Color color, int fila, int columna);

    //true si el movimiento es permitido; nx y ny son los nuevos valores de x e y
    bool mover(int nx, int ny);
    void dibuja(float ix, float iy);
    bool comer(int nx, int ny) { return mover(nx, ny); }
    bool getMovIni() { return movIni; }
    void setMovIni(bool nuevo) { movIni = nuevo; }
    bool getMovIniLargo() { return 0; } //solo para poder usar su formato virtual en Pieza y para poder comer al paso en los peones

};
