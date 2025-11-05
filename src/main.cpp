#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <climits>
using namespace std;

/*                   1 1 1 1 1 1 1 1 1 2
   1 2 3 4 5 6 7 8 9 1 2 3 4 5 6 7 8 9 0
1  # # # # # # # # # # # # # # # # # # #
2  # # # # # # # # # # # # # # # # # # #
3  # # # # # # # # # # # # # # # # # # #
4  # # # # # # # # # # # # # # # # # # #
5  # # # # # # # # # # # # # # # # # # #
6  # # # # # # # # # # # # # # # # # # #
7  # # # # # # # # # # # # # # # # # # #
8  # # # # # # # # # # # # # # # # # # #
9  # # # # # # # # # # # # # # # # # # #
10 # # # # # # # # # # # # # # # # # # #
11 # # # # # # # # # # # # # # # # # # #
12 # # # # # # # # # # # # # # # # # # #
13 # # # # # # # # # # # # # # # # # # #
14 # # # # # # # # # # # # # # # # # # #
15 # # # # # # # # # # # # # # # # # # #
16 # # # # # # # # # # # # # # # # # # #
17 # # # # # # # # # # # # # # # # # # #
18 # # # # # # # # # # # # # # # # # # #
19 # # # # # # # # # # # # # # # # # # #
20 # # # # # # # # # # # # # # # # # # #
*/

const int ROW = 20;
const int COL = 20;

const int DR[4] = {-1, 0, 1, 0};  // spostamento sulla riga - cambierà riga di una cella
const int DC[4] = {0, 1, 0, -1};  // spostamento sulla colonna - cabierà colonna di una cella
const int DR2[4] = {-2, 0, 2, 0}; // spostamento sulla colonna - cambierà riga di due celle
const int DC2[4] = {0, 2, 0, -2}; // spostamento sulla riga - cabierà colonna di due celle

enum DirezioneDiPartenza { alto, destra, basso, sinistra };

int generaIndiceRandom(int range)
{
    return rand() % range;
}

void stampaVettoreAnnidato(vector<vector<char>> &labirinto, int row, int col)
{
    for (int righe = 0; righe < row; righe++)
    {
        for (int colonne = 0; colonne < col; colonne++)
        {
            cout << labirinto[righe][colonne] << " ";
        }
        cout << endl;
    }
}

pair<int, int> generaCoordinatePartenza(int x, int y)
{
    int rigaDiPartenza;
    int colonnaDiPartenza;

    if (x == alto) { rigaDiPartenza = 0; colonnaDiPartenza = y; }
    else if (x == destra) { colonnaDiPartenza = COL - 1; rigaDiPartenza = y; }
    else if (x == basso) { rigaDiPartenza = ROW - 1; colonnaDiPartenza = y; }
    else { colonnaDiPartenza = 0; rigaDiPartenza = y; }

    return {rigaDiPartenza, colonnaDiPartenza};
}

pair<int, int> generaCoordinateArrivo(int rigaDiPartenza, int colonnaDiPartenza, int numeroRandom)
{
    int rigaDiArrivo;
    int colonnaDiArrivo;

    if (rigaDiPartenza == 0){ rigaDiArrivo = ROW - 1; colonnaDiArrivo = numeroRandom; }
    else if (rigaDiPartenza == ROW - 1) { rigaDiArrivo = 0; colonnaDiArrivo = numeroRandom; }
    else if (colonnaDiPartenza == 0) { colonnaDiArrivo = COL - 1; rigaDiArrivo = numeroRandom; }
    else { colonnaDiArrivo = 0; rigaDiArrivo = numeroRandom; }

    return {rigaDiArrivo, colonnaDiArrivo};
}

void generaBordi(vector<vector<char>> &labirinto, int row, int col)
{
    for (int i = 0; i < row; i++)
    {
        if (labirinto[0][i] != 'A' && labirinto[0][i] != 'B') labirinto[0][i] = '#';
        if (labirinto[i][0] != 'A' && labirinto[i][0] != 'B') labirinto[i][0] = '#';
    }
    for (int i = 0; i < col; i++)
    {
        if (labirinto[ROW - 1][i] != 'A' && labirinto[ROW - 1][i] != 'B') labirinto[ROW - 1][i] = '#';
        if (labirinto[i][COL - 1] != 'A' && labirinto[i][COL - 1] != 'B') labirinto[i][COL - 1] = '#';
    }
}

pair<int, int> spostaInternoA(pair<int, int> cella)
{
    auto [a, b] = cella;

    if (a == 0) a++;
    if (a == ROW - 1) a--;
    if (b == 0) b++;
    if (b == COL - 1) b--;

    return {a, b};
}

pair<int, int> spostaInternoB(pair<int, int> cella)
{
    auto [a, b] = cella;

    if (a == 0) a++;
    if (a == ROW - 1) a--;
    if (b == 0) b++;
    if (b == COL - 1) b--;

    return {a, b};
}

void generaLabirinto(stack<pair<int, int>> &percorso, vector<vector<char>> &labirinto)
{
    while (!percorso.empty())
    {
        auto [r, c] = percorso.top();
        vector<int> direzioniPossibili;

        for (int i = 0; i < 4; i++)
        {
            int nr = r + DR[i], nc = c + DC[i];
            int nrr = r + DR2[i], ncc = c + DC2[i];

            if (nrr >= 0 && nrr < ROW && ncc >= 0 && ncc < COL && labirinto[nr][nc] == '#' && labirinto[nrr][ncc] == '#')
                direzioniPossibili.push_back(i);
        }

        if (direzioniPossibili.empty()) percorso.pop();
        else
        {
            int dir = direzioniPossibili[rand() % direzioniPossibili.size()];
            int nr = r + DR[dir], nc = c + DC[dir];
            int nrr = r + DR2[dir], ncc = c + DC2[dir];

            labirinto[nr][nc] = '.';
            labirinto[nrr][ncc] = '.';
            percorso.push({nrr, ncc});
        }
    }
}

