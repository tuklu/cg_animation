# CG Animation - Ball to Rocket (OpenGL + GLUT)

---

## ⚙️ Setup & Prerequisites

### 🖥 Supported Platforms

* macOS
* Linux
* Windows (via MinGW)

### 📦 Requirements

* A C compiler (`gcc` or `clang`)
* OpenGL + GLUT libraries
* PNG support via `stb_image.h` (already included)

### 🚀 Quick Start (Manual Build)

#### macOS:

```bash
gcc main.c -o cg_anim -framework OpenGL -framework GLUT -DGL_SILENCE_DEPRECATION
./cg_anim
```

#### Linux (Debian-based):

```bash
sudo apt install build-essential freeglut3-dev libglew-dev
gcc main.c -o cg_anim -lGL -lGLU -lglut
./cg_anim
```

#### Windows (with MinGW):

```bash
gcc main.c -IC:\freeglut\include -LC:\freeglut\lib -lfreeglut -lopengl32 -o cg_anim.exe
cg_anim.exe
```

### 🔄 Automatic Setup

This repo includes platform-specific setup scripts:

* `setup_unix.sh`: For macOS & Linux – installs dependencies and builds automatically.
* `setup_windows.bat`: For Windows – installs MinGW, sets up freeglut, builds the executable, and copies required DLLs.

> Just run the appropriate script for your OS and you're good to go!

---

## 🧠 Overview

This project is a simple 2D OpenGL animation where a ball bounces a few times, changes color on each bounce, then morphs into a rocket and flies upward. The animation is projected in front of a classroom-like background. The animation starts only after pressing the space bar. The first background image (`cg_background.png`) is displayed at launch and then switches to `cg_background2.png` once the animation starts.

---

## 📦 Header Files and Macros

```c
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
```

* **`stb_image.h`** is a single-header image loader library used to load `.png`/`.jpg` files.

```c
#include <GLUT/glut.h>
```

* GLUT (OpenGL Utility Toolkit) provides window creation, input handling, and a basic render loop.

```c
#include <math.h>
#include <stdbool.h>
```

* `math.h` is used for sine/cosine functions.
* `stdbool.h` enables `bool`, `true`, `false` in C.

---

## 🎨 Global Variables

* **Textures:** `bg1`, `bg2`, `rocketTex` store OpenGL texture IDs.
* **State Flags:** `animationStarted`, `rocketMode`, `isPaused` are booleans to control animation states.
* **Physics:** `ballX`, `ballY`, `ballVelocity`, `gravity`, `rocketY` control motion.
* **Color Logic:** `bounceColors` holds different colors used per bounce.
* **Aspect Ratio:** `bgAspect` helps in maintaining image proportions during resizing.

---

## 📸 Texture Loading

```c
GLuint loadTexture(const char* filename, bool setAspect)
```

* Loads image using `stbi_load`.
* Creates an OpenGL texture using `glGenTextures`, `glTexImage2D`.
* Optionally sets the aspect ratio.

---

## 🧱 Drawing Functions

### `drawTexturedQuad`

Draws a full-screen quad and binds a given texture.

```glsl
   (-1,1)--------- (1,1)
     |              |
     |              |
   (-1,-1)--------(1,-1)
```

### `drawBall`

Draws a circle using `GL_TRIANGLE_FAN` and applies color from `bounceColors`. It corrects aspect ratio using current viewport dimensions to ensure the circle isn’t stretched.

### `drawRocket`

Draws a textured rectangle with `rocket.png`. Blending is enabled to support transparency.

---

## 🖥 Display Logic

### `display()`

* Clears the screen using `glClear`.
* Draws `bg1` if the animation hasn't started, otherwise `bg2`.
* Depending on the animation state, it either draws the ball or the rocket.

### `reshape()`

* Maintains the aspect ratio of background images.
* Adjusts viewport using `glViewport()`.
* Uses `gluOrtho2D()` to maintain a fixed coordinate range \[-1, 1].

### `timer()`

* Main animation update logic.
* Handles ball bouncing with gravity and bounce physics.
* After 4 bounces, switches to rocket mode.
* In rocket mode, moves the rocket upward.
* When the rocket goes beyond a safe top threshold, the animation resets.

### `key()`

* Pressing **space**:

  * Starts the animation if not already started.
  * Toggles pause/resume otherwise.

---

## ⛓ OpenGL Concepts Used

### Texturing

* `glEnable(GL_TEXTURE_2D)` enables 2D texturing.
* `glBindTexture(GL_TEXTURE_2D, textureID)` binds a texture to draw.
* `glTexCoord2f()` sets the texture coordinates.

### Blending

* Enables transparency using:

```c
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
```

### Viewport and Projection

* `glViewport(x, y, width, height)` sets the drawable region.
* `gluOrtho2D()` sets a 2D orthographic projection.

---

## 🔁 Control Flow Summary

1. **Start**: Shows first background.
2. **Press Space**: Switch to second background and begin animation.
3. **Ball bounces 4 times** with color changes.
4. **Morphs into rocket**: flies up.
5. **Rocket exits screen**, animation resets but keeps looping.
6. **Press Space again**: toggles pause/resume.

---

## 🎮 Main Function

```c
int main(int argc, char** argv)
```

* Initializes GLUT and creates a window.
* Loads textures.
* Registers callbacks:

  * `display()` for rendering
  * `reshape()` for resizing
  * `key()` for input
  * `timer()` for animation loop
* Starts GLUT main loop with `glutMainLoop()`.

---

## 🚀 Final Thoughts

This project is a great beginner-friendly introduction to:

* 2D animation in OpenGL
* Texture handling and blending
* Basic physics simulation
* Event-based programming with GLUT

Enhancements you could try:

* Add sound on bounce
* Add starry background after rocket launches
* Replace rocket with GIF-style fire trail using frame animation

---

### 📽 Slides (for presentation)

* This project uses [`maaslalani/slides`](https://github.com/maaslalani/slides) for live markdown-based slides.
* Install it using:

  ```bash
  go install github.com/maaslalani/slides@latest
  ```
* This tool requires [Go](https://golang.org/) to be installed on your system.

## 📑 Code Explanation & Presentation Script

[Detailed code breakdown and full team presentation script available here](https://www.notion.so/CG-Animation-1f357d6b7a8580639154c933c862243c?pvs=4)
