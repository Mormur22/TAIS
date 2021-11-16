#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Matriz.h"

using namespace std;

const int INFINITO = 1000000000;

/*

 f(i,j) = { T[i][j] + max(f(i-1, j-1), f(i-1,j), f(i-1, j+1)) //ojo con los laterales    i>j
 casos base:
 f(1, j) = T[1][j]
 sol = max(f(n, j))	 1<=j<=n
*/

typedef struct cruce
{
	bool visitado;
	int min_camino;
	char c;
	
};


//coste: O(N^2) en espacio y O(N ^ 2 + N) en tiempo donde N es el numero de filas/columnas del tablero
//coor.first --> row
//coor.second --> column
void resuelve(Matriz<cruce> &mapa, const int &N, const int& M, int &num_caminos, pair<int,int> coor)
{

	//Miramos si es posible ir al Sur                                                                                                                                                                                                                  
	if (coor.first + 1 < N && mapa.posCorrecta(coor.first + 1, coor.second) && mapa.at(coor.first + 1, coor.second).c != 'P')
	{
		if (mapa.at(coor.first + 1, coor.second).visitado == true)
		{
			num_caminos++;
		}

		else if (coor.first+1 == N && coor.second == M)
		{
			num_caminos++;
		}

		else {
			
			mapa.at(coor.first + 1, coor.second).visitado = true;
			resuelve(mapa, N, M, num_caminos, { coor.first + 1,coor.second });
		}
	}

	//Vamos al este
	if (coor.second + 1 < M && mapa.posCorrecta(coor.first , coor.second+1) && mapa.at(coor.first, coor.second+1).c != 'P')
	{
		if (mapa.at(coor.first, coor.second+1).visitado == true)
		{
			num_caminos++;
		}

		else if(coor.first == N && coor.second + 1 == M)
		{
			num_caminos++;
		}

		else {

			mapa.at(coor.first, coor.second+1).visitado = true;
			resuelve(mapa, N, M, num_caminos, { coor.first + 1,coor.second });
		}
	}

}

bool resuelveCaso() {
	int N,M;

	cin >> N>>M;

	if (!std::cin)  // fin de la entrada
		return false;

	Matriz<cruce> tablero(N, M);

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {

			cin >> tablero[i][j].c;
			tablero[i][j].min_camino = 0;
			tablero[i][j].visitado = false;
		}
	}

	int num_caminos = 0;
	pair<int, int> coor({ 0,0 });
	
	resuelve(tablero, N,M, num_caminos,coor);

	cout << num_caminos<<"\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("casos62.txt");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}