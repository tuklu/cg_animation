#!/bin/bash

echo "🖥️ Setting up environment for CG Animation..."
OS="$(uname -s)"

if [[ "$OS" != "Linux" && "$OS" != "Darwin" ]]; then
  echo "❌ Unsupported OS. Please use setup_windows.bat on Windows."
  exit 1
fi

echo "🔍 Checking for C compiler (gcc or clang)..."
if command -v gcc >/dev/null || command -v clang >/dev/null; then
  echo "✅ C compiler found."
else
  echo "❌ No compiler found. Installing..."
  if [[ "$OS" == "Linux" ]]; then
    sudo apt update && sudo apt install -y build-essential clang
  else
    xcode-select --install
  fi
fi

echo "🔍 Checking for OpenGL and GLUT support..."

if [[ "$OS" == "Linux" ]]; then
  echo "🧱 Installing required packages on Linux..."
  sudo apt install -y freeglut3-dev libglew-dev libglfw3-dev
elif [[ "$OS" == "Darwin" ]]; then
  echo "🍎 macOS detected. Using system frameworks."
  if ! command -v brew >/dev/null; then
    echo "🔽 Installing Homebrew..."
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
  fi
  brew install freeglut glew glfw
fi

echo
echo "📦 All dependencies installed!"
echo "🚀 Compiling your animation project..."

# macOS-specific build command
if [[ "$OS" == "Darwin" ]]; then
  echo
  echo "🔧 Running:"
  echo "gcc main.c -o cg_anim -framework OpenGL -framework GLUT -DGL_SILENCE_DEPRECATION"
  gcc main.c -o cg_anim -framework OpenGL -framework GLUT -DGL_SILENCE_DEPRECATION
else
  echo
  echo "🔧 Running:"
  echo "gcc main.c -o cg_anim -lGL -lGLU -lglut"
  gcc main.c -o cg_anim -lGL -lGLU -lglut
fi

echo
echo "✅ Done! Run the animation with:"
echo "./cg_anim"