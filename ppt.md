# 🚀 CG Animation: From Bounce to Blast

---
## 🧨 What Just Happened?

---
## 🧨 What Just Happened?

We ran:

```bash
$ ./animation
```

---
## 🧨 What Just Happened?

We ran:

```bash
$ ./animation
```

And then...

---

## 🧨 What Just Happened?

We ran:

```bash
$ ./animation
```

And then...

* Ball bounced

---

## 🧨 What Just Happened?

We ran:

```bash
$ ./animation
```

And then...

* Ball bounced
* Color shifted

---

## 🧨 What Just Happened?

We ran:

```bash
$ ./animation
```

And then...

* Ball bounced
* Color shifted
* Rocket launched

---

## 🧨 What Just Happened?

We ran:

```bash
$ ./animation
```

And then...

* Ball bounced
* Color shifted
* Rocket launched

Let’s explain what you *just saw*.

---

## ./intro.sh

**Scene**: Classroom whiteboard **Objects**:

---

## ./intro.sh

**Scene**: Classroom whiteboard **Objects**:

* Background swap simulates board update

---

## ./intro.sh

**Scene**: Classroom whiteboard **Objects**:

* Background swap simulates board update  
* Ball bounces + changes color 

---

## ./intro.sh

**Scene**: Classroom whiteboard **Objects**:

* Background swap simulates board update  
* Ball bounces + changes color  
* Morphs into rocket → launches

---

## ./intro.sh

**Scene**: Classroom whiteboard **Objects**:

* Background swap simulates board update  
* Ball bounces + changes color  
* Morphs into rocket → launches  
* Loop resets

---

## ./intro.sh

**Scene**: Classroom whiteboard **Objects**:

* Background swap simulates board update  
* Ball bounces + changes color  
* Morphs into rocket → launches  
* Loop resets  

**Keyframes**:

* Bounce ×4
* Morph
* Launch 🚀

---

## ./functions.sh

* `loadTexture()` → Loads PNGs to GPU

---

## ./functions.sh

* `loadTexture()` → Loads PNGs to GPU
* `drawBall(x, y)` → Renders circle with color

---

## ./functions.sh

* `loadTexture()` → Loads PNGs to GPU
* `drawBall(x, y)` → Renders circle with color
* `drawRocket(x, y)` → Textured rocket with alpha

---

## ./functions.sh

* `loadTexture()` → Loads PNGs to GPU
* `drawBall(x, y)` → Renders circle with color
* `drawRocket(x, y)` → Textured rocket with alpha
* `timer()` → Controls gravity, bounce, rocket launch

---

## ./functions.sh

* `loadTexture()` → Loads PNGs to GPU
* `drawBall(x, y)` → Renders circle with color
* `drawRocket(x, y)` → Textured rocket with alpha
* `timer()` → Controls gravity, bounce, rocket launch
* `key()` → Spacebar toggles start/pause

---

## ./functions.sh

* `loadTexture()` → Loads PNGs to GPU
* `drawBall(x, y)` → Renders circle with color
* `drawRocket(x, y)` → Textured rocket with alpha
* `timer()` → Controls gravity, bounce, rocket launch
* `key()` → Spacebar toggles start/pause
* `display()` → The render loop

---

## ./functions.sh

* `loadTexture()` → Loads PNGs to GPU
* `drawBall(x, y)` → Renders circle with color
* `drawRocket(x, y)` → Textured rocket with alpha
* `timer()` → Controls gravity, bounce, rocket launch
* `key()` → Spacebar toggles start/pause
* `display()` → The render loop
* `reshape()` → Maintains aspect ratio

---

## ./functions.sh

* `loadTexture()` → Loads PNGs to GPU
* `drawBall(x, y)` → Renders circle with color
* `drawRocket(x, y)` → Textured rocket with alpha
* `timer()` → Controls gravity, bounce, rocket launch
* `key()` → Spacebar toggles start/pause
* `display()` → The render loop
* `reshape()` → Maintains aspect ratio
* `drawTexturedQuad()` → Renders full background image

---

## ./functions.sh
* `loadTexture()` → Loads PNGs to GPU
* `drawBall(x, y)` → Renders circle with color
* `drawRocket(x, y)` → Textured rocket with alpha
* `timer()` → Controls gravity, bounce, rocket launch
* `key()` → Spacebar toggles start/pause
* `display()` → The render loop
* `reshape()` → Maintains aspect ratio
* `drawTexturedQuad()` → Renders full background image
  
**finally**
* `main()` → Initializes GLUT, sets callbacks, and enters render loop

---

## ./environment.sh

**Language**: C

---

## ./environment.sh

**Language**: C

**Renderer**: OpenGL + GLUT

---

## ./environment.sh

**Language**: C

**Renderer**: OpenGL + GLUT

**Image Loader**: stb\_image.h

---

## ./environment.sh

**Language**: C

**Renderer**: OpenGL + GLUT

**Image Loader**: stb\_image.h

**Editor**: Neovim / VS Code

---

## ./environment.sh

**Language**: C

**Renderer**: OpenGL + GLUT

**Image Loader**: stb_image.h

**Editor**: Neovim / VS Code

**Why?**

To konw under the hood of animation softwares.

---

## ./challenges.sh

---

## ./challenges.sh

* Background stretched

---

## ./challenges.sh

* Background stretched
* Background flipped upside down

---

## ./challenges.sh

* Background stretched
* Background flipped upside down
* Rocket flipped upside down

---

## ./challenges.sh

* Background stretched
* Background flipped upside down
* Rocket flipped upside down
* Ball flying into void

---

## ./challenges.sh

* Background stretched
* Background flipped upside down
* Rocket flipped upside down
* Ball flying into void
* And yes, the rocket killed us live.

---

## ./lessons.sh

---

## ./lessons.sh

* Animation = illusion cause by human eye's bottolneck + logic

---

## ./lessons.sh

* Animation = illusion cause by human eye's bottolneck + logic
* Texture, memory and binding

---

## ./lessons.sh

* Animation = illusion cause by human eye's bottolneck + logic
* Texture, memory and binding
* Aspect ratio handling

---

## ./lessons.sh

* Animation = illusion cause by human eye's bottolneck + logic
* Texture, memory and binding
* Aspect ratio handling
* Real-time user input with `glutKeyboardFunc`

---

## ./lessons.sh

* Animation = illusion cause by human eye's bottolneck + logic
* Texture, memory and binding
* Aspect ratio handling
* Real-time user input with `glutKeyboardFunc`
* Timing frames with `glutTimerFunc`

---

## ./lessons.sh

* Animation = illusion cause by human eye's bottolneck + logic
* Texture, memory and binding
* Aspect ratio handling
* Real-time user input with `glutKeyboardFunc`
* Timing frames with `glutTimerFunc`
* Chaos is part of the creative process

---

## ./exit.sh

Ball bounced

---

## ./exit.sh

Ball bounced ✅

---

## ./exit.sh

Ball bounced ✅

Rocket launched

---

## ./exit.sh

Ball bounced ✅

Rocket launched ✅

---

## ./exit.sh

Ball bounced ✅

Rocket launched ✅

We got vaporized

---

## ./exit.sh

Ball bounced ✅

Rocket launched ✅

We got vaporized ✅

```bash
$ thank_you
```

