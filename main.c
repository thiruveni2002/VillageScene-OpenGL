#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int sunX = 1100;
int sunY = 650;
int sunRadius = 50;
bool moveSun = false;

void drawSun(int x, int y, int radius){
int num_segments = 100;
float angle_step = 2 * M_PI / num_segments;

glColor3f(1.0, 0.65, 0.0); // orange
glBegin(GL_TRIANGLE_FAN);
glVertex2i(x,y);
for(int i=0; i<=num_segments; ++i){
    float angle = i * angle_step;
    float dx = radius * cos(angle);
    float dy = radius * sin(angle);
    glVertex2i(x + dx, y + dy);
}
glEnd();
}

void drawscene(){

//lower sky
glBegin(GL_POLYGON);
glColor3f(1.0, 1.0, 0.0);  // sky color:yellow
glVertex2i(0,600);
glVertex2i(1200,600);
glColor3f(1.0, 1.0, 1.0);  // sky gradient:white
glVertex2i(1200,50);
glVertex2i(0,50);
glEnd();

//upper sky
glBegin(GL_POLYGON);
glColor3f(1.0, 1.0, 0.0);  //sky color:yellow
glVertex2i(0,600);
glVertex2i(1200, 600);
glVertex2i(1200, 750);
glVertex2i(0, 750);
glEnd();

//mountain
glBegin(GL_POLYGON);
glColor3f(0.0, 0.5, 0.0);  //bright green
glVertex2i(0,200);
glVertex2i(0,350);
glVertex2i(200,400);
glVertex2i(300,420);
glVertex2i(400,440);
glVertex2i(600,420);
glVertex2i(800,390);
glVertex2i(1200,350);
glVertex2i(1200,200);
glEnd();

//river
glBegin(GL_POLYGON);
glColor3f(0.0, 0.5, 1.0);   //blue
glVertex2i(0,200);
glVertex2i(1200,200);
glVertex2i(1200,0);
glVertex2i(0,0);
glEnd();
}

//Texture IDs
GLuint roofTextureID;
GLuint doorTextureID;

//function to load textures
GLuint loadTexture(const char* filename){
GLuint textureID;
int width, height, nrChannels;

//load image using stb_image
unsigned char *data = stbi_load(filename, &width, &height, &nrChannels, STBI_rgb_alpha);
if(data){
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, width,height,0,GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  //wrap mode
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  //wrap mode
    stbi_image_free(data);
}else{
printf("Failed to load texture: %s\n", stbi_failure_reason());
}
return textureID;
}

//draw house1
void drawHouse1(int x,int y){
glColor3f(0.5f, 0.2f, 0.7f);  //purple
glBegin(GL_POLYGON);
glVertex2i(x,y);
glVertex2i(x+110, y);
glVertex2i(x+110, y+100);
glVertex2i(x,y+100);
glEnd();

//draw the roof with texture mapping
glBindTexture(GL_TEXTURE_2D, roofTextureID);    // bind the roof texture
glBegin(GL_POLYGON);
glColor3f(0.65, 0.33,0.16);  //brown
glTexCoord2f(0.0f, 0.0f); glVertex2i(x-10, y+100);
glTexCoord2f(0.5f, 1.0f); glVertex2i(x+23, y+120);
glTexCoord2f(1.0f, 1.0f); glVertex2i(x+90, y+120);
glTexCoord2f(1.0f, 0.0f); glVertex2i(x+120, y+100);
glEnd();

//draw the door with texture mapping
glBindTexture(GL_TEXTURE_2D, doorTextureID);   // bind the door texture
glBegin(GL_POLYGON);
glColor3f(0.65, 0.33, 0.16);  //brown
glTexCoord2f(0.0f, 0.0f); glVertex2i(x+35, y);
glTexCoord2f(0.0f, 1.0f); glVertex2i(x+35, y+75);
glTexCoord2f(1.0f, 1.0f); glVertex2i(x+75, y+75);
glTexCoord2f(1.0f, 0.0f); glVertex2i(x+75, y);
glEnd();
}

