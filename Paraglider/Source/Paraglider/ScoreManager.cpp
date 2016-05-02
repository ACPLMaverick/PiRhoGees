// Fill out your copyright notice in the Description page of Project Settings.

#include "Paraglider.h"
#include "ScoreManager.h"

#include <FileManager.h>
#include <Archive.h>
#include <ArchiveBase.h>

// Sets default values
AScoreManager::AScoreManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AScoreManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AScoreManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AScoreManager::AddScore(int32 score, FString name)
{
	_scores.Add(score, name);
	_scores.KeySort([](int32 A, int32 B)
	{
		return A > B;
	});
}

void AScoreManager::GetScoresFormatted(TArray<FString> &scoreArray, int32 charsPerLine)
{
	scoreArray.Empty();

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

		scoreArray.Add(line);
	}
}

void AScoreManager::GetScores(TArray<int32>& pointArray, TArray<FString>& nameArray)
{
	_scores.GenerateKeyArray(pointArray);
	_scores.GenerateValueArray(nameArray);
}

bool AScoreManager::LoadFromFile()
{
	TArray<uint8> binaryArray;
	bool bSuccess = FFileHelper::LoadFileToArray(binaryArray, _saveFilePath.GetCharArray().GetData());

	if (bSuccess)
	{
		UE_LOG(LogActor, Warning, TEXT("Load successful"), TEXT("ScoreManager"));
	}
	else
	{
		UE_LOG(LogActor, Error, TEXT("Load failed"), TEXT("ScoreManager"));
		binaryArray.Empty();
		return false;
	}

	FMemoryReader fromBinary = FMemoryReader(binaryArray, true);
	fromBinary.Seek(0);

	fromBinary << _scores;

	fromBinary.FlushCache();
	fromBinary.Close();

	return true;
}

bool AScoreManager::SaveToFile()
{
	FBufferArchive archive;
	archive << _scores;

	bool bSuccess = FFileHelper::SaveArrayToFile(archive, _saveFilePath.GetCharArray().GetData());

	if (bSuccess)
	{
		UE_LOG(LogActor, Warning, TEXT("Save successful"), TEXT("ScoreManager"));
	}
	else
	{
		UE_LOG(LogActor, Error, TEXT("Save failed"), TEXT("ScoreManager"));
	}

	archive.FlushCache();
	archive.Empty();

	return bSuccess;
}