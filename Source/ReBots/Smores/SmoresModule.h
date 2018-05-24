// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "PhysXPublic.h"
#include "Runtime/Engine/Private/PhysicsEngine/PhysXSupport.h"
#include "Runtime/Engine/Classes/Components/TextRenderComponent.h"
#include "Runtime/Engine/Classes/Components/ArrowComponent.h"
#include <sstream>
#include <iostream>
#include <functional>
#include <vector>
#include "Framework/ModuleMotorVector.h"
#include "Behaviors/JointBehavior.h"
#include "CustomActors/ReferenceFrameActor.h"
#include "CustomActors/ManipulatorObjectActor.h"
#include "Framework/RangedMessage.h"
#include "Framework/ModuleDock.h"
#include "Framework/TreeMessage.h"
#include "Framework/ModuleState.h"
#include "Framework/ModuleModel.h"
#include "Framework/ModuleConnectionPair.h"
#include "Behaviors/TwistBehavior.h"
#include "Behaviors/ModManipQBehavior.h"
#include "Behaviors/SnakeIKBehavior.h"
#include "Behaviors/CaterpillarBehavior.h"
#include "Behaviors/SuperBotDistKinematics.h"
#include "Behaviors/SuperBotDistKinematicsChain.h"
#include "Behaviors/StackToPlaneBehavior.h"
#include "Behaviors/ForwardKinematicsBehavior.h"
#include "Behaviors/GoToAnglesBehavior.h"
#include "Behaviors/TreeWalkingBehavior.h"
#include "Behaviors/DistributedIK.h"
#include "Framework/RobotModuleBehavior.h"
#include "Behaviors/GoToAnglesBehavior.h"
#include "Behaviors/FKIKBehavior.h"
#include "Behaviors/ReconfDemoQ.h"
#include "Behaviors/ReconfDemoQ2.h"
#include "Behaviors/ReconfIKBehavior.h"
#include "Behaviors/DistributedKinematicsBehavior.h"
#include "GameModes/ReBotsSimulatorGameMode.h"
#include "GameModes/ReBotsModuleGameMode.h"
#include "CustomActors/DockCollisionActor.h"
#include "CustomActors/BoundingSphere.h"
#include "Framework/ModularRobot.h"
#include "Framework/ModuleJoint.h"
#include "Framework/ModuleSensor.h"
#include "Framework/ModuleActuator.h"
#include "Framework/ModulePoseSensor.h"
#include "Framework/ModuleFlagSensor.h"
#include "Framework/ModuleFlagActuator.h"
#include "Framework/ModuleFloatActuator.h"
#include "Framework/ModuleFloatSensor.h"
#include "Framework/ModuleMessageSensor.h"
#include "Framework/ModuleMessageActuator.h"
#include "SmoresModule.generated.h"

