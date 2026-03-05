#include "raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SUN_MASS 100000

/* const double G =  */
const double G = 6.67408e-11; // in SI units (m³/kg/s²)


typedef struct {
    Vector3 coords;
    int M;
    double radius;
} Sun;

typedef struct {
    Vector3 coords;
    Vector3 velocity;
    int M;
    double radius;
} Planet;

void update_physics(Sun *sun, Planet *planet, double deltaTime) {
    // 1. Get the vector pointing from Planet to Sun
    Vector3 direction = {
        sun->coords.x - planet->coords.x,
        sun->coords.y - planet->coords.y,
        sun->coords.z - planet->coords.z
    };

    // 2. Get the TOTAL distance squared
    // Formula: r^2 = x^2 + y^2 + z^2
    double distSq = (direction.x * direction.x) + 
                    (direction.y * direction.y) + 
                    (direction.z * direction.z);
    
    // Safety check: if distance is too small, skip to avoid division by zero
    if (distSq < 0.01) return; 

    double dist = sqrt(distSq);

    // 3. Calculate total acceleration magnitude: a = (G * M) / r^2
    // Use a much larger G for the simulation to actually move
    double simG = 1; 
    double accelerationMag = (simG * sun->M) / distSq;

    // 4. Update velocity: change = direction_unit_vector * acceleration * time
    // We += here so the planet "remembers" its previous speed!
    planet->velocity.x += (direction.x / dist) * accelerationMag * deltaTime;
    planet->velocity.y += (direction.y / dist) * accelerationMag * deltaTime;
    planet->velocity.z += (direction.z / dist) * accelerationMag * deltaTime;

    // 5. Update position
    planet->coords.x += planet->velocity.x * deltaTime;
    planet->coords.y += planet->velocity.y * deltaTime;
    planet->coords.z += planet->velocity.z * deltaTime;
}

void draw_stuff(Sun *sun, Planet *earth, Planet* venus, Camera3D camera) {
    ClearBackground(BLACK);

    // Enter 3D mode using the camera
    BeginMode3D(camera);
        
        // Draw your 3D object
        DrawSphere(sun->coords, sun->radius, RED);
        DrawSphere(earth->coords, earth->radius, BLUE);
        DrawSphere(venus->coords, venus->radius, BROWN);
        
        // Helpful for orientation: draws a grid on the ground
        /* DrawGrid(10, 1.0f);  */

    EndMode3D();

    // 2D elements go here (after EndMode3D)
    DrawText("3D Mode Active", 10, 10, 20, DARKGRAY);
}

void draw_window() {
    Sun sun = {
        .coords = { 0.0f, 2.0f, 0.0f }, // Sun at the center
        .radius = 0.7f,
        .M = 10000 
    };

    Planet earth = {
        .coords = { 10.0f, 5.0f, 0.0f },  // 5 units to the right
        .velocity = { 25.0f, 0.0f, 25.0f }, // Kick it "forward" (Z axis)
        .radius = 0.4f,
        .M = 10
    };
    Planet venus = {
        .coords = { -22.f, -2.5f, -1.0f },
        .velocity = { -15.0f, 0.0f, -15.0f }, // Kick it "forward" (Z axis)
        .radius = 0.3f,
        .M = 7
};
    // Initialize the Camera
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 30.0f, 30.0f, 30.0f }; // Where the camera is
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // What the camera looks at
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Rotation of the camera (usually Y is up)
    camera.fovy = 45.0f;                                // Field of view
    camera.projection = CAMERA_PERSPECTIVE;             // Perspective or Orthographic


    while(!WindowShouldClose())
    {
        // Optional: Update camera to rotate around the center
        double delta = GetFrameTime();
        UpdateCamera(&camera, CAMERA_ORBITAL); 
        update_physics(&sun, &earth,  delta);
        update_physics(&sun, &venus,  delta);

        BeginDrawing();
            draw_stuff(&sun, &earth, &venus, camera);
        EndDrawing();
    }
}

int main(void) {
    InitWindow(800, 500, "Raylib 3D Test");
    SetTargetFPS(144);

    draw_window();

    CloseWindow();
    return 0;
}
