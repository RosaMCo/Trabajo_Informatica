#include "Tablero.h"
#include <iostream>
#include <string>

Tablero::Tablero() {
	setTurno(Color::blanco);//inician blancas
	std::cout << "Incializo turno en: "<< turno; imprimirTurno();
	
	for (int fila = 0; fila <8; fila++) {
		for (int columna = 0; columna <8; columna++) {
			casilla[fila][columna].setPosicion(columna * 20.0/8 - 10, fila * 20.0/8 - 2.5);//valores aleatorios de las casillas, cambiar a los concretos
			id[fila][columna] = nullptr;
		}
	}

	

	//los n�meros m�gicos son offsets para colocar las piezas en el tablero
	for (int i = 0; i < 16; i++) {//creaci�n de peones

		if (i < 8) {//blancos
			Peon* p = new Peon(blanco, 1, i);//fila 1, todas las columnas
			lista[i] = p;
			id[1][i] = lista[i];

		}

		else {//negros
			Peon* p = new Peon(negro, 6, i - 8);//fila 6, todas las columnas (-8 porque i empieza en 8 y las columnas en 0)
			lista[i] = p;
			id[6][i - 8] = lista[i];
		}
	}

	for (int i = 16; i < 20; i++) {//creaci�n de torres
		if (i < 18) {//blancas
			Torre* t = new Torre(blanco, 0, (i - 16) * 7);//fila 0, columnas 0 y 7
			lista[i] = t;
			id[0][(i - 16) * 7] = lista[i];
		}
		else {//negras
			Torre* t = new Torre(negro, 7, (i - 18) * 7);//fila 7, columnas 0 y 7
			lista[i] = t;
			id[7][(i - 18) * 7] = lista[i];
		}
	}

	for (int i = 20; i < 24; i++) {//creaci�n de caballos
		if (i < 22) {//0s
			Caballo* c = new Caballo(blanco, 0, (i - 20) * 5 + 1);//fila 0,  columnas 1 y 6
			lista[i] = c;
			id[0][(i - 20) * 5 + 1] = lista[i];
		}

		else {
			Caballo* c = new Caballo(negro, 7, (i - 22) * 5 + 1);//fila 7, columnas 1 y 6
			lista[i] = c;//negras
			id[7][(i - 22) * 5 + 1] = lista[i]; 
		}
	}

	for (int i = 24; i < 28; i++) {//creaci�n de alfiles
		if (i < 26) {//blancas
			Alfil* a = new Alfil(blanco, 0, (i - 24) * 3 + 2);//fila 0, columnas 2 y 5
			lista[i] = a;
			id[0][(i - 24) * 3 + 2] = lista[i];
		}

		else {//negras
			Alfil* a = new Alfil(negro, 7, (i - 26) * 3 + 2);//fila 7, columnas 2 y 5
			lista[i] = a;
			id[7][(i - 26) * 3 + 2] = lista[i]; 
		}
	
	}

	for (int i = 28; i < 30; i++) {
		if (i < 29) {
			Reina* r = new Reina(blanco, 0, i - 25);//fila 0, columna 3
			lista[i] = r;
			id[0][i - 25] = lista[i];
		}
		else {
			Reina* r = new Reina(negro, 7, i - 26);//fila 7, columna 3
			lista[i] = r;
			id[7][i - 26] = lista[i];
		}
	}

	for (int i = 30; i < 32; i++) {
		if (i < 31) {
			Rey* r = new Rey(blanco, 0, i - 26);//fila 0, columna 4
			lista[i] = r;
			id[0][i - 26] = lista[i];
		}

		else {
			Rey* r = new Rey(negro, 7, i - 27);//fila 7, columna 4
			lista[i] = r;
			id[7][i - 27]=lista[i];
		}
		
	}
	numero = 32;
	//comprobarAsignaciones();
	//imprimirLista();
}


