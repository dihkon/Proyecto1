#include "Ship.h"

namespace game
{
	Ship::Ship()
	{
		m_shipShape.setPointCount(3);
		m_shipShape.setPoint(0, sf::Vector2f(10.0f, 0.0f));
		m_shipShape.setPoint(1, sf::Vector2f(-10.0f, -7.5f));
		m_shipShape.setPoint(2, sf::Vector2f(-10.0f, 7.5f));

		m_shipShape.setFillColor(sf::Color(0,0,0,0));
		m_shipShape.setOutlineColor(sf::Color::White);
		m_shipShape.setOutlineThickness(2);
		m_shipShape.setPosition(0.0f, 0.0f);

		reset();

	}

	Ship::~Ship(){};

	void Ship::reset()
	{
		setPosition(320.0f, 240.0f);
		setRotation(0.0f);
		m_ship_velocity.x = 0.0f;
		m_ship_velocity.y = 0.0f;
	
	}

	void Ship::update(float delta_time_seconds)
	{
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			rotate(-1.0f * m_ship_rotation_velocity * delta_time_seconds);

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			rotate(m_ship_rotation_velocity * delta_time_seconds);

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			float rotation = getRotation();

			float cosRotation = std::cosf(rotation * degree2radian);
			float sinRotation =  std::sinf(rotation * degree2radian);

			m_ship_velocity.x += m_ship_aceleration * delta_time_seconds * cosRotation;
			m_ship_velocity.y += m_ship_aceleration * delta_time_seconds * sinRotation;


		}

		float ship_speed = std::sqrtf((m_ship_velocity.x * m_ship_velocity.x) + (m_ship_velocity.y * m_ship_velocity.y));

		if(ship_speed > 0)
		{
			float angle_of_velocity = std::atan2f(m_ship_velocity.y / ship_speed, m_ship_velocity.x / ship_speed);

			m_ship_velocity.x -= m_ship_drag_force * delta_time_seconds * std::cosf(angle_of_velocity);
			m_ship_velocity.y -= m_ship_drag_force * delta_time_seconds * std::sinf(angle_of_velocity);

			ship_speed = std::sqrtf( (m_ship_velocity.x * m_ship_velocity.x) + (m_ship_velocity.y * m_ship_velocity.y) );
 
   //Si es menos que cero, paro la nave para que no retroceda
   if( ship_speed < 0.0f ) m_ship_velocity = sf::Vector2f( 0.0f, 0.0f );
    
   //Actualizo la posición de la nave
   move( m_ship_velocity * delta_time_seconds );
 
   //Comprueba la posición
   sf::Vector2f position = getPosition();
 
   //Si se sale por los laterales izquierdo o derecho
   //los muevo hasta el lado contrario
   if( position.x <= -10.0f ) position.x = 640.0f + 10.0f;
   else if( position.x >= 650.0f ) position.x = - 10.0f;
 
   //Si se sale por los laterales superior o inferior
   //los muevo hasta el lado contrario
   if( position.y <= -10.0f ) position.y = 480.0f + 10.0f;
   else if( position.y >= 490.0f ) position.y = - 10.0f;
 
   //NOTA - Los 10 pixel de diferencia con los limites de la pantalla
   //  son para que no se vea que cambiamos de posición, queda mucho
   //  mejor visualmente
 
   //Ponemos la posición que obtenemos
   setPosition( position );
  }
 }
 
 //Definición de la función virtual de sf::Drawable
 void Ship::draw ( sf::RenderTarget &target, sf::RenderStates states ) const
 {
  //Aplicamos a la transformación que nos viene la transformación que tiene la nave
  states.transform *= getTransform();
 
  //Dibujamos la representación gráfica de la nave con la transformación calculada
  target.draw( m_shipShape, states );
 
  //NOTA - Una transformación contiene la información de posición, rotación y escalado.
 }
		
}


