#pragma once

#include "ecm.h"
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <Box2D\Box2D.h>

class SpriteComponent : public Component {
protected:
	std::shared_ptr<sf::Sprite> _sprite;
	b2Body* body; //added
	b2BodyDef bodyDef; //added
public:
	SpriteComponent() = delete;

	explicit SpriteComponent(Entity* p);
	
	void setBody(); //added

	void update(double dt) override;
	void render() override;

	sf::Sprite& getSprite() const;

	template <typename... Targs> void setSprite(Targs... params) {
		_sprite.reset(new sf::Sprite(params...));
	}
};







class ShapeComponent : public Component {
protected:
	std::shared_ptr<sf::Shape> _shape;
	//sf::Shape _shape;

public:
	ShapeComponent() = delete;

	explicit ShapeComponent(Entity* p);

	void update(double dt) override;
	void render() override;
	sf::Shape& getShape() const;
	template <typename T, typename... Targs> void setShape(Targs... params) {
		_shape.reset(new T(params...));
	}
};