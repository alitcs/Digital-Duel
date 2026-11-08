# Digital Duel

## Project Overview

I designed and built **Digital Duel**, a local two-player, top-down 2D shooter written in C with SDL2. The game takes place in an obstacle-filled arena. One player moves with `W`, `A`, `S`, and `D` and shoots with `E`; the other moves with the arrow keys and shoots with `/`. Players aim by moving, fire bullets with a cooldown, and try to hit their opponent.

The game moves between three states: a main menu, active gameplay, and a game-over screen. After a short game-over display, the players are reset and the game returns to the menu. The project includes the game assets, example screenshots, and instructions for building on Linux/WSL or Windows with MinGW.

**All graphics are hand-drawn.** This includes the visual assets used for the menu, arena, players, bullets, and game-over screen.

## Technologies

- **C** for game logic, data structures, input processing, and resource management.
- **SDL2** for window creation, rendering, keyboard and mouse input, events, and timing.
- **SDL2_image** for loading PNG assets and creating textures.
- **The C math library** for movement vectors, angles, and projectile direction.
- **GCC or MinGW** for compiling the project on Linux/WSL and Windows.

## Code Structure

- `src/main.c` initializes SDL, creates the window and renderer, loads textures, runs the frame loop, dispatches events, and switches between game states.
- `src/menu.c` draws the menu and handles mouse clicks on the play button.
- `src/game.c` contains the core gameplay: player input, movement, rotation, firing, bullet updates, collision checks, rendering, and player resets.
- `util/global.h` defines the shared `Player`, `Bullet`, and `GameState` data structures and declares shared game resources.
- `util/include.h` gathers SDL and standard C library headers.
- `util/util.c` loads images into SDL textures and releases shared SDL resources during shutdown.
- `util/util.h` contains declarations shared between the source modules.
- `assets/images/` contains the game artwork, and `ExampleImages/` contains screenshots of the menu, map, and game-over screen.

## Software Engineering Skills Demonstrated

### C Programming and Data Modeling

I use C structs to represent players and bullets, enums to represent game states, arrays to store arena boundaries and each player's active bullets, and header files to share types and declarations across modules. This demonstrates working with a lower-level language where data layout, pointer use, and resource lifetime are explicit concerns.

### Modular Design

The code separates application setup, menu behavior, gameplay, and shared utilities into focused source files. Shared data types and function declarations are placed in headers, making the boundaries between modules visible and keeping SDL setup and image loading out of the main gameplay logic.

### Real-Time Game Loops and Timing

The main loop processes SDL events, updates the active game state, renders a frame, and presents it. Movement uses frame delta time so player motion is based on elapsed time rather than simply on the number of frames rendered. SDL's tick counter also supports shot cooldowns and the timed game-over transition.

### Input and Interaction

The game supports independent keyboard layouts for two local players and mouse interaction in the menu. Player movement input is converted into movement vectors, and the player's facing angle is updated to match the movement direction.

### 2D Graphics and Collision Detection

SDL textures are rendered for the background, players, and bullets. Player and projectile sprites are rotated to match their direction. SDL rectangle intersection checks are used to detect collisions with arena boundaries and opponents; boundary checks also prevent players from moving through obstacles.

### Gameplay Logic

The game creates directional projectiles from a player's position, advances them using elapsed frame time, limits firing with a cooldown, and caps each player's active bullets at ten. A successful hit changes the game state to game over, followed by a reset and return to the menu.

### Memory and Resource Management

This project demonstrates manual memory management in C. Bullets are dynamically allocated with `malloc`, tracked through pointers in a fixed-size array, and intended to be released with `free` when removed. SDL resources have their own lifecycle: loaded surfaces are freed after conversion to textures, and textures, the renderer, the window, SDL_image, and SDL are released during shutdown.

Manual ownership also requires care around every path that removes or resets objects. In the current implementation, the player reset function sets the bullet count to zero before its cleanup loop, so that loop cannot visit and free previously active bullets. This is a useful example of why allocated objects must be released before clearing the metadata that tracks them. It is also an area where I can continue improving the project's memory-safety and lifecycle handling.

### Build and Platform Awareness

The README documents SDL2 dependencies, a GCC build command for Linux/WSL, and the runtime DLL requirements for Windows. This demonstrates configuring native-library dependencies and accounting for differences between development and runtime environments.

## Current Scope

Digital Duel is a compact local multiplayer game with a single arena, two players, obstacles, and basic projectile combat. It does not currently include sound, health bars, power-ups, or multiple weapon types. These are natural opportunities for future feature work.

## Build

On Linux/WSL, with SDL2 and SDL2_image development packages installed:

```bash
gcc src/main.c src/menu.c src/game.c util/util.c -o DigitalDuel -lSDL2 -lSDL2_image -lm
```

On Windows, build with a compiler such as MinGW and link the SDL2 libraries. The required SDL2 DLLs must be available next to the executable when running it. See `README.md` for dependency setup and run instructions.
