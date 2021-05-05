// Fill out your copyright notice in the Description page of Project Settings.


#include "C_WeaponBase.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AC_WeaponBase::AC_WeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;

}

// Called when the game starts or when spawned
void AC_WeaponBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AC_WeaponBase::Fire()
{
	//Hit scan 

	AActor* MyOwner = GetOwner();

	if (MyOwner)
	{
		FVector EyeLocation;
		FRotator EyeRotation;
		MyOwner->GetActorEyesViewPoint(EyeLocation, EyeRotation);

		FVector TraceEnd = EyeLocation + (EyeRotation.Vector() * 10000);

		FCollisionQueryParams QuerryParams;
		QuerryParams.AddIgnoredActor(MyOwner);
		QuerryParams.AddIgnoredActor(this);
		QuerryParams.bTraceComplex = true;

		FHitResult Hit;
		if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QuerryParams))
		{

		}

		DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::Red, false, 1.0f, 0, 1.0f);
	}


}

// Called every frame
void AC_WeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

