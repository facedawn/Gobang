#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <list>
class Point
{
public:
	void initialization();
	enum PointResult { Nothing,Exit,place };
	struct PointItem
	{
	public:
		sf::Rect<int> rect;
		PointResult action;
	};
	PointResult GetPointResponse(sf::RenderWindow& window);
	std::list<PointItem> _pointItems;

	PointResult HandleClick(int x, int y);
	int po[25][25];
	int cnt;
};