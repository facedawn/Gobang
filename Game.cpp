#include "Game.h"
#include "SplashScreen.h"
#include <time.h>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>
void Game::Start()
{
	if (_gameState != Uninitialized)
		return;
	_mainWindow.create(sf::VideoMode(1024, 768, 32), "five");
	_gameState = Game::ShowingSplash;

	point.initialization();

	while (!IsExiting())
	{
		GameLoop();
		if (_gameState == Exiting)
			break;
	}
	_mainWindow.close();
}

bool Game::IsExiting()
{
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}

void Game::GameLoop()
{
	sf::Event currentEvent; 
	while (_mainWindow.pollEvent(currentEvent));
	{
		if (currentEvent.type==sf::Event::MouseButtonPressed)
		{
			printf("%d %d\n", currentEvent.mouseButton.x, currentEvent.mouseButton.y);
		}
		/*if (currentEvent.type == sf::Event::Closed)
		{
			_gameState = Exiting;printf("%d\n",_gameState);
		}*/
		
		switch (_gameState)
		{
		case Game::ShowingMenu:
		{
			ShowMenu();
			break;
		}
		case Game::ShowingSplash:
		{
			ShowSplashScreen();
			break;
		}
		case Game::Playing_with_AI:
		{
			point.cnt = 0;
			sf::Texture image;
			if (image.loadFromFile("images/checkerboard.jpg") != true)
			{
				return;
			}
			sf::Sprite sprite(image);
			_mainWindow.clear(sf::Color(0, 0, 0));
			_mainWindow.draw(sprite);
			_mainWindow.display();
			play_with_AI();
			break;
		}
		case Game::Playing_with_human:
		{
			point.cnt = 0;
			sf::Texture image;
			if (image.loadFromFile("images/checkerboard.jpg") != true)
			{
				return;
			}
			sf::Sprite sprite(image);
			_mainWindow.clear(sf::Color(0, 0, 0));
			_mainWindow.draw(sprite);
			_mainWindow.display();
			play_with_human();
			break;
		}
		case Game::Exiting:
		{

			return;
		}
		}
	}
}

void Game::play_with_AI()
{
	system("cls");
	printf("play with AI\n");
	sf::Event pointEvent;
	time_t now=time(NULL);
	Game::timerstart = now;
	
	while (true)
	{
		drawall();
		
		while (_mainWindow.pollEvent(pointEvent))
		{
			//drawall();
			if (pointEvent.type == sf::Event::MouseButtonPressed)
			{
				system("cls");
				printf("%d %d\n", pointEvent.mouseButton.x, pointEvent.mouseButton.y);

				int x = pointEvent.mouseButton.x; int y = pointEvent.mouseButton.y;

				std::list<Point::PointItem>::iterator it;
				for (it = point._pointItems.begin(); it != point._pointItems.end(); it++)
				{
					sf::Rect<int>pointItemRect = (*it).rect;
					if (pointItemRect.top + pointItemRect.height > y
						&& pointItemRect.top < y
						&& pointItemRect.left< x
						&& pointItemRect.left + pointItemRect.width>x)
					{
						if (point.cnt % 2 == 0)
						{
							if (point.po[(x - 216) / 28][(y - 98) / 28] == 0)
							{
								point.po[(x - 216) / 28][(y - 98) / 28] = 1;
								if (judge((x - 216) / 28, (y - 98) / 28) == 1)
									_gameState = BlackWin;
								point.cnt++;
							}
							AI();
							point.cnt++;
							Game::timerstart = time(NULL);
						}
						drawall();
						break;
					}
				}
			}
			if (pointEvent.type == sf::Event::Closed)
			{
				_gameState = Exiting;
			}
		}
		if (_gameState == BlackWin)
		{
			printf("Black Win\n");
			_gameState = Exiting;
		}
		if (_gameState == WhiteWin)
		{
			printf("White Win\n");

			_gameState = Exiting;
		}
		if (_gameState == Exiting)
		{
			time_t start = time(NULL);
			time_t end = time(NULL);
			while (true)
			{
				end = time(NULL);
				//printf("%d\n", end - start);
				if (end - start >= 3)
				{
					_gameState = ShowingMenu;
					break;
				}
			}
			break;
		}

	}

}

