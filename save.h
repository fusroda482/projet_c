/* ------ SAVE.H ------- */

#ifndef SAVE_H
#define SAVE_H

// --- PROTOTYPES ---

void save(struct jeu p, int slot_number);
// Pourquoi pas une référence ?
struct jeu load(int slot_number);

#endif
