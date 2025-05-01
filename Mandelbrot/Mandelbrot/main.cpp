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

	Text title("Mandelbrot Set", font, 24);
	title.setPosition(20, 20);
	title.setFillColor(Color::White);

	Text mouseActions("", font, 24);
	mouseActions.setPosition(20, 40);
	mouseActions.setFillColor(Color::White);

	Mandelbrot.loadText(mouseActions);

	Text zoomOut("Zoom Out", font, 24);
	zoomOut.setPosition(20, 80);
	zoomOut.setFillColor(Color::White);

	Text zoomIn("Zoom In", font, 24);
	zoomIn.setPosition(20, 100);
	zoomIn.setFillColor(Color::White);

	Event event;

	while (window.pollEvent(event))
	{
		///Input
		if (event.type == event.Closed) window.close();

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				/*std::cout << "the left button was pressed" << std::endl;
				std::cout << "mouse x: " << event.mouseButton.x << std::endl;
				std::cout << "mouse y: " << event.mouseButton.y << std::endl; */
				Mandelbrot.setCenter({ event.mouseButton.x, event.mouseButton.y });
				Mandelbrot.zoomIn();
			}
			if (event.mouseButton.button == sf::Mouse::Right)
			{
				/*std::cout << "the left button was pressed" << std::endl;
				std::cout << "mouse x: " << event.mouseButton.x << std::endl;
				std::cout << "mouse y: " << event.mouseButton.y << std::endl; */
				Mandelbrot.setCenter({ event.mouseButton.x, event.mouseButton.y });
				Mandelbrot.zoomOut();
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		Mandelbrot.updateRender();
		Mandelbrot.loadText();

		window.clear();

		window.draw(Mandelbrot);
		window.draw(Text);

		window.display();

	}
