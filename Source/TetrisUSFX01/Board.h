// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Piece.h"
#include "Board.generated.h"

UCLASS()				 // indica que se esta creando una clase que se puede usar en el editor de Unreal Engine.
class TETRISUSFX01_API ABoard : public APawn
{
	GENERATED_BODY()     // macro que indica que la clase ABoard tiene una serie de funciones miembro que se generan autom�ticamente por el motor de Unreal Engine.

public:
	// Sets default values for this pawn's properties
	ABoard();			 // constructor de la clase ABoard.

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;		// funci�n que se ejecuta cuando el juego comienza o cuando se crea el objeto.

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;   // funci�n que se ejecuta cada fotograma.

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;   // funci�n que se ejecuta cuando se crea el objeto.

	UPROPERTY()     // macro que indica que la variable SceneComponent es una variable que se puede editar en el editor de Unreal Engine.
	APiece* CurrentPiece;		// variable que almacena la pieza actual.

	void Rotate();				// funci�n que rota la pieza actual.
	void MoveLeft(); 			// funci�n que mueve la pieza actual a la izquierda.
	void MoveRight();			// funci�n que mueve la pieza actual a la derecha.	
	void MoveDown();  			// funci�n que mueve la pieza actual hacia abajo.
	void NewPiece();			// funci�n que crea una nueva pieza.
	void CheckLine(); 			// funci�n que verifica si hay una l�nea completa.
	void MoveDownToEnd(); 		// funci�n que mueve la pieza actual hasta el fondo.

private:
	enum PieceStatus { PS_NOT_INITED, PS_MOVING, PS_GOT_BOTTOM };     // enum que almacena los estados de la pieza.
	PieceStatus Status = PS_NOT_INITED;                               // variable que almacena el estado de la pieza.

	const float CoolDown = 0.5f;									  // variable que almacena el tiempo de espera entre cada movimiento.
	float CoolLeft = 0.5f; 											  // variable que almacena el tiempo restante de espera.
	bool bGameOver = false;											  // variable que almacena si el juego ha terminado.

	bool CheckGameOver();											  // funci�n que verifica si el juego ha terminado.

};
