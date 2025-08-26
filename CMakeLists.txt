cmake_minimum_required(VERSION 3.30)
project(FootballGameProject)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(external/SFML)

add_executable(FootballGameProject
        src/main.cpp
        src/util/Logger.h
        src/Game.h
        src/util/math/Vector2D.h
        src/scene/Scene.h
        src/scene/TestScene.h
        src/scene/football/FootballScene.h
        src/input/InputManager.h
        src/util/Rectangle.h
        src/scene/football/entity/Entity.h
        src/scene/football/player/Player.h
        src/scene/football/entity/objects/FootballEntity.h
        src/scene/football/entity/positions/PositionEntity.h
        src/scene/football/controller/Controller.h
        src/scene/football/field/FootballField.h
        src/scene/football/controller/ControllerManager.h
        src/scene/football/team/Team.h
        src/scene/football/team/roster/DepthChart.h
        src/scene/football/team/roster/Roster.h
        src/scene/football/entity/positions/rating/Ratings.h
        src/scene/football/controller/PlayerController.h
        src/event/Event.h
        src/event/EventBus.h
        src/util/Demangler.h
        src/event/Emitter.h
        src/event/events/football/entity/ThrownPassEvent.h
        src/event/events/football/entity/FootballHitGroundEvent.h
        src/scene/football/state/StateMachine.h
        src/scene/football/state/IState.h
        src/scene/football/state/generic/IdleState.h
        src/scene/football/field/FieldState.h
        src/scene/football/util/Position.h
        src/scene/football/util/Util.h
        src/config/Config.h
        src/scene/football/team/playcalling/Play.cpp
        src/scene/football/team/playcalling/Play.h
        src/scene/football/team/playcalling/Formation.cpp
        src/scene/football/team/playcalling/Formation.h
        src/scene/football/team/playcalling/FormationSlot.h
        src/scene/football/util/FormationType.h
        src/scene/football/camera/Camera.h
        src/scene/football/field/FieldConstants.h
        src/scene/football/route/Route.h
        src/event/events/football/entity/PassCaughtEvent.h
        src/scene/football/entity/positions/PositionEntityState.h
        src/scene/football/route/RoutePresets.h
        src/scene/football/entity/positions/PositionEntity.cpp
        src/scene/football/entity/objects/FootballEntity.cpp
        src/scene/football/field/FootballField.cpp
        src/scene/football/team/roster/Roster.cpp
        src/scene/football/team/Team.cpp
        src/scene/football/team/roster/DepthChart.cpp
        src/scene/football/FootballScene.cpp
        src/scene/football/camera/Camera.cpp
        src/util/math/Vector2D.cpp
        src/util/Rectangle.cpp
)

target_link_libraries(FootballGameProject PRIVATE sfml-graphics)
target_include_directories(FootballGameProject PRIVATE external/SFML/include)

