cmake_minimum_required(VERSION 3.5)

project(OpenAI
        VERSION 1.0.0
        DESCRIPTION "Library for connect to open ai api"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

macro(set_if_undefined variable)
    if(NOT DEFINED "${variable}")
        set("${variable}" ${ARGN})
    endif()
endmacro()

option(OpenAI_SHARED_LIBS "Build libs as shared" OFF)

option(OpenAI_INSTALL "Generate target for installing ApiOpenAI" ${is_top_level})
set_if_undefined(OpenAI_INSTALL_CMAKEDIR
        "${CMAKE_INSTALL_LIBDIR}/cmake/openai" CACHE STRING
        "Install path for ApiOpenAI package-related CMake files")

if(DEFINED OpenAI_SHARED_LIBS)
    set(BUILD_SHARED_LIBS ${OpenAI_SHARED_LIBS})
endif()

if(NOT DEFINED CMAKE_BUILD_TYPE AND NOT DEFINED CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

add_library(OpenAI)
add_library(OpenAI::OpenAI ALIAS OpenAI)

set(OpenAI_INCLUDES
        include/OpenAI/HttpContext.h
        include/OpenAI/HttpsClient.h
        include/OpenAI/OpenAI.h
        include/OpenAI/OpenAIApi.h
        include/OpenAI/OpenAIModel.h
        include/OpenAI/GptTurbo.h
        include/OpenAI/Whisper.h
        include/OpenAI/Dalle.h
        include/OpenAI/Speaker.h
        include/OpenAI/Types/Voice.h
        include/OpenAI/Types/ResponseFormat.h
        include/OpenAI/Types/SpeechRequest.h

        include/OpenAI/Types/ChatCompletionsRequest.h
        include/OpenAI/Types/ChatCompletionsResponse.h
        include/OpenAI/Types/Usage.h
        include/OpenAI/Types/Message.h
        include/OpenAI/Types/TranscriptionsRequest.h
        include/OpenAI/Types/FileInfo.h
        include/OpenAI/Types/CreateImageRequest.h
        include/OpenAI/Types/Size.h
        include/OpenAI/Types/CreateImageResponse.h)

set(OpenAI_SOURCE
        src/OpenAI/OpenAI.cpp
        src/OpenAI/OpenAIApi.cpp
        src/OpenAI/OpenAIModel.cpp
        src/OpenAI/GptTurbo.cpp
        src/OpenAI/Whisper.cpp
        src/OpenAI/Dalle.cpp
        src/OpenAI/Speaker.cpp)

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES
        ${OpenAI_INCLUDES}
        ${OpenAI_SOURCE})

target_sources(OpenAI PRIVATE ${OpenAI_INCLUDES} ${OpenAI_SOURCE})

find_package(Boost REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(ExtendedCpp REQUIRED)

target_include_directories(OpenAI PUBLIC
        ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIRS}
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
        "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/OpenAI")

set_target_properties(OpenAI PROPERTIES
        SOVERSION ${PROJECT_VERSION_MAJOR}
        VERSION ${PROJECT_VERSION})

target_link_libraries(OpenAI PRIVATE ExtendedCpp::Json ExtendedCpp::Common ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES})

if(OpenAI_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    include(CMakePackageConfigHelpers)
    configure_package_config_file(cmake/openai-config.cmake.in openai-config.cmake
            INSTALL_DESTINATION "${OpenAI_INSTALL_CMAKEDIR}")
    write_basic_package_version_file(openai-config-version.cmake
            COMPATIBILITY SameMajorVersion)

    install(DIRECTORY include/
            TYPE INCLUDE
            COMPONENT OpenAI)

    set(targets_file "openai-shared-targets.cmake")
    if(NOT BUILD_SHARED_LIBS)
        set(targets_file "openai-static-targets.cmake")
    endif()

    install(EXPORT OpenAI_export
            COMPONENT "${PROJECT_NAME}"
            FILE "${targets_file}"
            DESTINATION ${OpenAI_INSTALL_CMAKEDIR}
            NAMESPACE ${PROJECT_NAME}::)

    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/openai-config.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/openai-config-version.cmake"
            COMPONENT OpenAI
            DESTINATION "${OpenAI_INSTALL_CMAKEDIR}")

    include(cmake/utils.cmake)
    install_projects(OpenAI)
endif()