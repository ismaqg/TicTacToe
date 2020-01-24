#include "PrepareText.hh" //obligatorio para traer el include sfml graphics Y LOS USING NAMESPACE

void funcion_texto(Text& text, const Font& font, const string& message, unsigned int charactersize, const Color& fillcolor, float outlinethickness, const Color& outlinecolor, bool origin_center, const Vector2f& position){
    text.setFont(font);
    text.setString(message);
    text.setFillColor(fillcolor); //setColor is now deprecated. Instead of it: setFillColor and setOutlineColor
    text.setOutlineColor(outlinecolor);
    text.setOutlineThickness(outlinethickness);
    text.setCharacterSize(charactersize);
    if(origin_center) text.setOrigin(text.getLocalBounds().width/2.0f, text.getLocalBounds().height/2.0f);
    text.setPosition(position); 
}