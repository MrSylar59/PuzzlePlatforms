// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform() {

	PrimaryActorTick.bCanEverTick = true;
	SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay(){
	Super::BeginPlay();

	if (HasAuthority()) { // Seul le serveur a le droit de répliquer
		SetReplicates(true); // Permet de répliquer l'objet sur les clients connectés au serveur
		SetReplicateMovement(true); // Permet de répliquer les mouvements sur les clients connectés au serveur
	}

	// Il faut transformer notre TargetLocation en WorldPosition pour avoir la direction
	GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
	GlobalStartLocation = GetActorLocation();
}

void AMovingPlatform::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	// Permet de modifier la position de l'acteur uniquement sur le serveur
	if (HasAuthority()) {
		FVector loc = GetActorLocation();
		FVector dir = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();

		if (!FVector::Coincident(dir, GlobalTargetLocation-loc)){
			FVector temp = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = temp;
		}

		loc += dir * MovingSpeed * DeltaTime;
		SetActorLocation(loc);
	}
}