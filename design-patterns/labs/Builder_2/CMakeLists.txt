cmake_minimum_required(VERSION 3.7)
project(Builder_2)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Builder.h
        Director.h
        Dish.h
        Functions.h
        Main.cpp
        Meal.h
        Order.h
        OrderBuilder.h
        Record.h)

add_executable(Builder_2 ${SOURCE_FILES})