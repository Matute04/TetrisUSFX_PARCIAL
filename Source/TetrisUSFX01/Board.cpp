// Fill out your copyright notice in the Description page of Project Settings.


#include "Board.h"
#include "EngineUtils.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
// Sets default values

ABoard::ABoard()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;           // propiedad de la clase AActor que indica si este actor debe llamar a la funci�n Tick en cada cuadro del juego

}

// Called when the game starts or when spawned
void ABoard::BeginPlay()                            // Funci�n que se ejecuta cuando el juego comienza o cuando se crea el actor
{
	Super::BeginPlay();							    // Llamar a la funci�n BeginPlay de la clase padre
	
    for (TActorIterator<APiece> it(GetWorld()); it; ++it)
    {
        if (it->GetFName() == TEXT("DissmissPieces"))
        {
            it->Dismiss();
            it->Destroy();
        }
    }
}

// Called every frame
void ABoard::Tick(float DeltaTime)				  // Funci�n que se ejecuta cada fotograma
{
	Super::Tick(DeltaTime);						  // Llamar a la funci�n Tick de la clase padre

    if (bGameOver)                                // Si el juego ha terminado
    {
		return;                                   // Salir de la funci�n
	}

    switch (Status)   						      // Seg�n el estado del juego
    {
    case PS_NOT_INITED:  					      // Si el juego no ha sido inicializado
        NewPiece();							      // Crear una nueva pieza
        CoolLeft = CoolDown; 				 	  // Establecer el tiempo de espera para la siguiente pieza
        Status = PS_MOVING; 					  // Establecer el estado del juego a "Moviendo"
        break;
    case PS_MOVING:							      // Si el juego est� en movimiento
        CoolLeft -= DeltaTime;					  // Restar el tiempo transcurrido desde el �ltimo fotograma
        if (CoolLeft <= 0.0f)                     // Si el tiempo de espera ha terminado
        {
            MoveDown(); 						  // Mover la pieza hacia abajo
        }
        break;
    case PS_GOT_BOTTOM:						      // Si la pieza ha llegado al fondo
        CoolLeft -= DeltaTime;					  // Restar el tiempo transcurrido desde el �ltimo fotograma
        if (CoolLeft <= 0.0f)                     // Si el tiempo de espera ha terminado
        {
            if (CurrentPiece)  				      // Si la pieza actual existe
            {
                CurrentPiece->Dismiss(); 	      // Desaparecer la pieza actual
                CurrentPiece->Destroy();		  // Destruir la pieza actual
            }
            CurrentPiece = nullptr;				  // Establecer la pieza actual a nulo
            NewPiece();							  // Crear una nueva pieza
            CoolLeft = CoolDown; 				  // Establecer el tiempo de espera para la siguiente pieza
            Status = PS_MOVING; 				  // Establecer el estado del juego a "Moviendo"
        }
        break; 
    default:
        break;
    }
}

// Called to bind functionality to input
void ABoard::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)                        // Funci�n que se ejecuta cuando se crea el actor
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);                                         // Llamar a la funci�n SetupPlayerInputComponent de la clase padre
    PlayerInputComponent->BindAction("Rotate", IE_Pressed, this, &ABoard::Rotate); 	                // Asignar la funci�n Rotate al evento "Rotate" del componente PlayerInputComponent 
    PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &ABoard::MoveLeft);              // Asignar la funci�n MoveLeft al evento "MoveLeft" del componente PlayerInputComponent
    PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &ABoard::MoveRight); 		    // Asignar la funci�n MoveRight al evento "MoveRight" del componente PlayerInputComponent 
    PlayerInputComponent->BindAction("MoveDownToEnd", IE_Pressed, this, &ABoard::MoveDownToEnd);    // Asignar la funci�n MoveDownToEnd al evento "MoveDownToEnd" del componente PlayerInputComponent
    PlayerInputComponent->BindAction("NewPiece", IE_Pressed, this, &ABoard::NewPiece); 			    // Asignar la funci�n NewPiece al evento "NewPiece" del componente PlayerInputComponent
    //PlayerInputComponent->BindAction("CheckLine", IE_Pressed, this, &ABoard::CheckLine);

}

void ABoard::Rotate()   // Rotar la pieza actual
{
    if (CurrentPiece && Status != PS_GOT_BOTTOM)  
    {
        CurrentPiece->TestRotate();
    }
}

void ABoard::MoveLeft()
{
    if (CurrentPiece)
    {
        CurrentPiece->MoveLeft();
        if (Status == PS_GOT_BOTTOM)
        {
            MoveDownToEnd();
        }
    }
}

void ABoard::MoveRight()
{
    if (CurrentPiece)
    {
        CurrentPiece->MoveRight();
        if (Status == PS_GOT_BOTTOM)
        {
            MoveDownToEnd();
        }
    }
}

