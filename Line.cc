#include "Line.hh"

Line::Line(string texture_file, float angle_offset_vertical, Vector2f desired_line_size){
    if (not textura_lineaganador.loadFromFile(texture_file)) cerr << "ERROR loading tictactoe winner line" << endl;
    linea.setTexture(textura_lineaganador);
    ResizeLine(desired_line_size);
    perfect_vertical = angle_offset_vertical;     
    linea.setOrigin(textura_lineaganador.getSize().x/2.0f, textura_lineaganador.getSize().y/2.0f);
} 

void Line::ResizeLine(Vector2f desired_size){
    linea.setScale(GetScale(desired_size, textura_lineaganador.getSize()));
    line_size = Vector2u(desired_size);
}

float Line::GetPerfectVerticalAngle(){
    return perfect_vertical;
}

void Line::SetColor(const Color& color){
    linea.setColor(color);
}

void Line::SetPosition(float x, float y){
    linea.setPosition(x,y);
}

void Line::SetRotation(float angle){
    linea.setRotation(angle);
}

void Line::Draw(RenderWindow& window){
    window.draw(linea);
}

Vector2f Line::GetScale(Vector2f desired_size, Vector2u texture_size){
    return {desired_size.x/texture_size.x, desired_size.y/texture_size.y};
}