#ifndef MATCH_H
#define MATCH_H
#include "Player.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Scene.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include "ObjetoSinTex.h"
#include <vector>

using namespace std;

class Match : public Scene{
public:
	Match();
	void Draw(RenderWindow &window);
	void Update(Game &gamee);
	void ProcessEvent(Event &e){}
	~Match();
private:
	Player player;
	Texture background_texture;	///textura del Fondo
	Sprite background;
	Texture face_texture;		///textura de la cara del gatito HUD
	Sprite Zeds_face;
	Texture coffee_texture;			///textura de la taza HUD
	int cant_obs = 0;		 // cant obstaculos esquivados
	
	Texture shadow_texture;			///textura de la sombra Enemigo
	Sprite Shadow;
	vector<ObjetoSinTex*>objetos;
	Font scoreFont;
	Text scorePrint;
	Text scoreText;
	float speed = -5;
	float maxspeed = -2.3f;
	float distan = 1.6; // distancia q hay entre cada obstaculo.
	Clock clockobst,clockpower;
	bool inmune = false;
	int puntaje = 0, cont_pup = 0;
	string scoreToStr;
	float tiempopowerup = 0;
	
	// rango de coordenadas verticales q van a tener los Objetos.
	int min_y = 230;
	int max_y = 341;
};

#endif

