#include <stdio.h>

#include "trie.h"
#include "parse.h"

//glowna funkcja programu, do zakonczenia odczytywania pliku
//rozpartuje kazda jego linie pod katem komend do wykonania
//na koniec czysci zaalokowana pamiec
int main() {
  //inicjalizacja drzewa historii
  init();
  while(!feof(stdin)) {
    //obluga pojedynczej linii
    parse(insert, delete, valid, equal, get_value, set_value, destroy);
  }
  //zwolnienie pamieci
  destroy();
  return 0;
}
