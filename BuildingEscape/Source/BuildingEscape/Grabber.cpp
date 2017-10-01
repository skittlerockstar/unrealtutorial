// COPYRAIT MAXZ

#include "Grabber.h"
#include "Engine.h"

#define OUT
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

	/// look for attached physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("PhysicsHandle not attached : %s"), *GetOwner()->GetName());
	}

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Release", IE_Released, this, &UGrabber::Release);

	}
	else {
		UE_LOG(LogTemp, Error, TEXT("InputComponent not attached : %s"), *GetOwner()->GetName());
	}
	
}

void UGrabber::Grab() {
	UE_LOG(LogTemp, Warning, TEXT("Grabbed"));

}
void UGrabber::Release() {
	UE_LOG(LogTemp, Warning, TEXT("Released"));

}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FVector viewpointVectorOut;
	FRotator viewpointRotatorOut;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(viewpointVectorOut, viewpointRotatorOut);
	FVector lineTraceOut = viewpointVectorOut + (viewpointRotatorOut.Vector() * Reach);
	DrawDebugLine(GetWorld(), viewpointVectorOut, lineTraceOut, FColor().Blue, false, 0.0f, 0.f,10.0f);
	
	///setup query parameters
	FCollisionQueryParams TraceParameters(FName("Text"), false, GetOwner());
	FHitResult hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT hit,
		viewpointVectorOut,
		lineTraceOut,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);
	AActor * objectHit = hit.GetActor();
	if (objectHit) {
		UE_LOG(LogTemp, Warning, TEXT("Pointing at: %s"), *(objectHit->GetName()));
	//	objectHit->SetActorTransform(FTransform(lineTraceOut/2));
	}
	}

