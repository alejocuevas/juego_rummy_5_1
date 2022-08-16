#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <time.h>
#include "rummy.h"


using namespace std;


int main(int argc, char **argv)
{
	State state = initializeState();
	printState(state);
	while (juegoterminado(state) == false)
	{
		juega_usuario(state);
		if (juegoterminado(state))
			break;
		juega_maquina(state);
		printState(state);
	}
	return 0;
}

/*
 * intercambiar las tarjetas en las posiciones pos1 y pos2.
 */

void swap(vector<int> &cartas, int posicion1, int posicion2)
{
	int temp = cartas[posicion1];
	cartas[posicion1] = cartas[posicion2];
	cartas[posicion2] = temp;
}

/*
 Mezcla las cartas del mazo
 */
void shuffle(vector<int> &mazo)
{
	srand(time(NULL));
	int size = mazo.size();
	for (int i = size-1; i >0; i--)
	{
		int cambiar_posicion = rand() % i;
		swap(mazo, i, cambiar_posicion);
	}
}

/* 
Devuelve un nuevo mazo mezclado
*/
vector<int> getNuevomazo()
{
	vector<int> mazo;
	for (int i = 0; i < 52; i++)
	{
		mazo.push_back(i);
	}
	shuffle(mazo);
	return mazo;
}


list<int> initializerestante()
{
	list<int> restante;
	for (int i = 0; i < 52; i++)
		restante.push_back(i);
	return restante;
}

/*

Cambia las cartas entre el usuario y la maquina

*/

void cambiar_cartas(vector<int> &mazo, vector<int> &mano_usuario, vector<int> &mano_maquina)
{
	for (int i = 0; i < 14; i ++)
	{
		int ultima_carta = mazo.back();
		mazo.pop_back();
		if (i%2 == 0)
			mano_usuario.push_back(ultima_carta);
		else
			mano_maquina.push_back(ultima_carta);
	}
}

/*
Ajusta las cartas restantes que no tiene ni el agente ni el usuario pero que todavia estan en juego.

*/

void ajustar_restante(list<int> &restante, vector<int> mano)
{
	for (int i = 0; i < mano.size(); i++)
		restante.remove(mano[i]);
}


State initializeState()
{
	State state;
	state.mazo = getNuevomazo();
	state.restante = initializerestante();
	cambiar_cartas(state.mazo, state.mano_usuario, state.mano_maquina);
	ajustar_restante(state.restante, state.mano_maquina);
	mergeSort(state.mano_usuario, 0, state.mano_usuario.size());
	state.turno_carta = 52;
	return state;
}

/* 
Simbolo de las cartas
*/

char getsimbolo(int i)
{
	if (i < 13)
		return '&';
	else if (i < 26)
		return '%';
	else if (i < 39)
		return '$';
	else
		return '@';
}

/* 
Numero de las cartas.
*/

char getnum(int i)
{
	int num = i % 13;
	if (num == 0)
		return 'A';
	if (num == 1)
		return '2';
	if (num == 2)
		return '3';
	if (num == 3)
		return '4';
	if (num == 4)
		return '5';
	if (num == 5)
		return '6';
	if (num == 6)
		return '7';
	if (num == 7)
		return '8';
	if (num == 8)
		return '9';
	if (num == 9)
		return 'T';
	if (num == 10)
		return 'J';
	if (num == 11)
		return 'Q';
	return 'K';
}

/* 
Mazo de la maquina
*/

void printmaquina_mano_mazo()
{
	
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 56; j++)
		{
			int k = j % 8;
			if (k == 7)
				cout << "* ";
			else if (i == 0 || i == 9 || k == 0)
				cout << "*";
			else
				cout << "?";
		}
		cout << endl;
	}
	cout << endl;


	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i == 0 || i == 9 || j == 0 || j == 7)
				cout << "*";
			else
				cout << "?";
		}
		cout << endl;
	}
	cout << endl;
}

/*

Carta del turno
*/

