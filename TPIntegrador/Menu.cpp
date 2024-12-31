#include "Menu.h"


Menu::Menu(float width, float height)
{
	MainMenuSelected = 0; // Para inicializar MainMenuSelected

	if (!font.loadFromFile("Fonts/Jaro-Regular-VariableFont_opsz.ttf")) {
		cout << "No hay fuente cargada" << endl;
	}

	mainMenu[0].setFont(font);
	mainMenu[0].setFillColor(sf::Color::Blue);
	mainMenu[0].setString("Play");
	mainMenu[0].setCharacterSize(60);
	mainMenu[0].setPosition(500, 275);

	mainMenu[1].setFont(font);
	mainMenu[1].setFillColor(sf::Color::White);
	mainMenu[1].setString("Credits");
	mainMenu[1].setCharacterSize(60);
	mainMenu[1].setPosition(500, 350);

	mainMenu[2].setFont(font);
	mainMenu[2].setFillColor(sf::Color::White);
	mainMenu[2].setString("Exit");
	mainMenu[2].setCharacterSize(60);
	mainMenu[2].setPosition(500, 425);
}



void Menu::draw(sf::RenderWindow& window)
{
	
	for (int i = 0; i < Max_main_menu; i++) {
		window.draw(mainMenu[i]);
	}

}


void Menu::MoveUp()
{
	if (MainMenuSelected - 1 >= 0) {

		mainMenu[MainMenuSelected].setFillColor(sf::Color::White);

		MainMenuSelected--;

		mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue);
	}
}

void Menu::MoveDown()
{
	if (MainMenuSelected + 1 <= Max_main_menu) {
		mainMenu[MainMenuSelected].setFillColor(sf::Color::White);

		MainMenuSelected++;
		mainMenu[MainMenuSelected].setFillColor(sf::Color::Blue);
	}
}

void Menu::processMouseEvents(sf::RenderWindow& window)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePos);

	//Resaltado de apartados al utilizar mouse
	for (int i = 0; i < Max_main_menu; i++) {
		if (mainMenu[i].getGlobalBounds().contains(mouseWorldPos)) {
			mainMenu[i].setFillColor(sf::Color::Blue); // Resalto opción
			MainMenuSelected = i; // Se actualiza la selección
		}
		else {
			mainMenu[i].setFillColor(sf::Color::Black); // Se quita resaltado
		}
	}

}

void Menu::initSonidosmenu()
{

	this->bgMenu.openFromFile("BGMgame.ogg");


	if (!this->bgMenu.openFromFile("BGMgame.ogg")) {
		std::cerr << "Error al cargar el archivo: sounds/BGMgame.wav\n";
	}


	this->bgMenu.play();
	this->bgMenu.setLoop(true);
	this->bgMenu.setVolume(50);

}


Menu::~Menu()
{
}


