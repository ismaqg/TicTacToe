#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class Line{
public:
    Line(string texture_file, float angle_offset_vertical, Vector2f desired_line_size); //el segundo atributo es es el offset en grados que hay desde la posicion original de la linea en la textura hasta una posicion vertical perfecta

    void ResizeLine(Vector2f desired_size);

    float GetPerfectVerticalAngle();

    void SetColor(const Color& color);

    void SetPosition(float x, float y);

    void SetRotation(float angle);

    void Draw(RenderWindow& window);

private:
    static Vector2f GetScale(Vector2f desired_size, Vector2u texture_size);

private:
    float perfect_vertical; //el offset en grados que hay desde la posicion original de la linea en la textura hasta una posicion vertical perfecta
    Texture textura_lineaganador;
    Sprite linea;
    Vector2u line_size;
};