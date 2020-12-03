#include "stdafx.h"
#include "MainMenu.h"

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
	//Load menu image from file
	sf::Texture image;
	image.loadFromFile("images/mainmenu.png");
	sf::Sprite sprite(image);

	//Play menu item coordinates
	MenuItem playwithhumanButton;
	playwithhumanButton.rect.top = 145;
	playwithhumanButton.rect.height = 135;
	playwithhumanButton.rect.left = 0;
	playwithhumanButton.rect.width = 1023;
	playwithhumanButton.action = Play_with_human;
	_menuItems.push_back(playwithhumanButton);

	//Exit menu item coordinates
	MenuItem exitButton;
	exitButton.rect.left = 0;
	exitButton.rect.width = 1023;
	exitButton.rect.top = 383;
	exitButton.rect.height = 177;
	exitButton.action = Exit;
	_menuItems.push_back(exitButton);

	
	playwithhumanButton.rect.top = 271;
	playwithhumanButton.rect.height = 110;
	playwithhumanButton.rect.left = 0;
	playwithhumanButton.rect.width = 1023;
	playwithhumanButton.action = Play_with_AI;
	_menuItems.push_back(playwithhumanButton);
	
	
	window.draw(sprite);
	window.display();

	return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;
	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		sf::Rect<int>menuItemRect = (*it).rect;
		//printf("%d %d %d %d\n", menuItemRect.top, menuItemRect.height, menuItemRect.top+ menuItemRect.height, y);
		if (menuItemRect.top + menuItemRect.height > y
			&& menuItemRect.top < y
			&& menuItemRect.left< x
			&& menuItemRect.left + menuItemRect.width>x)
		{
			return (*it).action;
		}
	}
	return Nothing;
}

MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;
	while (true)
	{
		while (window.pollEvent(menuEvent))
		{
			if (menuEvent.type == sf::Event::MouseButtonPressed)
			{
				//printf("%d %d\n", menuEvent.mouseButton.x, menuEvent.mouseButton.y);
				return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			}
			if (menuEvent.type == sf::Event::Closed)
			{
				return Exit;
			}
		}
	}
}