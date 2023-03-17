#include "Match.h"
#include "Menu.h"
#include "Game.h"
#include "GameOver.h"
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics/Text.hpp>
#include "Premio.h"
#include "Obstaculo.h"
#include <iostream>
#include <SFML/Graphics/Texture.hpp>
#include "Powerup.h"
#include <SFML/System/Time.hpp>
using namespace std;

string elegirText(){
	string elegida;
	int opcion = rand()% 3 + 1;
	switch (opcion){
	case 1:
		elegida = "calc.png";
		break;
	case 2:
		elegida = "calendar.png";
		break;
	case 3:
		elegida = "folder.png";
		break;		
	};
	return elegida;
}
Match::Match() {
	background_texture.loadFromFile("background.jfif");
	background.setTexture(background_texture);
	background.setPosition(0,-150);
	
	face_texture.loadFromFile("zeds-face.png");
	Zeds_face.setTexture(face_texture);
	Zeds_face.setPosition(250,20);
	Zeds_face.setScale(0.666,0.666);
	
	shadow_texture.loadFromFile("zeds-shadow.png");
	Shadow.setTexture(shadow_texture);
	Shadow.setPosition(-200,48);
	Shadow.setScale(2.0,2.0);
	
	scoreFont.loadFromFile("FreePixel.ttf");
	scoreText.setFont(scoreFont);
	scoreText.setString("score: ");
	scoreText.setCharacterSize(40);
	scoreText.setStyle(sf::Text::Bold);
	scoreText.setPosition(150,8.7);
	scoreText.setColor(sf::Color::Red);
	
	scoreToStr = to_string(puntaje);
	scorePrint.setFont(scoreFont);
	scorePrint.setString(scoreToStr);
	scorePrint.setCharacterSize(40);
	scorePrint.setStyle(sf::Text::Bold);
	scorePrint.setPosition(300,8.7);
	scorePrint.setColor(sf::Color::Red);
}

void Match::Draw (RenderWindow & window) {
	window.clear(Color(125,60,0,100));		///maximo 255
	window.draw(background);
	
	window.draw(Shadow);
	player.Draw(window,inmune); 
	
	scorePrint.setString(scoreToStr);
	window.draw(scoreText);
	window.draw(scorePrint);
	
	for(int i = 0; i< objetos.size(); i++) { 
		objetos[i]->Draw(window);
	}
	
	window.display();
}
bool estaafuera(ObjetoSinTex *obj){ // si la coordenada x es menor a la del final de la pantalla retorna true.
	return obj->posicion().x==-10;
}

void Match::Update ( Game &gamee ) {
	if(Keyboard::isKeyPressed(Keyboard::Key::Escape)){ // para volver a Menu
		gamee.SetScene(new Menu());
	}

	player.Update();
	
	///se encarga de ir controlando las colisiones y de liberar memoria
	for( auto it = objetos.begin(); it != objetos.end();/*No hacemos nada en este caso*/ )
	{
		auto* objeto = *it;
		objeto->Update();
		
		if(player.colisionaCon(objeto)){
			switch(objeto->Tipo()){ // dependiendo del tipo de obj va a ocurrir algo distinto
			case 1:
				puntaje += 100;
				delete objeto;
				objetos.erase(it); // antes era it = objetos.erase(it);
				it = objetos.begin();
				break;

			case 2: //no le pasa nada si  esta en estado inmune.
				if(inmune){
					break;
				}else{
					gamee.SetScene(new GameOver(puntaje));
				}
				break;
				
			case 3: 
				inmune = true;
				delete objeto;
				objetos.erase(it);
				it=objetos.begin();
				cout << "comienza modo inmune"<< endl;
				break;
				
			}
		}
		if( estaafuera(objeto) ) {
			it = objetos.erase(it);
		} else it++;
	}
	
	
	Time timeobst = clockobst.getElapsedTime();
	float secsPassed1  = timeobst.asSeconds();
	
	/// se encarga de spawnear los obstaculos/powerup/premio
	if( secsPassed1>=distan) { // los objetos se generan a cierta distancia
		
		ObjetoSinTex *aux_obj;
		
		if( cant_obs==4 ){ // si ya esquivó 4 Obstaculos, q haga alguno de los otros dos elementos:
			
			int valorobj = rand()% 2;
			
			if(valorobj==1){
				if( (puntaje%300==0 && puntaje>0) && !inmune ){
					Texture* texture = new sf::Texture;
					texture->loadFromFile("coffee-pickup.png");
					aux_obj = new Powerup(texture,speed);
					aux_obj->AsignarPos(min_y,max_y);
					objetos.push_back(aux_obj);
					
				} else {			 // y si no que haga un clip 
					Texture* texture = new sf::Texture;
					texture->loadFromFile("clip.png");
					aux_obj = new Premio(texture,speed);
					aux_obj->AsignarPos(min_y,max_y);
					objetos.push_back(aux_obj);
					
				}
			}else{		 // y si no que haga un clip 
				Texture* texture = new sf::Texture;
				texture->loadFromFile("clip.png");
				aux_obj = new Premio(texture,speed);
				aux_obj->AsignarPos(min_y,max_y);
				objetos.push_back(aux_obj);
			}
			cant_obs = -1; //reinicio la cant de Obstaculos
			
		} else if( cant_obs<4 || cant_obs>=1 ){ // si no todavia esquivó 4 Obstaculos, q siga spawneandolos
			string file_elegido = elegirText(); // para variar la textura de enemigo
			Texture* texture = new Texture; 
			texture->loadFromFile(file_elegido);
			aux_obj = new Obstaculo(texture,speed);
			aux_obj->AsignarPos(min_y,max_y);
			objetos.push_back(aux_obj);
		}
		cant_obs++;
		
		speed -= 0.18333; // la velocidad aumenta gradualmente.
		
		int valordistan = rand()% 2;
		if(valordistan == 1){ 
			distan = distan - 0.02; // se genera mas cerca
		} else {
			distan = distan + 0.07; // se genera mas lejos
			
			if(valordistan == 2){			
				distan = distan + 0.10; // se genera mas lejos
			} 
			else {
				distan = distan - 0.088; // se genera mas cerca **antes era 0.15
			}
		}
		clockobst.restart();
	//	cout << "reinicia reloj1" << endl;
		
		/// controla la inmunidad del player
		if(inmune && cont_pup>=3){ 
			inmune = false;
			cont_pup = 0;
			cout << "se terminó el powerup " << endl;		
		}else if(cont_pup<3 && inmune){
			cont_pup += 1;
			cout << "esquivo con power up" <<endl;
		}
	}	
	
	///se encarga de que no sobrepase la maxvelocidad
	if(speed>=maxspeed){
		speed = maxspeed; 
	}
	
	/// se encarga de actualizar el string de puntaje
	scoreToStr = to_string(puntaje);
}
Match::~Match(){
	for( auto &o:objetos ){
		delete o;
	}
}
