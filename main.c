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

int frame = 0;
float ballX = 0.0f;
float ballY = -0.3f;
float ballVelocity = 0.025f;
float gravity = -0.001f;
float rocketY = -0.3f;
int bounceCount = 0;

float bgAspect = 1.0f;  // Dynamically set based on image

// Safe vertical range (whiteboard safe area)
#define SAFE_BOTTOM -0.15f
#define SAFE_TOP     0.3f

// Ball colors on each bounce
float bounceColors[][3] = {
    {1.0, 0.0, 0.0},  // Red
    {0.0, 1.0, 0.0},  // Green
    {0.0, 0.0, 1.0},  // Blue
    {1.0, 1.0, 0.0}   // Yellow
};
int currentColor = 0;

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
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
    return tex;
}

void drawTexturedQuad(GLuint texture) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex2f(-1, 1);
        glTexCoord2f(1, 0); glVertex2f(1, 1);
        glTexCoord2f(1, 1); glVertex2f(1, -1);
        glTexCoord2f(0, 1); glVertex2f(-1, -1);
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

void drawBall(float x, float y) {
    float* color = bounceColors[currentColor % 4];
    glColor3f(color[0], color[1], color[2]);

    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for (int angle = 0; angle <= 360; angle += 10) {
            float rad = angle * 3.14159f / 180.0f;
            glVertex2f(x + cos(rad) * 0.05f, y + sin(rad) * 0.05f);
        }
    glEnd();
}

void drawRocket(float x, float y) {
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
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

void timer(int value) {
    if (animationStarted) {
        if (!rocketMode) {
            ballY += ballVelocity;
            ballVelocity += gravity;

            if (ballY < SAFE_BOTTOM) {
                ballY = SAFE_BOTTOM;
                ballVelocity *= -0.8f;
                bounceCount++;
                currentColor++;

                if (bounceCount >= 4) {
                    rocketMode = true;
                    rocketY = ballY;
                }
            }
        } else {
            rocketY += 0.02f;
            if (rocketY > SAFE_TOP) {
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
    glutTimerFunc(16, timer, 0);
}

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

void key(unsigned char key, int x, int y) {
    if (key == ' ' && !animationStarted) {
        animationStarted = true;
        frame = 0;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1500 , 1000);
    glutCreateWindow("CG Animation - Ball to Rocket");

    glClearColor(0, 0, 0, 1);
    bg1 = loadTexture("cg_background.png", false);
    bg2 = loadTexture("cg_background2.png", true); // sets bgAspect
    rocketTex = loadTexture("rocket.png", false);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(key);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}
