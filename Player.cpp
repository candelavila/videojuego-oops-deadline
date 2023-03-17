#include "Player.h"
#include <SFML/Window/Keyboard.hpp>

Player::Player() : m_pos(270,304){
	m_t.loadFromFile("walk.png");
	m_s.setTexture(m_t);
	m_s.scale(0.5,0.5);
}
bool Player::colisionaCon(ObjetoSinTex *obj){
	auto bounds_otro = obj->GetBB(); 
	auto bounds_player = this->GetBB();
	
	bounds_otro.height-=10; // se "achica" la altura del rect de player
	
	bounds_player.left+=20;  //se "alarga" la coordenada del lado izquierdo
	bounds_player.height-=20;// se achica la altura
	bounds_player.width-=50; // se achica el ancho 
	
	return bounds_player.intersects(bounds_otro);
}
void Player::Draw (RenderWindow &ww,bool inmune) {
	if(inmune){
		m_s.setColor(sf::Color(0, 255, 0)); // green
	}else{
	//	m_s.setTexture(m_t);
		m_s.setColor(sf::Color(255, 255, 255));
	}
	ww.draw(m_s);
}
void Player::Update () {

	auto tex_sz = m_t.getSize();
	m_s.setTextureRect({(m_num_frame/10)*int(tex_sz.x)/4,0,int(tex_sz.x)/4,int(tex_sz.y)});
	m_num_frame = (m_num_frame+1)%40;
	
	m_speed.y += 0.15;
	m_pos += m_speed;
	
	if(m_pos.y>=304){ // para q no se vaya volando x el techo
		m_speed.y = 0;
		m_pos.y = 304;
		if(Keyboard::isKeyPressed(Keyboard::Key::Up) && m_speed.y==0){ // cuando salta
			m_speed.y = -5.5;
		}
	}
	if(Keyboard::isKeyPressed(Keyboard::Key::Down)&&m_speed.y!=0){
		m_speed.y = 5.5;
	}
	
	m_s.setPosition(m_pos);
}
FloatRect Player::GetBB ( ) const {
	return m_s.getGlobalBounds();
}
