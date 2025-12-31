# include "raylib.h"
void draw_stuff() {
    ClearBackground(RAYWHITE);
    DrawRectangle(100, 100, 100, 100, RED);
}

int main(void) {
    // This project will test if your raylkib is good and make a windown with a red square
    InitWindow(800, 500, "Tästä tulee vitun paska simulaattori");

    while(!WindowShouldClose())
    {
        BeginDrawing();
        draw_stuff();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
