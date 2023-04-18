// Fill out your copyright notice in the Description page of Project Settings.

#pragma once		//le dice al preprocesador que solo incluya el archivo de encabezado una vez durante el proceso de compilación
					//lo que evita la duplicación de código y los errores de compilación resultantes.

#include "CoreMinimal.h"										
#include "GameFramework/Actor.h"							
#include "Block.generated.h"		
							
UCLASS()								// declara la clase como una clase de Unreal Engine que se puede usar en el editor de Unreal Engine.
class TETRISUSFX01_API ABlock : public AActor		// declara la clase ABlock como una clase que hereda de la clase AActor.
{
	GENERATED_BODY()					// declara que la clase ABlock tiene una serie de funciones miembro que se generan automáticamente por el motor de Unreal Engine.
	
public:	  
	// Sets default values for this actor's properties
	ABlock();							// declara el constructor de la clase ABlock.

protected: 
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;  

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;	// declara la función Tick que se ejecuta cada fotograma.

	UPROPERTY(EditAnywhere) 						// declara la variable BlockMesh como una variable que se puede editar en el editor de Unreal Engine.
	UStaticMeshComponent* BlockMesh;				// declara la variable BlockMesh como un componente de malla estática.

};
