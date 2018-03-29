#pragma once

#include <SFML/Graphics/Text.hpp>
#include <ecm.h>

class TextComponent : public Component {
public:
	TextComponent() = delete;
	explicit TextComponent(Entity* p, const std::string& str = "");
	void update(double dt) override;
	void MoveUp(); // added - sfa20
	void MoveDown();  // added - sfa20
	void render() override;
	int GetPressedItem() { return selectedItemIndex; } //added - sfa20

	~TextComponent() override = default;

	void SetText(const std::string& str);

	void setPos(float x, float y, float size);

	void setColor(int a, int b, int c, int d);

private:
	int selectedItemIndex;

protected:
	std::shared_ptr<sf::Font> _font;
	std::string _string;
	sf::Text _text;
};
