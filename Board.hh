#include <SFML/Graphics.hpp>
#include <iostream>
#include "Where.hh"
#include "Line.hh"
#include "Piece.hh"
using namespace sf;
using namespace std;

class Board{
public:
    Board(string texture_file);
    Board(string texture_file, Vector2f desired_size); //OJO QUE SI CAMBIA TAMAÑO TABLERO TAMBIEN TENGO QUE HACER RESIZE DE TAMAÑO CASILLA

    //place a nought or a cross.
    //Return value: The first component of the pair returned is true if the game has ended (false otherways) and the second component is true if there is any winner (false otherways).
    pair<bool, bool> Place_X_or_O(Vector2f click, vector<Piece>& crosses, vector<Piece>& noughts, int& positionCross, int& positionNought, bool& Noughts_turn, Line& line);

    //funcion for the modality tictactoe-extreme (a personal modality). It places an X or an O randomly.
    //Return value: The first component of the pair returned is true if the game has ended (false otherways) and the second component is 0 if there is no winner, 1 if crosses win, 2 if noughts win
    pair<bool, int> Place_X_or_O_extreme(Vector2f click, vector<Piece>& crosses, vector<Piece>& noughts, int& positionCross, int& positionNought, bool& Noughts_turn, Line& line, RenderWindow& window);

    void ResizeBoard(Vector2f desired_size); //OJO QUE SI CAMBIA TAMAÑO TABLERO TAMBIEN TENGO QUE HACER RESIZE DE TAMAÑO CASILLA

    void ResetBoard(); //vuelve a considerar el tablero como un tablero sin fichas

    void Draw(RenderWindow& window);

    static bool RandomBool();

private:
    int WhichRow(float clickY);
    int WhichColumn(float clickX);
    static Vector2f GetScale(Vector2f desired_size, Vector2u texture_size);
    void PositionLine(Where where, Line& linea); 

private:
    Vector2u board_size;
    Vector2f box_size; //el tamaño de una casilla del tablero
    vector< vector<bool> > tablero;  
    vector<int> filas_cruz, columnas_cruz, filas_circulo, columnas_circulo; //cada posicion representa una fila o columna. Si en algun caso el contador llega a 3 es que hay victoria de esa ficha. PERFECTAS PARA CLASE TABLERO
    int diagonal1_circulo, diagonal2_circulo, diagonal1_cruz, diagonal2_cruz; //cantidad de fichas de cada equipo en cada diagonal
    Texture textura_fondo;
    Sprite background;
    int contador_fichas;
};
