#include <iostream>
#include <random>
#include <time.h>
#include <conio.h>
#include <stdlib.h>

#define X_MAX 80
#define Y_MAX 23
#define ROOMS 8
#define ROOM_SIZE 7

#define WALL 0xB2
#define EMPTY 0xFF
#define PLAYER 0x02

using namespace std;

void move(unsigned char map[X_MAX][Y_MAX], int player[2])
{
    int player_x = player[0];
    int player_y = player[1];
    bool waiting = true;
    while(waiting)
    {
        if(getch() == 224)
        {
            switch(getch())
            {
                case 72: //Freccia su
                    if(map[player_x][player_y-1] == EMPTY)
                    {
                        map[player_x][player_y] = EMPTY;
                        map[player_x][player_y-1] = PLAYER;
                        player_y--;
                        waiting = false;
                    }
                    break;
                case 80: //Freccia giù
                    if(map[player_x][player_y+1] == EMPTY)
                    {
                        map[player_x][player_y] = EMPTY;
                        map[player_x][player_y+1] = PLAYER;
                        player_y++;
                        waiting = false;
                    }
                    break;
                case 75: //Freccia sinistra
                    if(map[player_x-1][player_y] == EMPTY)
                    {
                        map[player_x][player_y] = EMPTY;
                        map[player_x-1][player_y] = PLAYER;
                        player_x--;
                        waiting = false;
                    }
                    break;
                case 77: //Freccia destra
                    if(map[player_x+1][player_y] == EMPTY)
                    {
                        map[player_x][player_y] = EMPTY;
                        map[player_x+1][player_y] = PLAYER;
                        player_x++;
                        waiting = false;
                    }
                    break;
            }
        }
    }
    player[0] = player_x;
    player[1] = player_y;
}
//Aggiorna la console con la situazione corrente del gioco.
void draw(unsigned char map[X_MAX][Y_MAX])
{
    system("cls");
    for(int y=0; y<Y_MAX; y++)
    {
        for(int x=0; x<X_MAX; x++)
        {
            cout << map[x][y];
        }
    }
}

//Funzioni per la generazione della mappa
//Inizializza la mappa con spazi vuoti
void init(unsigned char map[X_MAX][Y_MAX])
{
    for(int y=0; y<Y_MAX; y++)
    {
        for(int x=0; x<X_MAX; x++)
        {
            map[x][y] = WALL;
        }
    }
}

//Crea una stanza quadrata
void room(unsigned char map[X_MAX][Y_MAX], int start_x, int start_y, int end_x, int end_y)
{
    for(int y=start_y; y<=end_y; y++)
    {
        for(int x=start_x; x<=end_x; x++)
        {
            map[x][y] = EMPTY;
        }
    }
}

//Crea un corridoio che connetta due punti
void corridor(unsigned char map[X_MAX][Y_MAX], int start_x, int start_y, int end_x, int end_y, bool verticale)
{
    if(verticale)
    {
        if(start_y > end_y)
        {
            for(int y=end_y; y<=start_y; y++)
            {
                map[start_x][y] = EMPTY;
            }
        }
        else
        {
            for(int y=start_y; y<=end_y; y++)
            {
                map[start_x][y] = EMPTY;
            }
        }
        if(start_x > end_x)
        {
            for(int x=end_x; x<=start_x; x++)
            {
                map[x][end_y] = EMPTY;
            }
        }
        else
        {
            for(int x=start_x; x<=end_x; x++)
            {
                map[x][end_y] = EMPTY;
            }
        }
    }
    else
    {
        if(start_x > end_x)
        {
            for(int x=end_x; x<=start_x; x++)
            {
                map[x][start_y] = EMPTY;
            }
        }
        else
        {
            for(int x=start_x; x<=end_x; x++)
            {
                map[x][start_y] = EMPTY;
            }
        }
        if(start_y > end_y)
        {
            for(int y=end_y; y<=start_y; y++)
            {
                map[end_x][y] = EMPTY;
            }
        }
        else
        {
            for(int y=start_y; y<=end_y; y++)
            {
                map[end_x][y] = EMPTY;
            }
        }
    }
}

void generate(unsigned char map[X_MAX][Y_MAX])
{
    int corridor_x;
    int corridor_y;
    for(int r=0; r<ROOMS; r++)
    {
        int size_x = rand() % ROOM_SIZE + 1;
        int size_y = rand() % ROOM_SIZE + 1;
        int start_x = rand() % (X_MAX - size_x - 2) + 1;
        int start_y = rand() % (Y_MAX - size_y - 2) + 1;
        room(map, start_x, start_y, start_x + size_x, start_y + size_y);
        if(r > 0)
        {
            int link_x = rand() % size_x + 1 + start_x;
            int link_y = rand() % size_y + 1 + start_y;
            corridor(map, link_x, link_y, corridor_x, corridor_y, rand() % 2);
        }
        corridor_x = rand() % size_x + start_x;
        corridor_y = rand() % size_y + start_y;
    }
}

int main()
{
    unsigned char map[X_MAX][Y_MAX]; //Mappa del gioco
    int player[2] = {1, 8}; //Mettiamo il giocatore da qualche parte, in attesa dell'algoritmo...
    map[1][8] = PLAYER;
    srand(0); //TODO: Rendere il seed modificabile...?
    init(map);
    generate(map);
    draw(map);
    while(true)
    {
        move(map, player);
        draw(map);
    }
    return 0;
}