void printturno_carta(int v)
{
	char simbolo = getsimbolo(v);
	char num = getnum(v);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i == 0 || i == 9 || j == 0 || j == 7)
				cout << "*";
			else if ((j == 1 && i == 1) || (j == 6 && i == 8) || (j == 3 && i == 4))
				cout << num;
			else if ((j == 6 && i == 1) || (j == 1 && i == 8) || (j == 4 && i == 5))
				cout << simbolo;
			else
				cout << " ";
		}
		cout << endl;
	}
	cout << endl;
}

/*
Dibuja la mano
*/

void printmano(vector<int> mano)
{
	int size = mano.size();
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < size; j++)
		{
			char num = getnum((mano[j]));
			char simbolo = getsimbolo((mano[j]));
			for (int k = 0; k < 8; k++)
			{
				if (k == 7)
					cout << "* ";
				else if (i == 0 || i == 9 || k == 0)
					cout << "*";
				else if ((k == 1 && i == 1) || (k == 6 && i == 8) || (k == 3 && i == 4))
					cout << num;
				else if ((k == 6 && i == 1) || (k == 1 && i == 8) || (k == 4 && i == 5))
					cout << simbolo;
				else
					cout << " ";
			}
		}
		cout << endl;
	}
	cout << endl;
}

/*
Dibuja el estado actual del juego
*/

void printState(State state)
{

	printmaquina_mano_mazo();
	if (state.turno_carta < 52)
		printturno_carta(state.turno_carta);
	printmano(state.mano_usuario);
}

/*
Combina los elementos del vector
*/

void merge(vector<int> integers, int a1, int m, int b2, vector<int> &output)
{
	int a2, b1;
	a2 = b1 = m;
	while (a1 < a2 && b1 < b2)
	{
		if (integers[a1] <= integers[b1])
			output.push_back(integers[a1++]);
		else
			output.push_back(integers[b1++]);
	}

	while (a1 < a2)
		output.push_back(integers[a1++]);
	while (b1 < b2)
		output.push_back(integers[b1++]);
}



void mergeSort(vector<int> &integers, int iniciar, int terminar)
{
	if ((terminar - iniciar) <= 1)
		return;
	int m = (terminar - iniciar) / 2;
	mergeSort(integers, iniciar, iniciar+m);
	mergeSort(integers, iniciar+m, terminar);

	vector<int> temp;
	merge(integers, iniciar, iniciar+m, terminar, temp);
	int tempIndex = 0;
	for (int i = iniciar; i < terminar; i++)
		integers[i] = temp[tempIndex++];
}

/*
Determina si la mano es el ganador o no.
*/

bool Es_Ganador(vector<int> mano)
{
	mergeSort(mano, 0, mano.size());		

	/* 
	Revisa si las primeras 4 cartas estan en racha (ejemplo 1-2-3-4)
	*/
	if (mano[0] % 13 < 10 && mano[1] == mano[0] + 1 && mano[2] == mano[0] + 2
				&& mano[3] == mano[0] + 3)
	{
		/*Revisa si las ultimas 3 cartas estan en racha */
		
		if (mano[4] % 13 < 11 && mano[5] == mano[4] + 1 && mano[6] == mano[4] + 1)
			return true;
		/* Revisa si las ultimas 3 cartas son iguales */
		if (mano[4] % 13 == mano[5] % 13 && mano[4] % 13 == mano[6] % 13)
			return true;
	}

 
/* Revisa si las primeras 3 cartas estan en racha */
	if (mano[0] % 13 < 11 && mano[1] == mano[0] + 1 && mano[2] == mano[0] + 2)
	{
	/* Revisa si las ultimas 4 cartas estan en racha */
		if (mano[3] % 13 < 10 && mano[4] == mano[3] + 1 && mano[5] == mano[3] + 2
					&& mano[6] == mano[3] + 3)
			return true;
	/* Revisa si las ultimas 4 cartas son iguales */
		if (mano[3] % 13 == mano[4] % 13 && mano[3] % 13 == mano[5] % 13
					&& mano[3] % 13 == mano[6] % 13)
			return true;
	}

	/* A�adir cartas que no sean del mismo rango que la primera a una lista */
	vector<int> no_iguales;
	for (int i = 0; i < mano.size(); i++)
	{
		if (mano[i] % 13 != mano[0] % 13)
			no_iguales.push_back(mano[i]);
	}

	
	if (no_iguales.size() != 3 && no_iguales.size() != 4)
		return false;

	
	bool racha = true;
	for (int i = 0; i < no_iguales.size(); i++)
	{
		if (no_iguales[i] != no_iguales[0] + i)
			racha = false;
	}
	if (racha)
		return true;

	
	for (int i = 0; i < no_iguales.size(); i++)
	{
		if (no_iguales[i] % 13 != no_iguales[0] % 13)
			return false;
	}
	return true;
}


