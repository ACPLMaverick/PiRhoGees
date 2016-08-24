// Fill out your copyright notice in the Description page of Project Settings.

#include "Paraglider.h"
#include "BezierWrapperComponent.h"


// Sets default values for this component's properties
UBezierWrapperComponent::UBezierWrapperComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBezierWrapperComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBezierWrapperComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

float UBezierWrapperComponent::EvalBezier(FVector vert1, FVector vert2, FVector cp1, FVector cp2, int32 NumPoints, TArray<FVector>& OutPoints)
{
	FVector tab[4]{ vert1, cp1, cp2, vert2 };
	return FVector::EvaluateBezier(tab, NumPoints, OutPoints);
}