#include <iostream>
#include <queue>
#include <vector>
#include <stack>
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

pair<int, int> generaCoordinateArrivo(int rigaDiPartenza, int colonnaDiPartenza, int numeroRandom){
    int rigaDiArrivo;
    int colonnaDiArrivo;
    if(rigaDiPartenza == 0){
        rigaDiArrivo = 19;
        colonnaDiArrivo = numeroRandom;
    }else if(rigaDiPartenza == 19){
        rigaDiArrivo = 0;
        colonnaDiArrivo = numeroRandom;
    }else if(colonnaDiPartenza == 0){
        colonnaDiArrivo = 19;
        rigaDiArrivo = numeroRandom;
    }else{
        colonnaDiArrivo = 0;
        rigaDiArrivo = numeroRandom;
    }
    return {rigaDiArrivo, colonnaDiArrivo}; 
}

void generaBordi(vector<vector<char>> &labirinto, int row, int col){
    for(int i = 0; i < row; i++){
        if (labirinto[0][i] != 'A' && labirinto[0][i] != 'B')
            labirinto[0][i] = '#';
    }
    for (int i = 0; i < col; i++)
    {
        if (labirinto[19][i] != 'A' && labirinto[19][i] != 'B')
        labirinto[19][i] = '#'; 
    }
    for (int i = 0; i < row; i++)
    {
        if (labirinto[i][0] != 'A' && labirinto[i][0] != 'B')
        labirinto[i][0] = '#'; 
    }
    for (int i = 0; i < col; i++)
    {
        if (labirinto[i][19] != 'A' && labirinto[i][19] != 'B')
        labirinto[i][19] = '#'; 
    }
}



int main(){
    srand(time(0) ^ getpid());

    vector<vector<char>> labirinto(ROW, vector<char>(COL, '#'));
    stack<pair<int,int>> percorso;
    
    cout << "Labirinto iniziale: " << endl;
    stampaVettoreAnnidato(labirinto, ROW, COL);
    
    // sceglie se partire dalla riga in: alto == 0, destra == 1, basso == 2, sinistra == 3;
    // ho separato le due coordinate per poter limitare la prima ai bordi
    int x = generaIndiceRandom(4);
    // sceglie la seconda coordinata per genersare due coordinate random
    int y = generaIndiceRandom(20);
    int z = generaIndiceRandom(20);

    pair<int, int> partenza = generaCoordinatePartenza(x, y);
    
    labirinto[partenza.first][partenza.second] = 'A';
    percorso.push(partenza);

    cout << "Labirinto con il punto di partenza: " << endl;
    stampaVettoreAnnidato(labirinto, ROW, COL);

    pair<int, int> arrivo = generaCoordinateArrivo(partenza.first, partenza.second, z);

    labirinto[arrivo.first][arrivo.second] = 'B';

    cout << "Labirinto con il punto di partenza e punto di arrivo: " << endl;
    stampaVettoreAnnidato(labirinto, ROW, COL);

    int dr[4] = {-1, 0, 1, 0}; // spostamento sulla riga - cambierà riga di una cella
    int dc[4] = {0, 1, 0, -1}; // spostamento sulla colonna - cabierà colonna di una cella

    int drr[4] = {-2, 0, 2, 0}; // spostamento sulla colonna - cambierà riga di due celle
    int dcc[4] = {0, 2, 0 ,-2}; // spostamento sulla riga - cabierà colonna di due celle

    //salva in due variabili le coordinate della cella attuale
    auto [a, b] = percorso.top();
        
    // sposto la cella attuale un passo più interno
    if(a == 0) a++;
    if(a == 19) a--;
    if(b == 0) b++;
    if(b == 19) b--;

    labirinto[a][b] = '.';
    percorso.push({a, b});

    int c,d;
    c = arrivo.first;
    d = arrivo.second;

    if(c == 0) c++;
    if(c == 19) c--;
    if(d == 0) d++;
    if(d == 19) d--;

    labirinto[c][d] = '.';  


    // Algoritmo DFS per creare un percorso
    while (!percorso.empty())
    {
        //salva in due variabili le coordinate della cella attuale
        auto [r, c] = percorso.top();

        vector<int> direzioniPossibili;

        // ciclo per controllare tutte le direzioni possibili
        for (int i = 0; i < 4; i++)
        {
            // celle accanto alla cella attuale
            int nr = r + dr[i];
            int nc = c + dc[i];

            // due celle accanto alla cella attuale
            int nrr = r + drr[i];
            int ncc = c + dcc[i];
            
            // controlla che la cella accanto e due celle accanto alla cella attuale siano dei muri e che non escano dal bordo
            if(nr >= 0 && nr < ROW && nc >= 0  && nc < COL && nrr >= 0 && nrr < ROW && ncc >= 0  && ncc < COL && labirinto[nr][nc] == '#' && labirinto[nrr][ncc] == '#'){
                direzioniPossibili.push_back(i);
            }
        }

        if(direzioniPossibili.empty()) percorso.pop();
        else{
            int k = rand() % direzioniPossibili.size();
            int dir = direzioniPossibili[k];

            int nr = r + dr[dir];
            int nc = c + dc[dir];

            int nrr = r + drr[dir];
            int ncc = c + dcc[dir];

            labirinto[nr][nc] = '.';
            labirinto[nrr][ncc] = '.';
            percorso.push({nrr, ncc});
        }
    }

    cout << "Labirinto con percorso: " << endl;
    stampaVettoreAnnidato(labirinto, ROW, COL);

    cout << "Labirinto con percorso e bordi: " << endl;
    generaBordi(labirinto, ROW, COL);
    stampaVettoreAnnidato(labirinto, ROW, COL);


    return 0;
}