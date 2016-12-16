// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	C++ class header boilerplate exported from UnrealHeaderTool.
	This is automatically generated by the tools.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

PRAGMA_DISABLE_DEPRECATION_WARNINGS
#ifdef PROJECTXYZ_PlayerCharacterController_generated_h
#error "PlayerCharacterController.generated.h already included, missing '#pragma once' in PlayerCharacterController.h"
#endif
#define PROJECTXYZ_PlayerCharacterController_generated_h

#define ProjectXYZ_Source_ProjectXYZ_PlayerCharacterController_h_16_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execMoveToWaypoint) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->MoveToWaypoint(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execTurnToWaypoint) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_deltaTime); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->TurnToWaypoint(Z_Param_deltaTime); \
		P_NATIVE_END; \
	}


#define ProjectXYZ_Source_ProjectXYZ_PlayerCharacterController_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execMoveToWaypoint) \
	{ \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->MoveToWaypoint(); \
		P_NATIVE_END; \
	} \
 \
	DECLARE_FUNCTION(execTurnToWaypoint) \
	{ \
		P_GET_PROPERTY(UFloatProperty,Z_Param_deltaTime); \
		P_FINISH; \
		P_NATIVE_BEGIN; \
		this->TurnToWaypoint(Z_Param_deltaTime); \
		P_NATIVE_END; \
	}


#define ProjectXYZ_Source_ProjectXYZ_PlayerCharacterController_h_16_INCLASS_NO_PURE_DECLS \
	private: \
	static void StaticRegisterNativesAPlayerCharacterController(); \
	friend PROJECTXYZ_API class UClass* Z_Construct_UClass_APlayerCharacterController(); \
	public: \
	DECLARE_CLASS(APlayerCharacterController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), 0, TEXT("/Script/ProjectXYZ"), NO_API) \
	DECLARE_SERIALIZER(APlayerCharacterController) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define ProjectXYZ_Source_ProjectXYZ_PlayerCharacterController_h_16_INCLASS \
	private: \
	static void StaticRegisterNativesAPlayerCharacterController(); \
	friend PROJECTXYZ_API class UClass* Z_Construct_UClass_APlayerCharacterController(); \
	public: \
	DECLARE_CLASS(APlayerCharacterController, APlayerController, COMPILED_IN_FLAGS(0 | CLASS_Config), 0, TEXT("/Script/ProjectXYZ"), NO_API) \
	DECLARE_SERIALIZER(APlayerCharacterController) \
	/** Indicates whether the class is compiled into the engine */ \
	enum {IsIntrinsic=COMPILED_IN_INTRINSIC};


#define ProjectXYZ_Source_ProjectXYZ_PlayerCharacterController_h_16_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API APlayerCharacterController(const FObjectInitializer& ObjectInitializer); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(APlayerCharacterController) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APlayerCharacterController); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APlayerCharacterController); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API APlayerCharacterController(APlayerCharacterController&&); \
	NO_API APlayerCharacterController(const APlayerCharacterController&); \
public:


#define ProjectXYZ_Source_ProjectXYZ_PlayerCharacterController_h_16_ENHANCED_CONSTRUCTORS \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API APlayerCharacterController(APlayerCharacterController&&); \
	NO_API APlayerCharacterController(const APlayerCharacterController&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, APlayerCharacterController); \
DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(APlayerCharacterController); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(APlayerCharacterController)


#define ProjectXYZ_Source_ProjectXYZ_PlayerCharacterController_h_16_PRIVATE_PROPERTY_OFFSET
#define ProjectXYZ_Source_ProjectXYZ_PlayerCharacterController_h_13_PROLOG
#define ProjectXYZ_Source_ProjectXYZ_PlayerCharacterController_h_16_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ProjectXYZ_Source_ProjectXYZ_PlayerCharacterController_h_16_PRIVATE_PROPERTY_OFFSET \
	ProjectXYZ_Source_ProjectXYZ_PlayerCharacterController_h_16_RPC_WRAPPERS \
	ProjectXYZ_Source_ProjectXYZ_PlayerCharacterController_h_16_INCLASS \
	ProjectXYZ_Source_ProjectXYZ_PlayerCharacterController_h_16_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define ProjectXYZ_Source_ProjectXYZ_PlayerCharacterController_h_16_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	ProjectXYZ_Source_ProjectXYZ_PlayerCharacterController_h_16_PRIVATE_PROPERTY_OFFSET \
	ProjectXYZ_Source_ProjectXYZ_PlayerCharacterController_h_16_RPC_WRAPPERS_NO_PURE_DECLS \
	ProjectXYZ_Source_ProjectXYZ_PlayerCharacterController_h_16_INCLASS_NO_PURE_DECLS \
	ProjectXYZ_Source_ProjectXYZ_PlayerCharacterController_h_16_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID ProjectXYZ_Source_ProjectXYZ_PlayerCharacterController_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
