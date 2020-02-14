#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    GLFWwindow *window;
    int screenWidth;
    int screenHeight;
    char *title;
    unsigned int screenTexID;
    unsigned int screenTexWidth;
    unsigned int screenTexHeight;
    //unsigned char (*screenTex)[];
    //unsigned char (*screenTex)[100][100][4];
    //unsigned char (*screenTex)[][][];
    unsigned char(*screenTex);
} Engine;

void window_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
    //printf("window resized\n");
}

Engine *newEngine()
{
    //Engine *self = malloc(sizeof(*self));
    Engine *self = (Engine *)calloc(1, sizeof(*self));
    self->screenWidth = 800;
    self->screenHeight = 600;
    self->screenTexWidth = 800;
    self->screenTexHeight = 600;

    self->title = "testing";
    //engine_init(self);
    return self;
}

void engine_put_pixel(Engine *self, int x, int y, unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    //(*(unsigned char(*)[self->screenTexWidth][self->screenTexHeight][4])self->screenTex)[x][y][0] = r;
    //(*(unsigned char(*)[self->screenTexWidth][self->screenTexHeight][4])self->screenTex)[x][y][1] = g;
    //(*(unsigned char(*)[self->screenTexWidth][self->screenTexHeight][4])self->screenTex)[x][y][2] = b;
    //(*(unsigned char(*)[self->screenTexWidth][self->screenTexHeight][4])self->screenTex)[x][y][3] = a;

    //(*(unsigned char(*)[self->screenTexHeight][self->screenTexWidth][4])self->screenTex)[x][y][0] = r;
    //(*(unsigned char(*)[self->screenTexHeight][self->screenTexWidth][4])self->screenTex)[x][y][1] = g;
    //(*(unsigned char(*)[self->screenTexHeight][self->screenTexWidth][4])self->screenTex)[x][y][2] = b;
    //(*(unsigned char(*)[self->screenTexHeight][self->screenTexWidth][4])self->screenTex)[x][y][3] = a;

    (*(unsigned char(*)[self->screenTexHeight][self->screenTexWidth][4])self->screenTex)[y][x][0] = r;
    (*(unsigned char(*)[self->screenTexHeight][self->screenTexWidth][4])self->screenTex)[y][x][1] = g;
    (*(unsigned char(*)[self->screenTexHeight][self->screenTexWidth][4])self->screenTex)[y][x][2] = b;
    (*(unsigned char(*)[self->screenTexHeight][self->screenTexWidth][4])self->screenTex)[y][x][3] = a;
}

int engine_init(Engine *self)
{
    self->screenTex = calloc(self->screenTexWidth * self->screenTexHeight * 4, sizeof(char));

    //unsigned char (*metapixel)[self->screenTexWidth][self->screenTexHeight][4] = (unsigned char (*)[self->screenTexWidth][self->screenTexHeight][4]) self->screenTex;

    //unsigned char (*cake)[self->screenTexWidth][self->screenTexHeight][4] = self->screenTex;
    //unsigned char (*cake)[100][100][4] = self->screenTex;

    //cake = (unsigned char (*)[self->screenTexWidth][self->screenTexHeight][4])&self->screenTex;

    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

    self->window = glfwCreateWindow(self->screenWidth, self->screenHeight, self->title, NULL, NULL);
    if (!self->window)
    {
        glfwTerminate();
        return -1;
    }
    
    for (int x = 0; x < self->screenTexWidth; x++)
    {
        for (int y = 0; y < self->screenTexHeight; y++)
        {
            //unsigned char r = rand() % 255;
            for (int z = 0; z < 4; z++)
            {
                unsigned char r = x % 256;
                unsigned char g = y % 256;
                unsigned char b = (x+y) % 256;
                engine_put_pixel(self, x, y, r, g, b, 255);

                //engine_put_pixel(self, x, y, r, r, r, 255);
                //if (x == y)
                //{
                //    engine_put_pixel(self, x, y, 255, 0, 0, 255);
                //}
            }
        }
    }
    
    /*
    engine_put_pixel(self, 0, 0, 255, 0, 0, 255);
    engine_put_pixel(self, 1, 0, 0, 255, 0, 255);
    engine_put_pixel(self, 0, 1, 0, 255, 0, 255);
    engine_put_pixel(self, 1, 1, 255, 0, 0, 255);
    engine_put_pixel(self, 2, 2, 255, 0, 0, 255);
    */

    glfwMakeContextCurrent(self->window);

    glEnable(GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    glGenTextures(1, &self->screenTexID);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, self->screenTexWidth, self->screenHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, self->screenTex);

    return 0;
}

void engine_draw(Engine *self)
{
    glClear(GL_COLOR_BUFFER_BIT);

    
    for (int x = 0; x < self->screenTexWidth; x++)
    {
        for (int y = 0; y < self->screenTexHeight; y++)
        {
            //printf("drawing\n");
            //unsigned char r = rand() % 255;
            for (int z = 0; z < 4; z++)
            {
                /*
                if (x == y)
                {
                    engine_put_pixel(self, x, y, 0, 0, 0, 255);
                }
                else
                {
                    //engine_put_pixel(self, x, y, r, r, r, 255);
                    engine_put_pixel(self, x, y, r, r, r, r);
                }
                */
                
                unsigned char r = x % 256;
                unsigned char g = y % 256;
                unsigned char b = (x+y) % 256;
                engine_put_pixel(self, x, y, r, g, b, 255);
            }
        }
    }
    
    

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, self->screenTexWidth, self->screenTexHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, self->screenTex);

    //glColor3d(0.5f, 0.25f, 0.0f);

    glBegin(GL_TRIANGLES);
    glTexCoord2f(0.0, 1.0); // 01
    glVertex2f(-1.0f, -1.0f);
    glTexCoord2f(0.0, 0.0); // 00
    glVertex2f(-1.0f, 1.0f);
    glTexCoord2f(1.0, 1.0); // 11
    glVertex2f(1.0f, -1.0f);

    glTexCoord2f(1.0, 1.0); // 11
    glVertex2f(1.0f, -1.0f);
    glTexCoord2f(0.0, 0.0); // 00
    glVertex2f(-1.0f, 1.0f);
    glTexCoord2f(1.0, 0.0); // 10
    glVertex2f(1.0f, 1.0f);
    glEnd();

    glfwSwapBuffers(self->window);

    glfwSwapInterval(1);
}

void engine_tick(Engine *self)
{
    static double lastTime = 0;
    static double dt = 0;
    static double nowTime = 0;
    static int fps = 0;

    nowTime = glfwGetTime();
    dt = (nowTime - lastTime);
    lastTime = nowTime;
    fps = (int)(1.0 / dt);

    //printf("%f\n", dt);
    printf("%i\n", fps);

    engine_draw(self);

    glfwPollEvents();
}

void engine_run(Engine *self)
{
    //glfwSwapInterval(60);
    
    
    while (!glfwWindowShouldClose(self->window))
    {
        //unsigned char (*metapixel)[self->screenTexWidth][self->screenTexHeight][4] = (unsigned char (*)[self->screenTexWidth][self->screenTexHeight][4]) self->screenTex;



        engine_tick(self);
    }
    
}

#endif
