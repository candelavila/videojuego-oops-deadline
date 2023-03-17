#ifndef POWERUP_H
#define POWERUP_H
#include "ObjetoSinTex.h"
#include <SFML/System/Vector2.hpp>

class Powerup : public ObjetoSinTex {
public:
	Powerup(sf::Texture *t, float speed);
	Vector2f posicion();
	void Update ();
	int Tipo()override{return 3;}
	void AsignarPos(const int &min_y,const int &max_y)override;
	void CambiarPosicion (int pos_y, int i);
	~Powerup(){}
private:
	Vector2f m_pos;
	float m_speed;
	int posx, posy;
};

#endif

