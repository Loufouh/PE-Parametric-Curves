// -------------------------------------------
// gMini : a minimal OpenGL/GLUT application
// for 3D graphics.
// Copyright (C) 2006-2008 Tamy Boubekeur
// All rights reserved.
// -------------------------------------------

// -------------------------------------------
// Disclaimer: this code is dirty in the
// meaning that there is no attention paid to
// proper class attribute access, memory
// management or optimisation of any kind. It
// is designed for quick-and-dirty testing
// purpose.
// -------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdio>
#include <cstdlib>

#include <algorithm>
#include <GL/glut.h>
#include <float.h>
#include "src/Vec3.h"
#include "src/Camera.h"


//Basis ( origin, i, j ,k )
struct Basis {
    inline Basis(Vec3 const &i_origin, Vec3 const &i_i, Vec3 const &i_j, Vec3 const &i_k) {
        origin = i_origin;
        i = i_i;
        j = i_j;
        k = i_k;
    }

    inline Basis() {
        origin = Vec3(0., 0., 0.);
        i = Vec3(1., 0., 0.);
        j = Vec3(0., 1., 0.);
        k = Vec3(0., 0., 1.);
    }

    Vec3 operator[](unsigned int ib) {
        if (ib == 0) return i;
        if (ib == 1) return j;
        return k;
    }

    Vec3 origin;
    Vec3 i;
    Vec3 j;
    Vec3 k;
};


// -------------------------------------------
// OpenGL/GLUT application code.
// -------------------------------------------

static GLint window;
static unsigned int SCREENWIDTH = 1600;
static unsigned int SCREENHEIGHT = 900;
static Camera camera;
static bool mouseRotatePressed = false;
static bool mouseMovePressed = false;
static bool mouseZoomPressed = false;
static int lastX = 0, lastY = 0, lastZoom = 0;
static bool fullScreen = false;

// ------------------------------------
// Application initialization
// ------------------------------------
void initLight() {
    GLfloat light_position1[4] = {22.0f, 16.0f, 50.0f, 0.0f};
    GLfloat direction1[3] = {-52.0f, -16.0f, -50.0f};
    GLfloat color1[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat ambient[4] = {0.3f, 0.3f, 0.3f, 0.5f};

    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, direction1);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, color1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, color1);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);
}

void init() {
    camera.resize(SCREENWIDTH, SCREENHEIGHT);
    initLight();
    glCullFace(GL_BACK);
    glDisable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
    glEnable(GL_COLOR_MATERIAL);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
}


// ------------------------------------
// Rendering.
// ------------------------------------

void drawVector(Vec3 const &i_from, Vec3 const &i_to) {

    glBegin(GL_LINES);
    glVertex3f(i_from[0], i_from[1], i_from[2]);
    glVertex3f(i_to[0], i_to[1], i_to[2]);
    glEnd();
}

void drawAxis(Vec3 const &i_origin, Vec3 const &i_direction) {
    glLineWidth(4); // for example...
    drawVector(i_origin, i_origin + i_direction);
}

void drawReferenceFrame(Vec3 const &origin, Vec3 const &i, Vec3 const &j, Vec3 const &k) {
    glDisable(GL_LIGHTING);
    glColor3f(0.8, 0.2, 0.2);
    drawAxis(origin, i);
    glColor3f(0.2, 0.8, 0.2);
    drawAxis(origin, j);
    glColor3f(0.2, 0.2, 0.8);
    drawAxis(origin, k);
    glEnable(GL_LIGHTING);

}

void drawReferenceFrame(Basis &i_basis) {
    drawReferenceFrame(i_basis.origin, i_basis.i, i_basis.j, i_basis.k);
}

typedef struct {
    float r;       // ∈ [0, 1]
    float g;       // ∈ [0, 1]
    float b;       // ∈ [0, 1]
} RGB;


