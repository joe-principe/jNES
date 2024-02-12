#include <raylib.h>

int 
main(void)
{
    InitWindow(640, 480, "jNES");

    while (!WindowShouldClose()) {
        BeginDrawing();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
/* EOF */
