// COPYRAIT MAXZ

#include "Grabber.h"
#include "Engine.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector viewpointVectorOut;
	FRotator viewpointRotatorOut;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(viewpointVectorOut, viewpointRotatorOut);
	FVector lineTraceOut = viewpointVectorOut + FVector(0.f, 0.f, 80.f);
	DrawDebugLine(GetWorld(), viewpointVectorOut, lineTraceOut, FColor().Blue, false, 0.0f, 0.f,10.0f);
}

