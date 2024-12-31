#pragma once

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <iostream>
#include <vector>
#include <ctime>
#include <iostream>

using namespace sf;
using namespace std;

#define Max_main_menu 3


class Menu
{
public:

	//Texturas y sprites
	sf::Texture t_fondoMenu;
	sf::Sprite s_fondoMenu;

	Font font;
	Text mainMenu[Max_main_menu];

	//Funciones
	Menu(float width, float height);

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void processMouseEvents(sf::RenderWindow& window);

	void initSonidosmenu();
	

	int MainMenuPressed() {
		return MainMenuSelected;
	}

	~Menu();

private:

	//Sonidos menu
	Music bgMenu;

	int MainMenuSelected;


};

