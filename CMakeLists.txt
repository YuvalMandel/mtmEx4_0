cmake_minimum_required(VERSION 3.15)
project(ex4)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

#add_executable(ex3
#        MtmParkingLot.cpp
#        ParkingLot.cpp
#        ParkingLot.h
#        ParkingLotPrinter.cpp
#        ParkingLotPrinter.h
#        ParkingLotTypes.h
#        ParkingSpot.cpp
#        ParkingSpot.h
#        ourTime.cpp
#        ourTime.h
#        UniqueArray.h
#        UniqueArrayImp.h)

add_executable(ex4
        graph.cpp
        graph.h
        gcalc.cpp
        gcalc.h)
