#include <stdio.h>

// Style = Theme & Skin


struct theme{
    char *border;
    char *objet_m_1;
    char *objet_1;
    char *objet_2;
};

struct theme_prototype theme_default = {"*", "-1", "1", "2"};
struct theme_prototype various = {"x", "-1", "5", "10"};
struct theme_prototype emoji = {
    "\U0001FAA8",
    "\U0001F4A9",
    "\U0001F4B2",
    "\U0001F48E"
};

struct skin{
    char *size_0;
    char *size_m_1;
    char *size_p_1;

};

struct skin_prototype skin_default = {"______", "___", "_______"};
