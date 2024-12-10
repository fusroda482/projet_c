#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

#include "gestion_clavier.h"

struct termios ancien_param;

void restaurer_terminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &ancien_param);
}

// Configuration du terminal pour lire les entrées sans appuyer sur Entrée
void config_terminal() {
    struct termios nouveau_param;
    
    // Sauvegarde de la configuration actuelle du terminal
    tcgetattr(STDIN_FILENO, &ancien_param);
    nouveau_param = ancien_param;
    nouveau_param.c_lflag &= ~(ICANON | ECHO); // Désactiver le mode canonique et l'affichage
    
    tcsetattr(STDIN_FILENO, TCSANOW, &nouveau_param);
    
    // Rendre l'entrée non bloquante
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
    
    // Rétablissement automatique de la configuration à la sortie
    //atexit(restaurer_terminal);
}
