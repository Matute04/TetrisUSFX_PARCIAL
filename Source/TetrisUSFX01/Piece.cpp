// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include <vector>

// Sets default values
APiece::APiece()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("Pieces Scene");   // Crear un componente de escena
	RootComponent = SceneComponent;                                             // Establecer el componente de escena como el componente raíz

    struct FConstructorStatics  
    {
        ConstructorHelpers::FObjectFinderOptional<UMaterial> Color_0;           // Cargar los materiales 
        ConstructorHelpers::FObjectFinderOptional<UMaterial> Color_1;
        ConstructorHelpers::FObjectFinderOptional<UMaterial> Color_2;
        ConstructorHelpers::FObjectFinderOptional<UMaterial> Color_3;
        ConstructorHelpers::FObjectFinderOptional<UMaterial> Color_4;
        ConstructorHelpers::FObjectFinderOptional<UMaterial> Color_5;
        ConstructorHelpers::FObjectFinderOptional<UMaterial> Color_6;
        ConstructorHelpers::FObjectFinderOptional<UMaterial> Color_7;
        ConstructorHelpers::FObjectFinderOptional<UMaterial> Color_8;
        ConstructorHelpers::FObjectFinderOptional<UMaterial> Color_9;
        ConstructorHelpers::FObjectFinderOptional<UMaterial> Color_10;
        ConstructorHelpers::FObjectFinderOptional<UMaterial> Color_11;
        FConstructorStatics()                                                   // "F" indica que es una estructura de datos de la biblioteca básica de Unreal Engine.
            : Color_0(TEXT("Material'/Game/Mesh/Material_0.Material_0'"))       // Cargar los materiales del unreal
            , Color_1(TEXT("Material'/Game/Mesh/Material_1.Material_1'"))
            , Color_2(TEXT("Material'/Game/Mesh/Material_2.Material_2'"))
            , Color_3(TEXT("Material'/Game/Mesh/Material_3.Material_3'"))
            , Color_4(TEXT("Material'/Game/Mesh/Material_4.Material_4'"))
            , Color_5(TEXT("Material'/Game/Mesh/Material_5.Material_5'"))
            , Color_6(TEXT("Material'/Game/Mesh/Material_6.Material_6'"))
            , Color_7(TEXT("Material'/Game/Mesh/Material_7.Material_7'"))
            , Color_8(TEXT("Material'/Game/Mesh/Material_8.Material_8'"))
            , Color_9(TEXT("Material'/Game/Mesh/Material_9.Material_9'"))
            , Color_10(TEXT("Material'/Game/StarterContent/Materials/M_Water_Lake.M_Water_Lake'"))
            , Color_11(TEXT("Material'/Game/StarterContent/Materials/M_Metal_Gold.M_Metal_Gold'"))

        {
        }
    };
    static FConstructorStatics ConstructorStatics;  						  // Instanciar la estructura de datos FConstructorStatics
    Colors.Add(ConstructorStatics.Color_0.Get());  					          // Agregar los materiales a la lista de materiales
    Colors.Add(ConstructorStatics.Color_1.Get());
    Colors.Add(ConstructorStatics.Color_2.Get());
    Colors.Add(ConstructorStatics.Color_3.Get());
    Colors.Add(ConstructorStatics.Color_4.Get());
    Colors.Add(ConstructorStatics.Color_5.Get());
    Colors.Add(ConstructorStatics.Color_6.Get());
    Colors.Add(ConstructorStatics.Color_7.Get());
    Colors.Add(ConstructorStatics.Color_8.Get());
    Colors.Add(ConstructorStatics.Color_9.Get());
    Colors.Add(ConstructorStatics.Color_10.Get());
    Colors.Add(ConstructorStatics.Color_11.Get());
}

// Called when the game starts or when spawned
void APiece::BeginPlay()
{
	Super::BeginPlay();
    SpawnBlocks();  														  // Llamar a la función SpawnBlocks
}