void Tablero::eliminarPieza(int c, int f)
{
	for (int i = 0; i < numero; i++)
	{
		if ((i < 0) || (i >= numero))
			return;
		if ((lista[i]->getColumna() == c) && (lista[i])->getFila() == f)
		{
			int eliminadaX = lista[i]->getColumna();
			int eliminadaY = lista[i]->getFila();
			//std::cout << "-----------Quiero eliminar:-------------\n"; imprimirId(eliminadaX, eliminadaY); imprimirLista(eliminadaX, eliminadaY);
			delete lista[i];
			std::cout << "Eliminada!!!!!!!!!!!!!!!!!!!!!!\nNueva ID:";
			//id[eliminadaY][eliminadaX] = nullptr;
			numero--;
			for (int j = i; j < numero; j++)
			{
				lista[j] = lista[j + 1];
			}
			return;
		}
	}
}

bool Tablero::selPieza(int forigen, int corigen) {//selecci�n de pieza a mover [pasar como const?]
	std::cout << "\tEntro en Tablero::seleccionar Pieza" << "\n";
	std::cout << "El turno en tablero es:"; imprimirTurno();
	auto& iden = id[forigen][corigen];//es muy largo de escribir, as� que referencia/alias
	if (iden) {//comprobar puntero no nulo (casilla no vac�a)
		if (iden->getColor() == turno) {//comprobar que coinciden el color de la pieza y el del turno
			std::cout << "Coinciden color y turno; hay una pieza de color" << iden->getColor() << "\n";
			return true;
		}
		else {
			return false;
			std::cout << "La pieza es de color " << iden->getColor() << "y el turno es "; imprimirTurno();std::cout << "por lo que no muevo" << "\n";
		}
	}
	else { return false; std::cout << "La id no contiene nada. Casilla vac�a" << "\n"; }
}


bool Tablero::mover(int fdestino, int cdestino, int forigen, int corigen) {//selecci�n de destino (una vez seleccionada pieza a mover)
	std::cout << "\n->Entro en mover de tablero\n";
	auto& destino = id[fdestino][cdestino];
	auto& origen = id[forigen][corigen];
	bool coincidentes = 0;
	if ((fdestino == forigen) && (cdestino == corigen))
	{
		coincidentes = 1; std::cout << "Elige un destino valido.\n <>VUELVE A SELECCIONAR LA PIEZA QUE DESEA MOVER: " << "\n"; 
		return false;
	}
	if ((piezaEnMedio(fdestino, cdestino, forigen, corigen))||coincidentes)
		return false;
	else
	{
		if (!origen) //si no hay una pieza en origen
		{
			std::cout << "Intentas mover una pieza? Selecciona una casilla donde halla una. \n ";
			return false;

		}
		else
		{
			if (destino)  //casilla ocupada
			{
				std::cout << "\ncasilla ocupada ";
				if (destino->getColor() != turno) {//comprobar pieza color distinto
					std::cout << "por pieza de distinto color \n ";
					if (origen->comer(cdestino, fdestino))//llamar a comer de la pieza seleccionada
					{
						std::cout << "La puedo comer!! \n ";
						eliminarPieza(cdestino, fdestino);
						return(actualizarId(fdestino, cdestino, forigen, corigen));						
					}
					else { return false; std::cout << "No la puedo comer :( \n "; }
				}
				else 
				{
					if (enroque(fdestino, cdestino, forigen, corigen))
					{
						std::cout << "Piezas del mismo color y enroque HECHO :) \n ";
						return true;
					}
					else
					{
						return false; std::cout << "Piezas del mismo color y enroque no valido \n ";
					}
						 
				}
			}

			else //casilla vac�a
			{
				std::cout << "La casilla destino esta vacia \n ";
				if (comerAlPaso(fdestino, cdestino, forigen, corigen))
				{
					return true;
				}
				else //llamar a mover de la pieza seleccionada
				{
					if (origen->mover(cdestino, fdestino))//realizar el movimiento
					{
						std::cout << "Me muevo a  \n ";
						imprimirId(cdestino, fdestino);
						return actualizarId(fdestino, cdestino, forigen, corigen);
					}
					else { return false; std::cout << "No me puedo mover... \n "; }
				}
				
			}
		}
	}
}
bool Tablero::actualizarId(int fdestino,int cdestino,int forigen,int corigen)
{
	std::cout << "\nestoy actualizando la id...";
	//auto& destino = id[fdestino][cdestino];
	//auto& origen = id[forigen][corigen];
	if (id[forigen][corigen])//si hay pieza, id no nula
	{
		id[forigen][corigen]->setPosicion(cdestino, fdestino);//actualizar posici�n de la pieza 
		id[fdestino][cdestino] = id[forigen][corigen];//copia de dir. de memoria para que apunten ambos a la misma pieza
		id[forigen][corigen] = nullptr;//casilla origen ahora vac�a (no apunta a la pieza)
		std::cout << "\nID ACTUALIZADA; Ahora nueva posicion:"; imprimirId(cdestino, fdestino); std::cout<<"\t\tLa posicion anterior: "; imprimirId(corigen, forigen);
		std::cout << "\nLISTA ACTUALIZADA: "; //imprimirLista(cdestino, fdestino);
		return true;
		
	}
	else 
	{
		std::cout << "Queria actualizar la id pero no hab�a nada en origen";
		return false;
	}
	

}

