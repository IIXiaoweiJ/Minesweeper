#pragma once
#include "tile.h"
#include <vector>
#include <random>
#include "textureManager.h"
#include <string>
textureManage manager;
map<string, Sprite> tileSpriteMap = manager.tileTextures();
map<string, Sprite> boardSpriteMap = manager.boardElements();
#define width 32
class board {
public:
	tile Tiles[16][25];
	int flags_remain = 50;
	int mines = 0;
	bool isWin= false;
	bool isLost= false;
	bool debugMode= false;
	bool revealed = 0;
	void setisWin(bool i) {
		isWin = i;
	
	}
	void setDebug(bool i) {
		debugMode = i;
	
	}
	void setisLost(bool i) {
		isLost = i;
	}
	vector<int> Generatebomblist(int min, int max, int num)
	{
		int random;
		vector<int> bomblist;
		vector<int> remain;

		for (int i = min; i < max + 1; i++)
		{
			remain.push_back(i);
		}
		srand((unsigned)time(0));
		for (int i = 0; i < num; i++)
		{
			do {
				random = min + rand() % (max - min + 1);

			} while (remain.at(random - min) == -1);
			bomblist.push_back(random);
			remain.at(random - min) = -1;
		}
		return bomblist;
	}
	string checkPosition(int i,int j) {
		if (i == 0 && j == 0) return"top left";
		else if (i == 0 && j == 24) return "top right";
		else if (i == 15 && j == 0) return "bottom left";
		else if (i == 15 && j == 24) return "bottom right";
		else if (i == 0) return "top";
		else if (j == 0) return "left side";
		else if (j == 24) return "right side";
		else if (i == 15) return "bottom";
		else return "middle";
	}


	void flag(int i, int j) {
		if (Tiles[i][j].displayCondition == 9)
		{
			Tiles[i][j].displayCondition = 11;
		}
		if (Tiles[i][j].displayCondition == 11)
		{
			Tiles[i][j].displayCondition = 9;
		}
	}


	void  setMinesAround() {
		for (int i = 0; i <16; i++) 
		{
			for (int j = 0; j < 25; j++)
			{

				int Neighborcounter = 0;		
				
				if (Tiles[i][j].realCondition != 0) //check if the tile is not mine
				{
					if (Tiles[i - 1][j - 1].realCondition == 0 && (i != 0) && (j != 0))
						Neighborcounter++;
					if (Tiles[i - 1][j].realCondition == 0 && (i != 0))
						Neighborcounter++;
					if (Tiles[i - 1][j + 1].realCondition == 0 && (i != 0) && (j != 24))
						Neighborcounter++;
					if (Tiles[i][j - 1].realCondition == 0 && (j!=0))
						Neighborcounter++;
					if (Tiles[i][j + 1].realCondition == 0 && (j!=24))
						Neighborcounter++;
					if (Tiles[i + 1][j - 1].realCondition == 0 && (i!=15)&&(j!=0))
						Neighborcounter++;
					if (Tiles[i + 1][j].realCondition == 0 && (i!=15))
						Neighborcounter++;

					if (Tiles[i + 1][j + 1].realCondition == 0 && (i != 15) && (j != 24))
					{
						Neighborcounter++;
					}

					if (Neighborcounter == 0)//no mines around that tile
						Tiles[i][j].setRealCondition(10);// set to default empty condition
					else
						Tiles[i][j].setRealCondition(Neighborcounter);

				}

				
				
			}
		}
	
	
	
	}
	bool winCondition() {
		bool win =true;
		for (int i = 0; i < 16; i++) {

			for (int j = 0; j < 25; j++)
			{
				if (Tiles[i][j].realCondition == 0 && Tiles[i][j].displayCondition != 11) win = false;

				if (Tiles[i][j].realCondition != 0 && Tiles[i][j].displayCondition == 9) win = false;
			}
		}
	
		return win;
	}
	void setRevealCondition(int i, int j)//for empty tiles
	{
		Tiles[i][j].setunRecursive(); //same from 10, just to differ to avoid recursive error
		if ((i != 0) && (j != 0) && hasMineArond(i, j) && Tiles[i - 1][j - 1].displayCondition != 11) Tiles[i - 1][j - 1].displayEqualsReal();

		if ((Tiles[i - 1][j].displayCondition != 11) && (i != 0) && hasMineArond(i - 1, j) || Tiles[i - 1][j].realCondition == 10) Tiles[i - 1][j].displayEqualsReal();

		if ((i != 0) && (j != 0) && hasMineArond(i, j) && Tiles[i - 1][j + 1].displayCondition != 11) Tiles[i - 1][j + 1].displayEqualsReal();//end of checking upper blocks

		if ((j != 24) && (hasMineArond(i, j + 1) || Tiles[i][j + 1].realCondition == 10) && (Tiles[i][j + 1].displayCondition != 11))Tiles[i][j + 1].displayEqualsReal();

		if ((i != 15) && (j != 24) && (hasMineArond(i + 1, j + 1)) && (Tiles[i + 1][j + 1].displayCondition != 11)) Tiles[i + 1][j + 1].displayEqualsReal();

		if ((Tiles[i + 1][j].displayCondition != 11) && (i != 15) && (hasMineArond(i + 1, j)) || Tiles[i + 1][j].realCondition == 10) Tiles[i + 1][j].displayEqualsReal();// end of checking lower blockes

		if ((Tiles[i + 1][j - 1].displayCondition != 11) && (i != 15) && (j != 0) && (hasMineArond(i + 1, j - 1))) Tiles[i + 1][j - 1].displayEqualsReal();

		if (j != 0 && (hasMineArond(i, j - 1) && (Tiles[i][j - 1].displayCondition != 11) || Tiles[i][j - 1].realCondition == 10)) Tiles[i][j - 1].displayEqualsReal();//end of checking left and right



	}

