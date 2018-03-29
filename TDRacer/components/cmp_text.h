#pragma once

#include <SFML/Graphics/Text.hpp>
#include <ecm.h>

class TextComponent : public Component {
public:
	TextComponent() = delete;
	explicit TextComponent(Entity* p, const std::string& str = "");
	void update(double dt) override;

	void render() override;

	~TextComponent() override = default;

	void SetText(const std::string& str);

	void setPos(float x, float y, float size);

	void setColor(int a, int b, int c, int d);

protected:
	std::shared_ptr<sf::Font> _font;
	std::string _string;
	sf::Text _text;
};
