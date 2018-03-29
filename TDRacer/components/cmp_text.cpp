#include "cmp_text.h"
#include <system_renderer.h>
#include <system_resources.h>
#include "engine.h"

#include <iostream>

void TextComponent::update(double dt) {

	

			//works but f's up keyboard with keyboard input
			//case sf::Event::MouseMoved:
			//{
			//	if (menu[0].getGlobalBounds().contains(mousePosF)) {
			//		menu[0].setFillColor(sf::Color(255, 0, 0, 255));
			//		menu[1].setFillColor(sf::Color(255, 255, 255, 255));
			//		menu[2].setFillColor(sf::Color(255, 255, 255, 255));
			//		menu[3].setFillColor(sf::Color(255, 255, 255, 255));
			//		selectedItemIndex = 0;
			//	}

			//	if (menu[1].getGlobalBounds().contains(mousePosF)) {
			//		menu[1].setFillColor(sf::Color(255, 0, 0, 255));
			//		menu[0].setFillColor(sf::Color(255, 255, 255, 255));
			//		menu[2].setFillColor(sf::Color(255, 255, 255, 255));
			//		menu[3].setFillColor(sf::Color(255, 255, 255, 255));
			//		selectedItemIndex = 1;
			//	}

			//	if (menu[2].getGlobalBounds().contains(mousePosF)) {
			//		menu[2].setFillColor(sf::Color(255, 0, 0, 255));
			//		menu[0].setFillColor(sf::Color(255, 255, 255, 255));
			//		menu[1].setFillColor(sf::Color(255, 255, 255, 255));
			//		menu[3].setFillColor(sf::Color(255, 255, 255, 255));
			//		selectedItemIndex = 2;
			//	}

			//	if (menu[3].getGlobalBounds().contains(mousePosF)) {
			//		menu[3].setFillColor(sf::Color(255, 0, 0, 255));
			//		menu[0].setFillColor(sf::Color(255, 255, 255, 255));
			//		menu[1].setFillColor(sf::Color(255, 255, 255, 255));
			//		menu[2].setFillColor(sf::Color(255, 255, 255, 255));
			//		selectedItemIndex = 3;
			//	}
			//	break;
			//	
			//	case sf::Event::MouseButtonPressed:
			//	{

			//		if (menu[0].getGlobalBounds().contains(mousePosF))
			//		{
			//			std::cout << "Clicked single player, yay!" << std::endl;

			//			sf::RenderWindow gameWindow(sf::VideoMode(900, 900), "TD Championship Racer ");

			//			while (true)
			//			{
			//			window.close();
			//			gameScreen.draw(gameWindow);
			//			}
			//		}

			//		else if (menu[1].getGlobalBounds().contains(mousePosF))
			//		{
			//			std::cout << "Clicked multiplayer, yay!" << std::endl;
			//		}

			//		else if (menu[2].getGlobalBounds().contains(mousePosF))
			//		{
			//		std::cout << "Clicked options, yay!" << std::endl;
			//		}

			//		else if (menu[3].getGlobalBounds().contains(mousePosF))
			//		{
			//		window.close();
			//		}
			//	}//case sf::Event::MouseButtonPressed:

			//}
	





	_text.setFillColor(sf::Color(255, 255, 255, 255));
}

void TextComponent::MoveUp() {

	//used for keyboard movement in menus
	if (selectedItemIndex - 1 >= 0) {
		std::cout << "Moved Up" << std::endl;
		//menu[selectedItemIndex].setFillColor(sf::Color(255, 255, 255, 255));
		selectedItemIndex--;
		//menu[selectedItemIndex].setFillColor(sf::Color(255, 0, 0, 255));
	}
}

void TextComponent::MoveDown() {

	//used for keyboard movement in menus
	if (selectedItemIndex + 1 >= 0) {
		std::cout << "Moved Down" << std::endl;
		//menu[selectedItemIndex].setFillColor(sf::Color(255, 255, 255, 255));
		selectedItemIndex++;
		//menu[selectedItemIndex].setFillColor(sf::Color(255, 0, 0, 255));
	}
}


void TextComponent::render() { Renderer::queue(&_text); }

TextComponent::TextComponent(Entity* const p, const std::string& str)
	: Component(p), _string(str) {
	_text.setString(_string);
	_font = Resources::get<sf::Font>("XpressiveBlack Regular.ttf");
	_text.setFont(*_font);
}

void TextComponent::SetText(const std::string& str) {
	_string = str;
	_text.setString(_string);
}


//added by craig sets position
void TextComponent::setPos(float xPos, float yPos, float size)
{
	_text.setPosition(xPos, yPos);
	_text.setCharacterSize(size);
}

//added by craig sets color
void TextComponent::setColor(int a, int b, int c, int d)
{
	_text.setFillColor(sf::Color(a, b, c, d));
}

