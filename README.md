# TicTacToe
2 juegos: 3 en raya clasico y una variante

Juegos desarrollados con la libreria SFML en el lenguaje c++

Si quiere ejecutarlo en linux deberá instalar las librerías para SFML. Para ello deberá escribir en el terminal lo siguiente:
#> sudo apt-get install libsfml-dev
(igual antes necesita hacer sudo apt update)

Hay adjunto un makefile, así que simplemente deberá escribir "make" (sin las comillas) en el terminal para que se compile el juego. Una vez compilado podrá ejecutarlo:
EJECUTAR JUEGO CLÁSICO:
#> ./3enraya_normal
EJECUTAR VARIANTE DEL 3 EN RAYA:
#> ./3enraya_extremo

Al final de todo, si no desea conservar los archivos de esta librería puede hacer:
#> sudo apt-get remove libsfml-dev
Esto no liberará todo el espacio que ha ocupado al instalar la librería, para ello tendrá que escribir (despues de ejecutar la orden anterior) 
#> sudo apt autoremove 
Esto lo que hace es "borrar los paquetes huérfanos, o las dependencias que quedan instaladas después de haber instalado una aplicación y luego eliminarla, por lo que ya no son necesarias." (información extraída de https://blog.desdelinux.net/comandos-para-liberar-espacio-con-apt-get/)


En su ordenador meta todos los archivos en la misma carpeta!!


# 3 EN RAYA EXTREMO, CÓMO FUNCIONA?

Ésta es la variante de 3 en raya que encontrará aquí. La idea es cambiar el mayor problema del 3 en raya original: Que las partidas normalmente queda empate. Para ello cada jugador va con una ficha, pero a la hora de colocar una ficha en el tablero es completamente aleatorio si colocan una suya o del oponente. Esto implica que, por ejemplo, si usted juga con las cruces y el oponente con los circulos y tenemos dos circulos en raya, deba decidir si frefiere impedir su tres en raya (a sabiendas de que puede colocar una ficha del oponente y eso implicaría regalarle la partida) o colocar en otro lugar y que sea su oponente el que deba decidir si arriesgarse a hacer 3 en raya o a fastidiarse él mismo su posibilidad de hacer 3 en raya.


