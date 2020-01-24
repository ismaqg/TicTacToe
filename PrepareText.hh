#include <SFML/Graphics.hpp>
using namespace std; //!!!! (std::string por ejemplo)
using namespace sf; //!!!!!


/**Pre: se debe recibir como argumentos un texto sobre el que queremos aplicar un estilo, una fuente de texto, un unsigned int para el tamaño de letra, un color del tipo Color de SFML para el color del texto, un float para
el ancho del borde texto, un color del tipo Color de SFML para el borde del texto, un booleano que indique si queremos que el punto origen del texto sea el centro del texto o que, por contrario, se mantenga el que ya tiene
y por ultimo un Vector2f indicando las coordenadas de la posicion donde queremos colocar el texto.*/
/**Post: se aplica al texto pasado como argumento el estilo compuesto desde el segundo argumento hasta el último*/
/**Observaciones: origin_center en caso de ser false no cambiará el origen del texto, por tanto seguirá siendo su esquina superior izquierda. Por tanto si se desea un origen distinto a este punto comentado o al centro se
 debera utilizar el metodo setOrigin(float x, float y) sobre texto para darle un punto de origen*/
void funcion_texto(Text& text, const Font& font, const string& message, unsigned int charactersize, const Color& fillcolor, float outlinethickness, const Color& outlinecolor, bool origin_center, const Vector2f& position);