//draw house2
void drawHouse2(float x, float y){
glColor3f(1.0f, 0.5f, 0.5f);  //pink
glBegin(GL_POLYGON);
glVertex2i(x,y);
glVertex2i(x+110,y);
glVertex2i(x+110,y+100);
glVertex2i(x,y+100);
glEnd();

//draw the roof with texture mapping
glBindTexture(GL_TEXTURE_2D, roofTextureID);   //bind the roof texture
glBegin(GL_POLYGON);
glColor3f(0.65,0.33,0.16);  //brown
glTexCoord2f(0.0f,0.0f);  glVertex2i(x-10,y+100);
glTexCoord2f(0.5f,1.0f);  glVertex2i(x+23,y+120);
glTexCoord2f(1.0f,1.0f);  glVertex2i(x+90,y+120);
glTexCoord2f(1.0f,0.0f);  glVertex2i(x+120,y+100);
glEnd();

//draw the door with texture mapping
glBindTexture(GL_TEXTURE_2D,doorTextureID);   //bind the door texture
glBegin(GL_POLYGON);
glColor3f(0.65,0.33,0.16);  //brown
glTexCoord2f(0.0f,0.0f);  glVertex2i(x+35,y);
glTexCoord2f(0.0f,1.0f);  glVertex2i(x+35,y+75);
glTexCoord2f(1.0f,1.0f);  glVertex2i(x+75,y+75);
glTexCoord2f(1.0f,1.0f);  glVertex2i(x+75,y);
glEnd();
}

void drawFish1(int x,int y){
//fish body
glBegin(GL_TRIANGLES);
glColor3f(1.0,1.0,0.0); //yellow
glVertex2i(x+25,y+25);
glVertex2i(x+50,y+37);
glVertex2i(x+50,y+13);

glVertex2i(x+50,y+37);
glVertex2i(x+75,y+25);
glVertex2i(x+50,y+13);
glEnd();

//fish tail
glBegin(GL_TRIANGLES);
glColor3f(1.0,0.0,0.0);  //red
glVertex2i(x+25,y+25);   //center
glVertex2i(x+12,y+32);   //top
glVertex2i(x+12,y+18);  //bottom
glEnd();

//fish feathers
glBegin(GL_TRIANGLES);
//top feather
glColor3f(1.0,0.0,0.0);  //red
glVertex2i(x+50,y+37); //top feather,body point
glVertex2i(x+30,y+45); //top feather,top point
glVertex2i(x+41,y+34); //top feather,bottom point
//bottom feather
glVertex2i(x+50,y+13);   //bottom body point
glVertex2i(x+30,y+5);   //top
glVertex2i(x+41,y+17);  //bottom
glEnd();

//eye
glPointSize(2);
glBegin(GL_POINTS);
glColor3f(0,0,0);
glVertex2i(58+x, 27+y);
glEnd();
}

void drawFish2(int x,int y){
//fish body
glBegin(GL_TRIANGLES);
glColor3f(1.0,1.0,0.0); //yellow
glVertex2i(x+25,y+25);
glVertex2i(x+50,y+37);
glVertex2i(x+50,y+13);

glVertex2i(x+50,y+37);
glVertex2i(x+75,y+25);
glVertex2i(x+50,y+13);
glEnd();

//fish tail
glBegin(GL_TRIANGLES);
glColor3f(1.0,0.0,0.0);  //red
glVertex2i(x+74,y+25);   //center
glVertex2i(x+91,y+32);   //top
glVertex2i(x+91,y+18);  //bottom
glEnd();

//fish feathers
glBegin(GL_TRIANGLES);
//top feather
glColor3f(1.0,0.0,0.0);  //red
glVertex2i(x+50,y+37); //top feather,body point
glVertex2i(x+70,y+45); //top feather,top point
glVertex2i(x+61,y+34); //top feather,bottom point
//bottom feather
glVertex2i(x+50,y+13);   //bottom body point
glVertex2i(x+70,y+5);   //top
glVertex2i(x+61,y+17);  //bottom
glEnd();

//eye
glPointSize(2);
glBegin(GL_POINTS);
glColor3f(0,0,0);
glVertex2i(40+x, 25+y);
glEnd();
}

//initial scaling factors
float vaseScaleFactor =1.0f;
float fishScaleFactor =1.0f;
float flowerScaleFactor =1.0f;

