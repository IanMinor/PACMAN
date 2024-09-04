#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <GL/glut.h>
#include "RgbImage.h"

#define NTexturas 6
GLuint Texturas[NTexturas];
char* filename1 = "pacman.bmp";
int LugarTextura1 = 0;
char* filename2 = "red.bmp";
int LugarTextura2 = 1;
char* filename3 = "blue.bmp";
int LugarTextura3 = 2;
char* filename4 = "orange.bmp";
int LugarTextura4 = 3;
char* filename5 = "pink.bmp";
int LugarTextura5 = 4;
char* filename6 = "mapa.bmp";
int LugarTextura6 = 5;

int CuadradoTam = 5; // Tamaño del cuadrado amarillo y rojo (Pacman y Fantasma)
const int MapaControl = 75; // 15 casillas de 5x5 pixeles
int ControlMatriz[MapaControl][MapaControl];

// Variables de Fantasma RED
int FVelMovim = 1; // Velocidad de movimiento
int FCordsXY[] = {35, 35}; // Casilla de inicio [7][7]
int dir; // valor de direccion
// valores iniciales de casos de fantasma
bool fcase1 = false;
bool fcase2 = false;
bool fcase3 = false;
bool fcase4 = false;
bool fcase5 = false;
bool fcase6 = false;
bool fcase7 = false;
bool fcase8 = false;
bool fcase9 = false;
bool fcase12 = false;

// Variables de Fantasma BLUE
int BVelMovim = 1; // Velocidad de movimiento
int BCordsXY[] = {35, 35}; // Casilla de inicio [7][7]
int Bdir; // valor de direccion
// valores iniciales de casos de fantasma
bool Bcase1 = false;
bool Bcase2 = false;
bool Bcase3 = false;
bool Bcase4 = false;
bool Bcase5 = false;
bool Bcase6 = false;
bool Bcase7 = false;
bool Bcase8 = false;
bool Bcase9 = false;
bool Bcase12 = false;

// Variables de Fantasma ORANGE
int OVelMovim = 1; // Velocidad de movimiento
int OCordsXY[] = {35, 35}; // Casilla de inicio [7][7]
int Odir; // valor de direccion
// valores iniciales de casos de fantasma
bool Ocase1 = false;
bool Ocase2 = false;
bool Ocase3 = false;
bool Ocase4 = false;
bool Ocase5 = false;
bool Ocase6 = false;
bool Ocase7 = false;
bool Ocase8 = false;
bool Ocase9 = false;
bool Ocase12 = false;

// Variables de Fantasma PINK
int PIVelMovim = 1; // Velocidad de movimiento
int PICordsXY[] = {35, 35}; // Casilla de inicio [7][7]
int PIdir; // valor de direccion
// valores iniciales de casos de fantasma
bool PIcase1 = false;
bool PIcase2 = false;
bool PIcase3 = false;
bool PIcase4 = false;
bool PIcase5 = false;
bool PIcase6 = false;
bool PIcase7 = false;
bool PIcase8 = false;
bool PIcase9 = false;
bool PIcase12 = false;

// Variables de Pacman
float PVelMovimX = 0; // Velocidad de movimiento en el eje X
float PVelMovimY = 0; // Velocidad de movimiento en el eje y
int PCordsXY[] = {35, 55}; // Posición inicial
// valores iniciales de direcciones de pacman
bool permitirmov = true; // variable que impide que el jugador haga otro movimiento y define si se esta moviendo
bool up    = false;
bool down  = false;
bool left  = false;
bool right = false;
// valores iniciales de casos de pacman
bool pcase1 = false;
bool pcase2 = false;
bool pcase3 = false;
bool pcase4 = false;
bool pcase5 = false;
bool pcase6 = false;
bool pcase7 = false;
bool pcase8 = false;
bool pcase9 = false;

void loadTextureFromFile(char *filename, int LugarTextura) // Funcion generica de RgbImage
{
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);

    RgbImage theTexMap(filename);
    //generate an OpenGL texture ID for this texture
    glGenTextures(1, &Texturas[LugarTextura]);
    //bind to the new texture ID
    glBindTexture(GL_TEXTURE_2D, Texturas[LugarTextura]);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(), 0,
                 GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());
    theTexMap.Reset();
}

void init(void) // Definición de la matriz de proyeccion
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-37.5, 37.5,-37.5,37.5);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void iniciar_ControlMatriz()   // Inicializamos la matriz de control
{

    // Llenamos de -1 todo el mapa
    for(int i=0 ; i < MapaControl ; i++)
    {
        for(int j=0 ; j < MapaControl ; j++)
        {
            ControlMatriz[i][j] = -1;
        }
    }

    // Ciclo for que genera los contornos en 0's
    for(int k=0 ; k < MapaControl ; k++)
    {
        for(int l=0 ; l < MapaControl ; l++)
        {
            // Columnas
            ControlMatriz[     0     ][l] = 0;
            ControlMatriz[MapaControl][l] = 0;
            // Filas
            ControlMatriz[k][     0     ] = 0;
            ControlMatriz[k][MapaControl] = 0;
        }
    }

    // Se utiliza una razon de (Coordenada * 5) + 3 para definir el punto medio de cada casilla
    ControlMatriz[5][65]=1  ;
    ControlMatriz[20][65]=7 ;
    ControlMatriz[30][65]=4 ;
    ControlMatriz[35][65]=0  ;
    ControlMatriz[40][65]=1   ;
    ControlMatriz[50][65]=7 ;
    ControlMatriz[65][65]=4  ;
    ControlMatriz[10][60]=0 ;
    ControlMatriz[15][60]=0 ;
    ControlMatriz[25][60]=0 ;
    ControlMatriz[35][60]=0  ;
    ControlMatriz[45][60]=0  ;
    ControlMatriz[55][60]=0  ;
    ControlMatriz[60][60]=0  ;
    ControlMatriz[5][55]=8  ;
    ControlMatriz[15][55]=7 ;
    ControlMatriz[20][55]=5 ;
    ControlMatriz[30][55]=5  ;
    ControlMatriz[35][55]=7  ;
    ControlMatriz[40][55]=5  ;
    ControlMatriz[50][55]=5  ;
    ControlMatriz[55][55]=7 ;
    ControlMatriz[65][55]=6  ;
    ControlMatriz[10][50]=0 ;
    ControlMatriz[20][50]=0 ;
    ControlMatriz[25][50]=0 ;
    ControlMatriz[30][50]=0  ;
    ControlMatriz[40][50]=0  ;
    ControlMatriz[45][50]=0  ;
    ControlMatriz[50][50]=0  ;
    ControlMatriz[60][50]=0 ;
    ControlMatriz[5][45]=2  ;
    ControlMatriz[15][45]=6 ;
    ControlMatriz[20][45]=0 ;
    ControlMatriz[25][45]=1  ;
    ControlMatriz[35][45]=5  ;
    ControlMatriz[45][45]=4  ;
    ControlMatriz[50][45]=0  ;
    ControlMatriz[55][45]=8 ;
    ControlMatriz[65][45]=3 ;
    ControlMatriz[5][40]=0  ;
    ControlMatriz[10][40]=0 ;
    ControlMatriz[20][40]=0 ;
    ControlMatriz[30][40]=0  ;
    ControlMatriz[35][40]=12 ;
    ControlMatriz[40][40]=0  ;
    ControlMatriz[50][40]=0  ;
    ControlMatriz[60][40]=0 ;
    ControlMatriz[65][40]=0 ;
    ControlMatriz[0][35]=10 ;
    ControlMatriz[15][35]=9 ;
    ControlMatriz[25][35]=6 ;
    ControlMatriz[30][35]=0  ;
    ControlMatriz[35][35]=12 ;
    ControlMatriz[40][35]=0  ;
    ControlMatriz[45][35]=8  ;
    ControlMatriz[55][35]=9 ;
    ControlMatriz[70][35]=11 ;
    ControlMatriz[5][30]=0  ;
    ControlMatriz[10][30]=0 ;
    ControlMatriz[20][30]=0 ;
    ControlMatriz[30][30]=0  ;
    ControlMatriz[35][30]=0  ;
    ControlMatriz[40][30]=0  ;
    ControlMatriz[50][30]=0  ;
    ControlMatriz[60][30]=0 ;
    ControlMatriz[65][30]=0 ;
    ControlMatriz[5][25]=1  ;
    ControlMatriz[15][25]=6 ;
    ControlMatriz[20][25]=0 ;
    ControlMatriz[25][25]=2  ;
    ControlMatriz[30][25]=7  ;
    ControlMatriz[40][25]=7  ;
    ControlMatriz[45][25]=3  ;
    ControlMatriz[50][25]=0 ;
    ControlMatriz[55][25]=8 ;
    ControlMatriz[65][25]=4 ;
    ControlMatriz[10][20]=0 ;
    ControlMatriz[20][20]=0 ;
    ControlMatriz[25][20]=0 ;
    ControlMatriz[35][20]=0  ;
    ControlMatriz[45][20]=0  ;
    ControlMatriz[50][20]=0  ;
    ControlMatriz[60][20]=0  ;
    ControlMatriz[10][15]=0 ;
    ControlMatriz[15][15]=8 ;
    ControlMatriz[30][15]=6 ;
    ControlMatriz[35][15]=0  ;
    ControlMatriz[40][15]=8  ;
    ControlMatriz[55][15]=6  ;
    ControlMatriz[60][15]=0  ;
    ControlMatriz[10][10]=0 ;
    ControlMatriz[20][10]=0 ;
    ControlMatriz[25][10]=0 ;
    ControlMatriz[30][10]=8  ;
    ControlMatriz[40][10]=6  ;
    ControlMatriz[45][10]=0  ;
    ControlMatriz[50][10]=0  ;
    ControlMatriz[60][10]=0 ;
    ControlMatriz[5][5]=2   ;
    ControlMatriz[15][5] =5 ;
    ControlMatriz[30][5] =3 ;
    ControlMatriz[35][5] =0  ;
    ControlMatriz[40][5] =2  ;
    ControlMatriz[55][5] =5  ;
    ControlMatriz[65][5] =3  ;

    //Wall ; -1 = Forward ; 1 = RD ; 2 = RU ; 3 = LU ; 4 = LD ; 5 = LRU ; 6 = LUD ; 7 = LRD ; 8 = RUD ; 9 = LRUD ; 10-11 = Portals ; 12 = Fantasmas ; 13 = Pacman
}

