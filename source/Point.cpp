#include "Point.h"

void Point::initialization()
{
	PointItem playButton;
	int i, j;
	for (i = 0; i < 21; i++)
	{
		for (j = 0; j < 21; j++)
		{
			playButton.rect.left = 216+28*i;
			playButton.rect.height = 28;
			playButton.rect.top = 98+28*j;
			playButton.rect.width = 28;
			playButton.action = place;
			_pointItems.push_back(playButton);
		}
	}
	cnt = 0;
}

Point::PointResult Point::HandleClick(int x, int y)
{
	std::list<PointItem>::iterator it;
	for (it = _pointItems.begin(); it != _pointItems.end(); it++)
	{
		sf::Rect<int>pointItemRect = (*it).rect;
		if (pointItemRect.top + pointItemRect.height > y
			&& pointItemRect.top < y
			&& pointItemRect.left< x
			&& pointItemRect.left + pointItemRect.width>x)
		{
			return (*it).action;
		}
	}
	return Nothing;
}

Point::PointResult Point::GetPointResponse(sf::RenderWindow& window)
{
	sf::Event pointEvent;
	while (true)
	{
		while (window.pollEvent(pointEvent))
		{
			if (pointEvent.type == sf::Event::MouseButtonPressed)
			{
				return HandleClick(pointEvent.mouseButton.x, pointEvent.mouseButton.y);
			}
			if (pointEvent.type == sf::Event::Closed)
			{
				return Exit;
			}
		}
	}
}