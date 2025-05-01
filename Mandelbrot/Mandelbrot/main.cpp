#include <SFML/Graphics.hpp>
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
    if (!font.loadFromFile("times.ttf")) {
        cerr << "Failed to load font!" << endl;
        return -1;
    }

    Text Instructions("", font, 24);
    Instructions.setPosition(20, 20);
    Instructions.setFillColor(Color::White);

    Event event;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == Mouse::Left)
                {
                    Mandelbrot.setCenter({ event.mouseButton.x, event.mouseButton.y });
                    Mandelbrot.zoomIn();
                }
                else if (event.mouseButton.button == Mouse::Right)
                {
                    
                    Mandelbrot.setCenter({ event.mouseButton.x, event.mouseButton.y });
                    Mandelbrot.zoomOut();
                }
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            {
                window.close();
            }
        }

        Mandelbrot.setMouseLocation(Mouse::getPosition(window));

        Mandelbrot.updateRender();
        Mandelbrot.loadText(Instructions);

        window.clear();
        window.draw(Mandelbrot);
        window.draw(Instructions);
        window.display();
    }

    return 0;
}
