#pragma once
#include <SFML/Graphics.hpp>
#include <map>
using namespace std;
using namespace sf;
class textureManage {
public:
	Texture one;
	Texture two;
	Texture three;
	Texture four;
	Texture five;
	Texture six;
	Texture seven;
	Texture eight;
	Texture hidden;
	Texture revealed;
	Texture flag;
	Texture mine;
	Texture debug;
	Texture digits;
	Texture faceHappy;
	Texture faceLose;
	Texture faceWin;
	Texture test1;
	Texture test2;
	Texture test3;

	map<string, Sprite> tileTextures() {
		map<string, Sprite> tileSprites;
		one.loadFromFile("images/number_1.png");//1

		tileSprites.emplace("one", Sprite(one));

		two.loadFromFile("images/number_2.png");//2
		tileSprites.emplace("two", Sprite(two));

		three.loadFromFile("images/number_3.png");//3
		tileSprites.emplace("three", Sprite(three));

		four.loadFromFile("images/number_4.png");//4
		tileSprites.emplace("four", Sprite(four));

		five.loadFromFile("images/number_5.png");//5
		tileSprites.emplace("five", Sprite(five));

		six.loadFromFile("images/number_6.png");//6
		tileSprites.emplace("six", Sprite(six));

		seven.loadFromFile("images/number_7.png");//7
		tileSprites.emplace("seven", Sprite(seven));

		eight.loadFromFile("images/number_8.png");//8
		tileSprites.emplace("eight", Sprite(eight));

		hidden.loadFromFile("images/tile_hidden.png");//9
		tileSprites.emplace("hidden", Sprite(hidden));

		revealed.loadFromFile("images/tile_revealed.png");//10
		tileSprites.emplace("revealed", Sprite(revealed));

		flag.loadFromFile("images/flag.png");//11
		tileSprites.emplace("flag", Sprite(flag));

		mine.loadFromFile("images/mine.png");//0
		tileSprites.emplace("mine", Sprite(mine));
		return tileSprites;
	}
	map<string, Sprite> boardElements() {
	
		map<string, Sprite> elementSprites;
		debug.loadFromFile("images/debug.png");
		elementSprites.emplace("debug", Sprite(debug));

		digits.loadFromFile("images/digits.png");
		elementSprites.emplace("digits", Sprite(digits));

		faceHappy.loadFromFile("images/face_happy.png");
		elementSprites.emplace("face happy", Sprite(faceHappy));

		faceLose.loadFromFile("images/face_lose.png");
		elementSprites.emplace("face lose", Sprite(faceLose));

		faceWin.loadFromFile("images/face_win.png");
		elementSprites.emplace("face win", Sprite(faceWin));

		test1.loadFromFile("images/test_1.png");
		elementSprites.emplace("test1", Sprite(test1));

		test2.loadFromFile("images/test_2.png");
		elementSprites.emplace("test2", Sprite(test2));

		test3.loadFromFile("images/test_3.png");
		elementSprites.emplace("test3", Sprite(test3));

		return elementSprites;
	
	}
	
};