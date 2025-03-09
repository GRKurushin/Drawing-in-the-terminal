#include <iostream>
#include <cmath>

const int WIDTH = 180;
const int HEIGHT = 60;

void drawHeart(float angleX, float angleY, float angleZ) {
    const char symbol = '@';
    char screen[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            screen[i][j] = ' ';
        }
    }

    float size = 2.0;

    for (float t = 0; t < 2 * M_PI; t += 0.05) {
        for (float u = 0; u < 2 * M_PI; u += 0.05) {
            // HEART
            float x = size * 16 * sin(t) * sin(t) * sin(t);
            float y = size * (13 * cos(t) - 5 * cos(2 * t) - 2 * cos(3 * t) - cos(4 * t));
            float z = size * cos(u);

            // Rotation
            float yRot = y * cos(angleX) - z * sin(angleX);
            float zRot = y * sin(angleX) + z * cos(angleX);

            float xRot = x * cos(angleY) + zRot * sin(angleY);
            zRot = -x * sin(angleY) + zRot * cos(angleY);

            float xRot_new = xRot * cos(angleZ) - yRot * sin(angleZ);
            float yRot_new = xRot * sin(angleZ) + yRot * cos(angleZ);
            xRot = xRot_new;
            yRot = yRot_new;

            // 2D proection
            int screenX = int(xRot * 2 + WIDTH / 2);
            int screenY = int(yRot * 1 + HEIGHT / 2);

            if (screenX >= 0 && screenX < WIDTH && screenY >= 0 && screenY < HEIGHT) {
                screen[screenY][screenX] = symbol;
            }
        }
    }

    for (int i = 0; i < HEIGHT; ++i) {
        for (int j = 0; j < WIDTH; ++j) {
            std::cout << screen[i][j];
        }
        std::cout << '\n';
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    float angleX = 0.0f, angleY = 0.0f, angleZ = 0.0f;

    while (true) {
        std::cout << "\x1B[H";
        // std::cout << "\033[2J";

        drawHeart(angleX, angleY, angleZ);

        angleX += 0.01f;
        angleY += 0.01f;
        // angleZ += 0.01f;

        if (angleX > 4 * M_PI) angleX -= 4 * M_PI;
        if (angleY > 4 * M_PI) angleY -= 4 * M_PI;
        if (angleZ > 4 * M_PI) angleZ -= 4 * M_PI;
    }

    return 0;
}
