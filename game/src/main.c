#include "raylib.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600

#define GAME_VERSION "Game v 0.01"


typedef struct Ball_t {
    Vector2 pos;
    int r; // size
    Color c ; // color 
    float v;
    int health; // health

} Ball;

typedef struct Food_t {
    Vector2 pos;
    Color c;
    int value; // use to tell if it a good fruit or not
    int r;
} Fruit;

void SetBall(Ball* b);
void DrawBall(Ball* b);
void moveBall(Ball* b);
bool isAlive(Ball* b);
void setFruit (Fruit* f);
void DrawFruit(Fruit* t);
bool collide(Fruit* f , Ball* b);


int main() {
    
    
    InitWindow(SCREEN_WIDTH,SCREEN_HEIGHT,"Ahmad Game");
    SetTargetFPS(120);
    Ball b = {{100,100},20,WHITE,2.5f,1};
    Fruit t = {{SCREEN_WIDTH/2 , SCREEN_HEIGHT / 2},RED,10,20};
    while (!(WindowShouldClose()))
    {
        
        BeginDrawing();
            ClearBackground(BLACK);
            DrawBall(&b);
            moveBall(&b);
            DrawFruit(&t);

            /*Random things to test*/
            if (collide(&t,&b)) {
                t.c.g = 100;
                t.c.a = 130;
                t.c.r = 29;
            }
            else {
                t.c.g = 20;
                t.c.r = 200;
            }
            
            printf("x : %0.01f , y : %0.01f\r",b.pos.x , b.pos.y); /* <---- shit*/
            DrawText(GAME_VERSION,0,0 , 20 , WHITE);
            DrawFPS(0,20); 
        EndDrawing();
    }
    

    return 0;
}


// set ball to deafult setting
void SetBall(Ball* ball) {
    if (ball == NULL)
    {
        return;
    }

    // position on the screen
    ball->pos.x = 10;
    ball->pos.y = 10;

        
    ball->r = 10; // ball size
    ball->health = 100; // ball health point I don't know why I add it
        
    /* set ball color */
    ball->c.a = 200;
    ball->c.b = 200;
    ball->c.g = 200;
    ball->c.r = 200;

}

void DrawBall(Ball* ball) {
    if (ball == NULL) 
        return;

    DrawCircle(ball->pos.x  , ball->pos.y , ball->r , ball->c);

    
}

bool isAlive(Ball* b) {
    if (b == NULL || b->health == 0) {
        return false;
    }
    return true;
}

void moveBall(Ball* b) {
    if (b == NULL || b->health == 0) return;
    
    if (IsKeyDown(KEY_W)) {
        b->pos.y -= b->v;
    }
    if (IsKeyDown(KEY_S)) {
       b->pos.y += b->v; 
    }
    if (IsKeyDown(KEY_A)) {
       b->pos.x -= b->v; 
    } 
    if (IsKeyDown(KEY_D)) {
       b->pos.x += b->v; 
    }
}

void setFruit(Fruit* f) {
    if (f == NULL) 
    f = malloc(sizeof(Fruit));

    f->r = 10;
    f->c = RED;
    f->value = (int) rand() % 10 + 1;
    f->pos.x = SCREEN_WIDTH / 2; f->pos.y = SCREEN_HEIGHT / 2;
}

void DrawFruit(Fruit* t) {
    if (t == NULL) return;
    DrawCircle(t->pos.x , t->pos.y,t->r,t->c);

}

bool collide(Fruit* f , Ball* b) {
    if (f == NULL || b == NULL) return false;

    bool xstatement = ((int)b->pos.x +  b->r) == ((int)f->pos.x + f->r);
    bool ystatement = ((int)b->pos.y +  b->r) == ((int)f->pos.y + f->r);

    if (xstatement && ystatement)
    {
        return true;
    }

    if (IsKeyDown(KEY_P))   
    {
        b->pos.x = f->pos.x;
        b->pos.y = f->pos.y;
    }
    
    return false;
}
