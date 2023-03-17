#ifndef OBSTACULO_H
#define OBSTACULO_H
#include "Obstaculo.h"
#include "ObjetoSinTex.h"

class Obstaculo : public ObjetoSinTex {
private: 
	int posx=0;
	int posy=0;
	float m_speed;
public:
	Obstaculo(sf::Texture *t, float speed);
	void Update();
	int Tipo()override{return 2;}
	Vector2f posicion();
	void AsignarPos(const int &min_y,const int &max_y)override;
	void CambiarPosicion (int pos_y,int i);
	~Obstaculo(){}
};

#endif
