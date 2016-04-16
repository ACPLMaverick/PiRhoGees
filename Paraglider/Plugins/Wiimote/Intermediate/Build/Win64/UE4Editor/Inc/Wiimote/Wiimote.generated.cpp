// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Boilerplate C++ definitions for a single module.
	This is automatically generated by UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "Private/WiimotePrivatePCH.h"
#include "Wiimote.generated.dep.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeWiimote() {}
	void UWiimoteFunctionLibrary::StaticRegisterNativesUWiimoteFunctionLibrary()
	{
		FNativeFunctionRegistrar::RegisterFunction(UWiimoteFunctionLibrary::StaticClass(),"SetIREnabled",(Native)&UWiimoteFunctionLibrary::execSetIREnabled);
		FNativeFunctionRegistrar::RegisterFunction(UWiimoteFunctionLibrary::StaticClass(),"SetMotionPlusEnabled",(Native)&UWiimoteFunctionLibrary::execSetMotionPlusEnabled);
		FNativeFunctionRegistrar::RegisterFunction(UWiimoteFunctionLibrary::StaticClass(),"SetMotionSensingEnabled",(Native)&UWiimoteFunctionLibrary::execSetMotionSensingEnabled);
		FNativeFunctionRegistrar::RegisterFunction(UWiimoteFunctionLibrary::StaticClass(),"SetRumbleEnabled",(Native)&UWiimoteFunctionLibrary::execSetRumbleEnabled);
	}
	IMPLEMENT_CLASS(UWiimoteFunctionLibrary, 826146795);
