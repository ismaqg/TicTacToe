#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Piece{
public:
    Piece();
    void Initialice(string file_texture, Vector2f  desired_piece_size, bool center_origin);

    void SetPosition(float x, float y);

    Vector2f GetSize();

    static Vector2f GetBiggerSizeComparation(Piece& a, Piece& b); //Gets a Vector2f with the maximum value in the X axis between 2 pieces and the same for the Y axis

    void Draw(RenderWindow& window);

private:
    static Vector2f GetScale(Vector2f desired_size, Vector2u texture_size);

private:
    Texture textura;
    Sprite ficha;
    Vector2f tamano;
};