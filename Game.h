#pragma once
#include "mainmenu.h"
#include "Point.h"
class Game {
	
public:
	static void Start();
	static sf::RenderWindow& GetWindow();
	const static sf::Event& GetInput();

	const static int SCREEN_WIDTH = 1024;
	const static int SCREEN_HEIGHT = 768;
	static Point point;
	static void drawall();
	static int judge(int x,int y);
	static void AI();
	static time_t timerstart;
private:
	static bool IsExiting();
	static void GameLoop();

	static void ShowSplashScreen();
	static void ShowMenu();
	
	static void play_with_AI();
	static void play_with_human();

	enum GameState {
		Uninitialized, ShowingSplash, Paused,
		ShowingMenu, Playing_with_AI,Playing_with_human, Exiting,BlackWin,WhiteWin
	};

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;

	

};