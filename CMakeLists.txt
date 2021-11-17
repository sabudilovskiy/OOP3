cmake_minimum_required(VERSION 3.20)
project(OOP3)

set(CMAKE_CXX_STANDARD 20)
include_directories(includes)
set (SOURCE_FILES main.cpp includes/Item.h includes/Seller.h includes/Support.h includes/Organization.h includes/Cargo.h includes/Shop.h includes/predeclare_classes.h)
add_executable(OOP3 ${SOURCE_FILES})
