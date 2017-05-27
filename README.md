# SOII

https://users.info.uvt.ro/~silviu/store/so2/

TEMA1
1. Scrieti un program in C ce primeste ca argument calea catre un fisier sau director si afiseaza informatiile continute in structura `stat` sub forma:

Informatii despre </cale/catre/fisier>
--------------------------------------
Dimensiune:  X bytes
Numarul de legatur: X legaturi
Numarul inode: X
Permisiuni: ----------
Acest fisier este/nu este un link symbolic.

2. Extindeti programul de la punctul 1 sa suporte ca parametrii de intrare mai multe fisiere in acelasi timp pentru care trebuie afisate informatiile continute in structura `stat`.

3. Creati un fisier Makefile pentru compilarea automata a programului C.

TEMA2
1. In completare la programul de la `Tema 1`, adaugati urmatoarele functionalitati folosind `dirent.h`:

	a. listati continutul directorului curent si pentru fiecare intrare din director de tip fisier afisati informatiile cerute la `Tema 1`;
	b. listati continutul directorului curent in mod recursiv, adica pentru fiecare intrare de tip director mergeti in adancime si afisati informatiile despre fisierele existente;
	c. introduce o functionalitate prin care pot trimite ca parametru adancimea maxima pana la cat pot face cautarea (de ex.: --max-depth NUMAR); pentru suport de parametrii folositi `getopt` si/sau `getopt_long`

TEMA3

1. In completare la programul de la `Tema 1&2`, adaugati urmatoarele functionalitati:

	a. --userid, --groupid, pentru a specifica o cautare dupa id-ul utilizatorului sau grupului asociat fisierului;
	b. --permisiuni, pentru a cauta fisierele ce au setate anumite permisiuni (masca de permisiuni va fi declarata in formatul `rwxrwxrwx`);
	c. --dim-max, --dim-min, pentru a afisa fisierele ce se incadreaza in intervalul specificat in bytes(B);
