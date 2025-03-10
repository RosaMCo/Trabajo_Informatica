#include "Alfil.h"
#include"freeglut.h"
#include <iostream>


//Para las piezas de tipo alfil, torre y reina, quiza fuera m�s conveniente sacar la posici�n actual(con fila y columna)
//y la posici�n a la que se desea mover (Quiza haciendo uso del raton) para sacar la casilla de destino

Alfil::Alfil(Color col, int f, int c) {
	setColor(col);
	setTipo(ALFIL);
	fila = f;
	columna = c;

}

bool Alfil::mover(int nc, int nf) 
{
	//std::cout << "Entro a mover alfil\n";
	if ((nc < 0) || (nc > 7) || (nf < 0) || (nf > 7))
	{
		std::cout << "Se sale del tablero\n";
		return false;
	}
	else
	{
		//std::cout <<"No se sale del tablero\n";
		//std::cout << "nc= "<<nc<<" columna = "<<columna<<" abs(nc - columna) = "<< abs(nc - columna)<<"\n";
		if (abs(nc - columna) == abs(nf - fila))
		{
			//std::cout << "MOVIMIENTO DIAGONAL\n";
			return true;
		}
		else
		{
			//std::cout << "MOVIMIENTO NO DIAGONAL\n";
			return false;
		}
		/*//El afil se mueve hacia arriba 

		if ((nf - fila) <= 7) 
		{
			//Se mueve hacia la derecha
			if ((nc - columna) <= 7)
			{
				return true;
			}
			//Se mueve hacia la izquierda 
			if ((nc + columna) <= 7)
			{
				return true;
			}
		}

		//El alfil se mueve hacia abajo
		else if (nf + fila <= 7) 
		{
			//Se mueve hacia la derecha
			if (nc - columna <= 7)
				return true;
			//Se mueve hacia la izquierda 
			if (nc + columna <= 7)
				return true;
		}

		//falta comprobar que en caso de que la casilla final sea la misma que otra ficha, comemos esa ficha 
		else return false;*/
	}
}

void Alfil::dibuja(float ix, float iy)
{
	if (color == blanco)
	{
		//Imagen de pieza blanca
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("bin/imagenes/Fichas/W-Bishop.png").id);
		glDisable(GL_LIGHTING);
	}
	else if (color == negro)
	{
		//Imagen de pieza negra
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("bin/imagenes/Fichas/B-Bishop.png").id);
		glDisable(GL_LIGHTING);
	}
	//Tengo que hacer el lugar donde se va a situar cada pieza, para ello hago un pol�gono
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1); glVertex3f(ix, iy, 0.1);
	glTexCoord2d(1, 1); glVertex3f(ix + 20.0 / 8, iy, 0.1);
	glTexCoord2d(1, 0); glVertex3f(ix + 20.0 / 8, iy + 20.0 / 8, 0.1);
	glTexCoord2d(0, 0); glVertex3f(ix, iy + 20.0 / 8, 0.1);
	glEnd();
	glDisable(GL_BLEND);
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}