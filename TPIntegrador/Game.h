#pragma once
#include <iostream>
#include <random>
#include <vector>
#include <ctime>
#include <sstream>

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include <Windows.h>


using namespace sf;
using namespace std;


class Game
{
private:
	//Variables

	//Windows
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event evt;
	sf::Clock relojEnemigo;

	//mouse
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Feedback
	sf::Font font;
	sf::Text uiText;

	std::vector<sf::Vector2f> posiciones; //Vector de posiciones base
	std::vector<sf::Sprite> vidasSprites;
	sf::Vector2f nuevaPosicion; //Seteo de nueva posicion para sprite

	sf::Texture t_crosshair, t_fondo, t_gameOver, t_win, t_vidas, t_mosquito, t_soldadito, t_gusano, t_mariquita, t_arania, t_petardo;
	sf::Sprite s_crosshair, s_fondo, s_gameOver, s_win, s_vidas, s_mosquito, s_soldadito, s_gusano, s_mariquita, s_arania, s_petardo;
	
	
	std::vector<sf::Sprite*> sprites = { &s_mosquito, &s_soldadito, &s_gusano, &s_arania, &s_mariquita, &s_petardo }; //Vector para grupo de sprites de enemigos
	std::vector<bool> enemigoBueno = { true,false, true, true, true, false};

	bool endGame;

	//Sonidos
	SoundBuffer sBuffer, sBufferGO, sBufferYWin;
	Sound rana, gameOverSound, youWinSound;
	Music bgM;

	//(Enemigos)
	int enemyIndex; //es el indice actual del enemigo en pantalla
	int maxEnemigo;
	int puntosPorEnemigo;
	int puntos;
	int vidasMax;
	int vidaActual;
	int eliminaciones;
	float spawnTime;
	bool mouseHeld; //Chequeo del clic sostenido
	bool initialized;
	bool enemigoEliminado;


	//Funciones privadas
	void initWindow();
	void initSounds();
	void initCrosshair();
	void initEnemigo();
	void initVariables();
	void initText();
	void initFont();
	void initFondo();

public:

	//Constructores y destructores
	Game();
	virtual ~Game();

	//Accesors
	const bool running() const;
	const bool getEndGame() const;


	//Funciones
	void spawnEnemigo();
	void pollEvents();

	void updateEnemigos();
	void updateMousePosition();
	void updateText();
	void update();

	void renderCrosshair();
	void renderEnemigo();
	void renderFondo();
	void render();



};

