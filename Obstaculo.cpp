#include "Obstaculo.h"
Obstaculo::Obstaculo(sf::Texture *t, float speed) : ObjetoSinTex(t) {
	m_s.scale(0.6,0.6);
	posx = 725;
	m_speed = speed;
}

void Obstaculo::CambiarPosicion (int pos_y, int i) {
	posy = pos_y;
	m_s.setPosition(posx+450*i,posy);
}
void Obstaculo::AsignarPos(const int &min_y, const int &max_y){
	int result = rand() % 2;  // varia la posicion donde se generan enemies
	
	if(result == 1){
		this->CambiarPosicion(max_y,0);
	}else{
		this->CambiarPosicion(min_y,0);
	}
}
void Obstaculo::Update ( ) {
	m_s.move(m_speed,0);
}
