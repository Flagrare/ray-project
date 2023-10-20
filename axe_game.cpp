#include "raylib.h"
#include "string.h"
#include "stdlib.h"
#include <iostream>

int main()
{
    int width{800}, height{450};

    InitWindow(width, height, "TENKAI");

    int circle_center_x{200}, circle_center_y{200}, circle_radius{25};

    int circle_x_max_limit{width - circle_radius}, circle_x_min_limit{circle_radius};
    int circle_y_max_limit{height - circle_radius}, circle_y_min_limit{circle_radius};

    int square_x{400}, square_y{0}, square_width{50}, square_height{50}, square_direction{10};
    int square_center_x{0}, square_center_y{0};
    int square_y_bottom{square_y + square_height}, square_y_top{square_y}, square_x_right{square_x + square_width}, square_x_left{square_x};

    int dx{0}, dy{0};
    int max_edge_dist_x{(square_width / 2) + (circle_radius)}, max_edge_dist_y{(square_height / 2) + (circle_radius)};

    int particle_speed = 10;

    bool collision_with_square{false};

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        DrawCircle(circle_center_x, circle_center_y, circle_radius, RED);
        DrawRectangle(square_x, square_y, square_width, square_height, BLUE);

        if (collision_with_square)
        {

            char text[] = "GAME OVER";

            // Calculate the width of the text
            int text_width = MeasureText(text, 20);

            // Calculate the x-coordinate to center the text
            int text_x = (width - text_width) / 2;

            DrawText(text, text_x, height / 2, 20, RED);
        }
        else
        {

            if (square_y > (height - square_height) || square_y < 0)
            {
                square_direction = -square_direction;
            }

            if (IsKeyDown(KEY_LEFT) && circle_center_x > circle_x_min_limit)
            {
                circle_center_x -= particle_speed;
            }

            else if (IsKeyDown(KEY_RIGHT) && circle_center_x < circle_x_max_limit)
            {
                circle_center_x += particle_speed;
            }
            else if (IsKeyDown(KEY_UP) && circle_center_y > circle_y_min_limit)
            {
                circle_center_y -= particle_speed;
            }
            else if (IsKeyDown(KEY_DOWN) && circle_center_y < circle_y_max_limit)
            {
                circle_center_y += particle_speed;
            }

            std::cout << "square_x:" << square_x << "\n";
            std::cout << "square_y: " << square_y << "\n";

            square_center_x = square_x + square_width / 2;
            square_center_y = square_y + square_height / 2;

            std::cout << "square_center_x:" << square_center_x << "\n";
            std::cout << "square_center_y: " << square_center_y << "\n";

            dx = abs(circle_center_x - square_center_x);
            dy = abs(circle_center_y - square_center_y);
            std::cout << "dx:" << dx << "\n";
            std::cout << "dy: " << dy << "\n";

            collision_with_square = dx <= max_edge_dist_x && dy <= max_edge_dist_y;

            square_y += square_direction;
        }

        EndDrawing();
    }
}