
#ifndef __RUMMY_51__
#define __RUMMY_51__

using namespace std;



struct State {
	vector<int> mazo;
	vector<int> mano_maquina;
	vector<int> mano_usuario;
	list<int> restante;
	int turno_carta;
};


void swap(vector<int> &cards, int posicion1, int posicion2);


void shuffle(vector<int> &mazo);


vector<int> getNuevomazo();


list<int> initializerestante();


void cambiar_cartas(vector<int> &mazo, vector<int> &mano_usuario, vector<int> &agentmano);



void ajustar_restante(list<int> &restante, vector<int> mano);


State initializeState();



char getsimbolo(int i);


char getnum(int i);


void printmaquina_mano_mazo();


void printturno_carta(int v);


void printmano(vector<int> mano);


void printState(State state);



void merge(vector<int> integers, int a1, int a2, int b1, int b2, vector<int> &output);


void mergeSort(vector<int> &integers, int iniciar, int terminar);


bool Es_Ganador(vector<int> mano);


bool juegoterminado(State state);


void juega_usuario(State &state);


int evaluate(State state);


bool taketurno_carta(State state);



int removepeorcarta(State &state);


void juega_maquina(State &state);

#endif