	bool isflagged(int i, int j) {
		return Tiles[i][j].displayCondition == 11;
	
	
	}
	void emptyField() {
		for (int i = 0; i < 16; i++) {

			for (int j = 0; j < 25; j++) {
				Tiles[i][j].setRealCondition(10);
				Tiles[i][j].tiledefault();
			}

		}
	}
	void generateBoard() {
		vector<int> bombList = Generatebomblist(0, 399, 50);
		flags_remain = 50;
		//generate random mine position
		emptyField();
		mines = 0;
		
		for (int i = 0; i < 16; i++) {
		
			for (int j = 0; j < 25; j++) {
				for (int bombCount = 0; bombCount < bombList.size(); bombCount++) {
					if (bombList[bombCount] == 25 * i + j)
					{
						bombCount++;
						Tiles[i][j].realCondition=0;//set the mine tile
						
						

					}
				
					
				}
				if (Tiles[i][j].realCondition == 0) { 
					mines++;
					cout << 0;
				}
				else {
					cout << 1;

				}
				
				Tiles[i][j].tiledefault(); //set display mode as hidden to 9
			}
			cout << endl;
		}
		
		setMinesAround();

		bombList.clear();
	}
	bool hasMineArond(int i,int j)//aren't mines, aren't flagged, realcondition as showing numbers
	{
		return(Tiles[i][j].realCondition >=1 && Tiles[i][j].realCondition < 9);
	
	}
	
	void RevealemptyTiles(int i, int j)
	{
		if (Tiles[i][j].realCondition == 10)
		{ 
			setRevealCondition(i, j);
			
			if ((i != 15) && Tiles[i + 1][j].realCondition == 10)RevealemptyTiles(i + 1, j);
			if ((j != 0) && Tiles[i][j - 1].realCondition == 10)RevealemptyTiles(i, j - 1);
			if ((j != 24) && Tiles[i][j + 1].realCondition == 10)RevealemptyTiles(i, j + 1);
			if ((i != 0) && Tiles[i - 1][j].realCondition == 10)RevealemptyTiles(i - 1, j);
				
		}
	}






	


	//start of draw functions
	void drawTile(Sprite obj, int i, int j, RenderWindow& w) {
		obj.setPosition(j * width, i * width);
		w.draw(obj);
	}
	void drawBlock(Sprite face,  int j, int i, RenderWindow& w) {
		face.setPosition(j, i);
		w.draw(face);


	}
	void drawDigit( RenderWindow& w,int flagsRemain) {
		Sprite negative = boardSpriteMap["digits"];
		negative.setTextureRect(Rect<int>(21 * 10, 0, 21, 32));
		negative.setPosition(0, 520);
		if (flagsRemain < 0) {
			w.draw(negative);
			flagsRemain = -flagsRemain;
		}
		
		int T=0;
		int O=0;
		

		if (flagsRemain > 10 || flagsRemain == 10) {
			 T = flagsRemain / 10;
			 O = flagsRemain %10;
		
		
		}
		else {
		
			T = 0;
			O = flagsRemain;
		}
		Sprite tens = boardSpriteMap["digits"];
		tens.setTextureRect(Rect<int>(21 * T, 0, 21, 32));
		tens.setPosition(44, 520);
		Sprite ones = boardSpriteMap["digits"];
		ones.setTextureRect(Rect<int>(21 * O, 0, 21, 32));
		ones.setPosition(66, 520);
		Sprite hundreds= boardSpriteMap["digits"];
		hundreds.setTextureRect(Rect<int>(0, 0, 21, 32));
		hundreds.setPosition(22, 520);
		
		w.draw(hundreds);
		w.draw(tens);
		w.draw(ones);
		
	}
	void revealAllbomb() {
		for (int i = 0; i <= 15; i++)
		{
			for (int j = 0; j <= 24; j++)
			{
				if(Tiles[i][j].realCondition==0)
				Tiles[i][j].displayEqualsReal();
			}
		}
	
	}
	
