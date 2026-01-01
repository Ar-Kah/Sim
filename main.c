# include "raylib.h"

// This function draws a white background with red rectangle
void draw_stuff() {
    ClearBackground(RAYWHITE);
    DrawRectangle(100, 100, 100, 100, RED);
}

void draw_circle() {
  DrawCircle(200, 200, 200, BLACK);
}

int main(void) {
    // This project will test if your raylkib is good and make a windown with a red square
    InitWindow(800, 500, "Tästä tulee vitun paska simulaattori");

    while(!WindowShouldClose())
    {
        BeginDrawing();
        draw_stuff();
        draw_circle();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
// Arska on homo!