/* 
Devuelve verdadero si el juego ha terminado o devuelve falso en caso contrario.

*/
bool juegoterminado(State state)
{
	/*Revisa si el usuario gana */
	if (Es_Ganador(state.mano_usuario))
	{
		cout << "Ganaste el juego!" << endl;
		printmano(state.mano_usuario);
		return true;
	}

/*Revisa si el usuario pierde */
	if (Es_Ganador(state.mano_maquina))
	{
		cout << "Gano la maquina!" << endl;
		printmano(state.mano_maquina);
		cout << "Perdiste el juego! :(" << endl;
		return true;
	}

	/* No gano ninguno */
	return false;
}


void juega_usuario(State &state)
{
	/* Le da opciones al usuario */
	if (state.turno_carta < 52)
		cout << "Ingrese \"t\" para tomar una carta del turno." << endl;
	cout << "Ingrese \"m\" para tomar una carta del mazo." << endl;
	char eleccion;
	cin >> eleccion;
	while (eleccion != 'm' && (eleccion != 't' || state.turno_carta == 52))
	{
		if (state.turno_carta < 52)
			cout << "Ingrese \"t\" para tomar una carta del turno." << endl;
		cout << "Ingrese \"m\" para tomar una carta del mazo." << endl;
		cin >> eleccion;
	}
	/* El usuario quiere tomar una carta del turno */
	if (eleccion == 't')
		state.mano_usuario.push_back(state.turno_carta);
	/*El usuario quiere tomar una carta del mazo */
	else
	{
		state.mano_usuario.push_back(state.mazo.back());
		state.mazo.pop_back();
	}
	printmano(state.mano_usuario);

	/*Le da opciones al usuario */
	cout << "Ingrese \"g\" para devolver la carta o \"r\" para reorganizar tu mano.";
	cout << endl;
	cin >> eleccion;
	while (eleccion != 'g' && eleccion != 'r')
	{
		cout << "Ingrese \"g\" para devolver la carta o \"r\" para reorganizar tu mano.";
		cout << endl;
		cin >> eleccion;
	}
	while (eleccion != 'g')
	{
		/*El usuario quiere reorganizar su mano */
		if (eleccion == 'r')
		{
			char posicion1, posicion2;
			cout << "Ingrese la posicion de la primera carta a cambiar 1-8." << endl;
			cin >> posicion1;
			while (posicion1 < '1' || posicion1 > '8')
			{
				cout << "Ingrese la posicion de la primera carta a cambiar 1-8." << endl;
				cin >> posicion1;
			}
			cout << "Ingrese la posicion de la segunda carta a cambiar 1-8." << endl;
			cin >> posicion2;
			while (posicion2 < '1' || posicion2 > '8')
			{
				cout << "Ingrese la posicion de la segunda carta a cambiar 1-8." << endl;
				cin >> posicion2;
			}
			/*cambia cartas */
			swap(state.mano_usuario, posicion1-49, posicion2-49);		
			printmano(state.mano_usuario);					
		}
		/*Le da opciones al usuario */
		cout << "Ingrese \"g\" para devolver la carta o \"r\" para reorganizar tu mano.";
		cout << endl;
		cin >> eleccion;
		while (eleccion != 'g' && eleccion != 'r')
		{
			cout << "Ingrese \"g\" para devolver la carta o \"r\" para reorganizar tu mano.";
			cout << endl;
			cin >> eleccion;
		}
	}
	/*El usuario quiere devolver una carta */
	if (eleccion == 'g')
	{
		cout << "Ingrese la posicion de la carta que te gustaria devolver 1-8";
		cout << endl;
		char pos;
		cin >> pos;
		while (pos < '1' || pos > '8')
		{
			cout << "Ingrese la posicion de la carta que te gustaria devolver 1-8";
			cout << endl;
			cin >> pos;
		}
		state.turno_carta = state.mano_usuario[pos-49];					
		state.restante.remove(state.turno_carta);						
		state.mano_usuario.erase(state.mano_usuario.begin()+pos-49);		
	}
}