// Called every frame
void APiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APiece::SpawnBlocks()
{
    std::vector<std::vector<std::pair<float, float>>> Shapes =                                               // Crear una lista de piezas
    {
        {{-20.0, 0.0}, {-10.0, 0.0}, {0.0, 0.0}, {10.0, 0.0}},                                               // Pieza Linea
        {{0.0, 10.0}, {0.0, 0.0}, {10.0, 0.0}, {20.0, 0.0}},                                                 // Pieza L
        {{-20.0, 0.0}, {-10.0, 0.0}, {0.0, 0.0}, {0.0, 10.0}},                                               // Pieza L Invertida
        {{0.0, 0.0}, {10.0, 0.0}, {0.0, -10.0}, {10.0, -10.0}},                                              // Cuadrado
        {{-10.0, -10.0}, {0.0, -10.0}, {0.0, 0.0}, {10.0, 0.0}},                                             // Pieza Z Invertida
        {{-10.0, 0.0}, {0.0, 0.0}, {0.0, 10.0}, {10.0, 0.0}},                                                // Pieza T
        //{{-10.0, 0.0}, {0.0, 0.0}, {0.0, -10.0}, {10.0, -10.0}},
        {{-20.0, 10.0}, {-10.0, 0.0}, {0.0, 10.0}, {10.0, 0.0}},                                             // Pieza Binaria
        //A partir de aca, incrementare 5 piezas mas en el juego
        {{-10.0, 0.0}, {0.0, 0.0}, {10.0, 0.0}, {0.0, 10.0}, {0.0, -10.0}},                                  // Pieza Cruz
        {{-10.0, 20.0}, {-10.0, 10.0}, {-10.0, 0.0}, {0.0, 0.0}, {10.0, 0.0}, {10.0, 10.0}, {10.0, 20.0}},   // Pieza Iman
        {{-10.0, 0.0}, {-10.0, 10.0}, {-10.0, 20.0}, {0.0, 20.0}, {0.0, 10.0}, {10.0, 20.0}, {20.0, 20.0}},  // Pieza Pistola
        {{0.0, 20.0}, {0.0, 10.0}, {10.0, 10.0}, {10.0, 0.0}, {20.0, 0.0}},                                  // Pieza Escalera
        {{0.0, 0.0}, {0.0, 10.0}, {10.0, 10.0}, {10.0, 20.0}, {10.0, 30.0}, {0.0, 30.0}}                     // Pieza Signo de Pregunta 
    };
    const int Index = FMath::RandRange(0, Shapes.size() - 1);               // Generar un número aleatorio entre 0 y el tamaño de la lista de piezas
    //const int Index = FMath::RandRange(7, Shapes.size() - 1);             // Generar un número aleatorio entre 7 y el tamaño de la lista de piezas para mostrar las 5 piezas creadas
    UE_LOG(LogTemp, Warning, TEXT("index=%d"), Index);  				    // Imprimir el número aleatorio generado
    const std::vector<std::pair<float, float>>& YZs = Shapes[Index];        // Obtener la pieza correspondiente al número aleatorio generado
    for (auto&& YZ : YZs)  												    // Iterar sobre la pieza
    {
        FRotator Rotation(0.0, 0.0, 0.0);  								    // Rotación de la pieza
        ABlock* B = GetWorld()->SpawnActor<ABlock>(this->GetActorLocation(), Rotation);  // Instanciar un bloque
        B->BlockMesh->SetMaterial(1, Colors[Index]);  					    // Asignar el material correspondiente al bloque
        Blocks.Add(B);  												    // Agregar el bloque a la lista de bloques
        B->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);  	    // Asignar la pieza como padre del bloque
        B->SetActorRelativeLocation(FVector(0.0, YZ.first, YZ.second));  	            // Asignar la posición del bloque
    }
}

void APiece::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    UE_LOG(LogTemp, Warning, TEXT("Piezas eliminadas"));
}

//void APiece::Dismiss()
//{
//    Blocks.Empty();
//}

void APiece::DrawDebugLines()  
{
    for (ABlock* B : Blocks)  // Iterar sobre la lista de bloques
    {
        FVector V1 = B->GetActorLocation();  // Obtener la posición del bloque
        FVector V2(V1.X, V1.Y, 5.0f);        // Crear un vector con la misma posición en X y Y, pero con una posición en Z mayor
        DrawDebugLine(GetWorld(), V1, V2, FColor::Green, false, 1, 0, 1);  // Dibujar una línea verde entre los dos vectores
    }
}

