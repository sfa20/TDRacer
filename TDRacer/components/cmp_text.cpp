#include "cmp_text.h"
#include <system_renderer.h>
#include <system_resources.h>
#include "engine.h"

#include <iostream>

void TextComponent::update(double dt) {}

//added by scott
sf::Text TextComponent::GetText() {
	return _text;
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
void TextComponent::setColor(int rgba1, int rgba2, int rgba3, int opacity)
{
	_text.setFillColor(sf::Color(rgba1, rgba2, rgba3, opacity));
}