/*
 Una funci�n que eval�a una mano determinada.
 Si la mano es ganadora, se devuelve el valor 100
 Si se da 4 iguales o 4 en racha se devuelve +15
 Se da +11 por 3 en raya con 2 cartas restantes que pueden hacer 4 en raya.
 se da 3 en una fila o 3 del mismo tipo con 1 restante +10
  se da por 3 seguidos o 3 iguales con 0 restantes. +9
  se da por 2 seguidos con 4 restantes. +4
  se da por 2 seguidos con 3 restantes. +3
  se da por 2 seguidos o un par con 2 restantes +2
  se da por 2 seguidos o un par con 1 restante +1
 */
int evaluate(State state)
{
	mergeSort(state.mano_maquina, 0, state.mano_maquina.size());
	vector<int> mano = state.mano_maquina;
	list<int> restante = state.restante;
	int puntos = 0;		/* puntos de la mano*/			
	int num;		    /* num de la carta */						
	int val;			/* valor almacenado de la carta */					

	/*Revisa si la mano es el ganador */
	if (Es_Ganador(mano))
		return 100;

	/* Comprueba si hay 4 del mismo tipo o 4 seguidos */
	for (int i = 0; i < mano.size() - 3; i++)
	{
		val = mano[i];
		num = val % 13;
		/* Revisa por 4 del mismo tipo */
		int contador_partida = 0;
		for (int j = i + 1; j < mano.size(); j++)
		{
			if (num == mano[j] % 13)
				contador_partida++;
		}
		if (contador_partida == 3)
		{
			puntos += 15;
			contador_partida = 0;
		}

	/*Revisa por 4 en racha */
		if (val < 10 && val+1 == mano[i+1] && val+2 == mano[i+2]
				&& val+3 == mano[i+3])
			puntos += 15;
	}

/* Revisa por 3 del mismo tipo o 3 en racha */
	for (int i = 0; i < mano.size() - 2; i++)
	{
		val = mano[i];
		num = val % 13;

	/* Revisa por 3 del mismo tipo */
		int contador_partida = 0;
		for (int j = i + 1; j < mano.size(); j++)
		{
			if (num == mano[j] % 13)
				contador_partida++;
		}
		if (contador_partida == 2)
		{
			puntos += 9;
		/* Revisa por 1 del mismo tipo en las cartas restantes */
			for (list<int>::iterator it = restante.begin();
						it != restante.end(); it++)
				if (*it % 13 == num)
					puntos ++;
			contador_partida = 0;
		}	

	/* Revisa por 3 en racha */
		if (num < 11 && val+1 == mano[i+1] && val+2 == mano[i+2])
		{
			puntos += 9;
/* Comprueba si hay 1 antes y 1 despu�s en las tarjetas restantes */
			for (list<int>::iterator it = restante.begin();
						it != restante.end(); it++)
			{
				if (num > 0 && *it == val - 1)
					puntos++;
				if (num < 10 && *it == val + 3)
					puntos++;
			}
		}
	}

/* Revisa si hay 2 en racha o 2 seguidos */
	for (int i = 0; i < mano.size() - 1; i++)
	{
		val = mano[i];
		num = val % 13;


		int contador_partida = 0;
		for (int j = i + 1; j < mano.size(); j++)
		{
			if (num == mano[j] % 13)
				contador_partida++;
		}
		if (contador_partida == 1)
		{
	/* Revisa si hay 2 iguales */
			for (list<int>::iterator it = restante.begin();
						it != restante.end(); it++)
				if (*it % 13 == num)
					puntos++;
			contador_partida = 0;
		}

/*Revisa si hay 2 en racha */
		if (num < 12 && val+1 == mano[i+1])
		{
		/* Comprobar 1 o 2 antes y 1 o 2 despu�s en las cartas restantes */
			for (list<int>::iterator it = restante.begin();
						it != restante.end(); it++)
			{
				if (num > 0 && *it == val - 1)
				{
					puntos++;
					for (list<int>::iterator jt = restante.begin();
						jt != restante.end(); jt++)
						if (num > 1 && *jt == val - 2)
							puntos++;
				}
				if (num < 11 && *it == val + 2)
				{
					puntos++;
					for (list<int>::iterator jt = restante.begin();
						jt != restante.end(); jt++)
						if (num < 10 && *jt == val + 3)
							puntos++;
				}
			}
		}			
	}

	return puntos;
}

