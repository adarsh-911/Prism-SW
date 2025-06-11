# Cursor AI Prompts for Horror Game Development

## 🎯 **Setup & Foundation Prompts**

### **Prompt 1: Project Structure Setup**
```
Create a C++ project structure for a first-person horror game with the following requirements:
- Uses existing OpenGL rendering system (gl/ namespace)
- Game logic in game/ namespace  
- Uses GLM for math operations
- Embedded-friendly (no STL containers like std::list, prefer std::vector)
- Create proper header/implementation file separation
- Include CMakeLists.txt or makefile integration

Directory structure should be:
- game/ (game logic)
- gl/ (existing rendering - DON'T MODIFY)
- graphics/ (existing graphics backend - DON'T MODIFY)
- assets/ (models, textures, scenes)
- test/ (test files)

Create the basic folder structure and main.cpp entry point.
```

---

## 🏗️ **Core System Prompts**

### **Prompt 2: Collision System Foundation**
```
Implement a collision system for the horror game with these specifications:

Requirements:
- Integrate with existing gl::Object class (has getBoundingBox() method)
- Support hardcoded static geometry (walls, floors)
- Dynamic object collision (player, NPCs, props)
- Collision layers: STATIC_WORLD, PLAYER, NPC, PROPS, TRIGGERS
- Spatial grid optimization for performance (5x5 meter cells)
- Raycast support for interaction and line-of-sight

Create files:
- game/CollisionSystem.hpp
- game/CollisionSystem.cpp

Include:
- StaticGeometry class for hardcoded walls/floors
- CollisionManager for dynamic objects
- SpatialGrid for performance optimization
- Raycast functionality
- Movement resolution (sliding collision)
```

### **Prompt 3: Entity Base Class**
```
Create a base Entity system that wraps the existing gl::Object rendering system:

Requirements:
- Entity base class with common functionality
- Integrates with gl::Object for rendering/physics
- Entity types: PLAYER, NPC, PROP, TRIGGER, KEY, DOOR
- Position, rotation, scale management
- Update/render interface
- Collision integration
- World/Room assignment

Create files:
- game/Entity.hpp
- game/Entity.cpp

Features needed:
- Transform delegation to gl::Object
- Bounding box access
- Active/inactive state
- Name and type identification
- Virtual update() and render() methods
```

### **Prompt 4: Player Controller**
```
Implement a Player class with first-person movement and camera control:

Requirements:
- Inherits from Entity base class
- First-person camera (uses existing gp::CameraBase interface)
- WASD movement with joystick input
- Mouse look with sensitivity settings
- Walking/running with stamina system
- Collision-based movement using CollisionSystem
- Health and inventory management
- Interaction raycast (2 meter range)

Create files:
- game/Player.hpp  
- game/Player.cpp

Include:
- Movement states (walk, run, crouch)
- Camera integration with existing graphics system
- Input processing (keyboard/mouse/joystick)
- Inventory system for keys
- Health/stamina stats
```

---

## 🤖 **AI & Behavior Prompts**

### **Prompt 5: NPC AI System**
```
Create an NPC AI system for the horror game enemy:

Requirements:
- Inherits from Entity base class
- State machine: IDLE, PATROL, ALERT, CHASE, SEARCH
- Vision system (field of view, range, line-of-sight)
- Hearing system (sound detection from player actions)
- Simple waypoint pathfinding between rooms
- Player pursuit and investigation behaviors

Create files:
- game/NPC.hpp
- game/NPC.cpp

Features:
- Vision cone detection using raycast
- Sound event response system
- Memory of last known player position
- Room-to-room navigation
- Configurable AI parameters (speed, hearing range, vision range)
```

### **Prompt 6: Game Objects (Props, Keys, Doors)**
```
Implement interactive game objects for the horror game:

Requirements:
- Prop class for interactive objects
- Key class for collectible items
- Door class with open/close animations and key requirements
- Interaction callbacks and state management
- Integration with Player interaction system

Create files:
- game/Props.hpp
- game/Props.cpp

Include:
- Prop base class with interaction callbacks
- Key pickup functionality
- Door states (CLOSED, OPENING, OPEN, LOCKED)
- Animation system for doors
- Inventory integration
```

---

## 🗺️ **World & Level Management Prompts**

### **Prompt 7: Room and Floor System**
```
Create a room-based level management system:

Requirements:
- Room class with AABB boundaries
- Floor class containing multiple rooms
- Room connections (doorways)
- Entity assignment to rooms
- Room-based audio occlusion
- Navigation between rooms

Create files:
- game/Room.hpp
- game/Room.cpp
- game/Floor.hpp
- game/Floor.cpp

Features:
- Room boundary checking
- Entity listing per room
- Room transition detection
- Audio properties per room
- Room connection graph
```

### **Prompt 8: Scene Loading System**
```
Implement a scene loader that can load levels from JSON files:

Requirements:
- JSON parsing (lightweight, no external dependencies)
- Load objects with positions/rotations from JSON
- Create Entity objects from scene data
- Integration with existing gl::Model loading
- Support for room definitions and triggers

Create files:
- game/SceneLoader.hpp
- game/SceneLoader.cpp

Features:
- Parse JSON scene files
- Instantiate Entity objects
- Load and assign gl::Models
- Set up room boundaries
- Configure triggers and interactions

Example JSON structure:
```json
{
  "rooms": [{"name": "Hall", "bounds_min": [-10,0,-10], "bounds_max": [10,3,10]}],
  "objects": [{"name": "door1", "type": "DOOR", "position": [0,0,5], "required_key": "key1"}]
}
```
```

