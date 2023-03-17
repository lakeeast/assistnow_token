cmake_minimum_required(VERSION 3.0.0)
project(token)

if (APPLE)
    set(OPENSSL_ROOT_DIR ${OPENSSL_ROOT_DIR} /opt/homebrew/Cellar/openssl@3/3.0.8)
    set(OPENSSL_CRYPTO_LIBRARY ${OPENSSL_ROOT_DIR}/lib/libcrypto.a CACHE FILEPATH "" FORCE)
    set(OPENSSL_SSL_LIBRARY ${OPENSSL_ROOT_DIR}/lib/libssl.a CACHE FILEPATH "" FORCE)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2b")
find_package(cpprestsdk REQUIRED)
find_package(Boost COMPONENTS regex system filesystem REQUIRED)
find_package(OpenSSL REQUIRED)
add_executable(assistnow_token main.cpp)

target_link_libraries(assistnow_token PRIVATE 
                            cpprestsdk::cpprest
                            ${Boost_FILESYSTEM_LIBRARY}
                            ${Boost_SYSTEM_LIBRARY}
                            ${Boost_REGEX_LIBRARY}
                            OpenSSL::SSL)