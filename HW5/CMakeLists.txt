cmake_minimum_required(VERSION 3.17)
project(HW4)

set(CMAKE_CXX_STANDARD 20)

add_executable(HW4 main.cpp PassengerGateway.cpp PassengerGateway.h Passenger.cpp Passenger.h MobileApp.cpp MobileApp.h Driver.cpp Driver.h "additional functions.cpp" Car.cpp Car.h DriverGateway.cpp DriverGateway.h AdminGateway.cpp AdminGateway.h Admin.cpp Admin.h Device.cpp Device.h)