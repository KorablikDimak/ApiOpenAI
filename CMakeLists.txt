cmake_minimum_required(VERSION 3.5)

project(OpenAI
        VERSION 1.0.0
        DESCRIPTION "Library for connect to open ai api"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(cmake/utils.cmake)

if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

string(COMPARE EQUAL "${CMAKE_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}" is_top_level)

option(BUILD_SHARED_LIBS "Build libs as shared" ON)
option(OpenAI_INSTALL "Generate target for installing ApiOpenAI" ${is_top_level})
set_if_undefined(OpenAI_INSTALL_CMAKEDIR
        "${CMAKE_INSTALL_LIBDIR}/openai" CACHE STRING
        "Install path for ApiOpenAI package-related CMake files")

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

add_library(OpenAI ${OpenAI_INCLUDES} ${OpenAI_SOURCE})
add_library(OpenAI::OpenAI ALIAS OpenAI)

find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED)
find_package(ExtendedCpp REQUIRED)

set_public_include_directories(OpenAI)
set_targets_version(OpenAI)

target_link_libraries(OpenAI PRIVATE
        ExtendedCpp::Json
        ExtendedCpp::Common
        ${OPENSSL_LIBRARIES}
        ${Boost_LIBRARIES})

if(MINGW)
    target_link_libraries(OpenAI PRIVATE ws2_32)
endif()

if(MSVC)
    target_compile_options(OpenAI PRIVATE /bigobj)
elseif(CMAKE_BUILD_TYPE MATCHES "Debug")
    target_compile_options(OpenAI PRIVATE -O1 -Wa,-mbig-obj)
endif()

if(OpenAI_INSTALL AND NOT CMAKE_SKIP_INSTALL_RULES)
    configure_package_config_file(cmake/openai-config.cmake.in openai-config.cmake
            INSTALL_DESTINATION "${OpenAI_INSTALL_CMAKEDIR}")

    write_basic_package_version_file(
            "${CMAKE_CURRENT_BINARY_DIR}/openai-config-version.cmake"
            VERSION ${PROJECT_VERSION}
            COMPATIBILITY SameMajorVersion)

    install(DIRECTORY include/
            TYPE INCLUDE)

    install(EXPORT OpenAI_export
            NAMESPACE OpenAI::
            FILE "openai-targets.cmake"
            DESTINATION ${OpenAI_INSTALL_CMAKEDIR})

    install(FILES
            "${CMAKE_CURRENT_BINARY_DIR}/openai-config.cmake"
            "${CMAKE_CURRENT_BINARY_DIR}/openai-config-version.cmake"
            DESTINATION ${OpenAI_INSTALL_CMAKEDIR})

    install_projects(OpenAI)
endif()