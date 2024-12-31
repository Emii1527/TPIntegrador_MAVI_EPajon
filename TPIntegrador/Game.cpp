#include "Game.h"
#include "Menu.h"
#include <windows.h>

using namespace sf;
using namespace std;

void Game::initVariables()
{
	//Declaro variables
	this->endGame = false;
	this->enemyIndex = 0;
	this->maxEnemigo = 5;
	this->enemigoEliminado = true;
	this->spawnTime = 1.0f;
	this->initialized = false;
	this->mouseHeld = false;
	this->puntos = 0;
	this->vidasMax = 3;
	this->vidaActual = vidasMax;
	this->puntosPorEnemigo = 0;
	this->eliminaciones = 0;

}


void Game::initWindow()
{

	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "Niamii", sf::Style::Titlebar | sf::Style::Close );

	this->window->setMouseCursorVisible(false);

	this->window->setFramerateLimit(60);


}

void Game::initSounds()
{
	this->sBuffer.loadFromFile("frogSound.wav");
	this->rana.setBuffer(sBuffer);

	this->sBufferGO.loadFromFile("gameOver.wav");
	this->gameOverSound.setBuffer(sBufferGO);

	this->sBufferYWin.loadFromFile("youWin.wav");
	this->youWinSound.setBuffer(sBufferYWin);

	this->bgM.openFromFile("BGMgame.ogg");

	if (!this->sBuffer.loadFromFile("frogSound.wav")) {
		std::cerr << "Error al cargar el archivo: sounds/frogSound.wav\n";
	}
	if (!this->bgM.openFromFile("BGMgame.ogg")) {
		std::cerr << "Error al cargar el archivo: sounds/BGMgame.wav\n";
	}

	if (!this->sBufferGO.loadFromFile("gameOver.wav")) {
		std::cerr << "Error al cargar el archivo: gameOver.wav\n";
	}

	if (!this->sBufferYWin.loadFromFile("youWin.wav")) {
		std::cerr << "Error al cargar el archivo: youWin.wav\n";
	}
	
		this->bgM.play();
		this->bgM.setLoop(true);
		this->bgM.setVolume(50);
	
}


void Game::initCrosshair()
{
	this->t_crosshair.loadFromFile("crosshair.png");
	this->s_crosshair.setTexture(t_crosshair);

	this->s_crosshair.setPosition(0,0);
}

void Game::initText()
{
	this->uiText.setFont(this->font);
	this->uiText.setCharacterSize(30);
	this->uiText.setPosition(10.f, 10.f);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setOutlineColor(sf::Color::Black);
	this->uiText.setOutlineThickness(3);
	this->uiText.setString("NONE");
}

void Game::initFont()
{
	if (!this->font.loadFromFile("Fonts/Jaro-Regular-VariableFont_opsz.ttf")) {
		std::cerr << "Error al cargar la fuente\n";
	}
}

void Game::initFondo()
{
	//Genero sprite de vidas
	this->t_vidas.loadFromFile("vidas.png");
	this->s_vidas.setTexture(t_vidas);
	this->s_vidas.setScale(sf::Vector2f(0.1f, 0.1f));

	for (int i = 0; i < vidasMax; ++i) {
		this->s_vidas.setPosition(640.f + i * 50.0f, 20.0f);
		this->vidasSprites.push_back(s_vidas);
	}

	//Genero sprite de fondo
	this->t_fondo.loadFromFile("fondo.jpg");
	this->s_fondo.setTexture(t_fondo);
	this->s_fondo.setPosition(0,0);

	//feedback
	this->t_gameOver.loadFromFile("GameOver.png");
	this->s_gameOver.setTexture(t_gameOver);
	this->s_gameOver.setPosition(230,175);

	this->t_win.loadFromFile("YouWin.png");
	this->s_win.setTexture(t_win);
	this->s_win.setPosition(230, 175);
}

