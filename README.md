# quantization

Opis działania programu  
Po uruchomieniu programu nie są dopuszczalne żadne kwantowe historie cząstki, zatem żadnej historii nie jest przypisana energia i żadne dwie energie nie są zrównane. W czasie działania program czyta ze standardowego wejścia i wykonuje następujące polecenia:      
DECLARE history – Powoduje, że każda kwantowa historia cząstki, będąca prefiksem podanej jako parametr history kwantowej historii cząstki, staje się dopuszczalna.      
REMOVE history – Powoduje, że każda kwantowa historia cząstki, mająca prefiks podany jako parametr history, przestaje być dopuszczalna.      
VALID history – Sprawdza, czy podana kwantowa historia cząstki jest dopuszczalna.      
ENERGY history energy – Jeśli podana w parametrze history kwantowa historia cząstki jest dopuszczalna i historia ta nie ma przypisanej energii, to przypisuje jej wartość energii podanej jako parametr energy. Jeśli ta kwantowa historia cząstki ma już przypisaną energię, to modyfikuje wartość tej energii.      
ENERGY history – Jeśli podana w parametrze history kwantowa historia cząstki jest dopuszczalna i historia ta ma przypisaną energię, to wypisuje wartość tej energii.      
EQUAL history_a history_b – Jeśli podane w parametrach history_a i history_b kwantowe historie cząstki są dopuszczalne, to: 
(a) jeśli chociaż jedna z nich ma przypisaną energię, zrównuje ich energie i domyka relację równoważności; 
(b) jeśli obie historie przed wykonaniem tego polecenia mają przypisane energie, to po wykonaniu polecenia energia przypisana tym historiom jest średnią arytmetyczną tych energii (z ewentualnym zaokrągleniem w dół); 
(c) jeśli obie historie są identyczne lub mają już zrównane energie, niczego nie zmienia.  
Poprawne dane wejściowe spełniają następujące dodatkowe warunki:      
Parametr opisujący kwantową historię cząstki jest niepustym ciągiem składającym się z cyfr 0, 1, 2 i 3.     
Energia jest dziesiętną liczbą całkowitą z przedziału od 1 do 2^64 − 1.     
Nazwa polecenia i jego parametry są oddzielone pojedynczą spacją, a każdy wiersz wejścia zawiera co najwyżej jedno polecenie i kończy się linuksowym znakiem przejścia do nowej linii (znak \n w C, kod ASCII 10). Są to jedyne białe znaki występujące w wierszu.  
Ponadto:      
Puste wiersze należy ignorować.     
Wiersze rozpoczynające się znakiem # należy ignorować.  
Informacje wypisywane przez program i obsługa błędów  Program kwituje poprawne wykonanie polecenia, wypisując informację na standardowe wyjście:      
Dla polecenia innego niż polecenie VALID lub jednoparametrowe polecenie ENERGY wiersz ze słowem OK.     
Dla polecenia VALID wiersz ze słowem YES lub NO zależnie od wyniku tego polecenia.     
Dla jednoparametrowego polecenia ENERGY dziesiętną liczbę całkowitą będącą wartością energii.     
Każdy wiersz wyjścia powinien kończyć się linuksowym znakiem przejścia do nowej linii (znak \n w C, kod ASCII 10). 
Jest to jedyny biały znak, jaki może pojawić się na wyjściu.  Program wypisuje informacje o błędach na standardowe wyjście diagnostyczne:      
Dla każdego błędnego wiersza i dla każdego polecenia, które nie może być wykonane, gdyż nie spełnia wyżej opisanych warunków, np. z powodu złej liczby parametrów lub błędnej wartości parametru, należy wypisać wiersz ze słowem ERROR, zakończony linuksowym znakiem końca linii (znak \n w C, kod ASCII 10). Jest to jedyny biały znak, jaki może pojawić się na wyjściu.
