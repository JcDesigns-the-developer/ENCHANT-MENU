#include "EventManager.h"
#include "../Player/PlayerController.h"
#include "../Vehicle/VehicleController.h"
#include "../World/WorldController.h"
#include "../Native/NativeHelpers.h"
namespace Enchant {
void ExecuteEvent(EventType t,float i){switch(t){case EventType::AmbientAudio:WorldController::AmbientDisturbance(i);break;case EventType::PedReaction:PlayerController::SmallMovementEffect(i);break;case EventType::VehicleReaction:VehicleController::ReactNearby(i);break;case EventType::CameraEffect:PlayerController::CameraJolt(i);break;case EventType::WorldEffect:WorldController::WeatherPulse(i);break;}}
}