// Fill out your copyright notice in the Description page of Project Settings.

#include "Paraglider.h"
#include "WiimoteWrapperComponent.h"
#include "../Public/WiimoteWrapperComponent.h"


// Sets default values for this component's properties
UWiimoteWrapperComponent::UWiimoteWrapperComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UWiimoteWrapperComponent::BeginPlay()
{
	Super::BeginPlay();

	float time = GetTimeSeconds();
	float newTime;
	bool connected;
	do
	{
		connected = _remote.Connect(wiimote::FIRST_AVAILABLE);
		newTime = GetTimeSeconds();
	} while (!connected && (newTime - time <= CONNECTION_WAIT_TIME_SECONDS));

	if (connected)
	{
		DEBUG_LOG("Wiimote found!");
	}
	else
	{
		DEBUG_LOG("Wiimote not found :(");
	}
}


// Called every frame
void UWiimoteWrapperComponent::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

inline float UWiimoteWrapperComponent::GetTimeSeconds()
{
	FDateTime now = FDateTime::Now();
	return now.GetMillisecond() * 0.001f + now.GetSecond() + now.GetMinute() * 60.0f + now.GetHour() * 3600.0f;
}

NATIVE_EVENT void UWiimoteWrapperComponent::Tilt(FVector vec)
{
	return NATIVE_EVENT void();
}

BLUEPRINT_CALLABLE float UWiimoteWrapperComponent::ReturnChuj()
{
	return 3.14f;
}