#if USE_COMPILED_IN_NATIVES
// Cross Module References
	ENGINE_API class UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();

	WIIMOTE_API class UFunction* Z_Construct_UFunction_UWiimoteFunctionLibrary_SetIREnabled();
	WIIMOTE_API class UFunction* Z_Construct_UFunction_UWiimoteFunctionLibrary_SetMotionPlusEnabled();
	WIIMOTE_API class UFunction* Z_Construct_UFunction_UWiimoteFunctionLibrary_SetMotionSensingEnabled();
	WIIMOTE_API class UFunction* Z_Construct_UFunction_UWiimoteFunctionLibrary_SetRumbleEnabled();
	WIIMOTE_API class UClass* Z_Construct_UClass_UWiimoteFunctionLibrary_NoRegister();
	WIIMOTE_API class UClass* Z_Construct_UClass_UWiimoteFunctionLibrary();
	WIIMOTE_API class UPackage* Z_Construct_UPackage_Wiimote();
	UFunction* Z_Construct_UFunction_UWiimoteFunctionLibrary_SetIREnabled()
	{
		struct WiimoteFunctionLibrary_eventSetIREnabled_Parms
		{
			int32 ControllerId;
			bool IsEnabled;
		};
		UObject* Outer=Z_Construct_UClass_UWiimoteFunctionLibrary();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("SetIREnabled"), RF_Public|RF_Transient|RF_Native) UFunction(FObjectInitializer(), NULL, 0x04022401, 65535, sizeof(WiimoteFunctionLibrary_eventSetIREnabled_Parms));
			CPP_BOOL_PROPERTY_BITMASK_STRUCT(IsEnabled, WiimoteFunctionLibrary_eventSetIREnabled_Parms, bool);
			UProperty* NewProp_IsEnabled = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("IsEnabled"), RF_Public|RF_Transient|RF_Native) UBoolProperty(FObjectInitializer(), EC_CppProperty, CPP_BOOL_PROPERTY_OFFSET(IsEnabled, WiimoteFunctionLibrary_eventSetIREnabled_Parms), 0x0000000000000080, CPP_BOOL_PROPERTY_BITMASK(IsEnabled, WiimoteFunctionLibrary_eventSetIREnabled_Parms), sizeof(bool), true);
			UProperty* NewProp_ControllerId = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ControllerId"), RF_Public|RF_Transient|RF_Native) UIntProperty(CPP_PROPERTY_BASE(ControllerId, WiimoteFunctionLibrary_eventSetIREnabled_Parms), 0x0000000000000080);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Wiimote"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Public/WiimoteFunctionLibrary.h"));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_UWiimoteFunctionLibrary_SetMotionPlusEnabled()
	{
		struct WiimoteFunctionLibrary_eventSetMotionPlusEnabled_Parms
		{
			int32 ControllerId;
			bool IsEnabled;
		};
		UObject* Outer=Z_Construct_UClass_UWiimoteFunctionLibrary();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("SetMotionPlusEnabled"), RF_Public|RF_Transient|RF_Native) UFunction(FObjectInitializer(), NULL, 0x04022401, 65535, sizeof(WiimoteFunctionLibrary_eventSetMotionPlusEnabled_Parms));
			CPP_BOOL_PROPERTY_BITMASK_STRUCT(IsEnabled, WiimoteFunctionLibrary_eventSetMotionPlusEnabled_Parms, bool);
			UProperty* NewProp_IsEnabled = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("IsEnabled"), RF_Public|RF_Transient|RF_Native) UBoolProperty(FObjectInitializer(), EC_CppProperty, CPP_BOOL_PROPERTY_OFFSET(IsEnabled, WiimoteFunctionLibrary_eventSetMotionPlusEnabled_Parms), 0x0000000000000080, CPP_BOOL_PROPERTY_BITMASK(IsEnabled, WiimoteFunctionLibrary_eventSetMotionPlusEnabled_Parms), sizeof(bool), true);
			UProperty* NewProp_ControllerId = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ControllerId"), RF_Public|RF_Transient|RF_Native) UIntProperty(CPP_PROPERTY_BASE(ControllerId, WiimoteFunctionLibrary_eventSetMotionPlusEnabled_Parms), 0x0000000000000080);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Wiimote"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Public/WiimoteFunctionLibrary.h"));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_UWiimoteFunctionLibrary_SetMotionSensingEnabled()
	{
		struct WiimoteFunctionLibrary_eventSetMotionSensingEnabled_Parms
		{
			int32 ControllerId;
			bool IsEnabled;
		};
		UObject* Outer=Z_Construct_UClass_UWiimoteFunctionLibrary();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("SetMotionSensingEnabled"), RF_Public|RF_Transient|RF_Native) UFunction(FObjectInitializer(), NULL, 0x04022401, 65535, sizeof(WiimoteFunctionLibrary_eventSetMotionSensingEnabled_Parms));
			CPP_BOOL_PROPERTY_BITMASK_STRUCT(IsEnabled, WiimoteFunctionLibrary_eventSetMotionSensingEnabled_Parms, bool);
			UProperty* NewProp_IsEnabled = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("IsEnabled"), RF_Public|RF_Transient|RF_Native) UBoolProperty(FObjectInitializer(), EC_CppProperty, CPP_BOOL_PROPERTY_OFFSET(IsEnabled, WiimoteFunctionLibrary_eventSetMotionSensingEnabled_Parms), 0x0000000000000080, CPP_BOOL_PROPERTY_BITMASK(IsEnabled, WiimoteFunctionLibrary_eventSetMotionSensingEnabled_Parms), sizeof(bool), true);
			UProperty* NewProp_ControllerId = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ControllerId"), RF_Public|RF_Transient|RF_Native) UIntProperty(CPP_PROPERTY_BASE(ControllerId, WiimoteFunctionLibrary_eventSetMotionSensingEnabled_Parms), 0x0000000000000080);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Wiimote"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Public/WiimoteFunctionLibrary.h"));
