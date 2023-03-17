#ifndef PREMIO_H
#define PREMIO_H
#include <SFML/System/Vector2.hpp>
#include "ObjetoSinTex.h"

class Premio : public ObjetoSinTex {
public:
	Premio(sf::Texture *t, float speed);
	Vector2f posicion();
	void Update();
	int Tipo()override{return 1;}
	void AsignarPos(const int &min_y,const int &max_y)override;
	void CambiarPosicion (int pos_y, int i);
	~Premio(){}
private:
	Vector2f m_pos;
	float m_speed;
	int posx, posy;
};
#endif
