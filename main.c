#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

GLuint bg1, bg2, rocketTex;
bool animationStarted = false;
bool rocketMode = false;
bool isPaused = false;

int frame = 0;
float ballX = 0.0f;
float ballY = -0.3f;
float ballVelocity = 0.025f;
float gravity = -0.001f;
float rocketY = -0.3f;
int bounceCount = 0;

float bgAspect = 1.0f;  // aspect ratio of background (set dynamically)

#define SAFE_BOTTOM -0.15f  // minimum height where ball hits
#define SAFE_TOP     0.3f   // rocket exit height

// Colors the ball will cycle through on each bounce
float bounceColors[][3] = {
    {1.0, 0.0, 0.0},  // Red
    {0.0, 1.0, 0.0},  // Green
    {0.0, 0.0, 1.0},  // Blue
    {1.0, 1.0, 0.0}   // Yellow
};
int currentColor = 0;

// Load texture from file and optionally set bg aspect ratio
GLuint loadTexture(const char* filename, bool setAspect) {
    int width, height, channels;
    unsigned char* data = stbi_load(filename, &width, &height, &channels, 4);
    if (!data) {
        fprintf(stderr, "Failed to load image: %s\n", filename);
        exit(1);
    }
    if (setAspect) {
        bgAspect = (float)width / (float)height;
    }
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    return tex;
}

// Fullscreen background rendering (either bg1 or bg2)
void drawTexturedQuad(GLuint texture) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1, 1, 1);  // reset color in case previous calls modified it

    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(-1, 1);
        glTexCoord2f(1, 0); glVertex2f(1, 1);
        glTexCoord2f(1, 1); glVertex2f(1, -1);
        glTexCoord2f(0, 1); glVertex2f(-1, -1);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

// Circle representing the ball — gets color from bounce count
void drawBall(float x, float y) {
    float* color = bounceColors[currentColor % 4];
    glColor3f(color[0], color[1], color[2]);

    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    float viewportAspect = (float)viewport[2] / (float)viewport[3];

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for (int angle = 0; angle <= 360; angle += 10) {
            float rad = angle * 3.14159f / 180.0f;
            glVertex2f(x + cos(rad) * 0.05f,
                       y + sin(rad) * 0.05f * viewportAspect);
        }
    glEnd();
}

// Renders rocket sprite at specified position
void drawRocket(float x, float y) {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);  // for alpha transparency
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindTexture(GL_TEXTURE_2D, rocketTex);
    glColor4f(1, 1, 1, 1);

    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(x - 0.05f, y + 0.1f);
        glTexCoord2f(1, 0); glVertex2f(x + 0.05f, y + 0.1f);
        glTexCoord2f(1, 1); glVertex2f(x + 0.05f, y - 0.1f);
        glTexCoord2f(0, 1); glVertex2f(x - 0.05f, y - 0.1f);
    glEnd();

    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Show the first bg until animation starts, then switch to second
    drawTexturedQuad(animationStarted ? bg2 : bg1);

    if (animationStarted) {
        if (!rocketMode) {
            drawBall(ballX, ballY);
        } else {
            drawRocket(ballX, rocketY);
        }
    }

    glutSwapBuffers();
}

// Timer callback for animation logic
void timer(int value) {
    if (animationStarted && !isPaused) {
        if (!rocketMode) {
            ballY += ballVelocity;
            ballVelocity += gravity;

            if (ballY < SAFE_BOTTOM) {
                // bounce logic
                ballY = SAFE_BOTTOM;
                ballVelocity *= -0.8f;  // reverse with energy loss
                bounceCount++;
                currentColor++;

                if (bounceCount >= 4) {
                    // switch to rocket mode after 4 bounces
                    rocketMode = true;
                    rocketY = ballY;
                }
            }
        } else {
            rocketY += 0.02f;
            if (rocketY > SAFE_TOP) {
                // reset everything when rocket exits
                rocketMode = false;
                ballY = SAFE_BOTTOM;
                ballVelocity = 0.025f;
                bounceCount = 0;
                currentColor = 0;
            }
        }
    }

    frame++;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);  // ~60 FPS
}

// Adjust viewport to maintain background aspect ratio
void reshape(int w, int h) {
    float winAspect = (float)w / (float)h;

    int viewW = w, viewH = h;
    if (winAspect > bgAspect) viewW = (int)(h * bgAspect);
    else viewH = (int)(w / bgAspect);

    int viewX = (w - viewW) / 2;
    int viewY = (h - viewH) / 2;

    glViewport(viewX, viewY, viewW, viewH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

// Spacebar: start or pause/resume
void key(unsigned char key, int x, int y) {
    if (key == ' ') {
        if (!animationStarted) {
            animationStarted = true;
            frame = 0;
        } else {
            isPaused = !isPaused;
        }
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1500, 1000);  // suitable for classroom projector
    glutCreateWindow("CG Animation - Ball to Rocket");

    glClearColor(0, 0, 0, 1);  // fallback black
    bg1 = loadTexture("cg_background.png", false);
    bg2 = loadTexture("cg_background2.png", true);
    rocketTex = loadTexture("rocket.png", false);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
