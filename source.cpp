#include <GL/glut.h>
#include <math.h>

void drawBranch(float length, float angle, float thickness) {
    glPushMatrix();
    glRotatef(angle, 0.0, 0.0, 1.0);
    glLineWidth(thickness);
    glColor3f(0.384, 0.224, 0.1); // Brown color
    glBegin(GL_LINES);
    glVertex2f(0.0, 0.0);
    glVertex2f(0.0, length);
    glEnd();
    glTranslatef(0.0, length, 0.0);
    glPopMatrix();
}

void drawLeaf() {
    glColor3f(0.9,0.3,0.1); // Yellow color
    glBegin(GL_TRIANGLES);
    glVertex2f(0.0, 0.0);
    glVertex2f(-5.0, -10.0);
    glVertex2f(5.0, -10.0);
    glEnd();
}

void drawTree(float posX, float posY, float scale, int level) {
    if (level <= 0)
        return;

    float branchLength = 80.0 * scale;
    float branchAngle = 45.0;
    float branchThickness = 10.0 * scale;

    drawBranch(branchLength, 0.0, branchThickness);

    if (level == 1) {
        glPushMatrix();
        glTranslatef(0.0, branchLength, 0.0);
        for (int i = -3; i <= 3; i++) {
            glPushMatrix();
            glTranslatef(i * 10.0, -10.0, 0.0);
            drawLeaf();
            glPopMatrix();
        }
        glPopMatrix();
    }

    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(0.0, branchLength, 0.0);
        glRotatef((i - 1) * branchAngle, 0.0, 0.0, 1.0);
        drawTree(0.0, 0.0, scale * 0.7, level - 1);
        glPopMatrix();
    }
}

void display() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-400, 400, -400, 400);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Draw the first tree
    glPushMatrix();
    glTranslatef(-200.0, -120.0, 0.0);
    drawTree(0.0, 0.0, 1.0, 4);
    glPopMatrix();

    // Draw the second tree
    glPushMatrix();
    glTranslatef(200.0, -120.0, 0.0);
    drawTree(0.0, 0.0, 1.0, 4);
    glPopMatrix();

    // Draw the third tree
    glPushMatrix();
    glTranslatef(0.0, -250.0, 0.0);
    drawTree(0.0, 0.0, 1.0, 4);
    glPopMatrix();

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Tree Data Structure");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
