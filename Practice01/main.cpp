#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <stdio.h>
// #include <vector>

class NewShape
{
	private:
		sf::Vector2f speed;
		
	public:
		sf::Text label;

		void setSpeed(float X, float Y)
		{
			speed.x = X;
			speed.y = Y;
		}

		const sf::Vector2f & getSpeed()
		{
			return speed;
		}	
};

class NewCircle: public NewShape, public sf::CircleShape
{};

class NewRectangle: public NewShape, public sf::RectangleShape
{};



int main()
{
		int W, H;	//Width and Height of Window
		sf::RenderWindow window;
		sf::Font font;
		sf::Text text;
		std::vector<NewCircle> circles;
		std::vector<NewRectangle> rectangles;

		std::string textLine, firstWord;
		std::ifstream conf("config.txt");

		// Use a while loop together with the getline() function to read the file line by line
		while (getline (conf, textLine)) {
		  // Output the text from the file
			std::istringstream iss(textLine);

			// if line null just skip
			if (iss.rdbuf()->in_avail() == 0) continue;
			
			iss >> firstWord;

			if (firstWord == "Window")
			{
				iss >> W >> H;
				window.create(sf::VideoMode(W, H), "Practice 01");
				window.setFramerateLimit(60);
				std::cout << "Window created successfully\n";
			}
			else if (firstWord == "Font")
			{
				std::string F;
				int S, R, G, B;
				iss >> F >> S >> R >> G >> B;
				if (!font.loadFromFile(F))
				{
					// error...
					std::cerr << "Could not load font: " << F << "\n";
					exit(-1);
				}
				// select the font
				text.setFont(font); // font is a sf::Font
				
				// set the character size
				text.setCharacterSize(S); // in pixels, not points!
				text.setFillColor(sf::Color(R, G, B));

				std::cout << "Font loaded successfully\n";
			}
			else if (firstWord == "Circle")
			{
				std::string N;
				float X, Y, SX, SY;
				int R, G, B, r;		// r is radius

				iss >> N >> X >> Y >> SX >> SY >> R >> G >> B >> r;
				NewCircle circle;
				circle.label = text;
				circle.label.setString(N);
				circle.setPosition(X, Y);
				circle.setSpeed(SX, SY);
				circle.setFillColor(sf::Color(R, G, B));	
				circle.setRadius(r);

				//push to vector list
				circles.push_back(circle);
				std::cout << "Circle loaded successfully\n";
			}
			else if (firstWord == "Rectangle")
			{
				std::string N;
				float X, Y, SX, SY;
				int R, G, B, width, height;		// r is radius

				iss >> N >> X >> Y >> SX >> SY >> R >> G >> B >> width >> height;
				NewRectangle rectangle;
				rectangle.label = text;
				rectangle.label.setString(N);
				rectangle.setPosition(X, Y);
				rectangle.setSpeed(SX, SY);
				rectangle.setFillColor(sf::Color(R, G, B));	
				rectangle.setSize(sf::Vector2f(width, height));

				//push to vector list
				rectangles.push_back(rectangle);
				std::cout << "Rectangle loaded successfully\n";
			} 
			else
			{
				std::cerr << "Wrong config format, check again!\n";
				exit(-1);
			}


		}	

		for (auto &i : rectangles)
		{
			std::string name = i.label.getString();
			std::cout << name << "\n";
		}

		float direction = 1.0f;
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

							//if x is pressed the direction will change and speed up 2x 
							//if z is pressed the direction will change and slow down by 0.5x
							if (event.key.code == sf::Keyboard::X)
							{
								direction *= -2.0f;
							}
							if (event.key.code == sf::Keyboard::Z)
							{
								direction *= -0.5f;
							}
						}
        }

        window.clear();

				for (auto & rectangle : rectangles)
				{
				 	rectangle.setPosition(rectangle.getPosition().x + rectangle.getSpeed().x * direction, rectangle.getPosition().y + rectangle.getSpeed().y * direction);

					//if touch x edge of the window, rectangle will bounce
					if (rectangle.getPosition().x <= 0 || rectangle.getPosition().x + rectangle.getSize().x > window.getSize().x)
					{
						rectangle.setSpeed(rectangle.getSpeed().x * -1.0f, rectangle.getSpeed().y);
						std::string name = rectangle.label.getString();
						std::cout << name <<  " Collisioned x \n";
					} 
					// if touch y edge of the window, rectangle will bounce
					if (rectangle.getPosition().y <= 0 || rectangle.getPosition().y + rectangle.getSize().y > window.getSize().y)
					{
						rectangle.setSpeed(rectangle.getSpeed().x, rectangle.getSpeed().y * -1.0f);
						std::string name = rectangle.label.getString();
						std::cout << name <<  " Collisioned y \n";
					}

					//center text to rect
					auto text = rectangle.label;
					text.setOrigin(text.getGlobalBounds().getSize() / 2.f + text.getLocalBounds().getPosition());
					text.setPosition(rectangle.getPosition() + (rectangle.getSize() / 2.f));

					window.draw(rectangle);
					window.draw(text);
				}
			
				for (auto & circle : circles)
				{
				 	circle.setPosition(circle.getPosition().x + circle.getSpeed().x * direction, circle.getPosition().y + circle.getSpeed().y * direction);

					//if touch x edge of the window, rectangle will bounce
					if (circle.getPosition().x <= 0 || circle.getPosition().x + circle.getRadius()*2 > window.getSize().x)
					{
						circle.setSpeed(circle.getSpeed().x * -1.0f, circle.getSpeed().y);
						std::string name = circle.label.getString();
						std::cout << name <<  " Collisioned x \n";
					} 
					//if touch y edge of the window, rectangle will bounce
					if (circle.getPosition().y <= 0 || circle.getPosition().y + circle.getRadius()*2 > window.getSize().y)
					{
						circle.setSpeed(circle.getSpeed().x, circle.getSpeed().y * -1.0f);
						std::string name = circle.label.getString();
						std::cout << name <<  " Collisioned x \n";
					}

					//center text to rect
					auto text = circle.label;
					text.setOrigin(text.getGlobalBounds().getSize() / 2.f + text.getLocalBounds().getPosition());
					text.setPosition(circle.getPosition() + sf::Vector2f(circle.getRadius(), circle.getRadius()));

				 	window.draw(circle);
					window.draw(text);
				}

        window.display();
    }

    return 0;
}
