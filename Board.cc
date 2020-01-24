#include "Board.hh"

Board::Board(string texture_file){
    if (not textura_fondo.loadFromFile(texture_file)) cerr << "ERROR loading tictactoe background" << endl;
    background.setTexture(textura_fondo);
    board_size = textura_fondo.getSize();
    box_size = {board_size.x/3.0f, board_size.y/3.0f};
    ResetBoard();
    srand (time(NULL));
}

Board::Board(string texture_file, Vector2f desired_size){
    if (not textura_fondo.loadFromFile(texture_file)) cerr << "ERROR loading tictactoe background" << endl;
    background.setTexture(textura_fondo);
    ResizeBoard(desired_size);
    ResetBoard();
    srand (time(NULL));
}

//place a nought or a cross. The first component of the pair returned is true if the game has ended (false otherways) and the second component is true if there is any winner (false otherways).
pair<bool, bool> Board::Place_X_or_O(Vector2f click, vector<Piece>& crosses, vector<Piece>& noughts, int& positionCross, int& positionNought, bool& Noughts_turn, Line& line){
    int fila = WhichRow(click.y);
    int columna = WhichColumn(click.x);
    if (fila == -1 or columna == -1) return{false,false};

    bool partida_finalizada = false;
    bool hay_ganador = false;
    bool todo_correcto = true;
    if(tablero[fila][columna]) todo_correcto = false; 
    else if(Noughts_turn){ //jugador 2 (los circulos)
        noughts[positionNought].SetPosition(box_size.x * columna + box_size.x/2, box_size.y * fila + box_size.y/2);
        ++positionNought;
    }
    else{ //jugador 1 (las cruces) 
        crosses[positionCross].SetPosition(box_size.x * columna + box_size.x/2, box_size.y * fila + box_size.y/2);
        ++positionCross;
    }

    if(todo_correcto){
        if(Noughts_turn){ 
            if(++filas_circulo[fila] == 3 or ++columnas_circulo[columna] == 3){ partida_finalizada = true; PositionLine(Nothing,line); }
            if(not partida_finalizada and fila == columna) if(++diagonal1_circulo == 3){ partida_finalizada = true; PositionLine(Diagonal1,line); } //ficha puesta en diagonal1. El if not partida_finalizada es porque si ya he visto antes que esa ficha ya es ganadora, me da igual seguir sumando cosas
            if(not partida_finalizada and fila+columna == 2) if(++diagonal2_circulo == 3){ partida_finalizada = true; PositionLine(Diagonal2,line); } //ficha puesta en diagonal2. El if not partida_finalizada es porque si ya he visto antes que esa ficha ya es ganadora, me da igual seguir sumando cosas
        }
        else{ 
            if(++filas_cruz[fila] == 3 or ++columnas_cruz[columna] == 3){ partida_finalizada = true; PositionLine(Nothing,line); }
            if(not partida_finalizada and fila == columna) if(++diagonal1_cruz == 3){ partida_finalizada = true; PositionLine(Diagonal1,line); }//ficha puesta en diagonal1. El if not partida_finalizadaes porque si ya he visto antes que esa ficha ya es ganadora, me da igual seguir sumando cosas
            if(not partida_finalizada and fila+columna == 2) if(++diagonal2_cruz == 3){ partida_finalizada = true; PositionLine(Diagonal2,line); }//ficha puesta en diagonal2. El if not partida_finalizada es porque si ya he visto antes que esa ficha ya es ganadora, me da igual seguir sumando cosas

        }
        tablero[fila][columna] = true;
        hay_ganador = partida_finalizada; //si la partida finaliza antes de que sumemos en el contador de fichas es que ha habido ganador
        if(++contador_fichas == 9) partida_finalizada = true;
        Noughts_turn = not Noughts_turn;
    } 
    return {partida_finalizada, hay_ganador}; //SI UNA PARTIDA FINALIZA NO SABEMOS SI HAY GANADOR, PORQUE HA PODIDO ACABAR EN EMPATE. POR ESO RETORNO ESTE PAR
}

