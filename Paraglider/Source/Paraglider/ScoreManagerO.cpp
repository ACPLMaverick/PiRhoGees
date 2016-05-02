// Fill out your copyright notice in the Description page of Project Settings.

#include "Paraglider.h"
#include "ScoreManagerO.h"

ScoreManagerO::ScoreManagerO()
{
}

ScoreManagerO::~ScoreManagerO()
{
}

void ScoreManagerO::AddScore(int32 score, FString name)
{
	_scores.Add(score, name);
}

void ScoreManagerO::GetScoresFormatted(FString * const scoreText, int32 charsPerLine)
{
	scoreText->Reset();

	TArray<int32> pointsArray;
	TArray<FString> namesArray;

	_scores.GenerateKeyArray(pointsArray);
	_scores.GenerateValueArray(namesArray);

	int32 count = _scores.Num();
	FString line, pointsStr, nameStr;
	int32 countCharsPoints, countCharsName, charsSpace;

	for (int32 i = 0; i < count; ++i)
	{
		line.Reset();

		pointsStr = FString::FromInt(pointsArray[i]);
		nameStr = namesArray[i];
		countCharsPoints = pointsStr.Len();
		countCharsName = nameStr.Len();
		charsSpace = charsPerLine - countCharsPoints - countCharsName;

		if (charsSpace < 0)
		{
			charsSpace = 0;
		}

		line.Append(pointsStr);

		for (int32 j = 0; j < charsSpace; ++j)
		{
			line.Append(" ");
		}

		line.Append(nameStr);

		scoreText->Append(line);
		scoreText->AppendChar('\n');
	}
}

void ScoreManagerO::LoadFromFile()
{
}

void ScoreManagerO::SaveToFile()
{
}
