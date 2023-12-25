#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

int main()
{
		int wLength = 640;
		int wHeight = 480;
    sf::RenderWindow window(sf::VideoMode(wLength, wHeight), "SFML works!");
		window.setFramerateLimit(60);
    sf::CircleShape shape(50);

		int r = 0;
		int g = 255;
		int b = 255;

    shape.setFillColor(sf::Color(r,g,b));
		shape.setPosition(300.0f, 300.0f);
		float moveSpeed = 1.0f;

		sf::Font font;
		if (!font.loadFromFile("/home/ripa/.local/share/fonts/OpenSans-SemiBold.ttf"))
		{
				// error...
			std::cerr << "Could not load font!\n";
			exit(-1);
		}
		sf::Text text;

		// select the font
		text.setFont(font); // font is a sf::Font

		// set the string to display
		text.setString("Hello world");

		// set the character size
		text.setCharacterSize(24); // in pixels, not points!

		text.setPosition(0, wHeight - (float)text.getCharacterSize()); 

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

						if (event.type == sf::Event::KeyPressed)
						{
							std::cout << "Key pressed with code : " << event.key.code << "\n";

							//example if X is pressed
							if (event.key.code == sf::Keyboard::X)
							{
								moveSpeed *= -1.0f;
							}
						}
        }
				shape.setPosition(shape.getPosition().x + moveSpeed, shape.getPosition().y + moveSpeed);
				std::cout << "moveSpeed : " << moveSpeed << "\n";

        window.clear();
        window.draw(shape);
				window.draw(text);
        window.display();
    }

    return 0;
}
