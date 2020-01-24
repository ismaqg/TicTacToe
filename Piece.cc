#include "Piece.hh"

Piece::Piece(){} //obligatorio despues de crear una pieza que se llame a inicializar

void Piece::Initialice(string file_texture, Vector2f desired_piece_size, bool center_origin){
    if(not textura.loadFromFile(file_texture)) cerr << "ERROR loading texture of a tictactoe piece" << endl;
    textura.setSmooth(true);
    ficha.setTexture(textura);
    ficha.setScale(GetScale(desired_piece_size, textura.getSize()));
    tamano = desired_piece_size;
    if(center_origin) ficha.setOrigin(textura.getSize().x/2.0f, textura.getSize().y/2.0f);
}

void Piece::SetPosition(float x, float y){
    ficha.setPosition(x,y);
}

Vector2f Piece::GetSize(){
    return tamano;
}

Vector2f Piece::GetBiggerSizeComparation(Piece& a, Piece& b){
    Vector2f retorno;
    if(a.GetSize().x > b.GetSize().x) retorno.x = a.GetSize().x; else retorno.x = b.GetSize().x;
    if(a.GetSize().y > b.GetSize().y) retorno.y = a.GetSize().y; else retorno.y = b.GetSize().y;
    return retorno;
}

void Piece::Draw(RenderWindow& window){
    window.draw(ficha);
}

Vector2f Piece::GetScale(Vector2f desired_size, Vector2u texture_size){
    return {desired_size.x/texture_size.x, desired_size.y/texture_size.y};
}