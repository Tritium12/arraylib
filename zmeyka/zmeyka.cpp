#include <ctime>
#include <iostream>
#include <cstdio>
using namespace::std;


#ifdef _WIN32
    #include <windows.h>
    void gotoxy(int x, int y) {
        COORD pos = { (SHORT)x, (SHORT)y };
        HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(output, pos);
    }
#else
   
    void gotoxy(int x, int y) {
        printf("\033[%d;%dH", y + 1, x + 1);
        fflush(stdout);
    }
#endif

void clearScreen() {
    
    cout << "\033[2J\033[H" << flush;
    // 2J — стереть весь экран
    // H  — курсор в левый верхний угол (1,1)
}
//cd zmeyka && g++ zmeyka.cpp -o snake && ./snake

const int WIDTH = 13;
const int HEIGHT =12;

const int MAX_LEN_SNAKE = (WIDTH - 3)*(HEIGHT - 2);

const int UP = 0;
const int DOWN = 1;
const int LEFT = 2;
const int RIGHT = 3;

const int snake_dir = UP;

bool isrunning = true;

char map[] = 
"############\n"
"#          #\n"
"#          #\n"
"#          #\n"
"#          #\n"
"#          #\n"
"#          #\n"
"#          #\n"
"#          #\n"
"#          #\n"
"#          #\n"
"############\n";

char snake = 'O';
int snake_x[MAX_LEN_SNAKE] = {0};
int snake_y[MAX_LEN_SNAKE] = {0};

int snake_len = 1;


int main(){
    clearScreen();
    cout << "\033[?25l" << flush; // спрятать курсор
    snake_x[0] = WIDTH/2;
    snake_y[0] = HEIGHT/2;
    
    double time = clock();

    while (isrunning){
        if (((clock() - time) / CLOCKS_PER_SEC) >= 0.3){
            time = clock(); 
            for (int i = snake_len - 2; i >= 0 ; --i){
                snake_x[i+1] = snake_x[i];
                snake_y[i+1] = snake_y[i];
            }
            
            if (snake_dir == UP){
                --snake_y[0];
            }
            if (snake_dir == DOWN){
                ++snake_y[0];
            }
            if (snake_dir == RIGHT){
                ++snake_x[0];
            }
            if (snake_dir == LEFT){
                --snake_x[0];
            }
            
             if(snake_x[0] == 0 || snake_y[0] == 0 || snake_x[0] == WIDTH-2 || snake_y[0] == HEIGHT - 1){
                isrunning = false;
             }

            gotoxy(0,0);
            for ( int i  = 0; i < snake_len; ++i){
                map[snake_y[i]*WIDTH + snake_x[i]] = snake;
            }
            cout << map;
            for ( int i  = 0; i < snake_len; ++i){
                map[snake_y[i]*WIDTH + snake_x[i]] = ' ';
            }

            
        }
    }
    cout << "\033[?25h" << flush; // показать курсор
    
    gotoxy(1, HEIGHT);
    cout << "YOUR SCORE IS " << snake_len << endl;
    return 0;

}