// Function to draw left flowers
void drawFlower(int cx, int cy, int r, float rColor, float gColor, float bColor, float scale) {
    const int numVertices = 100;
    glBegin(GL_POLYGON);
    glColor3f(rColor, gColor, bColor); // Set flower color
    for (int i = 0; i < numVertices; i++) {
        float angle = i * 2.0f * M_PI / numVertices;
        float x = cx + cos(angle) * r * scale; // Apply scaling factor
        float y = cy + sin(angle) * r * scale; // Apply scaling factor
        glVertex2f(x, y);
    }
    glEnd();
}

void drawLeftVasesWithFlowers(float x, float y) {
    // Draw left side vase with scaling factor
    glColor3f(0.65f, 0.16f, 0.16f); // Vase color
    glBegin(GL_POLYGON);
        glVertex2f(x + 80 * vaseScaleFactor, y + 10 * vaseScaleFactor);
        glVertex2f(x + 110 * vaseScaleFactor, y + 10 * vaseScaleFactor);
        glVertex2f(x + 120 * vaseScaleFactor, y + 50 * vaseScaleFactor);
        glVertex2f(x + 70 * vaseScaleFactor, y + 50 * vaseScaleFactor);
    glEnd();

    // Draw stem with scaling factor
    glColor3f(0.6f, 0.3f, 0.1f); // Stem color
    glBegin(GL_POLYGON);
        glVertex2f(x + 95 * vaseScaleFactor, y + 50 * vaseScaleFactor);
        glVertex2f(x + 97 * vaseScaleFactor, y + 50 * vaseScaleFactor);
        glVertex2f(x + 97 * vaseScaleFactor, y + 90 * vaseScaleFactor);
        glVertex2f(x + 95 * vaseScaleFactor, y + 90 * vaseScaleFactor);
    glEnd();

    // Left branch with scaling factor
    glColor3f(0.6f, 0.3f, 0.1f); // Branch color
    glBegin(GL_POLYGON);
        glVertex2f(x + 95 * vaseScaleFactor, y + 62 * vaseScaleFactor);
        glVertex2f(x + 69 * vaseScaleFactor, y + 69 * vaseScaleFactor);
        glVertex2f(x + 69 * vaseScaleFactor, y + 71 * vaseScaleFactor);
        glVertex2f(x + 95 * vaseScaleFactor, y + 64 * vaseScaleFactor);
    glEnd();

    // Right branch with scaling factor
    glColor3f(0.6f, 0.3f, 0.1f); // Branch color
    glBegin(GL_POLYGON);
        glVertex2f(x + 97 * vaseScaleFactor, y + 72 * vaseScaleFactor);
        glVertex2f(x + 123 * vaseScaleFactor, y + 79 * vaseScaleFactor);
        glVertex2f(x + 123 * vaseScaleFactor, y + 81 * vaseScaleFactor);
        glVertex2f(x + 97 * vaseScaleFactor, y + 74 * vaseScaleFactor);
    glEnd();

    // Draw flowers with scaling factor applied to both the vase and flower
    drawFlower(x + 95 * vaseScaleFactor, y + 90 * vaseScaleFactor, 8, 1.0, 0.71, 0.76, flowerScaleFactor); // light pink
    drawFlower(x + 69 * vaseScaleFactor, y + 70 * vaseScaleFactor, 8, 1.0, 0.0, 0.0, flowerScaleFactor);   // red
    drawFlower(x + 130 * vaseScaleFactor, y + 83 * vaseScaleFactor, 8, 0.5, 0.0, 0.5, flowerScaleFactor); // purple
}

