#include <ncurses.h>
#include <unistd.h>

#define DELAY 30000

int main() {
    int x = 0, y = 0;
    int max_x = 0, max_y = 0;
    int next_x = 0;
    int direction = 1;
    int ch;

    initscr();          // Initialise l'écran
    raw();              // Obtient l'entrée immédiatement
    keypad(stdscr, TRUE);// Active les touches spéciales
    noecho();           // Désactive l'affichage des touches
    curs_set(FALSE);     // Cache le curseur
    getmaxyx(stdscr, max_y, max_x); // Obtient les dimensions de l'écran
    nodelay(stdscr, TRUE); // Ne bloque pas sur getch()

    while ((ch = getch()) != 'q') {
        clear();
        mvprintw(y, x, "O"); // Dessine le radeau

        // Déplace le radeau
        if (ch == KEY_LEFT && x > 0) x--;
        if (ch == KEY_RIGHT && x < max_x - 1) x++;

        // Déplace l'objet
        if (direction == 1) {
            next_x++;
            if (next_x >= max_x - 1) direction = -1;
        } else {
            next_x--;
            if (next_x <= 0) direction = 1;
        }

        mvprintw(1, next_x, "*"); // Dessine l'objet
        refresh();
        usleep(DELAY);
    }

    endwin(); // Termine ncurses
    return 0;
}

