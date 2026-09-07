cmake_minimum_required(VERSION 3.16) 


project(Aetherium VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(Aetherium src/main.cpp src/crypto/crypto.cpp src/core/block.cpp src/core/blockchain.cpp)

# Bug on Mac of collision with LibreSSL
set(OPENSSL_ROOT_DIR /opt/homebrew/opt/openssl@3)

# Get Crypto package for SHA256
find_package(OpenSSL REQUIRED)
target_link_libraries(Aetherium PRIVATE OpenSSL::Crypto)
target_include_directories(Aetherium PRIVATE src)


