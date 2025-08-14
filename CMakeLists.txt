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
        src/scene/football/entity/positions/QB/QBEntity.h
        src/scene/football/controller/ControllerManager.h
        src/scene/football/team/Team.h
        src/scene/football/team/DepthChart.h
        src/scene/football/team/Roster.h
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
        src/scene/football/field/FootballFieldRenderer.h
        src/scene/football/field/Yard.h
)

target_link_libraries(FootballGameProject PRIVATE sfml-graphics)
target_include_directories(FootballGameProject PRIVATE external/SFML/include)