void drawfish3and4(int x, int y) {

    glBegin(GL_TRIANGLES);
        // First triangle for the body
        glColor3f(0.0, 0.0, 0.5); // Dark Blue
        glVertex2i(x + 25 * fishScaleFactor, y + 25 * fishScaleFactor); // Right point
        glVertex2i(x + 50 * fishScaleFactor, y + 37 * fishScaleFactor); // Top point
        glVertex2i(x + 50 * fishScaleFactor, y + 13 * fishScaleFactor); // Bottom point

        // Second triangle for the body
        glVertex2i(x + 50 * fishScaleFactor, y + 37 * fishScaleFactor); // Top point
        glVertex2i(x + 75 * fishScaleFactor, y + 25 * fishScaleFactor); // Left point
        glVertex2i(x + 50 * fishScaleFactor, y + 13 * fishScaleFactor); // Bottom point
    glEnd();

    // Fish Tail - single triangle with scaling factor
    glBegin(GL_TRIANGLES);
        glColor3f(1.0, 0.75, 0.8); // Pink
        glVertex2i(x + 74 * fishScaleFactor, y + 25 * fishScaleFactor); // Center of the body
        glVertex2i(x + 91 * fishScaleFactor, y + 32 * fishScaleFactor); // Top tail point
        glVertex2i(x + 91 * fishScaleFactor, y + 18 * fishScaleFactor); // Bottom tail point
    glEnd();

    // Fish Fins (Feathers) - two triangles with scaling factor
    glBegin(GL_TRIANGLES);
        // Top fin
        glColor3f(1.0, 0.75, 0.8); // Pink
        glVertex2i(x + 50 * fishScaleFactor, y + 37 * fishScaleFactor); // Top point of the body
        glVertex2i(x + 57 * fishScaleFactor, y + 45 * fishScaleFactor); // Top fin point
        glVertex2i(x + 43 * fishScaleFactor, y + 45 * fishScaleFactor); // Bottom fin point

        // Bottom fin
        glVertex2i(x + 50 * fishScaleFactor, y + 13 * fishScaleFactor); // Bottom point of the body
        glVertex2i(x + 57 * fishScaleFactor, y + 5 * fishScaleFactor); // Top fin point
        glVertex2i(x + 43 * fishScaleFactor, y + 5 * fishScaleFactor); // Bottom fin point
    glEnd();

}
void updateScalingFactors(){
vaseScaleFactor *= 1.5f;  //scale up
fishScaleFactor *= 1.5f;
flowerScaleFactor *= 1.5f;
}

bool scaleDownPlants = false;
float scaleDownFactor = 0.5f; //factor for scaling down when pressing 'S'

void drawChristmasTree(int x, int y){

float scaleFactor = scaleDownPlants ? 0.5f : 1.0f; //adjust scale factor if scale down
glPushMatrix(); // save the current transformation matrix
glTranslatef(x+10,y-50,0);  //translate to the center of the vase
glScalef(scaleFactor, scaleFactor, 1.0f);  //apply scale
glTranslatef(-x - 10, -y +50, 0);   //translate back
//draw the lines
glColor3f(0.6f,0.3f,0.1f);
glBegin(GL_LINES);
glVertex2i(x+25,y); //top of the left
glVertex2i(x+25,y+30); //top of the right
glVertex2i(x-25,y); //top of the left
glVertex2i(x-25,y+30); //top of the right
glEnd();

//draw the tree
glColor3f(0.0f,0.8f,0.0f); //green
glBegin(GL_TRIANGLES);

//bottom triangle
glVertex2i(x-50,y+10);
glVertex2i(x+50,y+10);
glVertex2i(x,y+80);

//middle tree
glVertex2i(x-40,y+45);
glVertex2i(x+40,y+45);
glVertex2i(x,y+105);

//top triangle
glVertex2i(x-30,y+80);
glVertex2i(x+30,y+80);
glVertex2i(x,y+140);
glEnd();

//draw trunk
glColor3f(0.6f,0.3f,0.1f); //trunk color brown
glBegin(GL_POLYGON);
glVertex2i(x-10,y+10);
glVertex2i(x+10,y+10);
glVertex2i(x+10,y-53);
glVertex2i(x-10,y-53);
glEnd();

glColor3ub(255,0,0);  //red balls in the tree
const int numBalls=2;
for(int i=0;i<numBalls;++i){
    int angle = i*360/numBalls;
    int radius = (i%3+2) *10; //increase the radius for higher layers
    int ox= x+5 + radius * cos(angle * M_PI /180.0);
    int oy= y + radius * sin(angle * M_PI /180.0);
    glBegin(GL_POLYGON);
    for(int j=0;j<360;j+=30){
        float rad = j*M_PI /180.0;
        glVertex2i(ox + 5 * cos(rad), oy + 5 *sin(rad));
    }
    glEnd();
    }
    glPopMatrix();
}

//function to draw flowers
void drawSmallFlower(int cx, int cy, int r, float rColor, float gColor, float bColor){
const int numVertices =100;
glBegin(GL_POLYGON);
glColor3f(rColor,gColor,bColor);
for(int i=0;i<numVertices; i++){
    float angle = i * 2.0f * M_PI /numVertices;
    float x = cx + cos(angle) * r;
    float y = cy + sin(angle) * r;
    glVertex2i(x,y);
}
glEnd();
}

