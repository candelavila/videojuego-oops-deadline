#ifndef OBJETO_SIN_TEX_H
#define OBJETO_SIN_TEX_H
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;

class ObjetoSinTex {
public:
	ObjetoSinTex(sf::Texture *t);
	void Draw(RenderWindow &ww);
	Vector2f posicion();
	virtual void Update()=0;
	virtual int Tipo()=0;
	virtual void AsignarPos(const int &min_y,const int &max_y)=0;
	virtual void CambiarPosicion(int pos_y, int i)=0;
	FloatRect GetBB()const;
	~ObjetoSinTex(){}
protected:
	Sprite m_s;
	Texture m_texture;
};

#endif