RGB scalarToRGB(float scalar_value) //Scalar_value ∈ [0, 1]
{
    RGB rgb;
    float H = scalar_value * 360., S = 1., V = 0.85,
            P, Q, T,
            fract;

    (H == 360.) ? (H = 0.) : (H /= 60.);
    fract = H - floor(H);

    P = V * (1. - S);
    Q = V * (1. - S * fract);
    T = V * (1. - S * (1. - fract));

    if (0. <= H && H < 1.)
        rgb = (RGB) {.r = V, .g = T, .b = P};
    else if (1. <= H && H < 2.)
        rgb = (RGB) {.r = Q, .g = V, .b = P};
    else if (2. <= H && H < 3.)
        rgb = (RGB) {.r = P, .g = V, .b = T};
    else if (3. <= H && H < 4.)
        rgb = (RGB) {.r = P, .g = Q, .b = V};
    else if (4. <= H && H < 5.)
        rgb = (RGB) {.r = T, .g = P, .b = V};
    else if (5. <= H && H < 6.)
        rgb = (RGB) {.r = V, .g = P, .b = Q};
    else
        rgb = (RGB) {.r = 0., .g = 0., .b = 0.};

    return rgb;
}

void drawVectorField(std::vector<Vec3> const &i_positions, std::vector<Vec3> const &i_directions) {
    glLineWidth(1.);
    for (unsigned int pIt = 0; pIt < i_directions.size(); ++pIt) {
        Vec3 to = i_positions[pIt] + 0.02 * i_directions[pIt];
        drawVector(i_positions[pIt], to);
    }
}

//Draw fonction
void draw() {
    glColor3f(0.8, 1, 0.8);

}

void display() {
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera.apply();
    draw();
    glFlush();
    glutSwapBuffers();
}

void idle() {
    glutPostRedisplay();
}

// ------------------------------------
// User inputs
// ------------------------------------
//Keyboard event
void key(unsigned char keyPressed, int x, int y) {
    switch (keyPressed) {
        case 'f':
            if (fullScreen) {
                glutReshapeWindow(SCREENWIDTH, SCREENHEIGHT);
                fullScreen = false;
            } else {
                glutFullScreen();
                fullScreen = true;
            }
            break;

        default:
            break;
    }
    idle();
}

//Mouse events
void mouse(int button, int state, int x, int y) {
    if (state == GLUT_UP) {
        mouseMovePressed = false;
        mouseRotatePressed = false;
        mouseZoomPressed = false;
    } else {
        if (button == GLUT_LEFT_BUTTON) {
            camera.beginRotate(x, y);
            mouseMovePressed = false;
            mouseRotatePressed = true;
            mouseZoomPressed = false;
        } else if (button == GLUT_RIGHT_BUTTON) {
            lastX = x;
            lastY = y;
            mouseMovePressed = true;
            mouseRotatePressed = false;
            mouseZoomPressed = false;
        } else if (button == GLUT_MIDDLE_BUTTON) {
            if (mouseZoomPressed == false) {
                lastZoom = y;
                mouseMovePressed = false;
                mouseRotatePressed = false;
                mouseZoomPressed = true;
            }
        }
    }

    idle();
}

//Mouse motion, update camera
void motion(int x, int y) {
    if (mouseRotatePressed == true) {
        camera.rotate(x, y);
    } else if (mouseMovePressed == true) {
        camera.move((x - lastX) / static_cast<float>(SCREENWIDTH), (lastY - y) / static_cast<float>(SCREENHEIGHT), 0.0);
        lastX = x;
        lastY = y;
    } else if (mouseZoomPressed == true) {
        camera.zoom(float(y - lastZoom) / SCREENHEIGHT);
        lastZoom = y;
    }
}


void reshape(int w, int h) {
    camera.resize(w, h);
}

unsigned int get_max(const std::vector<unsigned int> values) {
    unsigned int max = 0;

    for (auto value: values) {
        if (value > max) {
            max = value;
        }
    }

    return max;
}

void normalize_valences(const std::vector<unsigned int> &valences,
                        std::vector<float> &normalized) {

    unsigned int max = get_max(valences);

    normalized.clear();
    normalized.reserve(valences.size());

    for (auto valence: valences) {
        normalized.push_back((float) valence / (float) max);
    }
}

// ------------------------------------
// Start of graphical application
// ------------------------------------
int main(int argc, char **argv) {
    if (argc > 2) {
        exit(EXIT_FAILURE);
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(SCREENWIDTH, SCREENHEIGHT);
    window = glutCreateWindow("TP HAI702I");

    init();
    glutIdleFunc(idle);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutReshapeFunc(reshape);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);
    key('?', 0, 0);

    glutMainLoop();
    return EXIT_SUCCESS;
}

