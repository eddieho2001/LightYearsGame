#include<iostream>
#include<SFML/Graphics.hpp>

#include  "framework/Game.h"
//There are the 0.0.1 version of game -- everything in main function
int main(){
	/*
	sf::RenderWindow window(sf::VideoMode(640, 480), "SFML Application");
	sf::CircleShape shape;
	shape.setRadius(40.f);
	shape.setPosition(100.f, 100.f);
	shape.setFillColor(sf::Color::Cyan);
	while(window.isOpen()) {
		sf::Event evt;
		while (window.pollEvent(evt)) {
			if (evt.type == sf::Event::Closed) {
				window.close();
			}
		}

		window.clear();
		window.draw(shape);
		window.display();
	}
	*/
	Game game;
	game.run();

	return 0;
}