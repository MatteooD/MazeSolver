#include <iostream>
#include <queue>
#include <deque>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <utility>
using namespace std;


/*                   1 1 1 1 1 1 1 1 1 2
   1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9 0
1  # # # # # # # # # # # # # # # # # # #
2  # # # # # # # # # # # # # # # # # # #
3  # # # # # # # # # # # # # # # # # # #
4  # # # # # # # # # # # # # # # # # # #
5  # # # # # # # # # # # # # # # # # # #
6  # # # # # # # # # # # # # # # # # # #
7  # # # # # # # # # # # # # # # # # # #
8  # # # # # # # # # # # # # # # # # # #
9  # # # # # # # # # # # # # # # # # # #
10 # # # # # # # # # # # # # # # # # # #
11 # # # # # # # # # # # # # # # # # # #
12 # # # # # # # # # # # # # # # # # # #
13 # # # # # # # # # # # # # # # # # # #
14 # # # # # # # # # # # # # # # # # # #
15 # # # # # # # # # # # # # # # # # # #
16 # # # # # # # # # # # # # # # # # # #
17 # # # # # # # # # # # # # # # # # # #
18 # # # # # # # # # # # # # # # # # # #
19 # # # # # # # # # # # # # # # # # # #
20 # # # # # # # # # # # # # # # # # # #
*/

const int ROW = 20;
const int COL = 20;

enum direzioneDIPartenza{
    alto,
    destra,
    basso,
    sinistra
};

int generaIndiceRandom(int range){
    int x = rand() % range;
    return x;
}

void stampaVettoreAnnidato(vector<vector<char>> &labirinto, int row, int col){
    for (int righe = 0; righe < row; righe++)
    {
        for (int colonne = 0; colonne < col; colonne++)
        {
            cout << labirinto[righe][colonne] << " ";
        }
       cout << endl; 
    }
}

pair<int, int> generaCoordinatePartenza(int x, int y){
    srand(time(0) ^ getpid());

    int rigaDiPartenza;
    int colonnaDiPartenza;

    if (x == alto){
        rigaDiPartenza = 0;
        colonnaDiPartenza = y;
    }
    else if(x == destra){
        colonnaDiPartenza = 19;
        rigaDiPartenza = y;
    }
    else if(x == basso){
        rigaDiPartenza = 19;
        colonnaDiPartenza = y;
    }
    else{
        colonnaDiPartenza = 0;
        rigaDiPartenza = y;
    }
    return {rigaDiPartenza, colonnaDiPartenza};
}



int main(){

    vector<vector<char>> labirinto(ROW, vector<char>(COL, '#'));
    
    cout << "Labirinto iniziale: " << endl;
    stampaVettoreAnnidato(labirinto, ROW, COL);
    
    // sceglie se partire dalla riga in: alto == 0, destra == 1, basso == 2, sinistra == 3;
    // ho separato le due coordinate per poter limitare la prima ai bordi
    int x = generaIndiceRandom(4);
    // sceglie la seconda coordinata per genersare due coordinate random
    int y = generaIndiceRandom(20);

    pair<int, int> partenza = generaCoordinatePartenza(x, y);
    
    labirinto[partenza.first][partenza.second] = 'A';

    cout << "Labirinto con il punto di partenza: " << endl;
    stampaVettoreAnnidato(labirinto, ROW, COL);

    return 0;
}