void Game::play_with_human()
{
	system("cls");
	printf("play with human\n");
	time_t now = time(NULL);
	Game::timerstart = now;
	sf::Event pointEvent;
	while (true)
	{
		drawall();
		
		while (_mainWindow.pollEvent(pointEvent))
		{
			
			if (pointEvent.type == sf::Event::MouseButtonPressed)
			{	system("cls");
				//printf("%d %d\n", pointEvent.mouseButton.x, pointEvent.mouseButton.y);

				int x = pointEvent.mouseButton.x; int y = pointEvent.mouseButton.y;

				std::list<Point::PointItem>::iterator it;
				for (it = point._pointItems.begin(); it != point._pointItems.end(); it++)
				{
					sf::Rect<int>pointItemRect = (*it).rect;
					if (pointItemRect.top + pointItemRect.height > y
						&& pointItemRect.top < y
						&& pointItemRect.left< x
						&& pointItemRect.left + pointItemRect.width>x)
					{
						if (point.cnt % 2 == 0)
						{
							if (point.po[(x - 216) / 28][(y - 98) / 28] == 0)
							{
								point.po[(x - 216) / 28][(y - 98) / 28] = 1;
								if (judge((x - 216) / 28, (y - 98) / 28) == 1)
									_gameState = BlackWin;
								point.cnt++;
							}
						}
						else
						{
							if (point.po[(x - 216) / 28][(y - 98) / 28] == 0)
							{
								point.po[(x - 216) / 28][(y - 98) / 28] = -1;//-1代表白棋  1代表黑棋
								if (judge((x - 216) / 28, (y - 98) / 28) == -1)
									_gameState = WhiteWin;
								point.cnt++;
							}
						}
						drawall();
						Game::timerstart = time(NULL);
						break;
					}
				}
			}
			if (pointEvent.type == sf::Event::Closed)
			{
				_gameState = Exiting;
			}
		}
		if (_gameState == BlackWin)
		{
			printf("Black Win\n");
			_gameState = Exiting;
		}
		if (_gameState == WhiteWin)
		{
			printf("White Win\n");
			_gameState = Exiting;
		}
		if (_gameState == Exiting)
		{
			time_t start = time(NULL);
			time_t end = time(NULL);
			while (true)
			{
				end = time(NULL);
				//printf("%d\n", end - start);
				if (end - start >= 3)
				{
					_gameState = ShowingMenu;
					break;
				}
			}
			break;
		}
		
	}
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
Point Game::point;
time_t Game::timerstart;

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
	int i, j;
	for (i = 0; i < 21; i++)
	{
		for (j = 0; j < 21; j++)
		{
			point.po[i][j] = 0;
		}
	}
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch (result)
	{
	case MainMenu::Exit:
	{
		_gameState = Game::Exiting;
		break;
	}
	case MainMenu::Play_with_AI:
	{
		_gameState = Game::Playing_with_AI;
		break;
	}
	case MainMenu::Play_with_human:
	{
		_gameState = Game::Playing_with_human;
		break;
	}
	}
}

sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}

const sf::Event& Game::GetInput()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);
	return currentEvent;
}

