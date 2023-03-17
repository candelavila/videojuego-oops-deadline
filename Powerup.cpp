#include "Powerup.h"
#include <SFML/Graphics/Texture.hpp>

Powerup::Powerup(sf::Texture *t, float speed) : ObjetoSinTex(t) {
	m_s.scale(0.5,0.5);
	posx = 725;
	m_speed = speed;
}
void Powerup::Update() {
	m_s.move(m_speed ,0);
}
void Powerup::CambiarPosicion (int pos_y, int i) {
	posy = pos_y;
	m_s.setPosition(posx+450*i,posy);
}
void Powerup::AsignarPos(const int &min_y, const int &max_y){
	int result = min_y + rand()% (max_y - min_y);   // varia la posicion donde se generan
	
	this->CambiarPosicion(result,0);
}

