#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include "GUI.h"

class HighScores : public GUI
{
	sf::RectangleShape backgroundRect;
	sf::Texture bgImage;

	std::ifstream readFs;
	std::ofstream writeFs;

	sf::Font square721bt, square721ExtendedBT;

	sf::Text highScoresHeader;

	sf::RectangleShape scoresRect;
	std::vector<sf::Text> rankNumberTexts;
	std::vector<sf::Text> nameTexts;
	std::vector<sf::Text> scoreTexts;
	std::vector<sf::Text> linesTexts;
	std::vector<std::string> names;
	std::vector<unsigned int> scores;
	std::vector<unsigned int> lines;

	sf::Music bgm;

public:
	HighScores();

	short determineRank(unsigned int score);

	void updateHighScores(std::string &name, unsigned int score, unsigned int lineNum, short rank);


private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};