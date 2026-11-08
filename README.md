# Digital Duel

**Digital Duel** is a bird's-eye view 1v1 2D shooter built in C using SDL2.

Two players battle in a minimalist arena full of obstacles and bullets. It features local multiplayer gameplay, a smooth game loop, and transitions through Menu → Game → Game Over → Menu.

---

## Gameplay Overview

- **Player 1** (🔴 Red)
  - Move: `W`, `A`, `S`, `D`
  - Shoot: `E`

- **Player 2** (🔵 Blue)
  - Move: Arrow keys
  - Shoot: `/`

- Bullets travel in a straight line and collide with players or boundaries.
- The game ends when one player hits the other, then returns to the menu after a short Game Over screen.

---

## Screenshots

![Menu](ExampleImages/DigitalDuelMenu.png)

![Map](ExampleImages/DigitalDuelMap.png)

![Game Over](ExampleImages/DigitalDuelGameOver.png)

---

## Requirements

### Linux / WSL:

```bash
sudo apt install libsdl2-dev libsdl2-image-dev
```

### Windows:

Download and place the following files next to your compiled executable (`DigitalDuel.exe`):

- `SDL2.dll`
- `SDL2-2.30.10-win32-x64/`
- `SDL2_image-2.0.0-win32-x64/`

Download them from:

- [SDL2 Releases](https://github.com/libsdl-org/SDL/releases)
- [SDL2_image Releases](https://github.com/libsdl-org/SDL_image/releases)

---

## Build Instructions

### Browser (Emscripten)

The browser version uses the same C game and controls, compiled to WebAssembly.
On Windows, open your Ubuntu/WSL terminal and install Emscripten:

```bash
sudo apt update
sudo apt install emscripten
```

In that terminal, move to the project folder (adjust the Windows username if
needed), then build:

```bash
cd /mnt/c/Users/hamou/digital-duel/Digital-Duel
bash web/build.sh && python3 -m http.server 8000 --directory build/web
```

This starts the local server only if the build succeeds. Keep the terminal
running and open <http://localhost:8000> in your Windows browser. (The browser
cannot load the game directly from the filesystem.)

```bash
cd /mnt/c/Users/hamou/digital-duel/Digital-Duel
python3 -m http.server 8000 --directory build/web
```

The welcome screen explains the controls. Click the game to focus it: Player 1
uses `W`, `A`, `S`, `D` and `E`; Player 2 uses the arrow keys and `/`. Touch
devices automatically show directional and shoot buttons for both players;
hold a direction to move and aim, and hold shoot to fire. Two players share the
same screen, and landscape orientation is recommended on smaller devices.
Keyboard controls remain available on touch-enabled computers. This is local
multiplayer, not online multiplayer. Python is only used as a simple local HTTP
server; the game itself is compiled from C to WebAssembly and is not a Python
website.

### Deploy to Netlify

The root `netlify.toml` configures Netlify to install the pinned Emscripten
SDK, build the browser game, and publish `build/web`. Push the project to a
GitHub repository, then in Netlify choose **Add new site → Import an existing
project**, connect that repository, and deploy. Netlify reads the build command
and publish directory from `netlify.toml`; you do not need to configure a
Python runtime or enter a separate build command. Later pushes to the connected
branch trigger new deployments.

### Linux / WSL:

```bash
gcc src/main.c src/menu.c src/game.c util/util.c -o DigitalDuel -lSDL2 -lSDL2_image -lm
```

### Windows:

Use a compiler like MinGW and link the SDL2 libraries. Make sure the `.dll` files are next to `DigitalDuel.exe` when running.

---

## How to Run

### Linux:

```bash
./DigitalDuel
```

### Windows:

Double-click `DigitalDuel.exe` (ensure the SDL2 DLLs are present).

---

## Folder Structure

```
.
├── src/
│   ├── main.c
│   ├── menu.c
│   └── game.c
├── util/
│   ├── util.c
│   ├── util.h
│   ├── global.h
│   └── include.h
├── assets/
│   └── images/
│       ├── sky.png
│       ├── map.png
│       ├── menu.png
│       ├── redplayer.png
│       ├── blueplayer.png
│       ├── bullet.png
│       └── gameover.png
├── DigitalDuel               # Compiled binary
|── README.md
```

---

## Known Issues / Ideas

- No sound/music yet
- Max 10 bullets per player (static array)
- Would be fun to see someone add:
  - Health bars
  - Power-ups
  - Weapon changes
  - supply drops
  - audio

---

## License

This project is **public domain / open-source**.

You can:

- Use it in your own projects
- Modify it
- Distribute it
- Learn from it

No attribution required

The browser welcome screen uses the separately licensed Press Start 2P font.
Its SIL Open Font License is included in `web/fonts/OFL.txt`.

---

## Contributing

Pull requests and forks are welcome. If you'd like to add a new mechanic, fix bugs, or help polish the codebase, feel free to contribute!

---

## Author

Built by **Ali Hamoudi** — powered by SDL2, C, and way too much debugging.
