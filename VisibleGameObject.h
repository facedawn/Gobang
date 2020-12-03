#pragma once
#include <string>
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
class VisibleGameObject
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();

	virtual void Load(std::string filename);
	virtual void Draw(sf::RenderWindow& window);
	virtual void Update(float elapsedTime);

	virtual void SetPosition(float x, float y);
	virtual sf::Vector2f GetPosition()const;
	virtual bool IsLoaded()const;

	//��ȡ�������Ŀ�
	virtual float GetWidth() const;
	//��ȡ�������ĸ�
	virtual float GetHeight() const;
	//��ȡ�������ľ�������
	virtual sf::Rect<float> GetBoundingRect() const;

protected:
	sf::Sprite& GetSprite();

private:
	sf::Sprite _sprite;
	sf::Texture _image;
	std::string _filename;
	bool _isLoaded;
};