UCLASS()
class REBOTS_API ASmoresModule : public AModularRobot
{
	GENERATED_BODY()
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SmoresBody, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* SmoresInner; /**< inner component of module */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SmoresBody, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* SmoresOuter; /**< outer component of module */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SmoresBody, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* WheelFront; /**< front wheel component of module */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SmoresBody, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* WheelBack; /**< back wheel component of module */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SmoresBody, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent *WheelLeft; /**< left wheel component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SmoresBody, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent *WheelRight; /**< right wheel component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SmoresBody, meta = (AllowPrivateAccess = "true"))
		class UPhysicsConstraintComponent* InnerJoint; /**< inner joint (between slave inner and master inner */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SmoresBody, meta = (AllowPrivateAccess = "true"))
		class UPhysicsConstraintComponent* BackWheelJoint; /**< slave joint between slave outer and inner */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SmoresBody, meta = (AllowPrivateAccess = "true"))
		class UPhysicsConstraintComponent* LeftWheelJoint; /**< master joint between master outer and inner */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SmoresBody, meta = (AllowPrivateAccess = "true"))
		class UPhysicsConstraintComponent* RightWheelJoint; /**< slave joint between slave outer and inner */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = SmoresBody, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* SmoresController; /**< slave joint between slave outer and inner */
	RobotModuleBehavior* ModuleBehavior = NULL; /**< module behavior */
	const float smores_mass_inner = (0.52)*0.2; /**< inner smores mass */
	const float smores_mass_outer = (0.52)*0.7; /**< outer smores mass */
	const float smores_mass_wheel = (0.52)*0.025;
	const float smores_static_friction = 0.5; /**< superbot static friction */
	const float smores_kinetic_friction = 0.5; /**< superbot kinematic friction */
	const float smores_restitution = 0.0; /**< superbot restitution */
	const float smores_total_mass = 0.52; /**< superbot total mass */
	ModuleMotorVector curJoints; /**< current joint angles */
	ModuleMotorVector desJoints; /**< desired joint angles */
	std::string name; /**< name of module */
	int IDNumber; /**< ID number of module */
	bool JointBehaviorMode = true; /**< in joint behavior mode ? */
	AReferenceFrameActor* rFrameModule = NULL; /**< middle of module frame */
	AReferenceFrameActor* rFrameFrontDock = NULL; /**< master joint frame */
	AReferenceFrameActor* rFrameBackDock = NULL; /**< slave joint frame */
	AReferenceFrameActor* rFrameLeftDock = NULL; /**< left dock frame */
	AReferenceFrameActor* rFrameRightDock = NULL; /**< right dock frame */
	AReferenceFrameActor* rFrameUpDock = NULL; /**< up dock frame */
	AReferenceFrameActor* rFrameDownDock = NULL; /**< down dock frame */
	AReferenceFrameActor* rFrameFromFrontDock = NULL; /**< from front dock */
	AReferenceFrameActor* rFrameFromBackDock = NULL; /**< from front dock */
	AReferenceFrameActor* rFrameFromLeftDock = NULL; /**< from left dock */
	AReferenceFrameActor* rFrameFromRightDock = NULL; /**< from right dock */
	AReferenceFrameActor* rFrameFromUpDock = NULL; /**< from right dock */
	AReferenceFrameActor* rFrameFromDownDock = NULL; /**< from right dock */
	AReferenceFrameActor* GroundFrame = NULL; /**< ground frame */
	ADockCollisionActor *DCBFront = NULL; /**< dock collision box front */
	ADockCollisionActor *DCBBack = NULL; /**< dock collision box back */
	ADockCollisionActor *DCBLeft = NULL; /**< dock collision box left */
	ADockCollisionActor *DCBRight = NULL; /**< dock collision box right */
	ADockCollisionActor *DCBUp = NULL; /**< dock collision box up */
	ADockCollisionActor *DCBDown = NULL; /**< dock collision box down */
	SuperBotColor ModuleColor; /**< Color of the module */
	const int NumConnectors = 3;

public:
	/**
	* @brief constructor
	*/
	ASmoresModule();
	/**
	* @brief begin play (simulation)
	*/
	virtual void BeginPlay() override;
	/**
	* @brief initialize module
	*/
	virtual void InitModule();
	/**
	* @brief advance the simulation
	* @param DeltaSeconds fraction of a second by which to advance simulation
	*/
	virtual void Tick(float DeltaSeconds) override;
	/**
	* @brief get master outer component
	* @return master outer component
	*/
	FORCEINLINE class UStaticMeshComponent* GetSmoresInner() const { return SmoresInner; }
	/**
	* @brief get slave outer component
	* @return slave outer component
	*/
	FORCEINLINE class UStaticMeshComponent* GetSmoresOuter() const { return SmoresOuter; }
	/**
	* @brief get inner joint
	* @return inner joint component
	*/
	FORCEINLINE class UPhysicsConstraintComponent* GetInnerConstraint() const { return InnerJoint; }
	
};
