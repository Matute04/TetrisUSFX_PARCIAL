// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"

// Sets default values
ABlock::ABlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true; 

	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BlockMesh"));	// Crear un componente de malla estática
	RootComponent = BlockMesh;														// Establecer el componente de malla estática como el componente raíz

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BlockMeshAsset(TEXT("StaticMesh'/Game/Mesh/block.block'")); // Cargar la malla estática desde el disco duro

	if (BlockMeshAsset.Succeeded())  // Si la malla estática se ha cargado correctamente
	{
		BlockMesh->SetStaticMesh(BlockMeshAsset.Object);    // Establecer la malla estática del componente de malla estática
		BlockMesh->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f)); // Establecer la posición relativa del componente de malla estática
		
		//BlockMesh->SetWorldScale3D(FVector(0.1f, 0.1f, 0.1f));

		//AActor* MyActor = ...; // Obtener el puntero al actor que se desea modificar
		//FVector NewScale(2.0f, 2.0f, 2.0f); // Crear un vector que representa la nueva escala
		//ChangeActorSize(MyActor, NewScale); // Llamar a la funci�n para cambiar el tama�o del actor

	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("No existe la malla para Block"));   // Si la malla estática no se ha cargado correctamente, mostrar un mensaje de error
	}
}

// Called when the game starts or when spawned
void ABlock::BeginPlay()   // Función que se ejecuta cuando el juego comienza o cuando se crea el actor
{
	Super::BeginPlay();    // Llamar a la función BeginPlay de la clase padre
	
}

// Called every frame
void ABlock::Tick(float DeltaTime)    // Función que se ejecuta cada fotograma
{
	Super::Tick(DeltaTime);           // Llamar a la función Tick de la clase padre

}