void Game::initEnemigo()
{

	//cargo texturas personajes
	this->t_mosquito.loadFromFile("Mosquita.png");
	this->t_soldadito.loadFromFile("soldadito.png");
	this->t_gusano.loadFromFile("gusano.png");
	this->t_arania.loadFromFile("arania.png");
	this->t_mariquita.loadFromFile("mariquita.png");
	this->t_petardo.loadFromFile("petardo.png");

	//Genero sprites
	this->s_mosquito.setTexture(t_mosquito);
	this->s_soldadito.setTexture(t_soldadito);
	this->s_gusano.setTexture(t_gusano);
	this->s_arania.setTexture(t_arania);
	this->s_mariquita.setTexture(t_mariquita);
	this->s_petardo.setTexture(t_petardo);

	//Escalo
	this->s_mosquito.setScale(sf::Vector2f(0.25f, 0.25f));
	this->s_soldadito.setScale(sf::Vector2f(0.3f, 0.3f));
	this->s_gusano.setScale(sf::Vector2f(0.25f, 0.25f));
	this->s_arania.setScale(sf::Vector2f(0.25f, 0.25f));
	this->s_mariquita.setScale(sf::Vector2f(0.25f, 0.25f));
	this->s_petardo.setScale(sf::Vector2f(0.25f, 0.25f));

	//Posicion inicial de los personajes
	this->s_mosquito.setPosition(-100, -100); //Coloco los sprites fuera de la pantalla para ir utilizandolos
	this->s_soldadito.setPosition(-100, -100);
	this->s_gusano.setPosition(-100, -100);
	this->s_arania.setPosition(-100, -100);
	this->s_mariquita.setPosition(-100, -100);
	this->s_petardo.setPosition(-100, -100);


}



Game::Game()
{
	this->initWindow();

	this->initSounds();

	this->initVariables();

	this->initText();

	this->initFont();

	this->initCrosshair();

	this->initEnemigo();

	this->initFondo();
}

Game::~Game()
{
	delete this->window;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}


void Game::spawnEnemigo()
{

	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(posiciones.begin(), posiciones.end(), g);

	// Asignar posiciones a los sprites
	for (size_t i = 0; i < this->sprites.size(); ++i) {
		this->sprites[i]->setPosition(posiciones[i]);
	}


}

void Game::pollEvents()
{

	while (this->window->pollEvent(this->evt)) 

	switch (this->evt.type)
	{
	case sf::Event::Closed:
		this->window->close();
		break;

	case sf::Event::KeyPressed:
		if (this->evt.key.code == sf::Keyboard::Escape)
		this->window->close();
		break;

	}
}