void Tablero::dibuja() {
	//dibujado tablero
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("bin/imagenes/fichas/tablero.png").id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1); glVertex2f(-10, -2.5);
	glTexCoord2d(1, 1); glVertex2f(10, -2.5);
	glTexCoord2d(1, 0); glVertex2f(10, 17.5);
	glTexCoord2d(0, 0); glVertex2f(-10, 17.5);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	

	//llamada a dibujado piezas
	for (int i = 0; i < 32; i++) {
		int tempf, tempc;
		if (lista[i]) {//no llamar a dibujado si puntero vac�o
			//var. temporales para pasar las coordenadas correspondientes a la pieza
			tempf = lista[i]->getFila();
			tempc = lista[i]->getColumna();
			//pasamos las coordenadas correspondientes a la pieza para que se dibuje
			lista[i]->dibuja(casilla[tempf][tempc].getX(), casilla[tempf][tempc].getY());

		}
	}
}
bool Tablero::piezaEnMedio(int fdestino, int cdestino, int forigen, int corigen) {//selecci�n de destino (una vez seleccionada pieza a mover)
	if ((id[forigen][corigen]->getTipo()) == CABALLO)
	{
		std::cout << "Es un caballo ->No se buscan piezas en medio e\n";
		return false;
	}
	else
	{
		//definir sentido del movimiento
		int difY = fdestino - forigen;
		int difX = cdestino - corigen;
		int incrementoY = 0;
		int incrementoX = 0;
		char tipoMov = 'M';
		if (difY) //...si hay variacion en las filas
			incrementoY = difY / abs(difY); //...calculo el incremento...
		else
			tipoMov = 'H'; //...si no la hay, el movimiento horizontal

		if (difX) //...si hay variacion en las columnas
			incrementoX = difX / abs(difX); //...calculo el incremento...
		else
			tipoMov = 'V'; //...si no la hay movimiento vertical: difX = 0; difY!=0;

		if (abs(difY) == abs(difX))
			tipoMov = 'D'; //movimiento diagonal

		if (tipoMov == 'H')
		{
			for (int _columna = (corigen + incrementoX); _columna != cdestino; _columna += incrementoX)
			{
				if (casillaVacia(_columna,forigen)==0)
				//if(id[forigen,_columna])
				{
					std::cout << "Mov horizontal -> Se encontr� una pieza en medio en medio en: "; imprimirId(_columna, forigen);
					return true;
				}
			}
			return false;
		}
		else if (tipoMov == 'V')
		{
			for (int _fila = (forigen + incrementoY); _fila != fdestino; _fila+=incrementoY)
			{
				//std::cout << "\tColumna fija: " << corigen + 1 << "; buscando pieza en la fila: " << _fila +1 << "\n";
				if (casillaVacia(corigen,_fila)==0)
				{
					std::cout << "Mov vertical -> Se encontr� una pieza en medio en: "; imprimirId(corigen, _fila);
					return true;
				}
			}
			return false;
		}
		else if (tipoMov == 'D') //movimiento diagonal
		{
			int _fila = forigen + incrementoY;
			int _columna = corigen + incrementoX;
			while ((_fila != fdestino) || (_columna != cdestino))
			{
				if (casillaVacia(_columna, _fila) == 0)
				{
					std::cout << "Mov diagonal -> Se encontr� una pieza en medio en: "; //imprimirId(_columna, _fila);
					return true;
				}
				_fila += incrementoY;
				_columna += incrementoX;

			}
			return false;

		}
		else return false;
	}
}

