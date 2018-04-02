#pragma once

#include <SFML/Graphics/Text.hpp>
#include <ecm.h>

class TextComponent : public Component {
public:
	TextComponent() = delete;
	explicit TextComponent(Entity* p, const std::string& str = "");
	void update(double dt) override;
	void render() override;
	int GetPressedItem() { return selectedItemIndex; } //added - sfa20

	~TextComponent() override = default;

	void SetText(const std::string& str);

	sf::Text GetText();

	void setCenterPos(float xPos, float yPos, float size);

	void setColor(int rgba1, int rgba2, int rgba3, int opacity);

	void fadeTxt();

private:
	int selectedItemIndex;

protected:
	std::shared_ptr<sf::Font> _font;
	std::string _string;
	sf::Text _text;
};
