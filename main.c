#include "raylib.h"

typedef struct {
    Vector3 coords;
    Vector3 rotation;
    float angle;
} Sun;

void draw_stuff(Sun *sun, Camera3D camera) {

    ClearBackground(RAYWHITE);

    // Enter 3D mode using the camera
    BeginMode3D(camera);
        
        // Draw your 3D object
        DrawSphere(sun->coords, 2.0f, RED);
        
        // Helpful for orientation: draws a grid on the ground
        DrawGrid(10, 1.0f); 

    EndMode3D();

    // 2D elements go here (after EndMode3D)
    DrawText("3D Mode Active", 10, 10, 20, DARKGRAY);
}

void draw_window() {
    Sun sun = {
        .coords = { 0, 2.0f, 0 }, // Moved closer to center for visibility
        .rotation = { 1, 0, 0 },
        .angle = 0.0f
    };

    // Initialize the Camera
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Where the camera is
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // What the camera looks at
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Rotation of the camera (usually Y is up)
    camera.fovy = 45.0f;                                // Field of view
    camera.projection = CAMERA_PERSPECTIVE;             // Perspective or Orthographic

    while(!WindowShouldClose())
    {
        // Optional: Update camera to rotate around the center
        UpdateCamera(&camera, CAMERA_PERSPECTIVE); 

        BeginDrawing();
            draw_stuff(&sun, camera);
        EndDrawing();
    }
}

int main(void) {
    InitWindow(800, 500, "Raylib 3D Test");
    SetTargetFPS(60);

    draw_window();

    CloseWindow();
    return 0;
}
