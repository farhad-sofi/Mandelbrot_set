#include <SFML/Graphics.hpp>
#include <iostream>
#include "ComplexPlane.h"


using namespace sf;
using namespace std;


int main()
{
	int pixelWidth = VideoMode::getDesktopMode().width / 2;
	int pixelHeight = VideoMode::getDesktopMode().height / 2;
	VideoMode vm(pixelWidth, pixelHeight);
	RenderWindow window(vm, "Mandelbrot Set", Style::Default);

	ComplexPlane Mandelbrot(pixelWidth, pixelHeight);
	
	Font font;
	font.loadFromFile("times.ttf");

	Text Instructions("", font, 24);
	Instructions.setPosition(20, 20);
	Instructions.setFillColor(Color::White);

	Event event;

	while (window.pollEvent(event))
	{
		///Input
		if (event.type == event.Closed) window.close();

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				Mandelbrot.setCenter({ event.mouseButton.x, event.mouseButton.y });
				Mandelbrot.zoomIn();
			}
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				Mandelbrot.setCenter({ event.mouseButton.x, event.mouseButton.y });
				Mandelbrot.zoomOut();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		Mandelbrot.updateRender(Instructions);
		Mandelbrot.loadText();

		window.clear();

		window.draw(Mandelbrot);
		window.draw(Text);

		window.display();

	}
