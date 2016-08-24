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
#define DEBUG_LOG_STR(a) UE_LOG(LogActor, Error, (a), TEXT(CATEGORY))

#elif

#define DEBUG_LOG(a)

#endif

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWiimoteButtonSignature);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWiimoteOneVectorEventSignature, struct FVector, VectorParam);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PARAGLIDER_API UWiimoteWrapperComponent : public USceneComponent
{
	GENERATED_BODY()

private:

	const float CONNECTION_WAIT_TIME_SECONDS = 1.0f;

	wiimote _remote;
	wiimote_state _prevState;

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

#pragma region ButtonEvents
	
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonA;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonB;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonDUp;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonDDown;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonDLeft;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonDRight;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonHome;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonPlus;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonMinus;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonOne;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonTwo;

	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonAPressed;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonBPressed;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonDUpPressed;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonDDownPressed;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonDLeftPressed;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonDRightPressed;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonHomePressed;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonPlusPressed;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonMinusPressed;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonOnePressed;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonTwoPressed;

	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonAReleased;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonBReleased;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonDUpReleased;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonDDownReleased;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonDLeftReleased;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonDRightReleased;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonHomeReleased;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonPlusReleased;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonMinusReleased;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonOneReleased;
	UPROPERTY(BlueprintAssignable, Category = "WiimoteWrapper") FWiimoteButtonSignature OnButtonTwoReleased;
	
#pragma endregion

#pragma region Functions

	UFUNCTION(BlueprintCallable, Category = "WiimoteWrapper") FVector WiimoteTilt();
	UFUNCTION(BlueprintCallable, Category = "WiimoteWrapper") FVector WiimoteRotationRate();
	UFUNCTION(BlueprintCallable, Category = "WiimoteWrapper") FVector WiimoteAcceleration();
	UFUNCTION(BlueprintCallable, Category = "WiimoteWrapper") void CalibrateAtRest();

#pragma endregion
};
