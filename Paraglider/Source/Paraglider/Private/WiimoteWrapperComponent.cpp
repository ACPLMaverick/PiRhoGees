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

	if (_remote.IsConnected())
	{
		DEBUG_LOG("Wiimote found!");

		_remote.SetLEDs(1 | (1 << 3));
		_remote.ChangedCallback = OnRemoteStateChanged;
		_remote.CallbackTriggerFlags = (state_change_flags)(CONNECTED |
			WIIMOTE_CHANGED |
			EXTENSION_CHANGED |
			MOTIONPLUS_CHANGED);
		if (_remote.MotionPlusConnected())
		{
			_remote.EnableMotionPlus();
		}
		_remote.wrapperRef = this;
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

void UWiimoteWrapperComponent::BeginDestroy()
{
	if (_remote.IsConnected())
	{
		_remote.Disconnect();
	}

	Super::BeginDestroy();
}

inline float UWiimoteWrapperComponent::GetTimeSeconds()
{
	FDateTime now = FDateTime::Now();
	return now.GetMillisecond() * 0.001f + now.GetSecond() + now.GetMinute() * 60.0f + now.GetHour() * 3600.0f;
}

void UWiimoteWrapperComponent::OnRemoteStateChanged(wiimote & remote, state_change_flags changed, const wiimote_state & newState)
{
	FVector orientationVector, accelerationVector, speedVector;

	orientationVector.X = remote.Acceleration.Orientation.Pitch;
	orientationVector.Y = 0.0f;
	orientationVector.Z = remote.Acceleration.Orientation.Roll;

	accelerationVector.X = remote.Acceleration.X;
	accelerationVector.Y = remote.Acceleration.Y;
	accelerationVector.Z = remote.Acceleration.Z;

	speedVector.X = remote.MotionPlus.Speed.Pitch;
	speedVector.Y = remote.MotionPlus.Speed.Yaw;
	speedVector.Z = remote.MotionPlus.Speed.Roll;

	if (remote.wrapperRef != nullptr)
	{
		if (!orientationVector.Equals(remote.wrapperRef->_prevOrientation))
		{
			remote.wrapperRef->_prevOrientation = orientationVector;
			remote.wrapperRef->OnOrientationChanged.Broadcast(orientationVector);
		}

		if (!accelerationVector.Equals(remote.wrapperRef->_prevAcceleration))
		{
			remote.wrapperRef->_prevAcceleration = accelerationVector;
			remote.wrapperRef->OnAccelerationChanged.Broadcast(accelerationVector);
		}

		if (!speedVector.Equals(remote.wrapperRef->_prevSpeed))
		{
			remote.wrapperRef->_prevSpeed = speedVector;
			remote.wrapperRef->OnSpeedChanged.Broadcast(speedVector);
		}
	}
}

//void UWiimoteWrapperComponent::Tilt(FVector vec)
//{
//	return;
//}

float UWiimoteWrapperComponent::ReturnChuj()
{
	return 3.14f;
}

