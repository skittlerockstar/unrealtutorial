// COPYRAIT MAXZ

#include "OpenDoor.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	MyPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	// ...
	
}

void UOpenDoor::OpenDoor()
{
	AActor* Owner = GetOwner();
	FRotator OldRotation = Owner->GetActorRotation();
	FRotator NewRotation = FRotator(0.0f, OldRotation.Yaw+1.0f, 0.0f);
	Owner->SetActorRotation(NewRotation);
}

void UOpenDoor::CloseDoor()
{
	AActor* Owner = GetOwner();
	FRotator NewRotation = FRotator(0.0f,0.0f, 0.0f);
	Owner->SetActorRotation(NewRotation);
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PressurePlate->IsOverlappingActor(MyPawn)) {
		OpenDoor();
		LastDoorOpen = GetWorld()->GetTimeSeconds();
	}
	if (GetWorld()->GetTimeSeconds() - LastDoorOpen > DoorCloseDelay) {
		CloseDoor();
	}
}

