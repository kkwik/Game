/**
@file SFML_Working.cpp
@author Kevin Kwik
@date 11 May 2019
@brief Recreation of the flash game 2048
*/
#include "pch.h"
#include <SFML/Graphics.hpp>   //using namespace sf
#include <time.h>
#include <iostream>
#include <string>

///@brief width is the width of the window SFML creates
int width = 336;
///@brief height is the height of the window SFML creates
int height = 370;

///@brief  is used to store the current state of the gameBoard. The int value held is the value of the tile.
int gameBoard[4][4] = { {4,0,0,0},{4,0,0,0},{4,0,0,0},{4,4,4,4} }; 
///@brief zBoard is a game board full of zeros used to reset the game
int zBoard[4][4] = { {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0} };
///@brief score is an int used to store the player's current score
int score = 0;
///@brief gameActive is a bool used to store whether a game is running or has ended
bool gameActive = true;

/**
	@brief Global function to increase player score
	@param input is an integer value

	increaseScore increases the global variable score by the amount input.
*/
void increaseScore(int input)
{
	score += input;
}

/**
	@brief Global function to reset player score
	
	resetScore sets player score to zero to reset
*/
void resetScore()
{
	score = 0;
}

//returns int with amount of occupied slots
/**
	@brief Returns the amount of occupied tiles on the board
	@return int value with the amount of occupied tiles on the board
*/
int boardCapacity()
{
	int size = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (gameBoard[i][j] != 0)
				size++;
	return size;
}

//returns true if the board is full
/**
	@brief Checks if the game board is full
	@return A boolean which is true if the board is full
*/
bool boardFull()
{
	return boardCapacity() == 16;
}

//adds a value to the board at a random location
/**
	@brief Adds a value to a random empty tile on the board

	The value of the tile to be added is determined by the average tile value and a one in ten chance
	The slot the new tile is added to is determined using rand(), and a new slot is generated until an empty one is found
*/
void boardAdd()
{
	if (boardFull())
		return;
	double avgVal = (double)score / boardCapacity();
	//Function to decide value
	int value = 2;
	for (int i = 2048; i > 1; i /= 2)
	{
		if (avgVal / 3 > i && rand() % 10 == 0)
		{
			value = i;
			break;
		}
	}
	//std::cout << "Value " << value << " selected.\nAvg score: " << avgVal << std::endl;

	//Function to decide place
	int slot = rand() % 16;
	while (!boardFull() && gameBoard[slot / 4][slot % 4] != 0)
		slot = rand() % 16;
	gameBoard[slot / 4][slot % 4] = value;
}

///Helper function to printout state of the board on console
void printBoard()
{
	for (int i = 0; i < 4; i++)
	{
		std::cout << "|";
		for (int j = 0; j < 4; j++)
			std::cout << gameBoard[i][j] << "|";
		std::cout << std::endl;
	}
}

/**
	@brief Helper function to compare 2d arrays of size 4x4
	@param oBoard is a 4x4 2d matrix identical to gameBoard in size
	@return A boolean value which is true if both the gameBoard and the passed board are the same
*/
bool compareBoard(int oBoard[4][4])
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (gameBoard[i][j] != oBoard[i][j])
				return false;
	return true;
}

//copies the values in the board passed to board
/**
	@brief A helper function to copy the state of another board to gameBoard

	@param oBoard is a 4x4 2d matrix identical to gameBoard in size
*/
void cpyToBoard(int oBoard[4][4]) //Helper function to copy passed board to \gameBoard
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			gameBoard[i][j] = oBoard[i][j];
}

/**
	@brief Helper function that resets the state of the game

	Resets score to zero, resets board to all zeros and adds two tiles.
*/
void resetGame()
{
	resetScore(); 
	cpyToBoard(zBoard);
	boardAdd();
	boardAdd();
	gameActive = true;
}

/**
	@brief Helper function that moves all entries in gameBoard as far right as possible.

	Called twice when user presses right arrow. 
*/
void mvRight()
{
	int nBoard[4][4] = { {0,0,0,0},
						{0,0,0,0},
						{0,0,0,0},
						{0,0,0,0} };
	for (int i = 0; i < 4; i++)
	{
		int counter = 3;
		for (int j = 3; j > -1; j--)
			if (gameBoard[i][j] != 0)
				nBoard[i][counter--] = gameBoard[i][j];
	}
	cpyToBoard(nBoard);
}

/**
	@brief Helper function that moves all entries in gameBoard as far left as possible.

	Called twice when user presses left arrow.
*/
void mvLeft()
{
	int nBoard[4][4] = { {0,0,0,0},
						{0,0,0,0},
						{0,0,0,0},
						{0,0,0,0} };
	for (int i = 0; i < 4; i++)
	{
		int counter = 0;
		for (int j = 0; j < 4; j++)
			if (gameBoard[i][j] != 0)
				nBoard[i][counter++] = gameBoard[i][j];
	}
	cpyToBoard(nBoard);
}

