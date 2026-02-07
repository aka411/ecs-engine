# ECS Engine
[![CI Build Status](https://github.com/aka411/ecs-engine/actions/workflows/ci.yml/badge.svg)](https://github.com/aka411/ecs-engine/actions/workflows/ci.yml)

A custom-built **Entity Component System (ECS)**, originally developed as a subsystem for a game engine project I was working on.

After creating a minimum working prototype, I decided to move the ECS into its own dedicated repository where I can easily develop it as a standalone project.

## Project Philosophy

While mature frameworks like Flecs or EnTT exist, this project is meant to be a deep-dive into **Data-Oriented Design (DOD)**. The primary goal was to architect a high-performance ECS from the ground up to master:

- **Low-Level Memory Management:** Handling raw memory blocks and pointer arithmetic while ensuring memory safety and leak-free resource management.

- **Cache Locality:** Designing data structures that prioritize CPU cache hits through contiguous memory layouts, moving away from the **pointer chasing** common in traditional OOP.

- **API & Library Design:** Architecting the ECS as a standalone, reusable library. This involved creating a clean, decoupled interface that allows the engine to be integrated into various projects with minimal friction.

### Architecture Diagram

![System Architecture Diagram](docs/ecs_design_diagram.svg)

### Key Architectural Features

- **Archetype-Based Storage (SoA):** Entities with identical component compositions are grouped into archetypes. Data is stored in **Structure-of-Arrays (SoA)** format within chunks, ensuring contiguous memory access during system iterations.

- **Component Pools & Paging:** Managing memory in blocks to avoid fragmentation and maintain data in cache, minimizing pointer chasing.

- **Deferred Command Buffer:** Provides a way to stage structural changes like adding components to entities.

### Usage Example
The following example demonstrates how to initialize the engine, register components, and run a simple physics update system using chunk-based iteration.
```cpp

// Create the engine
ECS::NullFatalErrorHandler myErrorHandler;
ECS::ECSEngine ecsEngine(myErrorHandler);

// Assuming struct Position { float x, y, z; } and struct Velocity { float dx, dy, dz; } are defined
// Register components

auto positionId = ecsEngine.registerComponent<Position>();
auto velocityId = ecsEngine.registerComponent<Velocity>();

// Create an entity and add data
EntityId player = ecsEngine.createEntity();
ecsEngine.addComponentToEntity(player, Position{0.0f, 0.0f, 0.0f});
ecsEngine.addComponentToEntity(player, Velocity{10.0f, 1.0f, 0.0f});


 ecsEngine.processBufferedCommands();

 
 // Query the system
 auto query = ecsEngine.createQuery()
  .with<Position>()
  .with<Velocity>()
  .build();


 float deltaT = 0.016f; //  60 FPS 

 for (auto& chunk : query.getChunkArrayViews())
 {
   Position* posArr = chunk.getComponentArray<Position>();
   Velocity* velArr = chunk.getComponentArray<Velocity>();
   size_t count = chunk.getCount();

   for (size_t i = 0; i < count; ++i)
   {
     posArr[i].x += velArr[i].dx * deltaT;
     posArr[i].y += velArr[i].dy * deltaT;
     posArr[i].z += velArr[i].dz * deltaT;
   }
  }

```
 
