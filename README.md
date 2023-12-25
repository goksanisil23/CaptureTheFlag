# CaptureTheFlag
- Use base component and entity class
```c++
enum ComponentType {
    POSITION,
    VELOCITY,
    HEALTH,
    // ... other component types ...
    COMPONENT_COUNT
};
class Entity {
private:
    std::array<std::unique_ptr<Component>, COMPONENT_COUNT> components;

public:
    template <typename T>
    T* getComponent(ComponentType type) {
        return static_cast<T*>(components[type].get());
    }

    template <typename T, typename... Args>
    T* addComponent(ComponentType type, Args&&... args) {
        T* component = new T(std::forward<Args>(args)...);
        components[type] = std::unique_ptr<Component>(component);
        return component;
    }

    void removeComponent(ComponentType type) {
        components[type].reset();
    }

    // ... other entity-related methods ...
};
// ...
   Entity entity;
    entity.addComponent<PositionComponent>(POSITION, 10.0f, 20.0f);

    PositionComponent* position = entity.getComponent<PositionComponent>(POSITION);
    if (position) {
        // Do something with the position component
    }
```
- visibility cone of each player
- can only shoot within subset reachability within the visibility cone
- can make the environment grid like so that obstacles would be just a set of occupied cells for fast raycasting
  - consider CUDA grid
  - resolution can be smalle than the pixel size
- some traditional robots can add ability through componentns like path-finding component, object tracking component.
- 2vs2 or 1vs1?
- different weapons like short range high rate, long range low rate, and time triggered bomb



## Stretch features
- Integrate CUDA to avoid loading render buffer to texture for individual pixel operations
- Multiplayer over network
- Force field for a player that has killed multiple enemies.
