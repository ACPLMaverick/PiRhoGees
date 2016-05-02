// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ScoreManager.generated.h"

UCLASS()
class PARAGLIDER_API AScoreManager : public AActor
{
	GENERATED_BODY()

private:

	TMultiMap<int32, FString> _scores;
	FString _saveFilePath = FPaths::GameSavedDir() + "\\scores.bin";

public:	
	// Sets default values for this actor's properties
	AScoreManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	UFUNCTION(BlueprintCallable, Category = "ScoreManager") void AddScore(int32 score, FString name);
	UFUNCTION(BlueprintCallable, Category = "ScoreManager") void GetScoresFormatted(TArray<FString> &scoreArray, int32 charsPerLine);
	UFUNCTION(BlueprintCallable, Category = "ScoreManager") void GetScores(TArray<int32> &pointArray, TArray<FString> &nameArray);
	UFUNCTION(BlueprintCallable, Category = "ScoreManager") bool LoadFromFile();
	UFUNCTION(BlueprintCallable, Category = "ScoreManager") bool SaveToFile();
};