bool Tablero::casillaVacia(int c, int f)
{
	auto& iden = id[f][c];
	if (iden) {
		return false; std::cout << "---Casilla no vac�a---\n";
	}
	else {
		return true; std::cout << "---Casilla vac�a---\n";
	}
}

bool Tablero::colorDistinto(Pieza& pieza, Pieza& pieza2)
{
	if (pieza.getColor() != pieza2.getColor())
		return true;
	else return false;
}


bool Tablero::comerAlPaso(int fdestino, int cdestino, int forigen, int corigen)
{
	auto& origen = id[forigen][corigen];
	auto& destino = id[fdestino][cdestino];
	int incremento = (origen->getColor()) == blanco ? -1 : 1; //si el origen es blanco, nos interesa el incremento del contrario, esto es el negro, que se mueve decrementando filas
	auto& peonAComer = id[fdestino + incremento][cdestino];
	if (peonAComer)
	{
		if (colorDistinto(*origen, *peonAComer))//si las piezas son de distinto color...
		{
			if ((origen->getTipo() == PEON) && (peonAComer->getTipo() == PEON))//...y son peones...
			{
				if (peonAComer->getMovIniLargo()) // si el peon a comer se ha movido dos casillas en el primer movimiento...
				{
					if ((forigen == (fdestino + incremento)) && (abs(corigen - cdestino) == 1))//...si ambos peones se encuentran en la misma fila y a una columna de diferencia...
					{
						if (casillaVacia(cdestino, fdestino)) //y la casilla que est� detr�s del peon que se pretende comer al paso est� vac�a...
						{
							eliminarPieza(cdestino, (fdestino + incremento));
							if (actualizarId(fdestino, cdestino, forigen, corigen))
							{
								std::cout << "comida al paso!\n";
								return true;
							}
							else
							{
								std::cout << "comer al paso no completado\n";
								return false;
							}

						}
						else return false;
					}
					else return false;
				}
				else return false;
			}
			else return false;
		}
		else return false;
	}
	else return false;
}


bool Tablero::amenaza(Pieza& pieza)//no aplicado a comer al paso
{
	int _columna = pieza.getColumna();
	int _fila = pieza.getFila();
	for (int j = 0; j < 8; j++)
	{
		for (int i = 0; i < 8; i++)
		{
			if (id[j][i])
			{
				if ((colorDistinto(*id[j][i], pieza)) && ((i != _columna) && (j != _fila)))
				{
					if ((id[j][i]->comer(_columna, _fila)) && (piezaEnMedio(j, i, _fila, _columna) == 0))
					{
						std::cout << "----Puede comer al rey el"; imprimirTipo(id[j][i]->getTipo()); imprimirColor(id[j][i]->getColor());
						std::cout << " de x= " << i << " y= " << j << "estando supuestamente el rey en x= " << _columna << " y= " << _fila << "\n";
						return true;
					}
					
				}
			}
			
		}
		
	}
	return false;

}
bool Tablero::jaque(Color turno)
{
	for (int fila = 0; fila < 8; fila++)
	{
		for (int columna = 0; columna < 8; columna++)
		{
			if ((id[fila][columna]->getTipo() == REY) && (id[fila][columna]->getColor() == turno))
				return amenaza(*id[fila][columna]);
		}
	}
}


