#pragma once
#include <iostream>

namespace offsets
{
    uintptr_t GWorld = 0xc25b0c0; // Offsets::GWorld
    uintptr_t GNames = 0xc07d1c0; // Offsets::GNames

    uintptr_t OwningGameInstance = 0x190; // Offsets::Classes::UWorld::OwningGameInstance
    uintptr_t LocalPlayers = 0x40; // Offsets::Classes::UWorld::UGameInstance::LocalPlayers
    uintptr_t PlayerController = 0x38; // Offsets::Classes::UWorld::UGameInstance::UPlayer::PlayerController
    uintptr_t PlayerControlRotation = 0x248; // Offsets::Classes::AActor::UObject::AController
    uintptr_t GroupID = 0x38; // Offsets::Classes::APlayerState::Ainfo::AActor::UObject::GroupId
    uintptr_t CurrentHealth = 0x1E0; // Offsets::ACharacter::APawn::AActor::UObject::CurrentHealth
    uintptr_t CharacterMesh = 0x4d8; // Offsets::ACharacter::APawn::AActor::UObject::Mesh
    uintptr_t AcknowledgedPawn = 0x2B8; // Offsets::Classes::UWorld::UGameInstance::UPlayer::APlayerController::AcknowledgedPawn
    uintptr_t PlayerCameraManager = 0x2D0; // Offsets::Classes::UWorld::UGameInstance::UPlayer::APlayerController::PlayerCameraManager
    uintptr_t CameraCachePrivate = 0x1af0; // // PlayerCameraManager::CameraCachePrivate
    uintptr_t PlayerState = 0x250;  // Offsets::Classes::AActor::UObject::APawn::PlayerState
    uintptr_t PlayerStateLocalPlayer = 0x238;  // Offsets::Classes::AActor::UObject::AController::PlayerState
    uintptr_t RootComponent = 0x140; // Offsets::Classes::AActor::UObject::RootComponent 
    uintptr_t RelativeLocation = 0x134; // Offsets::USceneComponent::UObject::RelativeLocation
    uintptr_t RelativeRotation = 0x140; // Offsets::USceneComponent::UObject::RelativeRotation 
    uintptr_t PersistentLevel = 0x38; // Offsets::Classes::UWorld::PersistentLevel
    uintptr_t LODData = 0x508; // UMeshComponent::UPrimitiveComponent::USceneComponent::UActorComponent::UObject::LODData
    uintptr_t PlayerNamePrivate = 0x318; // APlayerState PlayerNamePrivate
    uintptr_t ActorArray = 0xa0; // Offsets::Classes::UWorld::ULevel::UNetConnection::OwningActor
    uintptr_t ActorCount = 0xa8; // Offsets::Classes::UWorld::ULevel::UNetConnection::MaxPacket
    uintptr_t ActorID = 0x18; // offset_actor_id
    uintptr_t ComponentToWorld = 0x1E0;
}