pair<bool, int> Board::Place_X_or_O_extreme(Vector2f click, vector<Piece>& crosses, vector<Piece>& noughts, int& positionCross, int& positionNought, bool& Noughts_turn, Line& line, RenderWindow& window){
    int fila = WhichRow(click.y);
    int columna = WhichColumn(click.x);
    if (fila == -1 or columna == -1) return{false,false};

    bool partida_finalizada = false;
    int ganador = 0;
    bool todo_correcto = true;

    bool colocamos_circulo = RandomBool();

    /*INICIALIZACIONES PARA LA PARTE DE ALTERNAR CRUZ Y CIRCULO*/
    Clock clock; //ES UNA CLASE DE SFML. Time es otra clase con funciones como asSeconds().

    float deelay = 0.1; //empezamos con un deelay de 0.1s
    int MAX_COUNTER;
    if(colocamos_circulo) MAX_COUNTER = 16;
    else  MAX_COUNTER = 17;

    Piece cruz_aux = crosses[positionCross]; //clase mia
    Piece circulo_aux = noughts[positionNought];
    Piece white_square;
    Vector2f white_square_size = Piece::GetBiggerSizeComparation(cruz_aux, circulo_aux);
    white_square.Initialice("white_square.png", white_square_size, true);
    white_square.SetPosition(box_size.x * columna + box_size.x/2, box_size.y * fila + box_size.y/2);
    cruz_aux.SetPosition(box_size.x * columna + box_size.x/2, box_size.y * fila + box_size.y/2);
    circulo_aux.SetPosition(box_size.x * columna + box_size.x/2, box_size.y * fila + box_size.y/2);
    bool imprimimos_cruz = true;
    /************************************************************/

    if(tablero[fila][columna]){ cout << "en esa casilla ya hay una ficha" << endl; todo_correcto = false; }
    else if(colocamos_circulo){ //jugador 2 (los circulos)
        noughts[positionNought].SetPosition(box_size.x * columna + box_size.x/2, box_size.y * fila + box_size.y/2);
        ++positionNought;
    }
    else{ //jugador 1 (las cruces) 
        crosses[positionCross].SetPosition(box_size.x * columna + box_size.x/2, box_size.y * fila + box_size.y/2);
        ++positionCross;
    }

    if(todo_correcto){
        /*AQUI LA PARTE DE ALTERNAR CRUZ Y CIRCULO*/
        for(int counter = 0; counter < MAX_COUNTER; ++counter){
            while(clock.getElapsedTime().asSeconds() < deelay);
            deelay = deelay + deelay * 0.20f;
            white_square.Draw(window);
            if(imprimimos_cruz) cruz_aux.Draw(window);
            else circulo_aux.Draw(window);
            window.display();
            imprimimos_cruz = not imprimimos_cruz;
        }
        /******************************************/
        if(colocamos_circulo){ 
            if(++filas_circulo[fila] == 3 or ++columnas_circulo[columna] == 3){ partida_finalizada = true; ganador = 2; PositionLine(Nothing,line); }
            if(not partida_finalizada and fila == columna) if(++diagonal1_circulo == 3){ partida_finalizada = true; ganador = 2; PositionLine(Diagonal1,line); } //ficha puesta en diagonal1. El if not partida_finalizada es porque si ya he visto antes que esa ficha ya es ganadora, me da igual seguir sumando cosas
            if(not partida_finalizada and fila+columna == 2) if(++diagonal2_circulo == 3){ partida_finalizada = true; ganador = 2; PositionLine(Diagonal2,line); } //ficha puesta en diagonal2. El if not partida_finalizada es porque si ya he visto antes que esa ficha ya es ganadora, me da igual seguir sumando cosas
        }
        else{ 
            if(++filas_cruz[fila] == 3 or ++columnas_cruz[columna] == 3){ partida_finalizada = true; ganador = 1; PositionLine(Nothing,line); }
            if(not partida_finalizada and fila == columna) if(++diagonal1_cruz == 3){ partida_finalizada = true; ganador = 1; PositionLine(Diagonal1,line); }//ficha puesta en diagonal1. El if not partida_finalizadaes porque si ya he visto antes que esa ficha ya es ganadora, me da igual seguir sumando cosas
            if(not partida_finalizada and fila+columna == 2) if(++diagonal2_cruz == 3){ partida_finalizada = true; ganador = 1; PositionLine(Diagonal2,line); }//ficha puesta en diagonal2. El if not partida_finalizada es porque si ya he visto antes que esa ficha ya es ganadora, me da igual seguir sumando cosas

        }
        tablero[fila][columna] = true;
        if(++contador_fichas == 9) partida_finalizada = true;
        Noughts_turn = not Noughts_turn;
    } 
    return {partida_finalizada, ganador}; //SI UNA PARTIDA FINALIZA NO SABEMOS SI HAY GANADOR, PORQUE HA PODIDO ACABAR EN EMPATE. POR ESO RETORNO ESTE PAR
}