	void readTestFile(int choice)
	{
		flags_remain = 50;

		emptyField();
		ifstream inFile;
		if (choice == 1)
		{
			inFile.open("boards/testboard1.brd");

		}
		if (choice == 2)
		{
			inFile.open("boards/testboard2.brd");

		}
		if (choice == 3) {
			inFile.open("boards/testboard3.brd");
		}
		string temp;
		if (inFile.is_open())
		{
			string temp ;
			int i = 0;
			while (getline(inFile, temp))
			{
					for (int j = 0; j < 25; j++)
					{
							if (j == 24) i++; //change line
							int a = temp[j] - 48;
							cout << a;
							if(a == 1) Tiles[i][j].setRealCondition(0);
					}
					cout << endl;
				

			}
			
		}
		inFile.close();
		setMinesAround();
	}



	void drawAll(RenderWindow &game) {
		game.clear(Color::White);
		drawDigit(game, flags_remain);
		if (isWin == true&&isLost==false) drawBlock(boardSpriteMap["face win"], 368, 520, game);
		if (isWin == false&&isLost==true) drawBlock(boardSpriteMap["face lose"],368,520, game);
		if (isWin == false && isLost == false) drawBlock(boardSpriteMap["face happy"], 368, 520, game); //draw faces...win lose happy

		drawBlock(boardSpriteMap["debug"], 500, 520, game);
		drawBlock(boardSpriteMap["test1"], 567, 520, game);
		drawBlock(boardSpriteMap["test2"], 631, 520, game);
		drawBlock(boardSpriteMap["test3"], 695, 520, game);
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 25; j++) {
				int obj = Tiles[i][j].displayCondition;
				switch (obj) {
				case 0: {
					drawTile(tileSpriteMap["revealed"], i, j, game);
					drawTile(tileSpriteMap["mine"], i, j, game);

					break;

				}
				case 1: {
					drawTile(tileSpriteMap["revealed"], i, j, game);
					drawTile(tileSpriteMap["one"], i, j, game);
					break;
				}
				case 2: {
					drawTile(tileSpriteMap["revealed"], i, j, game);
					drawTile(tileSpriteMap["two"], i, j, game);
					break; }

				case 3: {
					drawTile(tileSpriteMap["revealed"], i, j, game);
					drawTile(tileSpriteMap["three"], i, j, game);
					break; }
				case 4: {
					drawTile(tileSpriteMap["revealed"], i, j, game);
					drawTile(tileSpriteMap["four"], i, j, game);
					break; }
				case 5: {
					drawTile(tileSpriteMap["revealed"], i, j, game);
					drawTile(tileSpriteMap["five"], i, j, game);
					break; }
				case 6: {
					drawTile(tileSpriteMap["revealed"], i, j, game);
					drawTile(tileSpriteMap["six"], i, j, game);
					break; }
				case 7: {
					drawTile(tileSpriteMap["revealed"], i, j, game);
					drawTile(tileSpriteMap["seven"], i, j, game);
					break;
				}
				case 8: {
					drawTile(tileSpriteMap["revealed"], i, j, game);
					drawTile(tileSpriteMap["eight"], i, j, game);
					break; }
				case 9: {
					drawTile(tileSpriteMap["revealed"], i, j, game);
					drawTile(tileSpriteMap["hidden"], i, j, game);
					break;
				}
				case 10: {
					drawTile(tileSpriteMap["revealed"], i, j, game);
					break;
				}

				case 11: {
					drawTile(tileSpriteMap["revealed"], i, j, game);
					drawTile(tileSpriteMap["hidden"], i, j, game);
					drawTile(tileSpriteMap["flag"], i, j, game);
					break;
				}
				case 12: {
					drawTile(tileSpriteMap["revealed"], i, j, game);
					break; 
				}
				case 13: {
					drawTile(tileSpriteMap["revealed"], i, j, game);
					drawTile(tileSpriteMap["mine"], i, j, game);
					drawTile(tileSpriteMap["flag"], i, j, game);
					break;
					}
				}//end of switch

			}




		}

	
	
	}// end of drawAll
};