---

## 🎮 **Input & Interface Prompts**

### **Prompt 9: Input Management System**
```
Create an input management system for the horror game:

Requirements:
- Support keyboard, mouse, and joystick input
- Input state tracking (pressed, held, released)
- Configurable key bindings
- Integration with Player movement
- Interaction input handling

Create files:
- game/InputManager.hpp
- game/InputManager.cpp

Features:
- InputState struct with all input data
- Key mapping system
- Mouse sensitivity settings
- Joystick deadzone handling
- Input event callbacks
```

### **Prompt 10: Game World Manager**
```
Implement a central World manager that coordinates all game systems:

Requirements:
- Manages current Floor/Room
- Updates all Entity objects
- Handles CollisionSystem
- Manages Player reference
- Event broadcasting (sound events)
- Global game state

Create files:
- game/World.hpp
- game/World.cpp

Features:
- Entity lifecycle management
- System update coordination
- Event system for game-wide events
- Room transition handling
- Global queries (find entities, etc.)
```

---

## 🔊 **Audio & Events Prompts**

### **Prompt 11: Audio Event System**
```
Create an audio event system for the horror game:

Requirements:
- Integration with existing I2S audio engine
- 3D positional audio
- Sound event broadcasting
- Footstep generation based on movement
- Ambient audio per room

Create files:
- game/AudioManager.hpp
- game/AudioManager.cpp

Features:
- Sound event types (footstep, door, ambient)
- 3D audio positioning
- Volume based on distance
- Surface-based footstep sounds
- Audio occlusion by walls
```

### **Prompt 12: Trigger System**
```
Implement a trigger system for game events:

Requirements:
- Trigger zones with AABB bounds
- Multiple trigger types (proximity, timer, item-based)
- Event actions (play sound, spawn entity, unlock door)
- One-shot and repeating triggers
- Integration with Entity system

Create files:
- game/TriggerSystem.hpp
- game/TriggerSystem.cpp

Features:
- Trigger base class with polymorphic behavior
- ProximityTrigger, TimerTrigger, ItemTrigger classes
- Event action system
- Trigger enable/disable functionality
```

---

## 🎯 **Integration & Testing Prompts**

### **Prompt 13: Game Loop Integration**
```
Create the main game loop that integrates all systems:

Requirements:
- Fixed timestep at 30 FPS (embedded-friendly)
- Update order: Input → Physics → AI → Audio → Render
- Integration with existing OpenGL rendering
- Memory management and cleanup
- Game state management (MENU, PLAYING, PAUSED)

Create files:
- game/GameLoop.hpp
- game/GameLoop.cpp

Features:
- Main game loop with proper timing
- System initialization order
- Frame rate limiting
- Memory usage monitoring
- Clean shutdown process
```

### **Prompt 14: Test Scene Creation**
```
Create a test scene to demonstrate all game systems working together:

Requirements:
- Simple level with multiple rooms
- Player spawning and movement
- At least one NPC with basic AI
- Interactive doors and keys
- Collision detection testing
- Audio event testing

Create files:
- test/TestScene.cpp
- assets/test_level.json

Features:
- Hardcoded test geometry
- Entity placement
- Trigger setup
- Audio zone testing
- Performance monitoring
```

---

## 🛠️ **Debug & Tools Prompts**

### **Prompt 15: Debug Visualization**
```
Implement debug visualization tools for development:

Requirements:
- Collision boundary rendering
- AI state visualization
- Trigger zone display
- Performance metrics
- Entity information overlay

Create files:
- game/DebugRenderer.hpp
- game/DebugRenderer.cpp

Features:
- Wireframe AABB rendering
- AI vision cone display
- FPS and memory counters
- Entity list with states
- Toggle-able debug layers
```

### **Prompt 16: Memory Optimization**
```
Optimize the game for embedded hardware constraints:

Requirements:
- Object pooling for frequently created entities
- Memory usage profiling
- Reduce dynamic allocations
- Efficient data structures
- Resource cleanup

Create files:
- game/MemoryManager.hpp
- game/MemoryManager.cpp

Features:
- Entity object pools
- Memory usage tracking
- Resource lifetime management
- Allocation statistics
- Memory leak detection
```

---

## 📋 **Usage Instructions for Cursor AI**

### **How to Use These Prompts:**

1. **Start with Setup Prompts (1-2)** - Get basic project structure
2. **Core Systems (3-6)** - Build fundamental game classes
3. **World Management (7-8)** - Level and scene systems
4. **Input & Integration (9-10)** - User interaction and world coordination
5. **Audio & Events (11-12)** - Sound and trigger systems
6. **Integration (13-14)** - Complete game loop and testing
7. **Debug & Optimization (15-16)** - Development tools and performance

### **For Each Prompt:**
- Copy the prompt exactly to Cursor AI
- Wait for complete implementation
- Test the generated code
- Ask for fixes if needed: "Fix compilation errors in the generated code"
- Move to next prompt only after current one works

### **Additional Helper Prompts:**

```
"Fix all compilation errors in the current code and ensure it compiles with g++ -std=c++17"

"Add error handling and null pointer checks to the generated code"

"Optimize this code for embedded systems with limited memory"

"Add comprehensive comments and documentation to the generated code"

"Create a simple test function to verify this system works correctly"
```

This systematic approach will give you a complete, working horror game codebase that integrates with your existing OpenGL rendering system!