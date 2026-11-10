cmake_minimum_required(VERSION 3.16)

project(minishop)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(minishop
        main.cpp
        Product.cpp
        Customer.cpp
        CartItem.cpp
        ShoppingCart.cpp
        Order.cpp
        ProductFile.cpp
)
