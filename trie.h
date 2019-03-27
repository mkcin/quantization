#include <stdint.h>
//funkcja inicjalizujaca, wykonac raz przed uzywaniem drzewa
void init();
//funkcja dodajaca podana historie i jej prefiksy
//do zbioru dozwolonych historii
//wypisuje OK jesli sie udalo, lub bezpiecznie konczy program
//w razie problemow z alokacja
void insert(const char*);
//funkcja usuwajaca historie i historie, ktore maja ja za prefiks
//wypisuje OK
void delete(const char*);
//funkcja laczaca energie historii w relacje rownowaznosci
//wypisuje OK jesli sie udalo, error, jesli nie moze tego zrobic
//z powodu niespelnienia warunkow zadania
//lub bezpiecznie konczy program w razie problemow z alokacja
void equal(const char*, const char*);
//funkcja przypisujaca podana wartosc energii
//podanej historii i wszystkich historiom w jej relacji rownowaznosci
//wypisuje OK jesli sie udalo, error, jesli nie moze tego zrobic
//z powodu niespelnienia warunkow zadania
//lub bezpiecznie konczy program w razie problemow z alokacja
void set_value(const char*, uint64_t);
//funkcja wypisujaca energie historii
//lub error, jesli nie moze tego zrobic
//z powodu niespelnienia warunkow zadania
void get_value(const char*);
//funkcja wypisuje YES, jesli podana historia jest dozwolona
//lub NO jesli podana historia nie jest dozwolona
void valid(const char*);
//funkcja dealokuje cala pamiec zarezerwowana do utrzymywania struktur
//zaimplementowanych w module
void destroy();
