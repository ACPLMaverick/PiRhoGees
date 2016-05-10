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

#ifdef ENABLE_DEBUG_LOGS

#define DEBUG_LOG(a) UE_LOG(LogActor, Error, TEXT(a), TEXT(CATEGORY))

#elif

#define DEBUG_LOG(a)

#endif

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWiimoteOneVectorEventSignature, struct FVector, VectorParam);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARAGLIDER_API UWiimoteWrapperComponent : public USceneComponent
{
	GENERATED_BODY()

private:

	const float CONNECTION_WAIT_TIME_SECONDS = 5.0f;

	wiimote _remote;

	FVector _prevAcceleration;
	FVector _prevSpeed;
	FVector _prevOrientation;

	inline float GetTimeSeconds();
	static void OnRemoteStateChanged(wiimote &remote, state_change_flags changed, const wiimote_state &newState);
public:	
	// Sets default values for this component's properties
	UWiimoteWrapperComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	// This is called immediately upon deciding to destroy the object, to allow the object to begin an asynchronous cleanup process
	virtual void BeginDestroy() override;

#pragma region Events

	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteOneVectorEventSignature OnOrientationChanged;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteOneVectorEventSignature OnAccelerationChanged;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteOneVectorEventSignature OnSpeedChanged;

#pragma endregion

#pragma region Functions

	UFUNCTION(BlueprintCallable, Category = "WiimoteWrapper") float ReturnChuj();

#pragma endregion
};