/**
	@brief Helper function that moves all entries in gameBoard as far up as possible.

	Called twice when user presses up arrow.
*/
void mvUp()
{
	int nBoard[4][4] = { {0,0,0,0},
						{0,0,0,0},
						{0,0,0,0},
						{0,0,0,0} };
	for (int i = 0; i < 4; i++)
	{
		int counter = 0;
		for (int j = 0; j < 4; j++)
			if (gameBoard[j][i] != 0)
				nBoard[counter++][i] = gameBoard[j][i];
	}
	cpyToBoard(nBoard);
}

/**
	@brief Helper function that moves all entries in gameBoard as far down as possible.

	Called twice when user presses down arrow.
*/
void mvDown()
{
	int nBoard[4][4] = { {0,0,0,0},
						{0,0,0,0},
						{0,0,0,0},
						{0,0,0,0} };
	for (int i = 0; i < 4; i++)
	{
		int counter = 3;
		for (int j = 3; j > -1; j--)
			if (gameBoard[j][i] != 0)
				nBoard[counter--][i] = gameBoard[j][i];
	}
	cpyToBoard(nBoard);
}

/**
	@brief Helper function that adds all entries which are the same towards the right.

	Additions start from the right and then move to the left
*/
void addRight()
{
	for (int i = 0; i < 4; i++)
	{
		if (gameBoard[i][3] != 0 && gameBoard[i][3] == gameBoard[i][2])
		{
			gameBoard[i][2] *= 2;
			increaseScore(gameBoard[i][2]);
			gameBoard[i][3] = 0;
		}
		else if (gameBoard[i][2] != 0 && gameBoard[i][2] == gameBoard[i][1])
		{
			gameBoard[i][1] *= 2;
			increaseScore(gameBoard[i][1]);
			gameBoard[i][2] = 0;
		}
		if (gameBoard[i][1] != 0 && gameBoard[i][1] == gameBoard[i][0])
		{
			gameBoard[i][0] *= 2;
			increaseScore(gameBoard[i][0]);
			gameBoard[i][1] = 0;
		}
	}
}

/**
	@brief Helper function that adds all entries which are the same towards the left.

	Additions start from the left and then move to the right
*/
void addLeft()
{
	for (int i = 0; i < 4; i++)
	{
		if (gameBoard[i][0] != 0 && gameBoard[i][0] == gameBoard[i][1])
		{
			gameBoard[i][1] *= 2;
			increaseScore(gameBoard[i][1]);
			gameBoard[i][0] = 0;
		}
		else if (gameBoard[i][1] != 0 && gameBoard[i][1] == gameBoard[i][2])
		{
			gameBoard[i][1] *= 2;
			increaseScore(gameBoard[i][1]);
			gameBoard[i][2] = 0;
		}
		if (gameBoard[i][2] != 0 && gameBoard[i][2] == gameBoard[i][3])
		{
			gameBoard[i][3] *= 2;
			increaseScore(gameBoard[i][3]);
			gameBoard[i][2] = 0;
		}
	}
}

/**
	@brief Helper function that adds all entries which are the same downwards.

	Additions start from the bottom and then move to the top
*/
void addDown()
{
	for (int j = 0; j < 4; j++)
	{
		if (gameBoard[3][j] != 0 && gameBoard[3][j] == gameBoard[2][j])
		{
			gameBoard[3][j] *= 2;
			increaseScore(gameBoard[3][j]);
			gameBoard[2][j] = 0;
		}
		else if (gameBoard[2][j] != 0 && gameBoard[2][j] == gameBoard[1][j])
		{
			gameBoard[2][j] *= 2;
			increaseScore(gameBoard[2][j]);
			gameBoard[1][j] = 0;
		}
		if (gameBoard[1][j] != 0 && gameBoard[1][j] == gameBoard[0][j])
		{
			gameBoard[0][j] *= 2;
			increaseScore(gameBoard[0][j]);
			gameBoard[1][j] = 0;
		}
	}
}

/**
	@brief Helper function that adds all entries which are the same upwards.

	Additions start from the top and then move to the bottom
*/
void addUp()
{
	for (int j = 0; j < 4; j++)
	{
		if (gameBoard[0][j] != 0 && gameBoard[0][j] == gameBoard[1][j])
		{
			gameBoard[0][j] *= 2;
			increaseScore(gameBoard[0][j]);
			gameBoard[1][j] = 0;
		}
		else if (gameBoard[1][j] != 0 && gameBoard[1][j] == gameBoard[2][j])
		{
			gameBoard[1][j] *= 2;
			increaseScore(gameBoard[1][j]);
			gameBoard[2][j] = 0;
		}
		if (gameBoard[2][j] != 0 && gameBoard[2][j] == gameBoard[3][j])
		{
			gameBoard[3][j] *= 2;
			increaseScore(gameBoard[3][j]);
			gameBoard[2][j] = 0;
		}
	}
}

/**
	@brief Called when the user presses the right arrow

	Moves all entries right, adds them, moves them right again, and then spawns another tile
*/
void right()
{
	mvRight();
	addRight();
	mvRight();
	boardAdd();
}

