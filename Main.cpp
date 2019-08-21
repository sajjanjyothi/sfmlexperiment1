// SFMla aa.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SFML/Graphics.hpp"
using namespace sf;

int main(int argc, char** argb) //sorrry 4 the mess
{
	RenderWindow window(VideoMode(800, 800), "Gaboop");

	bool Up = false, Down = false, Left = false, Right = false;
	Vector2f movement(0, 0);

	Texture LlamaTexture;
	LlamaTexture.loadFromFile("Textures/llama.png");
	Sprite Llama;
	Llama.setOrigin(sf::Vector2f(48, 48));
	Llama.setTexture(LlamaTexture);
	IntRect LlamaFrame[6];
	Clock clock;
	float timer;
	int imgCount = 0;
	for (int i = 0; i < 6; i++) {
		LlamaFrame[i] = IntRect(0, 96 * i, 96, 96);
	}
	Llama.setTextureRect(LlamaFrame[0]);

	while (window.isOpen()) {
		Event event;
		timer = clock.getElapsedTime().asMilliseconds();
		if (timer > 83.f) {
			if (Up || Down || Left || Right) {
				if (imgCount >= 5) {
					imgCount = 0;
				}
				else {
					imgCount++;
					Llama.setTextureRect(LlamaFrame[imgCount]);
				}
				clock.restart();
			}
			else {
				imgCount = 0;
				Llama.setTextureRect(LlamaFrame[0]);
			}
		}
		
		if (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
			if (event.type == Event::KeyPressed) {
				if (event.key.code == Keyboard::W) {
					Up = true;
				}
				if (event.key.code == Keyboard::A) {
					Left = true;
				}
				if (event.key.code == Keyboard::S) {
					Down = true;
				}
				if (event.key.code == Keyboard::D) {
					Right = true;
				}
			}
			if (event.type == Event::KeyReleased) {
				if (event.key.code == Keyboard::W) {
					Up = false;
				}
				if (event.key.code == Keyboard::A) {
					Left = false;
				}
				if (event.key.code == Keyboard::S) {
					Down = false;
				}
				if (event.key.code == Keyboard::D) {
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
			Llama.setScale(sf::Vector2f(-1.f, 1.f));
		}
		if (Right) {
			movement.x += 0.1;
			Llama.setScale(sf::Vector2f(1.f, 1.f));
		}
		if (movement.x > 0.4f || movement.y > 0.4f) {
			movement.x = 0.4f;
			movement.y = 0.4f;
		}

		window.clear();
		//window.draw(ract);
		Llama.move(movement);
		window.draw(Llama);
		window.display();
		movement = sf::Vector2f(0, 0);
	}
}