void dibujarMapa() // Dibuja el mapa de Pac-Man
{
    glBindTexture(GL_TEXTURE_2D, Texturas[LugarTextura6]);
    glBegin(GL_QUADS);

    glTexCoord2i(0, 0);
    glVertex3i(0, 0, 0);
    glTexCoord2i(1, 0);
    glVertex3i(MapaControl, 0, 0);
    glTexCoord2i(1, 1);
    glVertex3i(MapaControl, MapaControl, 0);
    glTexCoord2i(0, 1);
    glVertex3i(0, MapaControl, 0);

    glEnd();
}

void dibujarPacman() // Dibuja al Pac-Man
{
    glBindTexture(GL_TEXTURE_2D, Texturas[LugarTextura1]);

    glBegin(GL_QUADS);
    glTexCoord2i(0, 0);
    glVertex3i(PCordsXY[0], PCordsXY[1], 0);
    glTexCoord2i(1, 0);
    glVertex3i(PCordsXY[0] + CuadradoTam, PCordsXY[1], 0);
    glTexCoord2i(1, 1);
    glVertex3i(PCordsXY[0] + CuadradoTam, PCordsXY[1] + CuadradoTam, 0);
    glTexCoord2i(0, 1);
    glVertex3i(PCordsXY[0], PCordsXY[1] + CuadradoTam, 0);

    glEnd();
}