/**
	@brief Called when the user presses the left arrow

	Moves all entries left, adds them, moves them left again, and then spawns another tile
*/
void left()
{
	mvLeft();
	addLeft();
	mvLeft();
	boardAdd();
}

/**
	@brief Called when the user presses the down arrow

	Moves all entries downwards, adds them, moves them downwards again, and then spawns another tile
*/
void down()
{
	mvDown();
	addDown();
	mvDown();
	boardAdd();
}

/**
	@brief Called when the user presses the up arrow

	Moves all entries upwards, adds them, moves them upwards again, and then spawns another tile
*/
void up()
{
	mvUp();
	addUp();
	mvUp();
	boardAdd();
}


int main()
{
	srand(time(0));
	cpyToBoard(zBoard);

	sf::RenderWindow window(sf::VideoMode(width, height), "2048");
	
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
		std::cout << "Failed to load font\n";
	font.loadFromFile("arial.ttf");

	sf::Color white(255, 255, 255);
	sf::Color black(0, 0, 0);

	sf::Text scoreBoard, gameOver;
	scoreBoard.setString("Score:");
	scoreBoard.setPosition(10, 335);
	scoreBoard.setFillColor(black);
	scoreBoard.setCharacterSize(26);
	scoreBoard.setFont(font);
	gameOver.setString("             Game Over\nPress [SPACE] to continue");
	gameOver.setPosition(10, 55);
	gameOver.setFillColor(black);
	gameOver.setCharacterSize(26);
	gameOver.setFont(font);
	

	sf::RectangleShape gameOverScreen, gameOverScreenBorder;
	gameOverScreen.setSize(sf::Vector2f(326, 70));
	gameOverScreenBorder.setSize(sf::Vector2f(336, 80));
	gameOverScreen.setPosition(5, 5+50);
	gameOverScreenBorder.setPosition(0, 0 + 50);
	gameOverScreen.setFillColor(white);
	gameOverScreenBorder.setFillColor(black);
	
	sf::Texture t2, t4, t8, t16, t32, t64, t128, t256, t512, t1024, t2048, ttsmih, tboard;
	t2.loadFromFile("images/2.png");
	t4.loadFromFile("images/4.png");
	t8.loadFromFile("images/8.png");
	t16.loadFromFile("images/16.png");
	t32.loadFromFile("images/32.png");
	t64.loadFromFile("images/64.png");
	t128.loadFromFile("images/128.png");
	t256.loadFromFile("images/256.png");
	t512.loadFromFile("images/512.png");
	t1024.loadFromFile("images/1024.png");
	t2048.loadFromFile("images/2048.png");
	ttsmih.loadFromFile("images/tsmih.png");
	tboard.loadFromFile("images/board.png");

	sf::Sprite sprite2(t2);
	sf::Sprite sprite4(t4);
	sf::Sprite sprite8(t8);
	sf::Sprite sprite16(t16);
	sf::Sprite sprite32(t32);
	sf::Sprite sprite64(t64);
	sf::Sprite sprite128(t128);
	sf::Sprite sprite256(t256);
	sf::Sprite sprite512(t512);
	sf::Sprite sprite1024(t1024);
	sf::Sprite sprite2048(t2048);
	sf::Sprite spritetsmih(ttsmih);
	sf::Sprite spriteboard(tboard);
	sf::Sprite *sprite = &spritetsmih;
	sf::Event e;

	resetGame();
	while (window.isOpen())
	{
		//Check when the window is closed
		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed) window.close();
			else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Up) { up(); }
			else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Down) { down(); }
			else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Left) { left(); }
			else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Right) { right(); }
			else if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Space) { resetGame(); }
		}

		/* Draws graphics */
		if (gameActive)
		{
			window.clear(white);
			window.draw(spriteboard);
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					switch (gameBoard[j][i])
					{
					case 0:
						continue;
					case 2:
						sprite = &sprite2;
						break;
					case 4:
						sprite = &sprite4;
						break;
					case 8:
						sprite = &sprite8;
						break;
					case 16:
						sprite = &sprite16;
						break;
					case 32:
						sprite = &sprite32;
						break;
					case 64:
						sprite = &sprite64;
						break;
					case 128:
						sprite = &sprite128;
						break;
					case 256:
						sprite = &sprite256;
						break;
					case 512:
						sprite = &sprite512;
						break;
					case 1024:
						sprite = &sprite1024;
						break;
					case 2048:
						sprite = &sprite2048;
						break;
					default:
						sprite = &spritetsmih;
					}
					sprite->setPosition(80 * i + 16, 80 * j + 16);
					window.draw(*sprite);
				}
			}

			scoreBoard.setString("Score: " + std::to_string(score));
			window.draw(scoreBoard);
			if (boardFull())
			{
				gameActive = false;
				window.draw(gameOverScreenBorder);
				window.draw(gameOverScreen);
				window.draw(gameOver);
			}
			window.display();
		}
	}
	return 0;
}