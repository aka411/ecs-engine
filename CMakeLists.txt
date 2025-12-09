

cmake_minimum_required(VERSION 3.15) # FetchContent_MakeAvailable requires 3.14+
project(TheEngineECS CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)




enable_testing()

add_library(TheEngine_ECS STATIC

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





target_include_directories(TheEngine_ECS
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>

        $<INSTALL_INTERFACE:include>
)

target_include_directories(TheEngine_ECS 
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src/internal

)

add_subdirectory(tests)
