#include "Text.h"

using namespace std;

Text::Text(const Vector2& position, const std::string& text) :
	colour(0.0f, 0.0f, 0.0f, 1.0f),
	position(position),
	text(text),
	visible(true)
{
}

const Vector4& Text::getColour() const
{
	return colour;
}

Texture* Text::getNormalMap() const
{
	return NULL;
}

const Vector2& Text::getPosition() const
{
	return position;
}

Model::PrimitiveType Text::getPrimitiveType() const
{
	return NA;
}

const string& Text::getText() const
{
	return text;
}

Texture* Text::getTexture() const
{
	return NULL;
}

bool Text::isVisible() const
{
	return visible;
}

void Text::render(Renderer& renderer) const
{
	renderer.render(*this);
}

void Text::setColour(const Vector4& colour)
{
	this->colour = colour;
}

void Text::setNormalMap(Texture*)
{
}

void Text::setPosition(const Vector2& position)
{
	this->position = position;
}

void Text::setPrimitiveType(PrimitiveType)
{
}

void Text::setText(const std::string& text)
{
	this->text = text;
}

void Text::setTexture(Texture*)
{
}

void Text::setVisible(bool visible)
{
	this->visible = visible;
}
