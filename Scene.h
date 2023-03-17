#ifndef SCENE_H
#define SCENE_H
#include <SFML/Graphics/RenderWindow.hpp>
#include "Game.h"
#include <iostream>

using namespace std;
using namespace sf;
class Game;
class Scene {
public:
	Scene();
	virtual void Draw(RenderWindow &Window) = 0;
	virtual void Update(Game &gamee) = 0;
	virtual void ProcessEvent(Event &e) = 0;
	virtual ~Scene () {cout << "pasa a otra escena" <<endl;}
private:
};

#endif

