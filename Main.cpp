// SFMla aa.cpp : Defines the entry point for the console application.
//

#include "SFML/Graphics.hpp"
#include <iostream>
#include<cstdlib>
using namespace sf;
using namespace std;

int main(int argc, char** argb) //sorrry 4 the mess
{
	RenderWindow window(VideoMode(800, 800), "Gold Digging!!!!");
	window.clear(sf::Color(255,0,0));
	bool Up = false, Down = false, Left = false, Right = false;
	Vector2f movement(0, 0);
	int score = 0;
	int collided = 0;

	Texture LlamaTexture,SwapnaTexture,HeartTexture;
	sf::Text ScoreText;

	LlamaTexture.loadFromFile("Textures/pinarayi.png");
	SwapnaTexture.loadFromFile("Textures/swapna.png");
	HeartTexture.loadFromFile("Textures/gold.png");
	sf::Font font;
	font.loadFromFile("gamefont.ttf");

	CircleShape Llama(40),Swapna(30),Heart(20),Score(20);
	Llama.setOutlineThickness(5);
	Llama.setOutlineColor(sf::Color(250, 150, 100));
	Swapna.setOutlineThickness(5);
	Swapna.setOutlineColor(sf::Color(250, 150, 100));

	//Llama.setOrigin(sf::Vector2f(50,50));
	Llama.setTexture(&LlamaTexture);

	//Swapna.setOrigin(sf::Vector2f(100,100));
	Swapna.setTexture(&SwapnaTexture);
	Heart.setTexture(&HeartTexture);
	Score.setTexture(&HeartTexture);

	srand((unsigned) time(NULL));

	int random = 100 + (rand() % window.getSize().x-50);
	Swapna.setPosition(random,0.f);

	IntRect LlamaFrame[6];
	Clock clock;
	float timer;
	while (window.isOpen()) {
		Event event;
		timer = clock.getElapsedTime().asMilliseconds();
		if (timer > 10){
			float movex,movey;
			//movex = Swapna.getPosition().x+0.1f;
			movey = Swapna.getPosition().y+0.1f;

			if (movex > 0.4f || movey > 0.4f){
				//movex = 0.4f;
				movey = 0.4f;
			}
			Swapna.move(movex,movey);
			clock.restart();
		}
		
		if (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::Up) {
					Up = true;
				}
				if (event.key.code == Keyboard::Left) {
					Left = true;
				}
				if (event.key.code == Keyboard::Down) {
					Down = true;
				}
				if (event.key.code == Keyboard::Right) {
					Right = true;
				}
			}
			if (event.type == Event::KeyReleased) {
				if (event.key.code == Keyboard::Up) {
					Up = false;
				}
				if (event.key.code == Keyboard::Left) {
					Left = false;
				}
				if (event.key.code == Keyboard::Down) {
					Down = false;
				}
				if (event.key.code == Keyboard::Right) {
					Right = false;
				}
			}

		}
		if (Up) {
			movement.y -= 0.1;
		}
		if (Down) {
			movement.y += 0.1;
		}
		if (Left) {
			movement.x -= 0.1;
		}
		if (Right) {
			movement.x += 0.1;
		}


		// if (movement.x > 0.4f || movement.y > 0.4f) {
		// 	movement.x = 0.4f;
		// 	movement.y = 0.4f;
		// }
		window.clear(sf::Color(255,0,0));
		if (Llama.getGlobalBounds().intersects(Swapna.getGlobalBounds())){
			Heart.setPosition(Swapna.getPosition().x-40,Swapna.getPosition().y-30);
			window.draw(Heart);
			if (!collided){
				score++;
				collided = 1;
			}
			// std::cout<< "collosion" << std::endl;
		}else{
			if (collided){
				int random = 80 + (rand() % window.getSize().x-100);
				Swapna.setPosition(random,0.f);
				collided = 0;
			}
			
		}
		
		//window.draw(ract);
		Score.setPosition(window.getSize().x-150,window.getSize().y-100);
		ScoreText.setString("Score: " + std::to_string(score));
		ScoreText.setPosition(window.getSize().x-100,window.getSize().y-100);
		ScoreText.setFont(font);

		Llama.move(movement);
		window.draw(Swapna);
		window.draw(Llama);
		window.draw(Score);
		window.draw(ScoreText);

		window.display();
		movement = sf::Vector2f(0, 0);
		if (Swapna.getPosition().y > window.getSize().y){
			srand((unsigned) time(NULL));
			int random = 80 + (rand() % window.getSize().x-100);
			Swapna.setPosition(random,0.f);
		}
	}
}