bool bfsVerifica(queue<pair<int, int>> &bfs, vector<vector<bool>> &visitato, vector<vector<char>> &labirinto, pair<int, int> arrivo)
{
    while (!bfs.empty())
    {
        auto [r, c] = bfs.front();
        bfs.pop();

        if (r == arrivo.first && c == arrivo.second) return true;

        for (int i = 0; i < 4; i++)
        {
            int nr = r + DR[i], nc = c + DC[i];


            if (nr >= 0 && nr < ROW && nc >= 0 && nc < COL && labirinto[nr][nc] != '#' && !visitato[nr][nc])
            {
                visitato[nr][nc] = true;
                bfs.push({nr, nc});
            }
        }
    }
    return false;
}

pair<int, int> trovaCellaVicinoAB(queue<pair<int, int>> bfs, vector<vector<bool>> visitato, vector<vector<char>> &labirinto, pair<int, int> Bin)
{
    pair<int, int> cellaPiuVicina = {-1, -1};
    int distanzaMinima = INT_MAX;

    while (!bfs.empty())
    {
        auto [r, c] = bfs.front();
        bfs.pop();

        int dist = abs(r - Bin.first) + abs(c - Bin.second);
        if(dist < distanzaMinima){
            distanzaMinima = dist;
            cellaPiuVicina = {r, c};
        }

        for(int i = 0; i < 4; i++){
            int nr = r + DR[i], nc = c + DC[i];
            
            if(nr >= 0 && nr < ROW && nc >= 0 && nc < COL && labirinto[nr][nc] != '#' && !visitato[nr][nc]){
                visitato[nr][nc] = true;
                bfs.push({nr, nc});
            }
        }
    }
    return cellaPiuVicina;
}

void forzaPercorso(pair<int,int> A, pair<int,int> B, vector<vector<char>> &labirinto){
   
    auto r = A.first, c = A.second;
    labirinto[r][c] = '.';

    while (r != B.first || c !=B.second)
    {
        if(r < B.first) r++;
        else if(r > B.first) r--;

        if (c < B.second) c++;
        else if (c > B.second) c--;
        
        labirinto[r][c] = '.';
    }
    
   }

void inizializzaTutto(vector<vector<char>> &labirinto, stack<pair<int, int>> &percorso, queue<pair<int, int>> &bfs, vector<vector<bool>> &visitato, pair<int, int> &partenza, pair<int, int> &arrivo, pair<int,int> &Ain, pair<int,int> &Bin)
{
    for (int righe = 0; righe < ROW; righe++)
    {
        for (int colonne = 0; colonne < COL; colonne++)
        {
            labirinto[righe][colonne] = '#';
            visitato[righe][colonne] = false;
        }
    }

    while (!percorso.empty()) percorso.pop();
    while (!bfs.empty()) bfs.pop();
    
    int x = generaIndiceRandom(4);
    int y = generaIndiceRandom(ROW);
    int z = generaIndiceRandom(COL);

    partenza = generaCoordinatePartenza(x, y);
    arrivo = generaCoordinateArrivo(partenza.first, partenza.second, z);

    labirinto[partenza.first][partenza.second] = 'A';

    Ain = spostaInternoA(partenza);
    Bin = spostaInternoB(arrivo);

    labirinto[Ain.first][Ain.second] = '.';


    percorso.push(Ain);
    bfs.push(Ain);
    visitato[Ain.first][Ain.second] = true;
}

int main()
{
    srand(time(0) ^ getpid());

    vector<vector<char>> labirinto(ROW, vector<char>(COL, '#'));
    stack<pair<int, int>> percorso;
    queue<pair<int, int>> bfs;
    vector<vector<bool>> visitato(ROW, vector<bool>(COL, false));

    pair<int,int> partenza, arrivo, Ain, Bin;
    bool collegato = false;

    do {
        inizializzaTutto(labirinto, percorso, bfs, visitato, partenza, arrivo, Ain, Bin);
        generaLabirinto(percorso, labirinto);

        // Resetto la BFS prima di ogni verifica
        while (!bfs.empty()) bfs.pop();
        bfs.push(Ain);
    
        for (int i = 0; i < ROW; i++)
            for (int j = 0; j < COL; j++)
                visitato[i][j] = false;

        visitato[Ain.first][Ain.second] = true;
    
        collegato = true;  // non serve più verificare con BFS

cout << "\nLabirinto generato, forzo il percorso...\n";

// Trova un punto aperto per B (qualsiasi)
pair<int, int> puntoB = Ain;
int maxDistanza = 0;

for (int r = 0; r < ROW; r++) {
    for (int c = 0; c < COL; c++) {
        if (labirinto[r][c] == '.') {
            int distanza = abs(Ain.first - r) + abs(Ain.second - c);
            if (distanza > maxDistanza) {
                maxDistanza = distanza;
                puntoB = {r, c};
            }
        }
    }
}

// Scava un percorso diretto da A a B
forzaPercorso(Ain, puntoB, labirinto);

// Posiziona simboli finali
labirinto[partenza.first][partenza.second] = 'A';
labirinto[puntoB.first][puntoB.second] = 'B';
    
    } while (!collegato);
    

    generaBordi(labirinto, ROW, COL);

    stampaVettoreAnnidato(labirinto, ROW, COL);


    return 0;
}
