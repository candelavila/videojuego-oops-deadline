#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Scene.h"

using namespace sf;
class Scene;

class Game {
public:
	Game();
	void Run();
	void Draw();
	void Update();
	void ProcesadoJuego();
	void SetScene(Scene *next_scene);
private:
	RenderWindow m_w;
	Scene *m_scene;
	Scene *m_next_scene = nullptr;
};



#endif

