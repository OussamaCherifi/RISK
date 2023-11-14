cmake_minimum_required(VERSION 3.26)
project(A1_COMP345)

set(CMAKE_CXX_STANDARD 17)

include_directories(Cards)
include_directories(GameEngine)
include_directories(Map)
include_directories(Orders)
include_directories(Player)
include_directories(LoggingObserver)
include_directories(CommandProcess)
include_directories(GameUtils)

add_executable(A1_COMP345
        Cards/Cards.cpp
        Cards/Cards.h
        Cards/CardsDriver.cpp
        GameEngine/GameEngine.cpp
        GameEngine/GameEngine.h
        GameEngine/GameEngineDriver.cpp
        Map/Map.cpp
        Map/Map.h
        Map/MapDriver.cpp
        Orders/Orders.cpp
        Orders/Orders.h
        Orders/OrdersDriver.cpp
        Player/Player.cpp
        Player/Player.h
        Player/PlayerDriver.cpp
        MainDriver.cpp
        LoggingObserver/LoggingObserver.cpp
        LoggingObserver/LoggingObserver.h
        LoggingObserver/LoggingObserverDriver.cpp
        CommandProcess/commandProcessing.cpp
        CommandProcess/commandProcessing.h
        CommandProcess/commandProcessingDriver.cpp
        GameUtils/gameutil.cpp
        GameUtils/gameutil.h
)
