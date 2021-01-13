#include "textureManager.h"
#include "board.h"
#include <iostream>
#define width 32
///Xiaowei Jiang
using namespace sf;
using namespace std;
void drawTile(Sprite obj, int i, int j,RenderWindow &w) {
	obj.setPosition(j * width, i * width);
	w.draw(obj);
}
void drawFace(Sprite face, RenderWindow& w) {
	face.setPosition(368, 520);
	w.draw(face);


}
int main() {
	
	RenderWindow game(VideoMode(800, 600), "MineSweeper");
	board gameBoard;
	gameBoard.generateBoard();
	
	//range
	while (game.isOpen()) //start of main game loop
	{
		Vector2i MouPos = Mouse::getPosition(game);
		int jPos = MouPos.x / 32;//horizontal position, 25 maximum value
		int iPos = MouPos.y / 32; //vertical position 18.75 maximum value 16 for maximum game board
		Event clickEvent;
		while (game.pollEvent(clickEvent))//start of any user inputs
		{

			if (clickEvent.type == Event::Closed)//close 
			{
				game.close();
			}
			if (Mouse::isButtonPressed(Mouse::Left)) // left click event
			{

				if (MouPos.y < 584 && MouPos.y>520 && MouPos.x > 368 && MouPos.x < 432) {
					gameBoard.setisLost(false);
					gameBoard.setisWin(false);
					gameBoard.generateBoard();


				}// reset game

				if (MouPos.y < 584 && MouPos.y>520 && MouPos.x > 567 && MouPos.x < 631)
				{
					gameBoard.readTestFile(1);
					gameBoard.setisLost(false);
					gameBoard.setisWin(false);

				}
				if (MouPos.y < 584 && MouPos.y>520 && MouPos.x > 631 && MouPos.x < 695)
				{
					gameBoard.readTestFile(2);
					gameBoard.setisLost(false);
					gameBoard.setisWin(false);

				}
				if (MouPos.y < 584 && MouPos.y>520 && MouPos.x > 695&& MouPos.x < 759)
				{
					gameBoard.readTestFile(3);
					gameBoard.setisLost(false);
					gameBoard.setisWin(false);

				}//test3

				if (MouPos.y < 584 && MouPos.y>520 && MouPos.x > 500 && MouPos.x <564) {
					if (gameBoard.debugMode == false) {
						for (int i = 0; i <= 15; i++)
						{
							for (int j = 0; j <= 24; j++)
							{
								if (gameBoard.Tiles[i][j].realCondition == 0)
									gameBoard.Tiles[i][j].displayEqualsReal();
							}
						}
						gameBoard.setDebug(true);
						cout << "In debug mode" << endl;
					}
					else if (gameBoard.debugMode == true) {
						for (int i = 0; i <= 15; i++)
						{
							for (int j = 0; j <= 24; j++)
							{
								if (gameBoard.Tiles[i][j].realCondition == 0)
									gameBoard.Tiles[i][j].setDisplayCondition(9);
							}
						}
						gameBoard.setDebug(false);
						cout << "Debug mode end" << endl;
					}

				}//debug

				if (iPos < 16 && (iPos >= 0) && (jPos >= 0) && jPos < 25 && gameBoard.Tiles[iPos][jPos].displayCondition != 11) //LEFT click event in the minefield
					{
						gameBoard.Tiles[iPos][jPos].displayEqualsReal(); // reveal a number tile
						if (gameBoard.Tiles[iPos][jPos].realCondition == 10)//empty tile
						{
						
							gameBoard.RevealemptyTiles(iPos,jPos);
						
						}
						if (gameBoard.Tiles[iPos][jPos].realCondition == 0)// revealed a mine, GG
						{
							gameBoard.setisLost(true);
							gameBoard.setisWin(false);
							gameBoard.revealAllbomb();
						}



				}//end of left click  event in minefield
				
			}//end of  left clicks 
			else if (Mouse::isButtonPressed(Mouse::Right)) {
			if (iPos <= 16 && iPos >= 0 && jPos >= 0 && jPos <= 25 && gameBoard.isLost
				== false && gameBoard.isWin == false&& gameBoard.Tiles[iPos][jPos].displayCondition == 9) {
				gameBoard.Tiles[iPos][jPos].setDisplayCondition(11);
				gameBoard.flags_remain--;

				}

			else if (iPos <= 16 && iPos >= 0 && jPos >= 0 && jPos <= 25 && gameBoard.isLost
				== false && gameBoard.isWin == false && gameBoard.Tiles[iPos][jPos].displayCondition == 11) {
				gameBoard.Tiles[iPos][jPos].setDisplayCondition(9);
				gameBoard.flags_remain++;

			}
			/*
			bool e = true;
			for (int i = 0; i < 16; i++) {
			
				for (int j = 0; j < 25; j++)
				{
					if (gameBoard.Tiles[i][j].realCondition == 0 && gameBoard.Tiles[i][j].displayCondition != 11) e = false;
					if (gameBoard.Tiles[i][j].realCondition != 0 && gameBoard.Tiles[i][j].displayCondition != gameBoard.Tiles[i][j].realCondition
						) e = false;


				}
			
			}


			if (e = true) {
				gameBoard.isWin = true;
				gameBoard.isLost = false;
			
			}
			*/
			}//right click events ,,,,,,,,,almost there
			bool a = true;
			for (auto i = 0; i < 16; i++)               //check if win
			{

				for (auto j = 0; j < 25; j++) {
					if (gameBoard.Tiles[i][j].realCondition != 0&& (gameBoard.Tiles[i][j].displayCondition == 9))
					{
						 a = false;
					}
					if (gameBoard.Tiles[i][j].realCondition == 0 && gameBoard.Tiles[i][j].displayCondition != 11)
					{
						a = false;
					}
				}

			}//end of auto loop
			if (a == true) {
				
				gameBoard.setisLost(false);
				gameBoard.setisWin(true);
			}
		}// end of click events
		
		gameBoard.drawAll(game);		
		game.display();
	
	

	
	
	}//end of main game loop

	return 0;

}