bool Tablero::enroque(int fdestino, int cdestino, int forigen, int corigen)
{
	auto& origen = id[forigen][corigen];
	auto& destino = id[fdestino][cdestino];
	Pieza* rey;
	Pieza* torre;
	std::cout << "->Enroque general\n";
	if (origen && destino)
	{
		std::cout << "->Hay piezas en seleccion\n";
		std::cout << "->En origen: "; imprimirTipo(origen->getTipo());
		std::cout << "->En destino: "; imprimirTipo(destino->getTipo());
		if (((origen->getTipo() == REY) && (destino->getTipo() == TORRE)) || ((origen->getTipo() == TORRE) && (destino->getTipo() == REY)))
		{
			std::cout << "->Una es rey y la otra torre\n";
			if (colorDistinto(*origen, *destino) == false)
			{
				std::cout << "->Su color es igual\n";
				std::cout << "->En origen: "; imprimirTipo(origen->getTipo());
				std::cout << "->En destino: "; imprimirTipo(destino->getTipo());
				switch (origen->getTipo())
				{
				case REY:
					rey = origen; std::cout << " rey es el origen, torre es el destino\n";
					torre = destino;
					break;
				case TORRE:
					rey = destino; std::cout << " torre es el origen, rey es el destino\n";
					torre = origen;
					break;
				default:
					break;
				}
				std::cout << "-> Miro si es el movimiento inicial: ";
				if (((rey->getMovIni() == false) && (torre->getMovIni() == false))) //si son del mismo color y nunca se han movido se sobreentiende que est�n en la misma fila.
				{
					std::cout << "es el movimiento inicial de ambos\n-> Rey en jaque? ";
					if (amenaza(*rey) == 0) //si el rey no est� en jaque
					{
						std::cout << "Rey no en jaque actualmente\n";
						if (piezaEnMedio(fdestino, cdestino, forigen, corigen))
						{
							return false; std::cout << "...pero hay una pieza en medio\n";
						}
						else
						{
							std::cout << "...y no hay pieza en medio\n";
							if (torre->getColumna() == 0) //torres de la izquierda
							{
								std::cout << "La columna de la torre es " << torre->getColumna() << " || Llamo a enroque largo\n";
								return (enroque(*torre, *rey, 'L'));
							}
							if (torre->getColumna() == 7)
							{
								std::cout << "La columna de la torre es " << torre->getColumna() << " |Llamo a enroque corto\n";
								return (enroque(*torre, *rey, 'C'));//torres de la derecha
							}
						}
					}
					else return false;
				}
				else return false;

			}
			else return false;
		}
		else return false;

	}
	else return false;
	
}

bool Tablero::enroque(Pieza& torre, Pieza& rey,char tipo)
{
	auto& _rey = rey;
	int _fila = torre.getFila();//tomo la fila en la que est� la torre
	int inicio = 2, fin = 4; //para enroque largo
	if (tipo == 'C') //enroque corto
	{
		inicio = fin;
		fin = 6;
	}
	for (int _columna = inicio; _columna == fin; _columna++)
	{
		_rey.setPosicion(_columna, _fila);//Compruebo que ninguna de las columnas por las que pasar� el rey quede atacada
		if (amenaza(_rey))
			return false;
	}
	if (tipo == 'C')
	{
		if ((actualizarId(_fila, 6, rey.getFila(), rey.getColumna()))&&(actualizarId(_fila, 5, torre.getFila(), torre.getColumna())))
				return true;
		else return false;
	}
	else //enroque largo
	{
		if ((actualizarId(_fila, 2, rey.getFila(), rey.getColumna()))&& (actualizarId(_fila, 3, torre.getFila(), torre.getColumna())))
			return true;
		else return false;
	}


}


