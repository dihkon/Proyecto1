 //Punto de entrada de todo programa de ordenador

#include <SFML/Graphics.hpp>
#include "Ship.h"


int main()
{
 
	//Definición del tamaño de la ventana
    sf::RenderWindow window(sf::VideoMode(640, 480), "Asteroid by David Pulido Vargas (2012)");
 
 //Reloj para sincronizar las imágenes y que no se disparen los frames
 sf::Clock syncronice_timer;
 
 //El objeto nave de nuestro juego
 game::Ship space_ship;
 
 
 //Bucle principal de la aplicación
 //Mientras nuestra ventana sigua abierta
    while (window.isOpen())
    {
  //Recogemos cuanto tiempo a pasado en el frame anterior
  //y volvemos a poner el contador a cero
  float delta_time_seconds = syncronice_timer.restart().asSeconds();
 
  //Capturamos los eventos de la ventana
  //Como cerrar, se ha pulsado una tecla,
  //se ha movido el ratón, etc.
        sf::Event event;
        while (window.pollEvent(event))
        {
   //Si se ha pulsado cerrar ventana cerramos nuestra ventana
            if (event.type == sf::Event::Closed)
                window.close();
        }  
 
  //Actualizamos
  space_ship.update( delta_time_seconds ); //Actualizamos la nave según el tiempo transcurrido
 
  //Dibujamos
        window.clear();  //Limpiar
 
  window.draw( space_ship ); //Dibujamos la nave
 
        window.display(); //Mostrar en pantalla
 
  //Sincronizamos para que no vaya mas rápido que 30 fps
  while( syncronice_timer.getElapsedTime().asSeconds() < 1.0f / 30.0f )
   sf::sleep( sf::seconds( 1.0f/60.0f ) );
    }
 
 //Finalizamos nuestra aplicación
    return 0;   //Finalizamos la aplicación
}