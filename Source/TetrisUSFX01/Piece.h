// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.h"
#include <functional>
#include "Piece.generated.h"

UCLASS()
class TETRISUSFX01_API APiece : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APiece();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()   // macro que declara la variable como una variable que se puede editar en el editor de Unreal Engine.
		class USceneComponent* SceneComponent;    // declara la variable SceneComponent como un componente de escena.

	void DrawDebugLines();  
	void TestRotate();
	void MoveLeft();
	void MoveRight();
	bool MoveDown(bool PlaySound = true);
	void Dismiss();
	bool CheckWillCollision(std::function<FVector(FVector OldLocation)> ChangeBeforeCheck);
	
	UPROPERTY(EditAnywhere)  // significa que la propiedad se puede editar tanto en el editor de Unreal Engine como en el código
	TArray<class UMaterial*> Colors;  // declara la variable Colors como un array de materiales.

private:

	TArray<ABlock*> Blocks;			  // declara la variable Blocks como un array de bloques.
	
public:
	void SpawnBlocks();

};