void Game::updateEnemigos()
{
	
	//verifico si el tiempo del enemigo actual termino y lo muevo fuera del area visible 
	if (!initialized || this->relojEnemigo.getElapsedTime().asSeconds() >= this->spawnTime) {

		//Verifico que un sprite "buenos" haya salido de pantalla sin dar clic
		if ((this->sprites[this->enemyIndex])->getPosition() != sf::Vector2f(-100.f, -100.f))
			if (this->enemigoBueno[this->enemyIndex]) {
				this->vidaActual--;
			}

		this->sprites[this->enemyIndex]->setPosition(-100.f, -100.f);

		//Seleccionamos otro enemigo al azar y le asignamos un lugar
		this->enemyIndex = rand() % this->sprites.size();

		this->posiciones = {
		{170.f,175.f},{610.f,175.f},
		{170.f,350.f},{610.f,350.f},
		{380.f,300.f}
		};

		this->nuevaPosicion = posiciones[rand() % this->posiciones.size()]; 

		FloatRect currBounds = this->sprites[this->enemyIndex]->getGlobalBounds(); //Transformo y doy tamaño a todos sprites del vector para poder trabajar con medidas x e y

		this->nuevaPosicion.x = this->nuevaPosicion.x - (currBounds.width / 2); //Resto a la distancia "x" de "nuevaPosicion" la mitad del sprite sorteado por el random 
		this->nuevaPosicion.y = this->nuevaPosicion.y - (currBounds.height / 2); //Hago lo mismo con la distancia "y" de "nuevaPosicion"

		this->sprites[this->enemyIndex]->setPosition(nuevaPosicion);

		std::cout << "Posicion X: " << nuevaPosicion.x << endl;
		std::cout << "Posicion Y: " << nuevaPosicion.y << endl;

		//Reinicio el reloj
		this->relojEnemigo.restart();
		initialized = true;
	}

	//Condiciones de Derrota y Victoria
	if (vidaActual <= 0) {
		this->initialized = false;
		this->gameOverSound.play();
		this->endGame = true;

	}

	if (puntos >= 500) {
		this->initialized = false;
		this->youWinSound.play();
		this->endGame = true;
	}


	//Eliminacion de enemigos por clic

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
	
		if (!this->mouseHeld) {

			this->mouseHeld = true;

			for (size_t i = 0; i < this->sprites.size(); i++) {

				if (this->sprites[i]->getGlobalBounds().contains(this->mousePosView)) {

		
					//En vez de "borrar" y para evitar conflictos, muevo el sprite fuera de pantalla
					this->sprites[i]->setPosition(-100.f, -100.f);


					//Alternativa  switch para puntos por tipo de enemigos
					switch (i) {

					case 0:
						this->eliminaciones++;
						this->rana.play();
						this->puntos += puntosPorEnemigo = 10;
						std::cout << "Mosquito: " << eliminaciones << endl;
						break;

					case 1:
						this->vidaActual--;
						this->rana.play();
						this->puntos -= puntosPorEnemigo = 5;
						std::cout << "Wakala: " << vidaActual << endl;
						break;

					case 2:
						this->eliminaciones++;
						this->rana.play();
						this->puntos += puntosPorEnemigo = 20;
						std::cout << "Gusano: " << eliminaciones << endl;
						break;

					case 3:
						this->eliminaciones++;
						this->rana.play();
						this->puntos += puntosPorEnemigo = 50; 
						std::cout << "Arania: " << eliminaciones << endl;
						break;

					case 4:
						this->eliminaciones++;
						this->rana.play();
						this->puntos += puntosPorEnemigo = 30;
						std::cout << "Mariquita: " << eliminaciones << endl;
						break;

					case 5:
						this->vidaActual--;
						this->rana.play();
						this->puntos -= puntosPorEnemigo = 10;
						std::cout << "Wakala: " << vidaActual << endl;
						break;

					default:
						break;
					}

				}

			}

		}
		else 
		{
			this->mouseHeld = false;
		}
	}
}

void Game::updateMousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText()
{
	std::stringstream ss;

	ss << "Score: " << this->puntos << "\n";

	this->uiText.setString(ss.str());
}


void Game::renderCrosshair()
{
	//Posición del mouse actual
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);

	//Actualización de posición de la mira en "x" e "y" 
	this->s_crosshair.setPosition(static_cast<float>(mousePosWindow.x), static_cast<float>(mousePosWindow.y));

	//Dibujo la mira
	this->window->draw(this->s_crosshair);
}

void Game::renderEnemigo()
{

	for (auto sprite : this->sprites) {

			(*this->window).draw(*sprite);
	}

}

void Game::renderFondo()
{
	
	(*this->window).draw(s_fondo);

	//Mecanismo de vidas
	for (int i = 0; i < vidaActual; i++) {
		(*this->window).draw(vidasSprites[i]);
	}

	//Feedback Derrota y Victoria
	if (vidaActual <= 0)
	{
		(*this->window).draw(s_gameOver);
		this->bgM.stop();
	
	}

	if (puntos >= 500)
	{
		(*this->window).draw(s_win);
		this->bgM.stop();
	}
}

void Game::update()
{
	
	this->pollEvents();

	if (this->endGame == false)
	{
		this->updateMousePosition();
		this->updateText();
		this->updateEnemigos();
	}

}

void Game::render()
{
	
	//Renovar la info
	this->window->clear();

	//Dibujo objetos de juego
	this->renderFondo();

	if (initialized)
		this->renderEnemigo();
	
	this->renderCrosshair();

	this->window->draw(this->uiText);

	//Mostrar al usuario, siempre va a lo ultimo
	this->window->display();
}