void APiece::TestRotate()     
{
    auto RotateVector = [this](FVector OldVector) {         // Función lambda que recibe un vector y devuelve otro vector
        FVector ActorVector = this->GetActorLocation();     // Obtener la posición de la pieza
        FVector BlockVector = OldVector;  				    // Obtener la posición del bloque
        FVector TempVector = BlockVector - ActorVector;     // Obtener la diferencia entre la posición del bloque y la posición de la pieza  
        TempVector = ActorVector + TempVector.RotateAngleAxis(90.0, FVector(1.0, 0.0, 0.0));  // Rotar el vector en 90 grados y sumarlo a la posición de la pieza
        return TempVector;  								// Devolver el vector rotado
    };

    if (!CheckWillCollision(RotateVector))                  // Si no hay colision
    {
        UE_LOG(LogTemp, Warning, TEXT("now can rotate"));   // Imprimir un mensaje
        FRotator NewRotation = this->GetActorRotation() + FRotator(0.0, 0.0, -90.0);  // Obtener la rotación actual de la pieza y sumarle 90 grados
        this->SetActorRelativeRotation(NewRotation);                                  // Asignar la rotación a la pieza
        /*if (RotateSoundCue)
        {
            UGameplayStatics::PlaySoundAtLocation(GetWorld(), RotateSoundCue, GetActorLocation(), GetActorRotation());
        }*/
    }
}

//void APiece::EndPlay(const EEndPlayReason::Type EndPlayReason)
//{
//    UE_LOG(LogTemp, Warning, TEXT("Pieces Deleted"));
//}

void APiece::Dismiss()
{
    Blocks.Empty();
}

void APiece::MoveLeft()
{
    auto MoveVectorLeft = [](FVector OldVector) {
        OldVector.Y -= 10.0f;
        return OldVector;
    };

    if (!CheckWillCollision(MoveVectorLeft))
    {
        FVector NewLocation = GetActorLocation();
        NewLocation.Y -= 10;
        SetActorLocation(NewLocation);

       /* if (MoveLeftRightSoundCue)
        {
            UGameplayStatics::PlaySoundAtLocation(GetWorld(), MoveLeftRightSoundCue, GetActorLocation(), GetActorRotation());
        }*/
    }
}

void APiece::MoveRight()
{
    auto MoveVectorRight = [](FVector OldVector) {
        OldVector.Y += 10.0f;
        return OldVector;
    };

    if (!CheckWillCollision(MoveVectorRight))
    {
        FVector NewLocation = GetActorLocation();
        NewLocation.Y += 10;
        SetActorLocation(NewLocation);

        /*if (MoveLeftRightSoundCue)
        {
            UGameplayStatics::PlaySoundAtLocation(GetWorld(), MoveLeftRightSoundCue, GetActorLocation(), GetActorRotation());
        }*/
    }
}

bool APiece::MoveDown(bool PlaySound)
{
    auto MoveVectorDown = [](FVector OldVector) {
        OldVector.Z -= 10.0f;
        return OldVector;
    };

    if (!CheckWillCollision(MoveVectorDown))
    {
        FVector NewLocation = GetActorLocation();
        NewLocation.Z -= 10;
        SetActorLocation(NewLocation);

        return true;
    }
    else
    {
        return false;
    }
}

bool APiece::CheckWillCollision(std::function<FVector(FVector OldLocation)> ChangeBeforeCheck)
{
    FCollisionQueryParams Params;
    for (ABlock* B : Blocks)
    {
        Params.AddIgnoredActor(B);
    }

    for (ABlock* B : Blocks)
    {
        FVector TempVector = B->GetActorLocation();
        TempVector = ChangeBeforeCheck(TempVector);

        TArray<struct FOverlapResult> OutOverlaps;
        FCollisionShape CollisionShape;
        CollisionShape.SetBox(FVector(4.0f, 4.0f, 4.0f));
        FCollisionResponseParams ResponseParam;
        bool b = GetWorld()->OverlapMultiByChannel(OutOverlaps,
            TempVector, B->GetActorQuat(), ECollisionChannel::ECC_WorldDynamic,
            CollisionShape, Params, ResponseParam);

        if (b)
        {
            for (auto&& Result : OutOverlaps)
            {
                UE_LOG(LogTemp, Warning, TEXT("OverLapped with actor %s, component=%s"), *Result.GetActor()->GetName(),
                    *Result.GetComponent()->GetName());
            }
            return true;
        }
    }

    return false;
}