void drawSmallVaseWithFlowers(int x,int y){
//draw box vase
float scaleFactor = scaleDownPlants ? 0.5f : 1.0f; //adjust scale factor if scale down
glPushMatrix(); // save the current transformation matrix
glTranslatef(x+90,y+30,0);  //translate to the center of the vase
glScalef(scaleFactor, scaleFactor, 1.0f);  //apply scale
glTranslatef(-x - 90, -y -30, 0);   //translate back

glColor3f(0.65f, 0.16f, 0.16f);
glBegin(GL_POLYGON);
glVertex2i(x+70, y+10);
glVertex2i(x+110, y+10);
glVertex2i(x+110, y+50);
glVertex2i(x+70, y+50);
glEnd();

//stem
glColor3f(0.65f, 0.3f, 0.1f);
glBegin(GL_POLYGON);
glVertex2i(x+95, y+50);
glVertex2i(x+97, y+50);
glVertex2i(x+97, y+90);
glVertex2i(x+95, y+90);
glEnd();
//left branch
glColor3f(0.6f, 0.3f, 0.1f);
glBegin(GL_POLYGON);
glVertex2i(x+95, y+62);
glVertex2i(x+69, y+69);
glVertex2i(x+69, y+71);
glVertex2i(x+95, y+64);
glEnd();

//right branch
glColor3f(0.6f, 0.3f, 0.1f);
glBegin(GL_POLYGON);
glVertex2i(x+97, y+72);
glVertex2i(x+123, y+79);
glVertex2i(x+123, y+81);
glVertex2i(x+97, y+74);
glEnd();

//draw flowers
drawSmallFlower(925,290,8,1.0,0.71,0.76);  // light pink
drawSmallFlower(899,270,8,1.0,0.0,0.0);  // red
drawSmallFlower(960,283,8,0.5,0.0,0.5);  // light purple

glPopMatrix();  //restore the original transformation matrix
}


float bigVaseScaleFactor = 1.0f;
void drawBigFlower(int cx, int cy, int r, float rColor, float gColor, float bColor) {

glPushMatrix();
glTranslatef(cx, cy, 0);
glScalef(bigVaseScaleFactor, bigVaseScaleFactor, 1.0f);
glTranslatef(-cx, -cy, 0);

    glBegin(GL_POLYGON);
    glColor3f(rColor, gColor, bColor);
    for (int i = 0; i < 100; i++) {
        float angle = i * 2.0f * M_PI / 100;
        float x = cx + cos(angle) * r;
        float y = cy + sin(angle) * r;
        glVertex2i(x, y);
    }
    glEnd();

    glPopMatrix();
}

void drawBigVaseWithFlowers(int x, int y) {

    float scaleFactor = scaleDownPlants ? 0.5f : 1.0f;

    int centerX = x + 155;
    int centerY = y + 35;

    glPushMatrix();
    glTranslatef(centerX, centerY, 0);
    glScalef(bigVaseScaleFactor, bigVaseScaleFactor, 1.0f);
    glScalef(scaleFactor, scaleFactor, 1.0f);
    glTranslatef(-centerX, -centerY, 0);

    // Draw big box vase
    glColor3f(0.65f, 0.16f, 0.16f); // Vase color
    glBegin(GL_POLYGON);
        glVertex2i(x + 130, y + 10);
        glVertex2i(x + 180, y + 10);
        glVertex2i(x + 180, y + 60);
        glVertex2i(x + 130, y + 60);
    glEnd();

    // Draw stem
    glColor3f(0.6f, 0.3f, 0.1f); // Stem color
    glBegin(GL_POLYGON);
        glVertex2i(x + 150, y + 60);
        glVertex2i(x + 152, y + 60);
        glVertex2i(x + 152, y + 110);
        glVertex2i(x + 150, y + 110);
    glEnd();

    // Draw left branch
    glColor3f(0.6f, 0.3f, 0.1f); // Branch color
    glBegin(GL_POLYGON);
        glVertex2i(x + 150, y + 72);
        glVertex2i(x + 124, y + 79);
        glVertex2i(x + 124, y + 81);
        glVertex2i(x + 150, y + 74);
    glEnd();

    // Draw right branch
    glColor3f(0.6f, 0.3f, 0.1f); // Branch color
    glBegin(GL_POLYGON);
        glVertex2i(x + 152, y + 92);
        glVertex2i(x + 178, y + 99);
        glVertex2i(x + 178, y + 101);
        glVertex2i(x + 152, y + 94);
    glEnd();

    // Draw flowers
    drawBigFlower(x + 155, y + 110, 10, 1.0, 0.71, 0.76); // Light pink
    drawBigFlower(x + 129, y + 79, 10, 1.0, 0.0, 0.0);    // Red
    drawBigFlower(x + 179, y + 99, 10, 0.5, 0.0, 0.5);    // Light purple

    glPopMatrix();
}