/*
  Una funci�n que determina si la maquina
  debe recoger la carta de turno o no.
 Si la carta del turno es ganadora, devuelve verdadero.
 Si la carta del turno da como resultado un tr�o
 o 3 seguidos que no estaban ahi antes, devuelve verdadero.
 De lo contrario, devuelve falso.
 */

bool taketurno_carta(State state)
{
	State originalState = state;
	vector<int> testmano = state.mano_maquina;
	testmano.push_back(state.turno_carta);	


	while (state.mano_maquina.empty() == false)
		state.mano_maquina.pop_back();


	for (int i = 0; i < testmano.size(); i++)
	{
		for (int j = 0; j < testmano.size(); j++)
		{
			if (i != j)
				state.mano_maquina.push_back(testmano[j]);
		}


		if (Es_Ganador(state.mano_maquina))
			return true;


		if (evaluate(state) > evaluate(originalState))
			return true;

		while (state.mano_maquina.empty() == false)
			state.mano_maquina.pop_back();
	}
	return false;
}

/*
 Una funci�n que elimina la peor carta de la maquina
 mano. 
 */
int removepeorcarta(State &state)
{
	State testState = state;


	while (testState.mano_maquina.empty() == false)
		testState.mano_maquina.pop_back();

	int maxEval = 0;
	int maxEvalIndex = 0;
	int eval = 0;


	for (int i = 0; i < state.mano_maquina.size(); i++)
	{
		for (int j = 0; j < state.mano_maquina.size(); j++)
		{
			if (i != j)
				testState.mano_maquina.push_back(state.mano_maquina[j]);
		}

		eval = evaluate(testState);
		if (eval > maxEval)
		{
			maxEval = eval;
			maxEvalIndex = i;
		}


		while (testState.mano_maquina.empty() == false)
			testState.mano_maquina.pop_back();
	}

	int returnVal = state.mano_maquina[maxEvalIndex];

 /* Remove worst card */
	state.mano_maquina.erase(state.mano_maquina.begin() + maxEvalIndex);

	return returnVal;
}


void juega_maquina(State &state)
{

	if (taketurno_carta(state))
	{
		cout << "La maquina toma una carta!" << endl;
		int turno_carta = state.turno_carta;
		state.mano_maquina.push_back(turno_carta);
		state.turno_carta = removepeorcarta(state);
	}
	else
	{
		cout << "La maquina toma una carta del mazo." << endl;
		state.mano_maquina.push_back(state.mazo.back());
		state.restante.remove(state.mazo.back());
		state.mazo.pop_back();
		state.turno_carta = removepeorcarta(state);
	}
}
