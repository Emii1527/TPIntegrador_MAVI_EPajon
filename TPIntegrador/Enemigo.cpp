#include "Enemigo.h"


void Enemigo::initWindow()
{
	this->window = new RenderWindow;
}

void Enemigo::initEnemigo()
{
	//cargo texturas personajes
	this->t_mosquito.loadFromFile("Mosquita.png");
	this->t_hongo.loadFromFile("Honguito.png");
	this->t_gusano.loadFromFile("gusano.png");
	this->t_arania.loadFromFile("arania.png");
	this->t_mariquita.loadFromFile("mariquita.png");
	this->t_caramelo.loadFromFile("caramelo.png");

	//Genero sprites
	this->s_mosquito.setTexture(t_mosquito);
	this->s_hongo.setTexture(t_hongo);
	this->s_gusano.setTexture(t_gusano);
	this->s_arania.setTexture(t_arania);
	this->s_mariquita.setTexture(t_mariquita);
	this->s_caramelo.setTexture(t_caramelo);

	//Escalo
	this->s_mosquito.setScale(sf::Vector2f(0.25f, 0.25f));
	this->s_hongo.setScale(sf::Vector2f(0.25f, 0.25f));
	this->s_gusano.setScale(sf::Vector2f(0.25f, 0.25f));
	this->s_arania.setScale(sf::Vector2f(0.25f, 0.25f));
	this->s_mariquita.setScale(sf::Vector2f(0.25f, 0.25f));
	this->s_caramelo.setScale(sf::Vector2f(0.25f, 0.25f));

	//Posicion inicial de los personajes
	this->s_mosquito.setPosition(-100, -100); //Coloco los sprites fuera de la pantalla para ir utilizandolos
	this->s_hongo.setPosition(-100, -100);
	this->s_gusano.setPosition(-100, -100);
	this->s_arania.setPosition(-100, -100);
	this->s_mariquita.setPosition(-100, -100);
	this->s_caramelo.setPosition(-100, -100);


	/*
	this->sprites.push_back(&this->s_mosquito); //Por acá está el problema de que aparezca en la posición 0,0 en el inicio
	this->sprites.push_back(&this->s_hongo);
	this->sprites.push_back(&this->s_gusano);
	this->sprites.push_back(&this->s_arania);
	this->sprites.push_back(&this->s_mariquita);
	this->sprites.push_back(&this->s_caramelo);
	*/
}


Enemigo::Enemigo()
{
}

Enemigo::~Enemigo()
{

}



void Enemigo::update()
{

}


void Enemigo::render(RenderWindow *window)
{
	//window.draw(this->sprites);
}
