// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * 
 */
class PARAGLIDER_API ScoreManagerO
{
private:
	
	TMultiMap<int32, FString> _scores;

public:
	ScoreManagerO();
	~ScoreManagerO();

	void AddScore(int32 score, FString name);
	void GetScoresFormatted(FString* const scoreText, int32 charsPerLine);
	void LoadFromFile();
	void SaveToFile();
};