void Game::drawall()
{
	_mainWindow.clear(sf::Color(0, 0, 0));
	
	sf::Texture image;
	if (image.loadFromFile("images/checkerboard.jpg") != true)
	{
		return;
	}
	sf::Sprite checkerboard(image);
	_mainWindow.draw(checkerboard);

	sf::Texture imageblack;
	if (imageblack.loadFromFile("images/black.png") != true)
	{
		return;
	}
	sf::Sprite black(imageblack);

	sf::Texture imagewhite;
	if (imagewhite.loadFromFile("images/white.png") != true)
	{
		return;
	}
	sf::Sprite white(imagewhite);

	int i, j;
	for (i = 0; i < 21; i++)
	{
		for (j = 0; j < 21; j++)
		{
			if (point.po[i][j] == 1)
			{
				black.setOrigin(black.getLocalBounds().width / 2, black.getLocalBounds().height / 2);
				black.setPosition(i * 28 + 216 + 14, (j * 28 + 98 + 14));
				_mainWindow.draw(black);
			}
			else if (point.po[i][j] == -1)
			{
				white.setOrigin(white.getLocalBounds().width / 2, white.getLocalBounds().height / 2);
				white.setPosition(i * 28 + 216 + 14, (j * 28 + 98 + 14));
				_mainWindow.draw(white);
			}
		}
	}
	sf::Font font;
	sf::Text text;
	font.loadFromFile("images/zt.ttf");

	time_t timerend=time(NULL);
	//printf("%d %d\n", timerend,Game::timerstart);
	sf::Text timer;
	int ss = 15-(timerend - Game::timerstart);
	if (ss < 0&&point.cnt%2==0)
	{
		_gameState = WhiteWin;
	}
	if (ss < 0 && point.cnt % 2 == 1)
	{
		_gameState = BlackWin;
	}
	std::string s;
	s = s + (char)((ss / 10) + '0');
	ss = ss - ss / 10 * 10;
	s = s + (char)(ss + '0');
	timer.setFont(font);
	timer.setString(s);
	timer.setFillColor(sf::Color::Black); 
	timer.setPosition(50, 50);
	_mainWindow.draw(timer);

	
	text.setFont(font);
	if(_gameState==BlackWin)
	{
		text.setString("                  Black win        \nReturn to the main menu in three seconds"); //设置字符
		text.setCharacterSize(36); //文字大小
		text.setFillColor(sf::Color::Black); //颜色
		text.setPosition(100, 100);
	}
	else if (_gameState == WhiteWin)
	{
		text.setString("                  White win       \nReturn to the main menu in three seconds"); //设置字符
		text.setCharacterSize(36); //文字大小
		text.setFillColor(sf::Color::Black); //颜色
		text.setPosition(100, 100);
	}
	_mainWindow.draw(text);

	
	_mainWindow.display();
}

int Game::judge(int x,int y)                   //返回1为黑胜 返回-1为白胜 返回0为无 
{
	int base = point.po[x][y];
	int i;

	//纵向判断
	int cnt = 0;
	for (i = y; i < 21 && i < y + 5; i++)
	{
		if (point.po[x][i] == base)
			cnt++;
		else
			break;
	}
	for (i = y; i >= 0 && i >= y - 4; i--)
	{
		if (point.po[x][i] == base)
			cnt++;
		else
			break;
	}
	cnt = cnt - 1;
	printf("竖：%d\n", cnt);
	if (cnt >= 5)
		return base;
	
	//横向判断
	cnt = 0;
	for (i = x; i < 21 && i < x + 5; i++)
	{
		if (point.po[i][y] == base)
			cnt++;
		else
			break;
	}
	for (i = x; i >= 0 && i >= x - 4; i--)
	{
		if (point.po[i][y] == base)
			cnt++;
		else
			break;
	}
	cnt = cnt - 1;
	printf("横：%d\n", cnt);
	if (cnt >= 5)
		return base;

	//左上到右下斜向
	cnt = 0;
	for (i = 0; x + i < 21 && y + i < 21 && i < 5; i++)
	{
		if (point.po[x + i][y + i] == base)
			cnt++;
		else
			break;
	}
	for (i = 0; x - i >= 0 && y - i >= 0 && i < 5; i++)
	{
		if (point.po[x - i][y - i] == base)
			cnt++;
		else
			break;
	}
	cnt--;
	if (cnt >= 5)
		return base;
	printf("左上到右下:%d\n", cnt);

	cnt = 0;
	for (i = 0; x + i < 21 && y - i < 21 && i < 5; i++)
	{
		if (point.po[x + i][y - i] == base)
			cnt++;
		else
			break;
	}
	for (i = 0; x - i >= 0 && y + i >= 0 && i < 5; i++)
	{
		if (point.po[x - i][y + i] == base)
			cnt++;
		else
			break;
	}
	cnt--;
	if (cnt >= 5)
		return base;
	printf("左下到右上:%d\n", cnt);
}

