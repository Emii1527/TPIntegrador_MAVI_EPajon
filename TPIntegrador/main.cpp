
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Menu.h"
#include "Game.h"

using namespace sf;
using namespace std;

int main() {

	RenderWindow MENU(VideoMode(800, 600), "Main Menu", Style::Titlebar | sf::Style::Close);
	Menu menu(MENU.getSize().x, MENU.getSize().y);

	//Main Menu fondo
	RectangleShape background;
	Texture mainTexture;

	background.setSize(Vector2f(800, 600));
	mainTexture.loadFromFile("apartados/mainMenu.jpg");
	background.setTexture(&mainTexture);

	//Credits fondo
	RectangleShape creditsBG;
	Texture t_creditsBG;

	creditsBG.setSize(Vector2f(800, 600));
	t_creditsBG.loadFromFile("apartados/credits.jpg");
	creditsBG.setTexture(&t_creditsBG);

	//Sonidos menu
	Music bgMenu;

	bgMenu.openFromFile("BGMgame.ogg");

	if(bgMenu.openFromFile("BGMgame.ogg")) {
		std::cerr << "Error al cargar el archivo: sounds/BGMgame.wav\n";
	}

	bgMenu.play();
	bgMenu.setLoop(true);
	bgMenu.setVolume(50);

	bool inGame = false;
	Game* game = nullptr;

	//Loop
	while (MENU.isOpen())
	{
		Event evt;

		while (MENU.pollEvent(evt))
		{
			if (evt.type == Event::Closed)
			{
				MENU.close();
			}

		}

		//Logica del menú
		if (!inGame && evt.type == sf::Event::MouseButtonReleased && evt.mouseButton.button == sf::Mouse::Left)
		{

			if (menu.MainMenuPressed() == 0) {
				std::cout << "Play seleccionado" << std::endl;

				//Entro al juego
				if (menu.MainMenuPressed() == 0) {
					inGame = true;
					game = new Game();
					bgMenu.stop();
				}
				else if (menu.MainMenuPressed() == 3) {

					MENU.close();
				}

			}

			//Entro a Credits
			if (menu.MainMenuPressed() == 1) {
				std::cout << "Credits seleccionado" << std::endl;

				RenderWindow Credits(VideoMode(800, 600), "Options");

				while (Credits.isOpen())
				{
					Event aevt;
					while (Credits.pollEvent(aevt)) {
						if (aevt.type == Event::Closed ||
							(aevt.type == Event::KeyPressed && aevt.key.code == Keyboard::Escape))
						{
							Credits.close();
						}
					}
					Credits.clear();
					Credits.draw(creditsBG);
					Credits.display();
				}

			}

			//Entro a Exit
			if (menu.MainMenuPressed() == 2) {
				std::cout << "Cierre del juego" << std::endl;
				MENU.close();
			}
		}

		    //In Game
			if (inGame) {

				//El juego se ejecuta
				if (game->running()) {

					game->update();
					game->render();

				}
				else {

					//Limpieza al  terminar
					inGame = false;
					delete game;
					game = nullptr;
					bgMenu.play();
				}
			}
			else {

				menu.processMouseEvents(MENU);
				MENU.clear();
				MENU.draw(background);
				menu.draw(MENU);
				MENU.display();
			}

		}

	return 0;
}