bool vaseScaledDown = false;
void update(int value) {
    if (moveSun) {
        sunX -= 2; // Move the sun to the left

        if (!vaseScaledDown) {
            if (bigVaseScaleFactor > 0.2f) { // Scale down the big vase
                bigVaseScaleFactor -= 0.01f;
            } else {
                bigVaseScaleFactor = 1.0f; // Reset to original size
                vaseScaledDown = true; // Set flag to true
            }
        }

        if (sunX < 0) { // Reset sun position if it moves off-screen
            sunX = 600;
        }

        glutPostRedisplay(); // Request to redraw the scene
        glutTimerFunc(30, update, 0); // Call update again after 30 ms
    }
}

void drawChristmasTree2(int x, int y) {

    glColor3f(0.0f, 0.8f, 0.0f); // Tree color
    glBegin(GL_TRIANGLES);
        // Bottom triangle
        glVertex2i(x - 50, y+10);
        glVertex2i(x + 50, y+10);
        glVertex2i(x, y + 80);

        // Middle triangle
        glVertex2i(x - 40, y + 45);
        glVertex2i(x + 40, y + 45);
        glVertex2i(x, y + 105);

        // Top triangle
        glVertex2i(x - 30, y + 80);
        glVertex2i(x + 30, y + 80);
        glVertex2i(x, y + 140);
    glEnd();

    // Draw the tree trunk
    glColor3f(0.6f, 0.3f, 0.1f); // Trunk color
    glBegin(GL_POLYGON);
        glVertex2i(x - 10, y+10);
        glVertex2i(x + 10, y+10);
        glVertex2i(x + 10, y - 50);
        glVertex2i(x - 10, y - 50);
    glEnd();

}


int boatX = 350;
int boatY = 150;
float boatSpeed = 1.0f;

float batBaseX = 20.0f;
float batTopX = 105.0f;
float batSpeed = 0.5f;
float batMinX = 20.0f;
float batMaxX = 100.0f;
bool batMovingForward = true;

void drawBoat(int x, int y) {
    // Draw the base of the boat
    glColor3f(0.65, 0.33, 0.16); // Brown
    glBegin(GL_POLYGON);
        glVertex2i(x+20, y + 10);
        glVertex2i(x + 300, y + 10);
        glVertex2i(x + 250, y-40);
        glVertex2i(x + 65, y-40);
    glEnd();

    // Draw the person
    //body
        glColor3f(1.0f, 1.0f, 1.0f); // White color
    glBegin(GL_POLYGON);
        glVertex2i(x + 70, y + 10);// Bottom left
        glVertex2i(x + 135, y + 10);// Bottom right
        glVertex2i(x + 105, y + 50);
        glVertex2i(x + 90, y + 50);
        glVertex2i(x + 70, y + 100);// Top right
        glVertex2i(x + 110, y + 100);// Top left

    glEnd();
//face
    glColor3f(0.8f, 0.5f, 0.4f); // skin color
    glBegin(GL_POLYGON);
        glVertex2f(x + 75, y + 100); // Bottom left of the face
        glVertex2f(x + 100, y + 100); // Bottom right of the face
        glVertex2f(x + 100, y + 120);
        glVertex2f(x + 105, y + 120);
        glVertex2f(x + 100, y + 150);
        glVertex2f(x + 75, y + 150); // Top right of the face
        glVertex2f(x + 75, y + 100);  // Top left of the face
    glEnd();

    // Draw the hair
    glColor3f(0.0f, 0.0f, 0.0f); // Black color
    glBegin(GL_POLYGON);
        glVertex2f(x + 75, y + 150);
        glVertex2f(x + 100, y + 150);
        glVertex2f(x + 105, y + 166);
        glVertex2f(x + 75, y + 163);

    glEnd();
// Draw the bat
    glColor3f(0.0f, 0.0f, 0.0f); // Black color
    glBegin(GL_TRIANGLES);
        glVertex2f(x + batBaseX, y - 50);
        glVertex2f(x + 45, y - 50);
        glVertex2f(x + batTopX, y + 50);
    glEnd();
}