#endif
		}
		return ReturnFunction;
	}
	UFunction* Z_Construct_UFunction_UWiimoteFunctionLibrary_SetRumbleEnabled()
	{
		struct WiimoteFunctionLibrary_eventSetRumbleEnabled_Parms
		{
			int32 ControllerId;
			bool IsEnabled;
		};
		UObject* Outer=Z_Construct_UClass_UWiimoteFunctionLibrary();
		static UFunction* ReturnFunction = NULL;
		if (!ReturnFunction)
		{
			ReturnFunction = new(EC_InternalUseOnlyConstructor, Outer, TEXT("SetRumbleEnabled"), RF_Public|RF_Transient|RF_Native) UFunction(FObjectInitializer(), NULL, 0x04022401, 65535, sizeof(WiimoteFunctionLibrary_eventSetRumbleEnabled_Parms));
			CPP_BOOL_PROPERTY_BITMASK_STRUCT(IsEnabled, WiimoteFunctionLibrary_eventSetRumbleEnabled_Parms, bool);
			UProperty* NewProp_IsEnabled = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("IsEnabled"), RF_Public|RF_Transient|RF_Native) UBoolProperty(FObjectInitializer(), EC_CppProperty, CPP_BOOL_PROPERTY_OFFSET(IsEnabled, WiimoteFunctionLibrary_eventSetRumbleEnabled_Parms), 0x0000000000000080, CPP_BOOL_PROPERTY_BITMASK(IsEnabled, WiimoteFunctionLibrary_eventSetRumbleEnabled_Parms), sizeof(bool), true);
			UProperty* NewProp_ControllerId = new(EC_InternalUseOnlyConstructor, ReturnFunction, TEXT("ControllerId"), RF_Public|RF_Transient|RF_Native) UIntProperty(CPP_PROPERTY_BASE(ControllerId, WiimoteFunctionLibrary_eventSetRumbleEnabled_Parms), 0x0000000000000080);
			ReturnFunction->Bind();
			ReturnFunction->StaticLink();
#if WITH_METADATA
			UMetaData* MetaData = ReturnFunction->GetOutermost()->GetMetaData();
			MetaData->SetValue(ReturnFunction, TEXT("Category"), TEXT("Wiimote"));
			MetaData->SetValue(ReturnFunction, TEXT("ModuleRelativePath"), TEXT("Public/WiimoteFunctionLibrary.h"));
#endif
		}
		return ReturnFunction;
	}
	UClass* Z_Construct_UClass_UWiimoteFunctionLibrary_NoRegister()
	{
		return UWiimoteFunctionLibrary::StaticClass();
	}
	UClass* Z_Construct_UClass_UWiimoteFunctionLibrary()
	{
		static UClass* OuterClass = NULL;
		if (!OuterClass)
		{
			Z_Construct_UClass_UBlueprintFunctionLibrary();
			Z_Construct_UPackage_Wiimote();
			OuterClass = UWiimoteFunctionLibrary::StaticClass();
			if (!(OuterClass->ClassFlags & CLASS_Constructed))
			{
				UObjectForceRegistration(OuterClass);
				OuterClass->ClassFlags |= 0x20100080;

				OuterClass->LinkChild(Z_Construct_UFunction_UWiimoteFunctionLibrary_SetIREnabled());
				OuterClass->LinkChild(Z_Construct_UFunction_UWiimoteFunctionLibrary_SetMotionPlusEnabled());
				OuterClass->LinkChild(Z_Construct_UFunction_UWiimoteFunctionLibrary_SetMotionSensingEnabled());
				OuterClass->LinkChild(Z_Construct_UFunction_UWiimoteFunctionLibrary_SetRumbleEnabled());

				OuterClass->AddFunctionToFunctionMap(Z_Construct_UFunction_UWiimoteFunctionLibrary_SetIREnabled()); // 3575805556
				OuterClass->AddFunctionToFunctionMap(Z_Construct_UFunction_UWiimoteFunctionLibrary_SetMotionPlusEnabled()); // 950275954
				OuterClass->AddFunctionToFunctionMap(Z_Construct_UFunction_UWiimoteFunctionLibrary_SetMotionSensingEnabled()); // 299549287
				OuterClass->AddFunctionToFunctionMap(Z_Construct_UFunction_UWiimoteFunctionLibrary_SetRumbleEnabled()); // 2181120093
				OuterClass->StaticLink();
#if WITH_METADATA
				UMetaData* MetaData = OuterClass->GetOutermost()->GetMetaData();
				MetaData->SetValue(OuterClass, TEXT("IncludePath"), TEXT("WiimoteFunctionLibrary.h"));
				MetaData->SetValue(OuterClass, TEXT("ModuleRelativePath"), TEXT("Public/WiimoteFunctionLibrary.h"));
#endif
			}
		}
		check(OuterClass->GetClass());
		return OuterClass;
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_UWiimoteFunctionLibrary(Z_Construct_UClass_UWiimoteFunctionLibrary, TEXT("UWiimoteFunctionLibrary"));
	DEFINE_VTABLE_PTR_HELPER_CTOR(UWiimoteFunctionLibrary);
	UPackage* Z_Construct_UPackage_Wiimote()
	{
		static UPackage* ReturnPackage = NULL;
		if (!ReturnPackage)
		{
			ReturnPackage = CastChecked<UPackage>(StaticFindObjectFast(UPackage::StaticClass(), NULL, FName(TEXT("/Script/Wiimote")), false, false));
			ReturnPackage->SetPackageFlags(PKG_CompiledIn | 0x00000000);
			FGuid Guid;
			Guid.A = 0x862A5FB4;
			Guid.B = 0x2050BD89;
			Guid.C = 0x00000000;
			Guid.D = 0x00000000;
			ReturnPackage->SetGuid(Guid);

		}
		return ReturnPackage;
	}
#endif

PRAGMA_ENABLE_DEPRECATION_WARNINGS
