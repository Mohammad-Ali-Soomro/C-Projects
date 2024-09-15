#include <iostream>
#include <windows.h>
#include <cmath>
#include <thread>
using namespace std;

class Donut 
{
public:
    Donut();
 //   ~Donut();
    void animate();
    void clearScreen();
    void calculateDonut();
    void drawDonut();
    void gotoxy(SHORT x, SHORT y);

private:
    float A, B;   //rotation angle representation of spinning donut
    float i, j;
    int k;
    float z[2100];
    char b[2100];
};

Donut::Donut() : A(0), B(0) {
    cout << "\x1b[2J";   //an ANSI escape sequence to clear the screen).
}

//Donut::~Donut() {
    // Destructor
//}

void Donut::clearScreen() {
    system("cls");
}

void Donut::gotoxy(SHORT x, SHORT y) {  //moves the cursor to a specific location in the console
    static HANDLE h = NULL;
    if (!h)
        h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = { x, y };
    SetConsoleCursorPosition(h, c);
}

void Donut::calculateDonut() 
{
    for (j = 0; j < 6.28; j += 0.07) {
        for (i = 0; i < 6.28; i += 0.02) {
            float c = sin(i);
            float d = cos(j);
            float e = sin(A);
            float f = sin(j);
            float g = cos(A);
            float h = d + 2;
            float D = 1 / (c * h * e + f * g + 5);
            float l = cos(i);
            float m = cos(B);
            float n = sin(B);
            float t = c * h * g - f * e;
            int x = 40 + 30 * D * (l * h * m - t * n);
            int y = 12 + 15 * D * (l * h * n + t * m);
            int o = x + 80 * y;
            int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);

            if (22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
                z[o] = D;
                b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
            }
        }
    }
}

void Donut::drawDonut() {
    cout << "\x1b[H";
    for (k = 0; k < 1761; k++) {
        putchar(k % 80 ? b[k] : 10);
        A += 0.00004;
        B += 0.00002;
    }
    gotoxy(0, 0);
}

void Donut::animate() {
    while (true) {
        clearScreen();
        memset(b, 32, 1760);
        memset(z, 0, 7040);
        calculateDonut();
        drawDonut();
        std::this_thread::sleep_for(std::chrono::nanoseconds(1));
        // Sleep(0.5); // Uncomment this line if you want to introduce a delay
    }
}

int main() {
    Donut donut;
    donut.animate();
    return 0;
}