// Update boat position
void updateBoatPosition(int value) {
    boatX += boatSpeed; // Move the boat to the right

    if (boatX > 1200) { // Reset position if it moves off-screen
        boatX = 0;
    }

    glutPostRedisplay(); // Request to redraw the scene
    glutTimerFunc(15, updateBoatPosition, 0);
}

// Update bat position
void updateBatPosition(int value) {
    if (batMovingForward) {
        batBaseX += batSpeed; // Move the bat bottom forward
        if (batBaseX > batMaxX) {
            batBaseX = batMaxX; // Ensure the bat does not exceed max position
            batMovingForward = false; // Reverse direction
        }
    } else {
        batBaseX -= batSpeed; // Move the bat bottom backward
        if (batBaseX < batMinX) {
            batBaseX = batMinX; // Ensure the bat does not go below min position
            batMovingForward = true; // Reverse direction
        }
    }

    glutPostRedisplay(); // Request to redraw the scene
    glutTimerFunc(15, updateBatPosition, 0); // Call updateBatPosition again after 30 ms
}

int horseX = 480;
int horseY = 70;
float tailAngle = 0.0f; // Initial angle for the tail rotation
bool movingLeft = true;
bool rotatingTail = false;

void drawHorse() {
    int x = horseX;
    int y = horseY;

    // Flip the horse if it's moving to the right
    if (!movingLeft) {
        glPushMatrix();
        glTranslatef(180 + x, 0, 0); // Translate to the horse's center
        glScalef(-1, 1, 1);          // Flip horizontally
        glTranslatef(-180 - x, 0, 0);
    }
	// Front leg
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex2i(90 + x, 200 + y);
    glVertex2i(100 + x, 200 + y);
    glVertex2i(100 + x, 250 + y);
    glVertex2i(90 + x, 250 + y);
    glEnd();

    // Back leg
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex2i(180 + x, 200 + y);
    glVertex2i(170 + x, 200 + y);
    glVertex2i(170 + x, 250 + y);
    glVertex2i(180 + x, 250 + y);
    glEnd();

    // Body
    glBegin(GL_POLYGON);
    glColor3f(0.9, 0.3, 0.1);
    glVertex2i(90 + x, 240 + y);
    glVertex2i(180 + x, 240 + y);
    glVertex2i(180 + x, 290 + y);
    glVertex2i(90 + x, 290 + y);
    glEnd();

    // Neck and face
    glBegin(GL_POLYGON);
    glColor3f(0.9, 0.3, 0.1);
    glVertex2i(110 + x, 290 + y);
    glVertex2i(80 + x, 380 + y);
    glVertex2i(50 + x, 320 + y);
    glVertex2i(50 + x, 340 + y);
    glVertex2i(70 + x, 340 + y);
    glVertex2i(90 + x, 290 + y);
    glEnd();

    // Mane(white part)
    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex2i(140 + x, 290 + y);
    glVertex2i(80 + x, 380 + y);
    glVertex2i(110 + x, 290 + y);
    glVertex2i(140 + x, 290 + y);
    glEnd();

    // mouth black part
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex2i(60 + x, 315 + y);
    glVertex2i(60 + x, 341 + y);
    glVertex2i(62 + x, 342 + y);
    glVertex2i(62 + x, 314 + y);
    glEnd();

    // Tail with rotation
    glPushMatrix();
    glTranslatef(180 + x, 290 + y, 0); // Translate to the tail's pivot point
    glRotatef(tailAngle, 0, 0, 1);     // Rotate around the pivot point
    glTranslatef(-180 - x, -290 - y, 0);

    glBegin(GL_POLYGON);
    glColor3f(1, 1, 1);
    glVertex2i(180 + x, 290 + y);
    glVertex2i(190 + x, 210 + y);
    glVertex2i(200 + x, 290 + y);
    glEnd();

    glPopMatrix();

    // Eye
    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3f(0, 0, 0);
    glVertex2i(75 + x, 350 + y);
    glEnd();

    // If the horse was flipped, undo the flipping transformation
    if (!movingLeft) {
        glPopMatrix();
    }
}

