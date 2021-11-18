cmake_minimum_required(VERSION 3.20)
project(OOP3)

set(CMAKE_CXX_STANDARD 20)
include_directories(includes)
set (SOURCE_FILES main.cpp includes/Item.h includes/Seller.h includes/Support.h includes/Organization.h includes/Cargo.h includes/Shop.h src/Cargo.cpp src/Item.cpp src/Organization.cpp src/Seller.cpp src/Shop.cpp src/Support.cpp includes/ConsoleSeller.h src/ConsoleSeller.cpp includes/ConsoleOrganization.h src/ConsoleOrganization.cpp src/ConsoleSellerFinance.cpp includes/ConsoleSellerFinance.h src/ConsoleSellerItems.cpp includes/ConsoleSellerItems.h src/ConsoleSellerEmployees.cpp includes/ConsoleSellerEmployees.h)
add_executable(OOP3 ${SOURCE_FILES})
