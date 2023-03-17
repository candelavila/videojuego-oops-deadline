#ifndef PLAYER_H
#define PLAYER_H
#include "ObjetoSinTex.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Player  {
public:
	Player();
	bool colisionaCon(ObjetoSinTex *obj);
	void Draw(RenderWindow &ww,bool inmune);
	void Update();
	FloatRect GetBB()const;
private:
	Vector2f m_pos,m_speed;
	int m_num_frame = 0;
	Texture m_t;
	Sprite m_s;
};

#endif
