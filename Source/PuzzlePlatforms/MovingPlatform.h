// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

	public:
		AMovingPlatform();

		UPROPERTY(EditAnywhere, Category="Moving Platform")
		float MovingSpeed = 5;

		// Meta pour ajouter un widget dans l'éditeur
		UPROPERTY(EditAnywhere, Category="Moving Platform", Meta=(MakeEditWidget=true))
		FVector TargetLocation;

	protected: 
		virtual void BeginPlay() override;
		virtual void Tick(float DeltaTime) override;

	private:
		FVector GlobalTargetLocation;
		FVector GlobalStartLocation;
	
};
