# CaptureTheFlag
- 2d world
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
