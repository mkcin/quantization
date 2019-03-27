#include <stdint.h>
//funkcja oblugujaca zapytania odczytane w jednej linii
//przyjmuje wskazniki do funkcji, ktore odbluguja kolejne zapytania:
//DECLARE
//REMOVE
//VALID
//EQUAL
//ENERGY z jednym argumentem
//ENERGY z dwoma argumentami
//oraz wskaznik do funkcji czyszczacej pamiec
//funkcja wypisuje ERROR w razie wykrycia niepoprawnego wyjscia,
//wykonuje komende i wypisuje odpowiedni komunikat w razie odczytania
//poprawnej komendy
//badz nie wypisuje nic i nie wykonuje nic w razie odczytania
//zakomentowanej badz pustej linii
void parse(
  void (*insert)(const char*),
  void (*delete)(const char*),
  void (*valid)(const char*),
  void (*equal)(const char*, const char*),
  void (*get_value)(const char*),
  void (*set_value)(const char*, uint64_t),
  void (*destroy)()
);
