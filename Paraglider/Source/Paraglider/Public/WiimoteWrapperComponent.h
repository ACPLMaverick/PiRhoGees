// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Paraglider.h"
#include "Components/ActorComponent.h"

#include "AllowWindowsPlatformTypes.h"
#include "WiimoteLib/wiimote.h"
#include "HideWindowsPlatformTypes.h"

#include "WiimoteWrapperComponent.generated.h"

#define ENABLE_DEBUG_LOGS
#define CATEGORY "WiimoteWrapper"
#define NATIVE_EVENT UFUNCTION(BlueprintNativeEvent, Category = CATEGORY)
#define BLUEPRINT_CALLABLE UFUNCTION(BlueprintCallable, Category = CATEGORY)

#ifdef ENABLE_DEBUG_LOGS

#define DEBUG_LOG(a) UE_LOG(LogActor, Error, TEXT(a), TEXT(CATEGORY))

#elif

#define DEBUG_LOG(a)

#endif

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARAGLIDER_API UWiimoteWrapperComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	const float CONNECTION_WAIT_TIME_SECONDS = 5.0f;

	wiimote _remote;

	inline float GetTimeSeconds();

public:	
	// Sets default values for this component's properties
	UWiimoteWrapperComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

#pragma region Events

	NATIVE_EVENT void Tilt(FVector vec);
	BLUEPRINT_CALLABLE float ReturnChuj();

#pragma endregion
};
