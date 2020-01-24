#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "PrepareText.hh"
#include "Audio.hh"
#include "Board.hh" //este incluye "Line.hh" y "Piece.hh". Si aqui duplico el include me da error de redefinition
using namespace std;
using namespace sf;


const int NUM_MAXIMO_FICHAS = 7; //Extreme version
const Vector2f tamano_ficha = {200.0f, 200.0f}; 
const Vector2u original_window_size = {864, 864}; //ESTA VARIABLE SIEMPRE SERA IDENTICA A WindowSize CON EL APAÑO QUE LE HE HECHO PARA QUE NO SE PUEDA HACER RESIZE
const Vector2u barra_inferior_size = {864,86};
const Vector2f tamano_linea = {1000.0f, 875.2941176f};

//RECORDATORIO: A UNA FUNCION LE PUEDO PASAR TAMBIEN UNA VARIABLE GLOBAL COMO PARAMETRO, NO DA ERROR.
struct Puntuacion{
    int scorePlayer1 = 0;
    int scorePlayer2 = 0;
};





int main(){
    Puntuacion puntuacion;

    ////****RENDER WINDOW****
    RenderWindow window(VideoMode(original_window_size.x, original_window_size.y+barra_inferior_size.y), "3 en raya", Style::Titlebar | Style::Close); //AÑADIR EL TERCER PARAMETRO ES IMPORTANTE PARA QUE *NO* SALGA LA OPCION DE HACER GRANDE LA PANTALLA NI RESIZE(sin ese atributo pues se activa todo, y si quisiesemos que saliese pues lo añadimos a ese tercer atributo).
    window.setFramerateLimit(60);

    //****MUSIC****
    //musica (no efectos. efectos gratis) de  https://patrickdearteaga.com/
    //Solo permitido .ogg
    Audio musica("Su_Turno.ogg", 10.0f); //AUDIO ES CLASE MIA
    musica.Play(true);
    Audio aplausos("claps3.ogg", 10.0f);
    Audio lamentos("boo2.ogg", 23.0f);

    //****BOARD****
    Board board("FONDOROJO_tictactoe.png"); //BOARD ES CLASE MIA
    //****WINNER LINE****
    Line linea("LINEA_tictactoe.png", -48.0f, tamano_linea); //LINE ES UNA CLASE MIA. Representa la linea que señala las piezas que hacen tres en raya

    //****TEXTURES****
    //texturas de X, de O y tablero de https://www.pinclipart.com/
    Texture textura_barra_inferior, textura_informacion_extreme;
    if(not textura_barra_inferior.loadFromFile("Barrainferior_3enraya.png")) cerr << "ERROR loading tictactoe bottom menu" << endl;
    if(not textura_informacion_extreme.loadFromFile("Informacion_3enraya_extremo.png")) cerr << "ERROR loading tictactoe information menu" << endl;


    //****SPRITE****
    Sprite information(textura_informacion_extreme);
    information.setOrigin(textura_informacion_extreme.getSize().x/2.0f, textura_informacion_extreme.getSize().y/2.0f);
    information.setPosition(original_window_size.x/2.0f, (original_window_size.y+barra_inferior_size.y)/2.0f);
    Sprite bottom_menu(textura_barra_inferior);
    bottom_menu.setPosition(0,original_window_size.y);
    vector<Piece> cruces(NUM_MAXIMO_FICHAS);  //PIECE ES UNA CLASE MIA
    vector<Piece> circulos(NUM_MAXIMO_FICHAS); //PIECE ES UNA CLASE MIA
    for(int i = 0; i<NUM_MAXIMO_FICHAS; ++i){
        cruces[i].Initialice("CRUZNEGRA_tictactoe.png", tamano_ficha, true);
        circulos[i].Initialice("CIRCULOROJO_tictactoe.png", tamano_ficha, true);
    }


    int posCirculo, posCruz; //señalan la ficha que toca poner (señalan una posicion de los vectores de fichas)       

    //****FONT and TEXT****
    Font font;
    if (not font.loadFromFile("yoster.ttf")) cerr << "ERROR: Cannot load font" << endl;
    Text text, text_pressSpace, texto_creador;
    funcion_texto(texto_creador, font, "Created by\nIsmael Quinones", 24, Color::White, 2.0f, Color::Black, true, Vector2f(750.0f, original_window_size.y+(barra_inferior_size.y/2.0f -3.8f))); //el -3.8f es porque así da la sensacion de estar mas centrado, nada mas


    //****EACH_ROUND**** 
restart_game: //etiqueta para un goto del final

    board.ResetBoard();

    //****VARIABLES**** 
    bool GANADOR_CIRCULO = false;
    bool GANADOR_CRUZ = false;
    bool jug_circulo = Board::RandomBool(); //false es jugador1(empieza jugando cruz) y true es jugador2
    bool partida_finalizada = false;
    bool texto_seteado = false;
    bool podemos_aplaudir = true;
    bool podemos_lamentarnos = true;
    posCirculo = posCruz = 0; //se declaran una vez por ronda, no por partida
    int anterior_transparencia = 0;
    bool mostrando_informacion = false;


    while(window.isOpen()){
        Event e;
        while(window.pollEvent(e)){
            switch(e.type){
                case Event::Closed:
                    window.close();
                    break;
                case Event::MouseButtonPressed:
                    if(not partida_finalizada and not mostrando_informacion){ //para que no sirvan los clicks si se han puesto las 9 fichas o ya tenemos ganador. Y si se está mostrando la informacion por pantalla (usuario pulsando 'I') pues tampoco queremos que haga caso de los clicks
                        pair<bool,int> cojo_resultado = board.Place_X_or_O_extreme(Vector2f(e.mouseButton.x, e.mouseButton.y), cruces, circulos, posCruz, posCirculo, jug_circulo, linea, window);
                        partida_finalizada = cojo_resultado.first;
                        int ganador = cojo_resultado.second;
                        if(ganador == 1){
                            GANADOR_CRUZ = true;
                            ++puntuacion.scorePlayer1; //suma el score de cruz
                        }
                        else if(ganador == 2){ 
                             GANADOR_CIRCULO = true;
                             ++puntuacion.scorePlayer2;
                        }
                    }
                    break;
                 case Event::KeyPressed:
                    if(e.key.code == Keyboard::Space) goto restart_game;
                    else if(e.key.code == Keyboard::M){ musica.Mute_or_unmute(); aplausos.Mute_or_unmute(); lamentos.Mute_or_unmute(); }
                    else if(e.key.code == Keyboard::Add){ musica.Volume_up(); aplausos.Volume_up(); lamentos.Volume_up(); }
                    else if(e.key.code == Keyboard::Subtract){ musica.Volume_down(); aplausos.Volume_down(); lamentos.Volume_down(); }
                    break;
            }
        }
        
        //ESTO LO PRIMERITO DE TODO, ANTES DE DIBUJAR LAS OTRAS COSAS
        window.clear(Color::White);
        board.Draw(window);


        for(int i = 0; i<posCirculo; ++i) circulos[i].Draw(window);
        for(int i = 0; i<posCruz; ++i) cruces[i].Draw(window);

        if(GANADOR_CIRCULO or GANADOR_CRUZ){

            linea.SetColor(sf::Color(255,255,255,anterior_transparencia)); //esto hace un efecto de que la linea se hace mas fuerte progresivamente
            if(anterior_transparencia < 255) ++anterior_transparencia;
            linea.Draw(window);

            if(not texto_seteado){
                texto_seteado = true;
                if(GANADOR_CRUZ) funcion_texto(text, font, "Player 1 wins", 85, Color::White, 6.0f, Color::Black, true, Vector2f(original_window_size.x/2.0f, original_window_size.y/2.0f));
                else if(GANADOR_CIRCULO) funcion_texto(text, font, "Player 2 wins", 85, Color::White, 4.5f, Color::Black, true, Vector2f(original_window_size.x/2.0f, original_window_size.y/2.0f));
                funcion_texto(text_pressSpace, font, "Press Space for another round", 45, Color::White, 4.5f, Color::Black, true, Vector2f(original_window_size.x/2.0f, original_window_size.y/2.0f + text.getLocalBounds().height));
            }
            //los draw fuera para que no se pinte la linea encima
            window.draw(text);
            window.draw(text_pressSpace);
            if(podemos_aplaudir){
                aplausos.Play(false);
                podemos_aplaudir = false;
            }  
        } 
        else if(partida_finalizada){ //ENTRA AQUI SI NO HAY GANADOR (de ahi la importancia de else if) PERO LA PARTIDA SÍ ESTÁ FINALIZADA
            if(not texto_seteado){
                texto_seteado = true;
                funcion_texto(text, font, "It's a tie", 85, Color::White, 6.0f, Color::Black, true, Vector2f(original_window_size.x/2.0f, original_window_size.y/2.0f));
                funcion_texto(text_pressSpace, font, "Press Space for another round", 45, Color::White, 4.5f, Color::Black, true, Vector2f(original_window_size.x/2.0f, original_window_size.y/2.0f + text.getLocalBounds().height));
            }
            window.draw(text);
            window.draw(text_pressSpace);
            if(podemos_lamentarnos){
                lamentos.Play(false);
                podemos_lamentarnos = false;
            }
        }

        if(Keyboard::isKeyPressed(Keyboard::Key::S)){
            //el texto a cargar debe cambiar si hay un ganador. O sea, no simplemente que sea correcto al inicio de ronda sino en todos los momentos de la ronda
            Text texto_score_p1, texto_score_p2;
            string aux1 = to_string(puntuacion.scorePlayer1);
            string aux2 = to_string(puntuacion.scorePlayer2);
            string stringP1 = "Score Player 1: "+aux1;
            string stringP2 = "Score Player 2: "+aux2;
            funcion_texto(texto_score_p1, font, stringP1, 60, Color::White, 4.5f, Color::Black, false, Vector2f(0.0f,0.0f));
            funcion_texto(texto_score_p2, font, stringP2, 60, Color::White, 4.5f, Color::Black, false, Vector2f(0.0f, 0.0f+texto_score_p1.getLocalBounds().height));

            window.draw(texto_score_p1);
            window.draw(texto_score_p2);
        }

        //LA BARRA INFERIOR DE OPCIONES HAY QUE PINTARLA DESPUES DE LA LINEA
        window.draw(bottom_menu);

        if(partida_finalizada){
            window.draw(texto_creador);
        }
        else{
            Text texto_turno;
            if(jug_circulo) funcion_texto(texto_turno, font, "Player 2,\nyour turn", 30, Color::Red, 2.0f, Color::Black, true, Vector2f(750.0f, original_window_size.y+(barra_inferior_size.y/2.0f -4.7f))); //el -4.7f es porque así da la sensacion de estar mas centrado, nada mas
            else funcion_texto(texto_turno, font, "Player 1,\nyour turn", 30, Color::Black, 1.6f, Color::White, true, Vector2f(750.0f, original_window_size.y+(barra_inferior_size.y/2.0f -4.7f)));
            window.draw(texto_turno);
        }

        if(Keyboard::isKeyPressed(Keyboard::Key::I)){
            window.draw(information);
            mostrando_informacion = true;
        }
        else mostrando_informacion = false;

        window.display();

    }

    return 0;
}

//nombre_sprite.setOrigin para poner una nueva posicion central del sprite diferente a la esquina superior izquierda del propio sprite. Y ENTRE PARENTESIS NO SE LE PASA EL TAMAÑO DEL SPRITE DIVIDIDO ENTRE 2 SINO EL DE LA TEXTURA ENTRE 2