bool Tablero::jaqueMate(Rey& rey)
{
	int _columna = rey.getColumna();
	int _fila = rey.getFila();
	if (amenaza(rey))//si est� en jaque..
	{
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
			{
				if ((rey.mover(i, j)) && casillaVacia(i, j))//..y el rey se puede mover a una casilla vac�a...
					return false; //...no hay jaque mate
				else return false;
			}
	}
	else
		return true;
}
void Tablero::imprimirId(int i, int j)
{
	if (id[j][i]) 
	{
		std::cout << "\n-------SOBRE LA ID----------" << "\n";
		std::cout << "id[" << i << "][" << j << "] "; imprimirTipo(id[j][i]->getTipo()); std::cout<< " en x= " << (id[j][i]->getColumna()) + 1 << " | y=" << (id[j][i]->getFila()) + 1 << "\n";
		imprimirColor(id[j][i]->getColor()); std::cout<< "\n";
	}
	else { std::cout << "\t PUNTERO NULO, casilla vacia: x=" << i +1 << " | y=" << j +1 << "\n"; }
}
void Tablero::imprimirLista(int i, int j)
{
	std::cout << "\n-------SOBRE LA LISTA----------" << "\n";
	for (int k = 0; k < numero; k++)
	{
		if ((lista[k]->getColumna() == i)&&(lista[k]->getFila() == j))
		{
			std::cout << "lista[" << k << "] esta en c=" << i + 1 << " f=" << j + 1; imprimirTipo(lista[k]->getTipo()); std::cout << "\n";
			imprimirColor(lista[k]->getColor()); std::cout << "\n";
		}
		//else { std::cout << "\t No se encuentra ninguna pieza en la lista en: x=" << i + 1 << " | y=" << j + 1 << "\n"; }
	}
}
void Tablero::imprimirLista()
{
	std::cout << "\n-------SOBRE LA LISTA----------" << "\n";
	for (int k = 0; k < numero; k++)
	{
		std::cout << "lista[" << k << "] esta en c=" << (lista[k]->getColumna())+1 << " f=" << (lista[k]->getFila()) + 1;
		imprimirTipo(lista[k]->getTipo()); std::cout << "\n";
		imprimirColor(lista[k]->getColor()); std::cout << "\n";
	}
}

void Tablero::imprimirTurno()
{
	std::string _turno;
	switch (turno)
	{
	case indefinido:
		break;
	case blanco:
		_turno = "BLANCAS";
		break;
	case negro:
		_turno = "NEGRAS";
		break;
	default:
		_turno = "indefinidas";
		break;
	}	
	std::cout << "\t ******** Juegan las  " << _turno << " **************\n";

}

void Tablero::imprimirColor(Color col)
{
	std::string _color;
	switch (col)
	{
	case indefinido:
		_color = "indefinido";
		break;
	case blanco:
		_color = "blanco";
		break;
	case negro:
		_color = "negro";
		break;
	default:
		break;
	}
	std::cout << " color: " << _color << " ";

}

void Tablero::imprimirTipo(Tipo tip)
{
	std::string _tip;
	switch (tip)
	{
		case PEON:
			_tip = "peon"; break;
		case TORRE:
			_tip = "torre"; break;
		case CABALLO:
			_tip = "caballo"; break;
		case ALFIL:
			_tip = "alfil"; break;
		case REY:
			_tip = "rey"; break;
		case REINA:
			_tip = "reina"; break;
		case INDEFINIDO:
			_tip = "indefinido"; break;
		default:
			break;
	}

	std::cout<< " tipo: " << _tip << " ";
}

void Tablero::comprobarAsignaciones()
{
	std::cout << "\n\n<<<<<<<<<<<<<<<<<<<<<<<<<<<COMPRUEBO ASIGNACION>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n";
	for (int k = 0; k < numero; k++)
	{
		std::cout << "\n\n\===============" << k << "===============";
		int _columna = lista[k]->getColumna();
		int _fila = lista[k]->getFila();
		imprimirId(_columna, _fila);
		imprimirLista(_columna, _fila);

	}
	std::cout << "\n-------------FIN--------------\n";

 }