void updateHorsePosition(int value) {
    if (movingLeft) {
        horseX -= 1; // Move the horse to the left
        // Reappear on the right edge if the horse goes off the left edge
        if (horseX < -180) {
            horseX = 1200;
        }
    } else {
        horseX += 1; // Move the horse to the right
        // Reappear on the left edge if the horse goes off the right edge
        if (horseX > 1200) {
            horseX = -180;
        }
    }
    glutPostRedisplay(); //redrew scene

    glutTimerFunc(15, updateHorsePosition, 0);
}
void updateTailRotation(int value) {
    tailAngle -= 10.0f; // Increment the tail's rotation angle  (clockwise  +)(anticlockwise -)
    if (tailAngle >= 360.0f) {
        tailAngle -= 360.0f; // Keep the angle within 0-360 degrees
    }

    glutPostRedisplay();
    // Continue rotating
    if (rotatingTail) {
        glutTimerFunc(30, updateTailRotation, 0);
    }
}


void handleKeypress(unsigned char key, int x, int y){
static bool boatMoving = false;
static bool batMoving = false;

if(key == 'b' || key == 'B'){
    if(!boatMoving){
        glutTimerFunc(15, updateBoatPosition, 0);  //boat movement start
        boatMoving = true;
        }
}
if(key == 'w' || key == 'W'){
    if(!batMoving){
        glutTimerFunc(15, updateBatPosition, 0);  //bat movement start
        batMoving = true;
        }
    }
if(key ==' '){
    moveSun = !moveSun;
    if(moveSun){
        glutTimerFunc(15,update, 0);  //start the update timer
    }
}
if(key == 's' || key == 'S'){
    scaleDownPlants = !scaleDownPlants;   //toggle scaling down
    glutPostRedisplay();   //request a redrew to apply changes
}
if(key == 'u' || key == 'U'){
    updateScalingFactors();
    glutPostRedisplay();  //redrew the scene
}
if(key == 'f' || key == 'F'){
    movingLeft = true;   //horse moving to left
    rotatingTail = false;
    glutTimerFunc(15, updateHorsePosition, 0);
} else if(key == 'r' || key == 'R'){
    rotatingTail = true;  //tail rotate
    glutTimerFunc(30, updateTailRotation, 0);
} else if(key == 'q' || key == 'Q'){
    movingLeft = false;  //change direction to right
    rotatingTail = false;
    tailAngle = 0.0f;  //optionally reset tail rotation
//update horse position to move right
    horseX += 20;  //adjust to position the horse for the new direction
    glutTimerFunc(15, updateHorsePosition, 0);
}
}

void display(){
glClear(GL_COLOR_BUFFER_BIT);
drawscene();
drawSun(sunX, sunY, sunRadius);
drawFish1(80,80);
drawFish2(200,120);
drawfish3and4(800,120);
drawfish3and4(1000,80);
drawChristmasTree(850,436);
drawChristmasTree(620,445);
drawChristmasTree2(50,345);

//enable texture mapping
glEnable(GL_TEXTURE_2D);
//draw house with textures
drawHouse1(400,420);
drawHouse2(700,390);

glDisable(GL_TEXTURE_2D);

drawHorse();
drawLeftVasesWithFlowers(100,200);
drawLeftVasesWithFlowers(200,250);
drawSmallVaseWithFlowers(830,200);
drawBigVaseWithFlowers(900,200);
drawBoat(boatX,boatY);
glutSwapBuffers();
}

//initialization function
void init(){
glClearColor(1.0f,1.0f,1.0f,1.0f);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0,1200,0,750);
glMatrixMode(GL_MODELVIEW);

//load texture
roofTextureID = loadTexture("roof.jpg");
doorTextureID = loadTexture("door.jpg");
}

int main(int argc, char** argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1200,750);
    glutCreateWindow("drawscene");
    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(handleKeypress);
    glutMainLoop();
    return 0;
}