void idlePacman(int) // Funcion de movimiento del pac-man
{
    glutPostRedisplay();
    glutTimerFunc(1000/10, idlePacman, 0); //10 frames per second

    // Reinicia los booleanos de los casos a false. Esto impide sobreposiciones de casos
    if(ControlMatriz[PCordsXY[0]][PCordsXY[1]] == 1 || ControlMatriz[PCordsXY[0]][PCordsXY[1]] == 2 || ControlMatriz[PCordsXY[0]][PCordsXY[1]] == 3
            || ControlMatriz[PCordsXY[0]][PCordsXY[1]] == 4 || ControlMatriz[PCordsXY[0]][PCordsXY[1]] == 5 || ControlMatriz[PCordsXY[0]][PCordsXY[1]] == 6
            || ControlMatriz[PCordsXY[0]][PCordsXY[1]] == 7 || ControlMatriz[PCordsXY[0]][PCordsXY[1]] == 8 || ControlMatriz[PCordsXY[0]][PCordsXY[1]] == 9)
    {
        pcase1 = false;
        pcase2 = false;
        pcase3 = false;
        pcase4 = false;
        pcase5 = false;
        pcase6 = false;
        pcase7 = false;
        pcase8 = false;
        pcase9 = false;
    }

    if(ControlMatriz[PCordsXY[0]][PCordsXY[1]] != 0 && permitirmov)
    {
        permitirmov = true; //El movimiento se define como permitido
        switch (ControlMatriz[PCordsXY[0]][PCordsXY[1]])
        {
        case 1:
            if (right == true)
            {
                PCordsXY[0] += PVelMovimX; // Sumara la velocidad de movimiento inyectada por la funcion keyboard
                PCordsXY[1] += PVelMovimY; // Sumara 1 o 0
            }
            else if (down == true)
            {
                PCordsXY[0] += PVelMovimX;
                PCordsXY[1] += PVelMovimY;
            }
            else
            {
                printf("PACMAN ESTATICO \n");
            }
            pcase1 = true;
            break;

        case 2:
            if (right == true)
            {
                PCordsXY[0] += PVelMovimX;
                PCordsXY[1] += PVelMovimY;
            }
            else if(up == true)
            {
                PCordsXY[0] += PVelMovimX;
                PCordsXY[1] += PVelMovimY;
            }
            else
            {
                printf("PACMAN ESTATICO \n");
            }
            pcase2 = true;
            break;

        case 3:
            if (left == true)
            {
                PCordsXY[0] += PVelMovimX;
                PCordsXY[1] += PVelMovimY;
            }
            else if(up == true)
            {
                PCordsXY[0] += PVelMovimX;
                PCordsXY[1] += PVelMovimY;
            }
            else
            {
                printf("PACMAN ESTATICO \n");
            }
            pcase3 = true;
            break;

        case 4:
            if (left == true)
            {
                PCordsXY[0] += PVelMovimX;
                PCordsXY[1] += PVelMovimY;
            }
            else if(down == true)
            {
                PCordsXY[0] += PVelMovimX;
                PCordsXY[1] += PVelMovimY;
            }
            else
            {
                printf("PACMAN ESTATICO \n");
            }
            pcase4 = true;
            break;

        case 5:
            if (up == true)
            {
                PCordsXY[0] += PVelMovimX;
                PCordsXY[1] += PVelMovimY;
            }
            else if(right == true)
            {
                PCordsXY[0] += PVelMovimX;
                PCordsXY[1] += PVelMovimY;
            }
            else if(left == true)
            {
                PCordsXY[0] += PVelMovimX;
                PCordsXY[1] += PVelMovimY;
            }
            else
            {
                printf("PACMAN ESTATICO \n");
            }
            pcase5 = true;
            break;

        case 6:
            if (up == true)
            {
                PCordsXY[0] += PVelMovimX;
                PCordsXY[1] += PVelMovimY;
            }
            else if(down == true)
            {
                PCordsXY[0] += PVelMovimX;
                PCordsXY[1] += PVelMovimY;
            }
            else if(left == true)
            {
                PCordsXY[0] += PVelMovimX;
                PCordsXY[1] += PVelMovimY;
            }
            else
            {
                printf("PACMAN ESTATICO \n");
            }
            pcase6 = true;
            break;

        case 7:
            if (right == true)
            {
                PCordsXY[0] += PVelMovimX;
                PCordsXY[1] += PVelMovimY;
            }
            else if(left == true)
            {
                PCordsXY[0] += PVelMovimX;
                PCordsXY[1] += PVelMovimY;
            }
            else if(down == true)
            {
                PCordsXY[0] += PVelMovimX;
                PCordsXY[1] += PVelMovimY;
            }
            else
            {
                printf("PACMAN ESTATICO \n");
            }
            pcase7 = true;
            break;

        case 8:
            if (right == true)
            {
                PCordsXY[0] += PVelMovimX;
                PCordsXY[1] += PVelMovimY;
            }
            else if (down == true)
            {
                PCordsXY[0] += PVelMovimX;
                PCordsXY[1] += PVelMovimY;
            }
            else if(up == true)
            {
                PCordsXY[0] += PVelMovimX;
                PCordsXY[1] += PVelMovimY;
            }
            else
            {
                printf("PACMAN ESTATICO \n");
            }
            pcase8 = true;
            break;

        case 9:
            if (left == true)
            {
                PCordsXY[0] += PVelMovimX;
                PCordsXY[1] += PVelMovimY;
            }
            else if(right == true)
            {
                PCordsXY[0] += PVelMovimX;
                PCordsXY[1] += PVelMovimY;
            }
            else if(down == true)
            {
                PCordsXY[0] += PVelMovimX;
                PCordsXY[1] += PVelMovimY;
            }
            else if(up == true)
            {
                PCordsXY[0] += PVelMovimX;
                PCordsXY[1] += PVelMovimY;
            }
            else
            {
                printf("PACMAN ESTATICO \n");
            }
            pcase9 = true;
            break;

        case 10:
            // Teleportara al pacman a las coordenadas siguientes
            PCordsXY[0] = 70;
            PCordsXY[1] = 35;
            PCordsXY[0] += PVelMovimX;
            break;

        case 11:
            // Teleportara al pacman a las coordenadas siguientes
            PCordsXY[0] = 0;
            PCordsXY[1] = 35;
            PCordsXY[0] -= PVelMovimX;
            break;

        default:
            if(pcase1 == true)
            {
                if(right == true)
                {
                    left = false ;
                    down = false;
                    up = false;
                    PCordsXY[0] += PVelMovimX;
                }
                else if(down == true)
                {
                    left = false ;
                    right = false;
                    up = false;
                    PCordsXY[1] += PVelMovimY; // restando -1
                }

            }
            else if(pcase2 == true)
            {
                if(right == true)
                {
                    left = false ;
                    down = false;
                    up = false;
                    PCordsXY[0] += PVelMovimX;
                }
                else if(up == true)
                {
                    left = false ;
                    down = false;
                    right = false;
                    PCordsXY[1] += PVelMovimY;
                }

            }
            else if(pcase3 == true)
            {
                if(left == true)
                {
                    right = false ;
                    down = false;
                    up = false;
                    PCordsXY[0] += PVelMovimX; // restando -1
                }
                else if(up == true)
                {
                    left = false ;
                    down = false;
                    right = false;
                    PCordsXY[1] += PVelMovimY;
                }

            }
            else if(pcase4 == true)
            {
                if(left == true)
                {
                    right = false ;
                    down = false;
                    up = false;
                    PCordsXY[0] += PVelMovimX; // restando -1
                }
                else if(down == true)
                {
                    left = false ;
                    right = false;
                    up = false;
                    PCordsXY[1] += PVelMovimY; // restando -1
                }
            }
            else if(pcase5 == true)
            {
                if(up == true)
                {
                    left = false ;
                    down = false;
                    right = false;
                    PCordsXY[1] += PVelMovimY;
                }
                else if(left == true)
                {
                    right = false ;
                    down = false ;
                    up = false;
                    PCordsXY[0] += PVelMovimX;  // restando -1
                }
                else if(right == true)
                {
                    left = false ;
                    down = false;
                    up = false;
                    PCordsXY[0] += PVelMovimX;
                }
            }
            else if(pcase6 == true)
            {
                if(up == true)
                {
                    right = false ;
                    left = false ;
                    down = false;
                    PCordsXY[1] += PVelMovimY;
                }
                else if(down == true)
                {
                    left = false ;
                    up = false;
                    right = false;
                    PCordsXY[1] += PVelMovimY;  // restando -1
                }
                else if(left == true)
                {
                    down = false ;
                    up = false;
                    right = false;
                    PCordsXY[0] += PVelMovimX;  // restando -1
                }
            }
            else if(pcase7 == true)
            {
                if(down == true)
                {
                    left = false ;
                    up = false;
                    right = false;
                    PCordsXY[1] += PVelMovimY;  // restando -1
                }
                else if(right == true)
                {
                    left = false ;
                    up = false;
                    down = false;
                    PCordsXY[0] += PVelMovimX;
                }
                else if(left == true)
                {
                    right = false ;
                    up = false;
                    down = false;
                    PCordsXY[0] += PVelMovimX;  // restando -1
                }
            }
            else if(pcase8 == true)
            {
                if(up == true)
                {
                    right = false ;
                    left = false;
                    down = false;
                    PCordsXY[1] += PVelMovimY;
                }
                else if(down == true)
                {
                    right = false ;
                    left = false;
                    up = false;
                    PCordsXY[1] += PVelMovimX;  // restando -1
                }
                else if(right == true)
                {
                    down = false ;
                    left = false;
                    up = false;
                    PCordsXY[0] += PVelMovimX;
                }
            }
            else if(pcase9 == true)
            {
                if(down == true)
                {
                    right = false ;
                    left = false;
                    up = false;
                    PCordsXY[1] += PVelMovimY;  // restando -1
                }
                else if(up == true)
                {
                    right = false ;
                    left = false;
                    down = false;
                    PCordsXY[1] += PVelMovimY;
                }
                else if(left == true || right == true)
                {
                    right = false ;
                    up = false;
                    down = false;
                    PCordsXY[0] += PVelMovimX;  // restando -1
                }
                else if(right == true)
                {
                    left = false ;
                    up = false;
                    down = false;
                    PCordsXY[0] += PVelMovimX;
                }
            }
        }
    }
    else
    {
        permitirmov = false;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    if (permitirmov == true)
    {
        switch(key)
        {
        case 'w':
        case 'W':
            up    = true;
            //down  = false;  //De esta forma, el pacman podra regresar
            left  = false;
            right = false;
            PVelMovimX = 0;
            PVelMovimY = 1;
            std::cout<<"Accionando tecla W..."<< "\n";
            break;

        case 's':
        case 'S':
            down = true;
            //up = false;  //De esta forma, el pacman podra regresar
            left = false;
            right = false;
            PVelMovimX = 0;
            PVelMovimY = -1;
            std::cout<<"Accionando tecla s..."<< "\n";
            break;

        case 'd':
        case 'D':
            right = true;
            up = false;
            down = false;
            //left = false;  //De esta forma, el pacman podra regresar
            PVelMovimX = 1;
            PVelMovimY = 0;
            std::cout<<"Accionando tecla D..."<< "\n";
            break;

        case 'a':
        case 'A':
            left = true;
            up = false;
            down = false;
            //right = false;  //De esta forma, el pacman podra regresar
            PVelMovimX = -1;
            PVelMovimY = 0;
            std::cout<<"Accionando tecla A..."<< "\n";
            break;

        case 27:    // codigo ASCII de ESCAPE
            exit(0);
            break;

        }
    }
    glutPostRedisplay();
}

void dibujarFantasma() // Dibuja al fantasma RED
{
    glBindTexture(GL_TEXTURE_2D, Texturas[LugarTextura2]);

    glBegin(GL_QUADS);
    glTexCoord2i(0, 0);
    glVertex3i(FCordsXY[0], FCordsXY[1], 0);
    glTexCoord2i(1, 0);
    glVertex3i(FCordsXY[0] + CuadradoTam, FCordsXY[1], 0);
    glTexCoord2i(1, 1);
    glVertex3i(FCordsXY[0] + CuadradoTam, FCordsXY[1] + CuadradoTam, 0);
    glTexCoord2i(0, 1);
    glVertex3i(FCordsXY[0], FCordsXY[1] + CuadradoTam, 0);
    glEnd();
}

void dibujarFantasmaB() // Dibuja al fantasma BLUE
{
    glBindTexture(GL_TEXTURE_2D, Texturas[LugarTextura3]);

    glBegin(GL_QUADS);
    glTexCoord2i(0, 0);
    glVertex3i(BCordsXY[0], BCordsXY[1], 0);
    glTexCoord2i(1, 0);
    glVertex3i(BCordsXY[0] + CuadradoTam, BCordsXY[1], 0);
    glTexCoord2i(1, 1);
    glVertex3i(BCordsXY[0] + CuadradoTam, BCordsXY[1] + CuadradoTam, 0);
    glTexCoord2i(0, 1);
    glVertex3i(BCordsXY[0], BCordsXY[1] + CuadradoTam, 0);
    glEnd();
}

void dibujarFantasmaO() // Dibuja al fantasma ORANGE
{
    glBindTexture(GL_TEXTURE_2D, Texturas[LugarTextura4]);

    glBegin(GL_QUADS);
    glTexCoord2i(0, 0);
    glVertex3i(OCordsXY[0], OCordsXY[1], 0);
    glTexCoord2i(1, 0);
    glVertex3i(OCordsXY[0] + CuadradoTam, OCordsXY[1], 0);
    glTexCoord2i(1, 1);
    glVertex3i(OCordsXY[0] + CuadradoTam, OCordsXY[1] + CuadradoTam, 0);
    glTexCoord2i(0, 1);
    glVertex3i(OCordsXY[0], OCordsXY[1] + CuadradoTam, 0);
    glEnd();
}

void dibujarFantasmaPI()  // Dibuja al fantasma PINK
{
    glBindTexture(GL_TEXTURE_2D, Texturas[LugarTextura5]);

    glBegin(GL_QUADS);
    glTexCoord2i(0, 0);
    glVertex3i(PICordsXY[0], PICordsXY[1], 0);
    glTexCoord2i(1, 0);
    glVertex3i(PICordsXY[0] + CuadradoTam, PICordsXY[1], 0);
    glTexCoord2i(1, 1);
    glVertex3i(PICordsXY[0] + CuadradoTam, PICordsXY[1] + CuadradoTam, 0);
    glTexCoord2i(0, 1);
    glVertex3i(PICordsXY[0], PICordsXY[1] + CuadradoTam, 0);
    glEnd();
}

void idleFantasma(int) // Fantasma RED
{
    glutPostRedisplay();
    glutTimerFunc(1000/15, idleFantasma, 0);

    std::srand(std::time(0));  // Semilla del randomizer

    // Resetea los casos ejecutados en false para evitar sobreposiciones de casos
    if(ControlMatriz[FCordsXY[0]][FCordsXY[1]] == 1 || ControlMatriz[FCordsXY[0]][FCordsXY[1]] == 2 || ControlMatriz[FCordsXY[0]][FCordsXY[1]] == 3
            || ControlMatriz[FCordsXY[0]][FCordsXY[1]] == 4 || ControlMatriz[FCordsXY[0]][FCordsXY[1]] == 5 || ControlMatriz[FCordsXY[0]][FCordsXY[1]] == 6
            || ControlMatriz[FCordsXY[0]][FCordsXY[1]] == 7 || ControlMatriz[FCordsXY[0]][FCordsXY[1]] == 8 || ControlMatriz[FCordsXY[0]][FCordsXY[1]] == 9
            || ControlMatriz[FCordsXY[0]][FCordsXY[1]] == 12)
    {
        fcase1 = false;
        fcase2 = false;
        fcase3 = false;
        fcase4 = false;
        fcase5 = false;
        fcase6 = false;
        fcase7 = false;
        fcase8 = false;
        fcase9 = false;
        fcase12 = false;

    }
    if(ControlMatriz[FCordsXY[0]][FCordsXY[1]] != 0)
    {
        switch (ControlMatriz[FCordsXY[0]][FCordsXY[1]])
        {
        case 1:
            dir = (std::rand() % 2) + 2; // Esto generará 2 o 3
            if (dir==2)
            {
                FCordsXY[0] += FVelMovim;
            }
            else
            {
                FCordsXY[1] -= FVelMovim;
            }
            fcase1 = true;
            break;

        case 2:
            dir = (std::rand() % 2) + 1; // Esto generará 1 o 2
            if (dir==2)
            {
                FCordsXY[0] += FVelMovim;
            }
            else
            {
                FCordsXY[1] += FVelMovim;
            }
            fcase2 = true;
            break;

        case 3:
            dir = (std::rand() % 2) + 1; // Esto generará 1 o 2
            if (dir==2)
            {
                dir = 4;
                FCordsXY[0] -= FVelMovim;
            }
            else
            {
                FCordsXY[1] += FVelMovim;
            }
            fcase3 = true;
            break;

        case 4:
            dir = (std::rand() % 2) + 3; // Esto generará 3 o 4
            if (dir==4)
            {
                FCordsXY[0] -= FVelMovim;
            }
            else
            {
                FCordsXY[1] -= FVelMovim;
            }
            fcase4 = true;
            break;

        case 5:
            dir = std::rand() % 3; // Esto generara 0, 1 y 2
            if (dir==0)
            {
                dir = 1;
                FCordsXY[1] += FVelMovim;
            }
            else if (dir==1)
            {
                dir = 2;
                FCordsXY[0] += FVelMovim;
            }
            else
            {
                dir = 4;
                FCordsXY[0] -= FVelMovim;
            }
            fcase5 = true;
            break;

        case 6:
            dir = std::rand() % 3; // Esto generara 0, 1 y 2
            if (dir==0)
            {
                dir = 1;
                FCordsXY[1] += FVelMovim;
            }
            else if (dir==1)
            {
                dir = 3;
                FCordsXY[1] -= FVelMovim;
            }
            else
            {
                dir = 4;
                FCordsXY[0] -= FVelMovim;
            }
            fcase6 = true;
            break;

        case 7:
            dir = (std::rand() % 3) + 2; // Esto generara 2, 3 o 4
            if (dir==2)
            {
                FCordsXY[0] += FVelMovim;
            }
            else if (dir==3)
            {
                FCordsXY[1] -= FVelMovim;
            }
            else
            {
                FCordsXY[0] -= FVelMovim;
            }
            fcase7 = true;
            break;

        case 8:
            dir = (std::rand() % 3) + 1; // Esto generara 1, 2 o 3
            if (dir==1)
            {
                FCordsXY[1] += FVelMovim;
            }
            else if (dir==2)
            {
                FCordsXY[0] += FVelMovim;
            }
            else
            {
                FCordsXY[1] -= FVelMovim;
            }
            fcase8 = true;
            break;

        case 9:
            dir = (std::rand() % 4) + 1; // Esto generara 1, 2, 3 o 4
            if (dir==1)
            {
                FCordsXY[1] += FVelMovim;
            }
            else if (dir==2)
            {
                FCordsXY[0] += FVelMovim;
            }
            else if (dir==3)
            {
                FCordsXY[1] -= FVelMovim;
            }
            else
            {
                FCordsXY[0] -= FVelMovim;
            }
            fcase9 = true;
            break;

        case 10:
            FCordsXY[0] = 70;
            FCordsXY[1] = 35;
            FCordsXY[0] -= FVelMovim;
            break;

        case 11:
            FCordsXY[0] = 0;
            FCordsXY[1] = 35;
            FCordsXY[0] += FVelMovim;
            break;

        case 12:
            FCordsXY[1] += FVelMovim;
            fcase12 = true;
            break;

        default:
            if(fcase1 == true)
            {
                if(dir==2)
                {
                    FCordsXY[0] += FVelMovim;
                }
                else
                {
                    FCordsXY[1] -= FVelMovim;
                }

            }
            else if(fcase2 == true)
            {
                if(dir==2)
                {
                    FCordsXY[0] += FVelMovim;
                }
                else
                {
                    FCordsXY[1] += FVelMovim;
                }

            }
            else if(fcase3 == true)
            {
                if(dir==4)
                {
                    FCordsXY[0] -= FVelMovim;
                }
                else if(dir==1)
                {
                    FCordsXY[1] += FVelMovim;
                }

            }
            else if(fcase4 == true)
            {
                if(dir==4)
                {
                    FCordsXY[0] -= FVelMovim;
                }
                else if(dir==3)
                {
                    FCordsXY[1] -= FVelMovim;
                }
            }
            else if(fcase5 == true)
            {
                if (dir==1)
                {
                    FCordsXY[1] += FVelMovim;
                }
                else if (dir==2)
                {
                    FCordsXY[0] += FVelMovim;
                }
                else if (dir==4)
                {
                    FCordsXY[0] -= FVelMovim;
                }
            }
            else if(fcase6 == true)
            {
                if (dir==1)
                {
                    FCordsXY[1] += FVelMovim;
                }
                else if (dir==3)
                {
                    FCordsXY[1] -= FVelMovim;
                }
                else if (dir==4)
                {
                    FCordsXY[0] -= FVelMovim;
                }
            }
            else if(fcase7 == true)
            {
                if (dir==2)
                {
                    FCordsXY[0] += FVelMovim;
                }
                else if (dir==3)
                {
                    FCordsXY[1] -= FVelMovim;
                }
                else if (dir==4)
                {
                    FCordsXY[0] -= FVelMovim;
                }
            }
            else if(fcase8 == true)
            {
                if (dir==1)
                {
                    FCordsXY[1] += FVelMovim;
                }
                else if (dir==2)
                {
                    FCordsXY[0] += FVelMovim;
                }
                else if (dir==3)
                {
                    FCordsXY[1] -= FVelMovim;
                }
            }
            else if(fcase9 == true)
            {
                if (dir==1)
                {
                    FCordsXY[1] += FVelMovim;
                }
                else if (dir==2)
                {
                    FCordsXY[0] += FVelMovim;
                }
                else if(dir==3)
                {
                    FCordsXY[1] -= FVelMovim;
                }
                else
                {
                    FCordsXY[0] -= FVelMovim;
                }
            }
            else if (fcase12 == true)
            {
                FCordsXY[1] += FVelMovim;
            }

        }
    }
}

void idleFantasmaB(int) // Fantasma BLUE
{
    glutPostRedisplay();
    glutTimerFunc(1000/12, idleFantasmaB, 0);

    std::srand(std::time(0));
    if(ControlMatriz[BCordsXY[0]][BCordsXY[1]] == 1 || ControlMatriz[BCordsXY[0]][BCordsXY[1]] == 2 || ControlMatriz[BCordsXY[0]][BCordsXY[1]] == 3
            || ControlMatriz[BCordsXY[0]][BCordsXY[1]] == 4 || ControlMatriz[BCordsXY[0]][BCordsXY[1]] == 5 || ControlMatriz[BCordsXY[0]][BCordsXY[1]] == 6
            || ControlMatriz[BCordsXY[0]][BCordsXY[1]] == 7 || ControlMatriz[BCordsXY[0]][BCordsXY[1]] == 8 || ControlMatriz[BCordsXY[0]][BCordsXY[1]] == 9
            || ControlMatriz[BCordsXY[0]][BCordsXY[1]] == 12)
    {
        Bcase1 = false;
        Bcase2 = false;
        Bcase3 = false;
        Bcase4 = false;
        Bcase5 = false;
        Bcase6 = false;
        Bcase7 = false;
        Bcase8 = false;
        Bcase9 = false;
        Bcase12 = false;
    }
    if(ControlMatriz[BCordsXY[0]][BCordsXY[1]] != 0)
    {
        switch (ControlMatriz[BCordsXY[0]][BCordsXY[1]])
        {
        case 1:
            Bdir = (std::rand() % 2) + 2; // Esto generará 2 o 3
            if (Bdir == 2)
            {
                BCordsXY[0] += BVelMovim;
            }
            else
            {
                BCordsXY[1] -= BVelMovim;
            }
            Bcase1 = true;
            break;

        case 2:
            Bdir = (std::rand() % 2) + 1; // Esto generará 1 o 2
            if (Bdir == 2)
            {
                BCordsXY[0] += BVelMovim;
            }
            else
            {
                BCordsXY[1] += BVelMovim;
            }
            Bcase2 = true;
            break;

        case 3:
            Bdir = (std::rand() % 2) + 1; // Esto generará 1 o 2
            if (Bdir == 2)
            {
                Bdir = 4;
                BCordsXY[0] -= BVelMovim;
            }
            else
            {
                BCordsXY[1] += BVelMovim;
            }
            Bcase3 = true;
            break;

        case 4:
            Bdir = (std::rand() % 2) + 3; // Esto generará 3 o 4
            if (Bdir == 4)
            {
                BCordsXY[0] -= BVelMovim;
            }
            else
            {
                BCordsXY[1] -= BVelMovim;
            }
            Bcase4 = true;
            break;

        case 5:
            Bdir = std::rand() % 3; // Esto generará 0, 1 y 2
            if (Bdir == 0)
            {
                Bdir = 1;
                BCordsXY[1] += BVelMovim;
            }
            else if (Bdir == 1)
            {
                Bdir = 2;
                BCordsXY[0] += BVelMovim;
            }
            else
            {
                Bdir = 4;
                BCordsXY[0] -= BVelMovim;
            }
            Bcase5 = true;
            break;

        case 6:
            Bdir = std::rand() % 3; // Esto generará 0, 1 y 2
            if (Bdir == 0)
            {
                Bdir = 1;
                BCordsXY[1] += BVelMovim;
            }
            else if (Bdir == 1)
            {
                Bdir = 3;
                BCordsXY[1] -= BVelMovim;
            }
            else
            {
                Bdir = 4;
                BCordsXY[0] -= BVelMovim;
            }
            Bcase6 = true;
            break;

        case 7:
            Bdir = (std::rand() % 3) + 2; // Esto generará 2, 3 o 4
            if (Bdir == 2)
            {
                BCordsXY[0] += BVelMovim;
            }
            else if (Bdir == 3)
            {
                BCordsXY[1] -= BVelMovim;
            }
            else
            {
                BCordsXY[0] -= BVelMovim;
            }
            Bcase7 = true;
            break;

        case 8:
            Bdir = (std::rand() % 3) + 1; // Esto generara 1, 2 o 3
            if (Bdir == 1)
            {
                BCordsXY[1] += BVelMovim;
            }
            else if (Bdir == 2)
            {
                BCordsXY[0] += BVelMovim;
            }
            else
            {
                BCordsXY[1] -= BVelMovim;
            }
            Bcase8 = true;
            break;

        case 9:
            Bdir = (std::rand() % 4) + 1; // Esto generara 1, 2, 3 o 4
            if (Bdir == 1)
            {
                BCordsXY[1] += BVelMovim;
            }
            else if (Bdir == 2)
            {
                BCordsXY[0] += BVelMovim;
            }
            else if (Bdir == 3)
            {
                BCordsXY[1] -= BVelMovim;
            }
            else
            {
                BCordsXY[0] -= BVelMovim;
            }
            Bcase9 = true;
            break;

        case 10:
            BCordsXY[0] = 70;
            BCordsXY[1] = 35;
            BCordsXY[0] -= BVelMovim;
            break;

        case 11:
            BCordsXY[0] = 0;
            BCordsXY[1] = 35;
            BCordsXY[0] += BVelMovim;
            break;

        case 12:
            BCordsXY[1] += BVelMovim;
            Bcase12 = true;
            break;

        default:
            if(Bcase1 == true)
            {
                if(Bdir == 2)
                {
                    BCordsXY[0] += BVelMovim;
                }
                else
                {
                    BCordsXY[1] -= BVelMovim;
                }

            }
            else if(Bcase2 == true)
            {
                if(Bdir == 2)
                {
                    BCordsXY[0] += BVelMovim;
                }
                else
                {
                    BCordsXY[1] += BVelMovim;
                }

            }
            else if(Bcase3 == true)
            {
                if(Bdir == 4)
                {
                    BCordsXY[0] -= BVelMovim;
                }
                else if(Bdir == 1)
                {
                    BCordsXY[1] += BVelMovim;
                }

            }
            else if(Bcase4 == true)
            {
                if(Bdir == 4)
                {
                    BCordsXY[0] -= BVelMovim;
                }
                else if(Bdir == 3)
                {
                    BCordsXY[1] -= BVelMovim;
                }
            }
            else if(Bcase5 == true)
            {
                if (Bdir == 1)
                {
                    BCordsXY[1] += BVelMovim;
                }
                else if (Bdir == 2)
                {
                    BCordsXY[0] += BVelMovim;
                }
                else if (Bdir == 4)
                {
                    BCordsXY[0] -= BVelMovim;
                }
            }
            else if(Bcase6 == true)
            {
                if (Bdir == 1)
                {
                    BCordsXY[1] += BVelMovim;
                }
                else if (Bdir == 3)
                {
                    BCordsXY[1] -= BVelMovim;
                }
                else if (Bdir == 4)
                {
                    BCordsXY[0] -= BVelMovim;
                }
            }
            else if(Bcase7 == true)
            {
                if (Bdir == 2)
                {
                    BCordsXY[0] += BVelMovim;
                }
                else if (Bdir == 3)
                {
                    BCordsXY[1] -= BVelMovim;
                }
                else if (Bdir == 4)
                {
                    BCordsXY[0] -= BVelMovim;
                }
            }
            else if(Bcase8 == true)
            {
                if (Bdir == 1)
                {
                    BCordsXY[1] += BVelMovim;
                }
                else if (Bdir == 2)
                {
                    BCordsXY[0] += BVelMovim;
                }
                else if (Bdir == 3)
                {
                    BCordsXY[1] -= BVelMovim;
                }
            }
            else if(Bcase9 == true)
            {
                if (Bdir == 1)
                {
                    BCordsXY[1] += BVelMovim;
                }
                else if (Bdir == 2)
                {
                    BCordsXY[0] += BVelMovim;
                }
                else if(Bdir == 3)
                {
                    BCordsXY[1] -= BVelMovim;
                }
                else
                {
                    BCordsXY[0] -= BVelMovim;
                }
            }
            else if (Bcase12 == true)
            {
                BCordsXY[1] += BVelMovim;
            }
        }
    }
}

void idleFantasmaO(int) // Fantasma ORANGE
{
    glutPostRedisplay();
    glutTimerFunc(1000/9, idleFantasmaO, 0);

    std::srand(std::time(0));
    if(ControlMatriz[OCordsXY[0]][OCordsXY[1]] == 1 || ControlMatriz[OCordsXY[0]][OCordsXY[1]] == 2 || ControlMatriz[OCordsXY[0]][OCordsXY[1]] == 3
            || ControlMatriz[OCordsXY[0]][OCordsXY[1]] == 4 || ControlMatriz[OCordsXY[0]][OCordsXY[1]] == 5 || ControlMatriz[OCordsXY[0]][OCordsXY[1]] == 6
            || ControlMatriz[OCordsXY[0]][OCordsXY[1]] == 7 || ControlMatriz[OCordsXY[0]][OCordsXY[1]] == 8 || ControlMatriz[OCordsXY[0]][OCordsXY[1]] == 9
            || ControlMatriz[OCordsXY[0]][OCordsXY[1]] == 12)
    {
        Ocase1 = false;
        Ocase2 = false;
        Ocase3 = false;
        Ocase4 = false;
        Ocase5 = false;
        Ocase6 = false;
        Ocase7 = false;
        Ocase8 = false;
        Ocase9 = false;
        Ocase12 = false;
    }
    if(ControlMatriz[OCordsXY[0]][OCordsXY[1]] != 0)
    {
        switch (ControlMatriz[OCordsXY[0]][OCordsXY[1]])
        {
        case 1:
            Odir = (std::rand() % 2) + 2; // Esto generará 2 o 3
            if (Odir == 2)
            {
                OCordsXY[0] += OVelMovim;
            }
            else
            {
                OCordsXY[1] -= OVelMovim;
            }
            Ocase1 = true;
            break;

        case 2:
            Odir = (std::rand() % 2) + 1; // Esto generará 1 o 2
            if (Odir == 2)
            {
                OCordsXY[0] += OVelMovim;
            }
            else
            {
                OCordsXY[1] += OVelMovim;
            }
            Ocase2 = true;
            break;

        case 3:
            Odir = (std::rand() % 2) + 1; // Esto generará 1 o 2
            if (Odir == 2)
            {
                Odir = 4;
                OCordsXY[0] -= OVelMovim;
            }
            else
            {
                OCordsXY[1] += OVelMovim;
            }
            Ocase3 = true;
            break;

        case 4:
            Odir = (std::rand() % 2) + 3; // Esto generará 3 o 4
            if (Odir == 4)
            {
                OCordsXY[0] -= OVelMovim;
            }
            else
            {
                OCordsXY[1] -= OVelMovim;
            }
            Ocase4 = true;
            break;

        case 5:
            Odir = std::rand() % 3; // Esto generara 0, 1 y 2
            if (Odir == 0)
            {
                Odir = 1;
                OCordsXY[1] += OVelMovim;
            }
            else if (Odir == 1)
            {
                Odir = 2;
                OCordsXY[0] += OVelMovim;
            }
            else
            {
                Odir = 4;
                OCordsXY[0] -= OVelMovim;
            }
            Ocase5 = true;
            break;

        case 6:
            Odir = std::rand() % 3; // Esto generara 0, 1 y 2
            if (Odir == 0)
            {
                Odir = 1;
                OCordsXY[1] += OVelMovim;
            }
            else if (Odir == 1)
            {
                Odir = 3;
                OCordsXY[1] -= OVelMovim;
            }
            else
            {
                Odir = 4;
                OCordsXY[0] -= OVelMovim;
            }
            Ocase6 = true;
            break;

        case 7:
            Odir = (std::rand() % 3) + 2; // Esto generara 2, 3 o 4
            if (Odir == 2)
            {
                OCordsXY[0] += OVelMovim;
            }
            else if (Odir == 3)
            {
                OCordsXY[1] -= OVelMovim;
            }
            else
            {
                OCordsXY[0] -= OVelMovim;
            }
            Ocase7 = true;
            break;

        case 8:
            Odir = (std::rand() % 3) + 1; // Esto generara 1, 2 o 3
            if (Odir == 1)
            {
                OCordsXY[1] += OVelMovim;
            }
            else if (Odir == 2)
            {
                OCordsXY[0] += OVelMovim;
            }
            else
            {
                OCordsXY[1] -= OVelMovim;
            }
            Ocase8 = true;
            break;

        case 9:
            Odir = (std::rand() % 4) + 1; // Esto generara 1, 2, 3 o 4
            if (Odir == 1)
            {
                OCordsXY[1] += OVelMovim;
            }
            else if (Odir == 2)
            {
                OCordsXY[0] += OVelMovim;
            }
            else if (Odir == 3)
            {
                OCordsXY[1] -= OVelMovim;
            }
            else
            {
                OCordsXY[0] -= OVelMovim;
            }
            Ocase9 = true;
            break;

        case 10:
            OCordsXY[0] = 70;
            OCordsXY[1] = 35;
            OCordsXY[0] -= OVelMovim;
            break;

        case 11:
            OCordsXY[0] = 0;
            OCordsXY[1] = 35;
            OCordsXY[0] += OVelMovim;
            break;

        case 12:
            OCordsXY[1] += OVelMovim;
            Ocase12 = true;
            break;

        default:
            if(Ocase1 == true)
            {
                if(Odir == 2)
                {
                    OCordsXY[0] += OVelMovim;
                }
                else
                {
                    OCordsXY[1] -= OVelMovim;
                }
            }
            else if(Ocase2 == true)
            {
                if(Odir == 2)
                {
                    OCordsXY[0] += OVelMovim;
                }
                else
                {
                    OCordsXY[1] += OVelMovim;
                }
            }
            else if(Ocase3 == true)
            {
                if(Odir == 4)
                {
                    OCordsXY[0] -= OVelMovim;
                }
                else if(Odir == 1)
                {
                    OCordsXY[1] += OVelMovim;
                }
            }
            else if(Ocase4 == true)
            {
                if(Odir == 4)
                {
                    OCordsXY[0] -= OVelMovim;
                }
                else if(Odir == 3)
                {
                    OCordsXY[1] -= OVelMovim;
                }
            }
            else if(Ocase5 == true)
            {
                if (Odir == 1)
                {
                    OCordsXY[1] += OVelMovim;
                }
                else if (Odir == 2)
                {
                    OCordsXY[0] += OVelMovim;
                }
                else if (Odir == 4)
                {
                    OCordsXY[0] -= OVelMovim;
                }
            }
            else if(Ocase6 == true)
            {
                if (Odir == 1)
                {
                    OCordsXY[1] += OVelMovim;
                }
                else if (Odir == 3)
                {
                    OCordsXY[1] -= OVelMovim;
                }
                else if (Odir == 4)
                {
                    OCordsXY[0] -= OVelMovim;
                }
            }
            else if(Ocase7 == true)
            {
                if (Odir == 2)
                {
                    OCordsXY[0] += OVelMovim;
                }
                else if (Odir == 3)
                {
                    OCordsXY[1] -= OVelMovim;
                }
                else if (Odir == 4)
                {
                    OCordsXY[0] -= OVelMovim;
                }
            }
            else if(Ocase8 == true)
            {
                if (Odir == 1)
                {
                    OCordsXY[1] += OVelMovim;
                }
                else if (Odir == 2)
                {
                    OCordsXY[0] += OVelMovim;
                }
                else if (Odir == 3)
                {
                    OCordsXY[1] -= OVelMovim;
                }
            }
            else if(Ocase9 == true)
            {
                if (Odir == 1)
                {
                    OCordsXY[1] += OVelMovim;
                }
                else if (Odir == 2)
                {
                    OCordsXY[0] += OVelMovim;
                }
                else if(Odir == 3)
                {
                    OCordsXY[1] -= OVelMovim;
                }
                else
                {
                    OCordsXY[0] -= OVelMovim;
                }
            }
            else if (Ocase12 == true)
            {
                OCordsXY[1] += OVelMovim;
            }
        }
    }
}

void idleFantasmaPI(int) // Fantasma PINK
{
    glutPostRedisplay();
    glutTimerFunc(1000/6, idleFantasmaPI, 0);

    std::srand(std::time(0));
    if(ControlMatriz[PICordsXY[0]][PICordsXY[1]] == 1 || ControlMatriz[PICordsXY[0]][PICordsXY[1]] == 2 || ControlMatriz[PICordsXY[0]][PICordsXY[1]] == 3
            || ControlMatriz[PICordsXY[0]][PICordsXY[1]] == 4 || ControlMatriz[PICordsXY[0]][PICordsXY[1]] == 5 || ControlMatriz[PICordsXY[0]][PICordsXY[1]] == 6
            || ControlMatriz[PICordsXY[0]][PICordsXY[1]] == 7 || ControlMatriz[PICordsXY[0]][PICordsXY[1]] == 8 || ControlMatriz[PICordsXY[0]][PICordsXY[1]] == 9
            || ControlMatriz[PICordsXY[0]][PICordsXY[1]] == 12)
    {
        PIcase1 = false;
        PIcase2 = false;
        PIcase3 = false;
        PIcase4 = false;
        PIcase5 = false;
        PIcase6 = false;
        PIcase7 = false;
        PIcase8 = false;
        PIcase9 = false;
        PIcase12 = false;
    }
    if(ControlMatriz[PICordsXY[0]][PICordsXY[1]] != 0)
    {
        switch (ControlMatriz[PICordsXY[0]][PICordsXY[1]])
        {
        case 1:
            PIdir = (std::rand() % 2) + 2; // Esto generará 2 o 3
            if (PIdir == 2)
            {
                PICordsXY[0] += PIVelMovim;
            }
            else
            {
                PICordsXY[1] -= PIVelMovim;
            }
            PIcase1 = true;
            break;

        case 2:
            PIdir = (std::rand() % 2) + 1; // Esto generará 1 o 2
            if (PIdir == 2)
            {
                PICordsXY[0] += PIVelMovim;
            }
            else
            {
                PICordsXY[1] += PIVelMovim;
            }
            PIcase2 = true;
            break;

        case 3:
            PIdir = (std::rand() % 2) + 1; // Esto generará 1 o 2
            if (PIdir == 2)
            {
                PIdir = 4;
                PICordsXY[0] -= PIVelMovim;
            }
            else
            {
                PICordsXY[1] += PIVelMovim;
            }
            PIcase3 = true;
            break;

        case 4:
            PIdir = (std::rand() % 2) + 3; // Esto generará 3 o 4
            if (PIdir == 4)
            {
                PICordsXY[0] -= PIVelMovim;
            }
            else
            {
                PICordsXY[1] -= PIVelMovim;
            }
            PIcase4 = true;
            break;

        case 5:
            PIdir = std::rand() % 3; // Esto generara 0, 1 y 2
            if (PIdir == 0)
            {
                PIdir = 1;
                PICordsXY[1] += PIVelMovim;
            }
            else if (PIdir == 1)
            {
                PIdir = 2;
                PICordsXY[0] += PIVelMovim;
            }
            else
            {
                PIdir = 4;
                PICordsXY[0] -= PIVelMovim;
            }
            PIcase5 = true;
            break;

        case 6:
            PIdir = std::rand() % 3; // Esto generara 0, 1 y 2
            if (PIdir == 0)
            {
                PIdir = 1;
                PICordsXY[1] += PIVelMovim;
            }
            else if (PIdir == 1)
            {
                PIdir = 3;
                PICordsXY[1] -= PIVelMovim;
            }
            else
            {
                PIdir = 4;
                PICordsXY[0] -= PIVelMovim;
            }
            PIcase6 = true;
            break;

        case 7:
            PIdir = (std::rand() % 3) + 2; // Esto generara 2, 3 o 4
            if (PIdir == 2)
            {
                PICordsXY[0] += PIVelMovim;
            }
            else if (PIdir == 3)
            {
                PICordsXY[1] -= PIVelMovim;
            }
            else
            {
                PICordsXY[0] -= PIVelMovim;
            }
            PIcase7 = true;
            break;

        case 8:
            PIdir = (std::rand() % 3) + 1; // Esto generara 1, 2 o 3
            if (PIdir == 1)
            {
                PICordsXY[1] += PIVelMovim;
            }
            else if (PIdir == 2)
            {
                PICordsXY[0] += PIVelMovim;
            }
            else
            {
                PICordsXY[1] -= PIVelMovim;
            }
            PIcase8 = true;
            break;

        case 9:
            PIdir = (std::rand() % 4) + 1; // Esto generara 1, 2, 3 o 4
            if (PIdir == 1)
            {
                PICordsXY[1] += PIVelMovim;
            }
            else if (PIdir == 2)
            {
                PICordsXY[0] += PIVelMovim;
            }
            else if (PIdir == 3)
            {
                PICordsXY[1] -= PIVelMovim;
            }
            else
            {
                PICordsXY[0] -= PIVelMovim;
            }
            PIcase9 = true;
            break;

        case 10:
            PICordsXY[0] = 70;
            PICordsXY[1] = 35;
            PICordsXY[0] -= PIVelMovim;
            break;

        case 11:
            PICordsXY[0] = 0;
            PICordsXY[1] = 35;
            PICordsXY[0] += PIVelMovim;
            break;

        case 12:
            PICordsXY[1] += PIVelMovim;
            PIcase12 = true;
            break;

        default:
            if(PIcase1 == true)
            {
                if(PIdir == 2)
                {
                    PICordsXY[0] += PIVelMovim;
                }
                else
                {
                    PICordsXY[1] -= PIVelMovim;
                }
            }
            else if(PIcase2 == true)
            {
                if(PIdir == 2)
                {
                    PICordsXY[0] += PIVelMovim;
                }
                else
                {
                    PICordsXY[1] += PIVelMovim;
                }
            }
            else if(PIcase3 == true)
            {
                if(PIdir == 4)
                {
                    PICordsXY[0] -= PIVelMovim;
                }
                else if(PIdir == 1)
                {
                    PICordsXY[1] += PIVelMovim;
                }
            }
            else if(PIcase4 == true)
            {
                if(PIdir == 4)
                {
                    PICordsXY[0] -= PIVelMovim;
                }
                else if(PIdir == 3)
                {
                    PICordsXY[1] -= PIVelMovim;
                }
            }
            else if(PIcase5 == true)
            {
                if (PIdir == 1)
                {
                    PICordsXY[1] += PIVelMovim;
                }
                else if (PIdir == 2)
                {
                    PICordsXY[0] += PIVelMovim;
                }
                else if (PIdir == 4)
                {
                    PICordsXY[0] -= PIVelMovim;
                }
            }
            else if(PIcase6 == true)
            {
                if (PIdir == 1)
                {
                    PICordsXY[1] += PIVelMovim;
                }
                else if (PIdir == 3)
                {
                    PICordsXY[1] -= PIVelMovim;
                }
                else if (PIdir == 4)
                {
                    PICordsXY[0] -= PIVelMovim;
                }
            }
            else if(PIcase7 == true)
            {
                if (PIdir == 2)
                {
                    PICordsXY[0] += PIVelMovim;
                }
                else if (PIdir == 3)
                {
                    PICordsXY[1] -= PIVelMovim;
                }
                else if (PIdir == 4)
                {
                    PICordsXY[0] -= PIVelMovim;
                }
            }
            else if(PIcase8 == true)
            {
                if (PIdir == 1)
                {
                    PICordsXY[1] += PIVelMovim;
                }
                else if (PIdir == 2)
                {
                    PICordsXY[0] += PIVelMovim;
                }
                else if (PIdir == 3)
                {
                    PICordsXY[1] -= PIVelMovim;
                }
            }
            else if(PIcase9 == true)
            {
                if (PIdir == 1)
                {
                    PICordsXY[1] += PIVelMovim;
                }
                else if (PIdir == 2)
                {
                    PICordsXY[0] += PIVelMovim;
                }
                else if(PIdir == 3)
                {
                    PICordsXY[1] -= PIVelMovim;
                }
                else
                {
                    PICordsXY[0] -= PIVelMovim;
                }
            }
            else if (PIcase12 == true)
            {
                PICordsXY[1] += PIVelMovim;
            }
        }
    }
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    dibujarPacman();
    dibujarFantasma();
    dibujarFantasmaB();
    dibujarFantasmaO();
    dibujarFantasmaPI();
    dibujarMapa();

    glFlush();
    glDisable(GL_TEXTURE_2D);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(750, 750);
    glutCreateWindow("PAC-MAN");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 75, 0.0, 75.0, -1.0, 1.0);

    std::cout<<"Iniciando programa..."<<"\n";
    iniciar_ControlMatriz(); // Inicializa la matriz de control

    loadTextureFromFile(filename1, LugarTextura1);
    loadTextureFromFile(filename2, LugarTextura2);
    loadTextureFromFile(filename3, LugarTextura3);
    loadTextureFromFile(filename4, LugarTextura4);
    loadTextureFromFile(filename5, LugarTextura5);
    loadTextureFromFile(filename6, LugarTextura6);
    glutDisplayFunc(display);
    glutTimerFunc(0, idlePacman, 0);
    glutTimerFunc(0, idleFantasma, 0);
    glutTimerFunc(0, idleFantasmaB, 0);
    glutTimerFunc(0, idleFantasmaO, 0);
    glutTimerFunc(0, idleFantasmaPI, 0);
    glutKeyboardFunc(keyboard);
    glutMainLoop();

    return 0;
}