void Game::AI()
{
	int maxscore = 0;
	int maxi=0, maxj=0;
	int scoretable[20] = {0,0,  1,1,  3,2  ,   5,4  ,    8,6  , 120,100  ,200,150  ,300000,200000  ,6000000,4000000  ,6000000,4000000};//己方无阻 (cnt-1)*4+2  敌方无阻(cnt-1)*4+3  己方一阻(cnt-1)*4 敌方一阻(cnt-1)*4  两阻碍 0
					//0子        1子 2子阻挡  2子无阻 3子阻挡   3子无阻   4子阻挡      4子无阻          5子阻挡           五子无阻
					//己方5子 600分  敌方5子 400分 己方四子（无阻挡） 300分 敌方四子（无阻挡）200分  己方四子（一阻挡）20分  敌方四子（一阻挡）15分  己方三子（无阻挡）12分
				    //敌方三子（无阻挡）10分   己方三子（一阻挡）8分    敌方三子（一阻挡）6分   己方两子（无阻挡）5分  敌方两子（无阻挡）4分   己方两子（一阻挡）3分   敌方两子（一阻挡）2分
					//只要两阻挡就是0分
	int i, j;
	for (i = 0; i < 21; i++)
	{
		for (j = 0; j < 21; j++)
		{
			if (point.po[i][j] == 0)
			{
				//printf("%d %d\n", i, j);
				int tempscore = 0;
				int k;
				int cnt = 1, hinder = 0;
				for (k = j+1; k < 21 && k < j + 5; k++)//己方横向
				{
					if (point.po[i][k] == -1)
						cnt++;
					else
						break;
				}
				if (point.po[i][k] == 1 || k >= 21 || k < 0)
					hinder++;
				for (k = j-1; k >= 0 && k >= j - 4; k--)
				{
					if (point.po[i][k] == -1)
						cnt++;
					else
						break;
				}
				if (point.po[i][k] == 1 || k >= 21 || k < 0)
					hinder++;
				if (cnt > 5)
					cnt = 5;
				if (hinder == 1)
				{
					tempscore += scoretable[(cnt - 1) * 4];
				}
				else if (hinder == 0)
				{
					tempscore += scoretable[(cnt - 1) * 4+2];
				}

				cnt = 1, hinder = 0;
				for (k = i+1; k < 21 && k < i + 5; k++)//己方纵向
				{
					if (point.po[k][j] == -1)
						cnt++;
					else
						break;
				}
				if (point.po[k][j] == 1 || k >= 21 || k < 0)
					hinder++;
				for (k = i-1; k >= 0 && k > i - 5; k--)
				{
					if (point.po[k][j] == -1)
						cnt++;
					else
						break;
				}
				if (point.po[k][j] == 1 || k >= 21 || k < 0)
					hinder++;
				if (cnt > 5)
					cnt = 5;
				if (hinder == 1)
				{
					tempscore += scoretable[(cnt - 1) * 4];
				}
				else if (hinder == 0)
				{
					tempscore += scoretable[(cnt - 1) * 4+2];
				}

				cnt = 1, hinder = 0;
				for (k = 1; i + k < 21 && j + k < 21 && k < 5; k++)//右上到左下
				{
					if (point.po[i + k][j + k] == -1)
						cnt++;
					else
						break;
				}
				if (point.po[i + k][j + k] == 1 || k+i >= 21 || k + j>=21)
					hinder++;
				for (k = 1; i - k >= 0 && j - k >= 0 && k < 5; k++)
				{
					if (point.po[i - k][j - k] == -1)
						cnt++;
					else
						break;
				}
				if (point.po[i - k][j - k] == 1 || i-k <0  || j-k < 0)
					hinder++;
				if (cnt > 5)
					cnt = 5;
				if (hinder == 1)
				{
					tempscore += scoretable[(cnt - 1) * 4];
				}
				else if (hinder == 0)
				{
					tempscore += scoretable[(cnt - 1) * 4+2];
				}


				cnt = 1, hinder = 0;
				for (k = 1; i + k < 21 && j - k >=0 && k < 5; k++)//右下到左上
				{
					if (point.po[i + k][j - k] == -1)
						cnt++;
					else
						break;
				}
				if (point.po[i + k][j - k] == 1 || k+i >= 21 || j-k < 0)
					hinder++;
				for (k = 1; i - k >= 0 && j + k <21 && k < 5; k++)
				{
					if (point.po[i - k][j + k] == -1)
						cnt++;
					else
						break;
				}
				if (point.po[i - k][j + k] == 1 || i-k <0 || j+k >= 21)
					hinder++;
				if (cnt > 5)
					cnt = 5;
				if (hinder == 1)
				{
					tempscore += scoretable[(cnt - 1) * 4];
				}
				else if (hinder == 0)
				{
					tempscore += scoretable[(cnt - 1) * 4+2];
				}

				//敌方
				cnt = 1, hinder = 0;
				for (k = j+1; k < 21 && k < j + 5; k++)//横向
				{
					if (point.po[i][k] == 1)
						cnt++;
					else
						break;
				}
				if (point.po[i][k] == -1 || k >= 21 || k < 0)
					hinder++;
				for (k = j-1; k >= 0 && k >= j - 4; k--)
				{
					if (point.po[i][k] == 1)
						cnt++;
					else
						break;
				}
				if (point.po[i][k] == -1 || k >= 21 || k < 0)
					hinder++;
				if (cnt > 5)
					cnt = 5;
				if (hinder == 1)
				{
					tempscore += scoretable[(cnt - 1) * 4 + 1];
				}
				else if (hinder == 0)
				{
					tempscore += scoretable[(cnt - 1) * 4+3];
				}

				cnt = 1, hinder = 0;
				for (k = i+1; k < 21 && k < i + 5; k++)//纵向
				{
					if (point.po[k][j] == 1)
						cnt++;
					else
						break;
				}
				if (point.po[k][j] == -1 || k >= 21 || k < 0)
					hinder++;
				for (k = i-1; k >= 0 && k > i - 5; k--)
				{
					if (point.po[k][j] == 1)
						cnt++;
					else
						break;
				}
				if (point.po[k][j] == -1 || k >= 21 || k < 0)
					hinder++;
				if (cnt > 5)
					cnt = 5;
				if (hinder == 1)
				{
					tempscore += scoretable[(cnt - 1) * 4 + 1];
				}
				else if (hinder == 0)
				{
					tempscore += scoretable[(cnt - 1) * 4+3];
				}

				cnt = 1, hinder = 0;
				for (k = 1; i + k < 21 && j + k < 21 && k < 5; k++)//右上到左下
				{
					if (point.po[i + k][j + k] == 1)
						cnt++;
					else
						break;
				}
				if (point.po[i + k][j + k] == -1 || k+i >= 21 || j+k >=21)
					hinder++;
				for (k = 1; i - k >= 0 && j - k >= 0 && k < 5; k++)
				{
					if (point.po[i - k][j - k] == 1)
						cnt++;
					else
						break;
				}
				if (point.po[i - k][j - k] == -1 || i-k <0 || j-k < 0)
					hinder++;
				if (cnt > 5)
					cnt = 5;
				if (hinder == 1)
				{
					tempscore += scoretable[(cnt - 1) * 4 + 1];
				}
				else if (hinder == 0)
				{
					tempscore += scoretable[(cnt - 1) * 4+3];
				}


				cnt = 1, hinder = 0;
				for (k = 1; i + k < 21 && j - k >= 0 && k < 5; k++)//右下到左上
				{
					if (point.po[i + k][j - k] == 1)
						cnt++;
					else
						break;
				}
				if (point.po[i + k][j - k] == -1 || i+k >= 21 || j-k < 0)
					hinder++;
				for (k = 1; i - k >= 0 && j + k < 21 && k < 5; k++)
				{
					if (point.po[i - k][j + k] == 1)
						cnt++;
					else
						break;
				}
				if (point.po[i - k][j + k] == -1 || j+k >= 21 || i-k < 0)
					hinder++;
				if (cnt > 5)
					cnt = 5;
				if (hinder == 1)
				{
					tempscore += scoretable[(cnt - 1) * 4 + 1];
				}
				else if (hinder == 0)
				{
					tempscore += scoretable[(cnt - 1) * 4+3];
				}
				
				//printf("%d %d %d\n", i, j, tempscore);
				if (tempscore > maxscore)
				{
					maxscore = tempscore;
					maxi = i;
					maxj = j;
				}
			}
		}
	}
	//printf("%d\n", maxscore);
	point.po[maxi][maxj] = -1;
	if (_gameState == Playing_with_AI)
	{
		if (judge(maxi, maxj) == -1)
			_gameState = WhiteWin;
	}
}