void ABoard::MoveDown()
{
    if (CurrentPiece)
    {
        if (!CurrentPiece->MoveDown())
        {
            Status = PS_GOT_BOTTOM;
        }
        CoolLeft = CoolDown;
    }
}

void ABoard::NewPiece()  // Crear una nueva pieza
{
    CheckLine();         // Comprobar si hay alguna l�nea completa
    if (CurrentPiece)   // Si la pieza actual existe
    {
        CurrentPiece->Dismiss();  // Desaparecer la pieza actual
        CurrentPiece->Destroy();  // Destruir la pieza actual
    }

    FVector Location(0.0, 5.0, 195.0);  // Establecer la posici�n de la nueva pieza
    FRotator Rotation(0.0, 0.0, 0.0);   // Establecer la rotaci�n de la nueva pieza
    CurrentPiece = GetWorld()->SpawnActor<APiece>(Location, Rotation);   // Crear la nueva pieza
    bGameOver = CheckGameOver();  // Comprobar si el juego ha terminado
    if (bGameOver)   
    {
        UE_LOG(LogTemp, Warning, TEXT("Game Over!!!!!!!!"));
        /*if (GameOverSoundCue)
        {
            UGameplayStatics::PlaySoundAtLocation(GetWorld(), GameOverSoundCue, GetActorLocation(), GetActorRotation());
        }*/
    }
}

void ABoard::CheckLine()
{
    auto MoveDownFromLine = [this](int z) {
        FVector Location(0.0f, 0.0f, 5.0 * z + 100.0);
        FRotator Rotation(0.0f, 0.0f, 0.0f);
        TArray<struct FOverlapResult> OutOverlaps;
        FCollisionShape CollisionShape;
        FVector Extent(4.5f, 49.5f, 95.0 + 4.5 - 5.0 * z);
        CollisionShape.SetBox(Extent);
        DrawDebugBox(GetWorld(), Location, Extent, FColor::Purple, false, 1, 0, 1);
        FCollisionQueryParams Params;
        FCollisionResponseParams ResponseParam;
        if (GetWorld()->OverlapMultiByChannel(OutOverlaps,
            Location, Rotation.Quaternion(), ECollisionChannel::ECC_WorldDynamic,
            CollisionShape, Params, ResponseParam))
        {
            for (auto&& Result : OutOverlaps)
            {
                FVector NewLocation = Result.GetActor()->GetActorLocation();
                NewLocation.Z -= 10.0f;
                Result.GetActor()->SetActorLocation(NewLocation);
            }
        }
    };

    int z = 0;
    while (z < 20)
    {
        FVector Location(0.0f, 0.0f, 10.0f * z + 5.0f);
        FRotator Rotation(0.0f, 0.0f, 0.0f);
        TArray<struct FOverlapResult> OutOverlaps;
        FCollisionShape CollisionShape;
        CollisionShape.SetBox(FVector(4.0f, 49.0f, 4.0f));
        //DrawDebugBox(GetWorld(), Location, FVector(4.5f, 49.5f, 4.5f), FColor::Purple, false, 1, 0, 1);
        FCollisionQueryParams Params;
        FCollisionResponseParams ResponseParam;
        bool b = GetWorld()->OverlapMultiByChannel(OutOverlaps,
            Location, Rotation.Quaternion(), ECollisionChannel::ECC_WorldDynamic,
            CollisionShape, Params, ResponseParam);
        if (!b || OutOverlaps.Num() < 10)
        {
            ++z;
            continue;
        }
        else // this line is full, remove the line
        {
            UE_LOG(LogTemp, Warning, TEXT("Find FULL LINE at z=%d"), z);
            for (auto&& Result : OutOverlaps)
            {
                Result.GetActor()->Destroy();
            }
            MoveDownFromLine(z);

            /*if (LineRemoveSoundCue)
            {
                UGameplayStatics::PlaySoundAtLocation(GetWorld(), LineRemoveSoundCue, GetActorLocation(), GetActorRotation());
            }*/
        }
    }
}

void ABoard::MoveDownToEnd()
{
    if (!CurrentPiece)
    {
        return;
    }

    while (CurrentPiece->MoveDown())
    {
    }

    /*if (MoveToEndSoundCue)
    {
        UGameplayStatics::PlaySoundAtLocation(GetWorld(), MoveToEndSoundCue, GetActorLocation(), GetActorRotation());
    }*/

    switch (Status)
    {
    case PS_MOVING:
        Status = PS_GOT_BOTTOM;
        CoolLeft = CoolDown;
        break;
    case PS_GOT_BOTTOM:
        break;
    default:
        UE_LOG(LogTemp, Warning, TEXT("Wrong status for MoveDownToEnd"));
        break;
    }
}

bool ABoard::CheckGameOver()
{
    if (!CurrentPiece)
    {
        UE_LOG(LogTemp, Warning, TEXT("NoPieces"));
        return true;
    }

    return CurrentPiece->CheckWillCollision([](FVector OldVector) { return OldVector; });
}
