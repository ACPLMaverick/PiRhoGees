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

	_remote.ChangedCallback = OnRemoteStateChanged;
	_remote.CallbackTriggerFlags = (state_change_flags)(CONNECTED |
		WIIMOTE_CHANGED |
		EXTENSION_CHANGED |
		MOTIONPLUS_CHANGED);
	_remote.wrapperRef = this;

	do
	{
		connected = _remote.Connect(wiimote::FIRST_AVAILABLE, false);
		newTime = GetTimeSeconds();
	} while (!connected && (newTime - time <= CONNECTION_WAIT_TIME_SECONDS));

	if (_remote.IsConnected())
	{
		DEBUG_LOG("Wiimote found!");

		_remote.SetLEDs(1 | (1 << 3));
		_remote.RefreshState();
		
		_prevState = (wiimote_state)_remote;
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

	if (_remote.IsConnected())
	{
		state_change_flags sc = _remote.RefreshState();
	}
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
	// from example code

			if (changed & CONNECTED)
			{
				// ask the wiimote to report everything (using the 'non-continous updates'
				//  default mode - updates will be frequent anyway due to the acceleration/IR
				//  values changing):

				// note1: you don't need to set a report type for Balance Boards - the
				//		   library does it automatically.

				// note2: for wiimotes, the report mode that includes the extension data
				//		   unfortunately only reports the 'BASIC' IR info (ie. no dot sizes),
				//		   so let's choose the best mode based on the extension status:
				if (newState.ExtensionType != wiimote::BALANCE_BOARD)
				{
					if (newState.bExtension)
						remote.SetReportType(wiimote::IN_BUTTONS_ACCEL_IR_EXT); // no IR dots
					else
						remote.SetReportType(wiimote::IN_BUTTONS_ACCEL_IR);		//    IR dots
				}
			}
			// a MotionPlus was detected
			if (changed & MOTIONPLUS_DETECTED)
			{
				// enable it if there isn't a normal extension plugged into it
				// (MotionPlus devices don't report like normal extensions until
				//  enabled - and then, other extensions attached to it will no longer be
				//  reported (so disable the M+ when you want to access them again).
				if (remote.ExtensionType == wiimote_state::NONE) {
					bool res = remote.EnableMotionPlus();
				}
			}
			// an extension is connected to the MotionPlus
			else if (changed & MOTIONPLUS_EXTENSION_CONNECTED)
			{
				// We can't read it if the MotionPlus is currently enabled, so disable it:
				if (remote.MotionPlusEnabled())
					remote.DisableMotionPlus();
			}
			// an extension disconnected from the MotionPlus
			else if (changed & MOTIONPLUS_EXTENSION_DISCONNECTED)
			{
				// enable the MotionPlus data again:
				if (remote.MotionPlusConnected())
					remote.EnableMotionPlus();
			}
			// another extension was just connected:
			else if (changed & EXTENSION_CONNECTED)
			{
				// switch to a report mode that includes the extension data (we will
				//  loose the IR dot sizes)
				// note: there is no need to set report types for a Balance Board.
				if (!remote.IsBalanceBoard())
					remote.SetReportType(wiimote::IN_BUTTONS_ACCEL_IR_EXT);
			}
			// extension was just disconnected:
			else if (changed & EXTENSION_DISCONNECTED)
			{
				// use a non-extension report mode (this gives us back the IR dot sizes)
				remote.SetReportType(wiimote::IN_BUTTONS_ACCEL_IR);
			}

	//
	FVector orientationVector, accelerationVector, speedVector;

	orientationVector.X = newState.Acceleration.Orientation.Pitch;
	orientationVector.Y = 0.0f;
	orientationVector.Z = newState.Acceleration.Orientation.Roll;

	accelerationVector.X = newState.Acceleration.X;
	accelerationVector.Y = newState.Acceleration.Y;
	accelerationVector.Z = newState.Acceleration.Z;

	speedVector.X = newState.MotionPlus.Speed.Pitch;
	speedVector.Y = newState.MotionPlus.Speed.Yaw;
	speedVector.Z = newState.MotionPlus.Speed.Roll;

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

#pragma region inputEventsCodeshit

	// fire appropriate input events
	wiimote_state prevState = remote.wrapperRef->_prevState;
	if (newState.Button.A())
	{
		remote.wrapperRef->OnButtonA.Broadcast();
	}
	if (newState.Button.B())
	{
		remote.wrapperRef->OnButtonB.Broadcast();
	}
	if (newState.Button.Up())
	{
		remote.wrapperRef->OnButtonDUp.Broadcast();
	}
	if (newState.Button.Down())
	{
		remote.wrapperRef->OnButtonDDown.Broadcast();
	}
	if (newState.Button.Left())
	{
		remote.wrapperRef->OnButtonDLeft.Broadcast();
	}
	if (newState.Button.Right())
	{
		remote.wrapperRef->OnButtonDRight.Broadcast();
	}
	if (newState.Button.Home())
	{
		remote.wrapperRef->OnButtonHome.Broadcast();
	}
	if (newState.Button.Plus())
	{
		remote.wrapperRef->OnButtonPlus.Broadcast();
	}
	if (newState.Button.Minus())
	{
		remote.wrapperRef->OnButtonMinus.Broadcast();
	}
	if (newState.Button.One())
	{
		remote.wrapperRef->OnButtonOne.Broadcast();
	}
	if (newState.Button.Two())
	{
		remote.wrapperRef->OnButtonTwo.Broadcast();
	}

	if (newState.Button.A() && !prevState.Button.A())
	{
		remote.wrapperRef->OnButtonAPressed.Broadcast();
	}
	if (newState.Button.B() && !prevState.Button.B())
	{
		remote.wrapperRef->OnButtonBPressed.Broadcast();
	}
	if (newState.Button.Up() && !prevState.Button.Up())
	{
		remote.wrapperRef->OnButtonDUpPressed.Broadcast();
	}
	if (newState.Button.Down() && !prevState.Button.Down())
	{
		remote.wrapperRef->OnButtonDDownPressed.Broadcast();
	}
	if (newState.Button.Left() && !prevState.Button.Left())
	{
		remote.wrapperRef->OnButtonDLeftPressed.Broadcast();
	}
	if (newState.Button.Right() && !prevState.Button.Right())
	{
		remote.wrapperRef->OnButtonDRightPressed.Broadcast();
	}
	if (newState.Button.Home() && !prevState.Button.Home())
	{
		remote.wrapperRef->OnButtonHomePressed.Broadcast();
	}
	if (newState.Button.Plus() && !prevState.Button.Plus())
	{
		remote.wrapperRef->OnButtonPlusPressed.Broadcast();
	}
	if (newState.Button.Minus() && !prevState.Button.Minus())
	{
		remote.wrapperRef->OnButtonMinusPressed.Broadcast();
	}
	if (newState.Button.One() && !prevState.Button.One())
	{
		remote.wrapperRef->OnButtonOnePressed.Broadcast();
	}
	if (newState.Button.Two() && !prevState.Button.Two())
	{
		remote.wrapperRef->OnButtonTwoPressed.Broadcast();
	}

	if (!newState.Button.A() && prevState.Button.A())
	{
		remote.wrapperRef->OnButtonAReleased.Broadcast();
	}
	if (!newState.Button.B() && prevState.Button.B())
	{
		remote.wrapperRef->OnButtonBReleased.Broadcast();
	}
	if (!newState.Button.Up() && prevState.Button.Up())
	{
		remote.wrapperRef->OnButtonDUpReleased.Broadcast();
	}
	if (!newState.Button.Down() && prevState.Button.Down())
	{
		remote.wrapperRef->OnButtonDDownReleased.Broadcast();
	}
	if (!newState.Button.Left() && prevState.Button.Left())
	{
		remote.wrapperRef->OnButtonDLeftReleased.Broadcast();
	}
	if (!newState.Button.Right() && prevState.Button.Right())
	{
		remote.wrapperRef->OnButtonDRightReleased.Broadcast();
	}
	if (!newState.Button.Home() && prevState.Button.Home())
	{
		remote.wrapperRef->OnButtonHomeReleased.Broadcast();
	}
	if (!newState.Button.Plus() && prevState.Button.Plus())
	{
		remote.wrapperRef->OnButtonPlusReleased.Broadcast();
	}
	if (!newState.Button.Minus() && prevState.Button.Minus())
	{
		remote.wrapperRef->OnButtonMinusReleased.Broadcast();
	}
	if (!newState.Button.One() && prevState.Button.One())
	{
		remote.wrapperRef->OnButtonOneReleased.Broadcast();
	}
	if (!newState.Button.Two() && prevState.Button.Two())
	{
		remote.wrapperRef->OnButtonTwoReleased.Broadcast();
	}

#pragma endregion

	// set current state as new
	remote.wrapperRef->_prevState = newState;
}

FVector UWiimoteWrapperComponent::WiimoteTilt()
{
	return FVector(_remote.Acceleration.Orientation.Pitch, 0.0f, _remote.Acceleration.Orientation.Roll);
}

FVector UWiimoteWrapperComponent::WiimoteRotationRate()
{
	return FVector(_remote.MotionPlus.Speed.Pitch, _remote.MotionPlus.Speed.Yaw, _remote.MotionPlus.Speed.Roll);
}

FVector UWiimoteWrapperComponent::WiimoteAcceleration()
{
	return FVector(_remote.Acceleration.X, _remote.Acceleration.Y, _remote.Acceleration.Z);
}

void UWiimoteWrapperComponent::CalibrateAtRest()
{
	_remote.CalibrateAtRest();
}
