// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Piece.h"
#include "Board.generated.h"

UCLASS()				 // indica que se esta creando una clase que se puede usar en el editor de Unreal Engine.
class TETRISUSFX01_API ABoard : public APawn
{
	GENERATED_BODY()     // macro que indica que la clase ABoard tiene una serie de funciones miembro que se generan automáticamente por el motor de Unreal Engine.

public:
	// Sets default values for this pawn's properties
	ABoard();			 // constructor de la clase ABoard.

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;		// función que se ejecuta cuando el juego comienza o cuando se crea el objeto.

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;   // función que se ejecuta cada fotograma.

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;   // función que se ejecuta cuando se crea el objeto.

	UPROPERTY()     // macro que indica que la variable SceneComponent es una variable que se puede editar en el editor de Unreal Engine.
	APiece* CurrentPiece;		// variable que almacena la pieza actual.

	void Rotate();				// función que rota la pieza actual.
	void MoveLeft(); 			// función que mueve la pieza actual a la izquierda.
	void MoveRight();			// función que mueve la pieza actual a la derecha.	
	void MoveDown();  			// función que mueve la pieza actual hacia abajo.
	void NewPiece();			// función que crea una nueva pieza.
	void CheckLine(); 			// función que verifica si hay una línea completa.
	void MoveDownToEnd(); 		// función que mueve la pieza actual hasta el fondo.

private:
	enum PieceStatus { PS_NOT_INITED, PS_MOVING, PS_GOT_BOTTOM };     // enum que almacena los estados de la pieza.
	PieceStatus Status = PS_NOT_INITED;                               // variable que almacena el estado de la pieza.

	const float CoolDown = 0.5f;									  // variable que almacena el tiempo de espera entre cada movimiento.
	float CoolLeft = 0.5f; 											  // variable que almacena el tiempo restante de espera.
	bool bGameOver = false;											  // variable que almacena si el juego ha terminado.

	bool CheckGameOver();											  // función que verifica si el juego ha terminado.

};
