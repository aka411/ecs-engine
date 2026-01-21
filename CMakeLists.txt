cmake_minimum_required(VERSION 3.15) 

if(TARGET ECSEngine)
    return()
endif()

project(ECSEngine VERSION 1.0.0 LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(ecs_engine_sources
    "src/archetype_manager.cpp"
    "src/command_buffer.cpp"
    "src/command_processor.cpp"
    "src/bump_allocator.cpp"
    "src/entity_manager.cpp"
    "src/component_registry.cpp"
    "src/ecs_engine.cpp"
    "src/null_fatal_error_handler.cpp" 
    "src/query-system/query_system.cpp"
    "src/query-system/entity_chunk_view.cpp"
    "src/query-system/chunk_array_view.cpp"
    "src/query-system/query.cpp"
    "src/query-system/query_builder.cpp" 
    "src/ecs_internal_manager.cpp"
)


add_library(ECSEngine STATIC ${ecs_engine_sources})


add_library(ECSEngine::ECSEngine ALIAS ECSEngine)


target_include_directories(ECSEngine
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        #$<INSTALL_INTERFACE:include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal
)

option(ECSEngine_FORCE_ENABLE_TESTS "Enable Tests" OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR OR ECSEngine_FORCE_ENABLE_TESTS)
    #option(ECSEngine_ENABLE_TESTS "Enable Tests" ON)
    #if(ECSEngine_ENABLE_TESTS)
        enable_testing()
        add_subdirectory(tests)
   # endif()
endif()