void Board::ResizeBoard(Vector2f desired_size){
    background.setScale(GetScale(desired_size, textura_fondo.getSize()));
    board_size = Vector2u(desired_size);
    box_size = {board_size.x/3.0f, board_size.y/3.0f};
} 

void Board::ResetBoard(){
    tablero = vector< vector<bool> >(3, vector<bool>(3,false));
    filas_cruz = filas_circulo = columnas_circulo = columnas_cruz = vector<int>(3,0);
    diagonal1_circulo = diagonal2_circulo = diagonal1_cruz = diagonal2_cruz = 0;
    contador_fichas = 0;
}

void Board::Draw(RenderWindow& window){
    window.draw(background);
}

bool Board::RandomBool(){
    return 0 + (rand() % (1 - 0 + 1)) == 1;
}


int Board::WhichRow(float clickY){
    if(clickY < box_size.y) return 0; //columna 1
    else if(clickY < 2 * box_size.y) return 1; //columna 2
    else if (clickY < 3 * box_size.y) return 2; //columna 3
    else return -1;
}

int Board::WhichColumn(float clickX){
    if(clickX < box_size.x) return 0; //columna 1
    else if(clickX < 2 * box_size.x) return 1; //columna 2
    else if (clickX < 3 * box_size.x) return 2; //columna 3
    else return -1;
}

Vector2f Board::GetScale(Vector2f desired_size, Vector2u texture_size){
    return {desired_size.x/texture_size.x, desired_size.y/texture_size.y};
}

void Board::PositionLine(Where where, Line& linea){
    if(where != Nothing and where != Diagonal1 and where != Diagonal2){
         cerr<<"ERROR: En algun punto de tu codigo llamas a posicionar_linea de una forma no válida" << endl;
         exit(-1);
    }
    float perfect_vertical = linea.GetPerfectVerticalAngle();
    if(where == Diagonal2){
        linea.SetRotation(perfect_vertical + 45.0f);
        linea.SetPosition(board_size.x/2.0f, board_size.y/2.0f);
    }
    else if (where == Diagonal1){
        linea.SetRotation(perfect_vertical - 45.0f); //rota 90 grados para una diagonal al reves
        linea.SetPosition(board_size.x/2.0f, board_size.y/2.0f);
    }
    else{ //where == Nothing
        bool linea_horizontal = false;
        int i;
        for(i=0; i<3; i++)
            if(filas_cruz[i] == 3 or filas_circulo[i] == 3){linea_horizontal = true; break;}
        if(linea_horizontal){
            linea.SetRotation(perfect_vertical + 90.0f);
            linea.SetPosition(board_size.x/2.0f, board_size.y/6.0f*(2*i +1)); //i es la fila/columna que ha hecho raya
        }
        else{
            for(i=0; i<3; i++)
                if(columnas_cruz[i] == 3 or columnas_circulo[i] == 3) break;
            linea.SetRotation(perfect_vertical);
            linea.SetPosition(board_size.x/6.0f*(2*i +1), board_size.y/2.0f); //i es la fila/columna que ha hecho raya
        }
        
    }
}