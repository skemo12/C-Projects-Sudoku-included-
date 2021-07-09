        Tema2 PC -- Paunoiu Darius Alexandru -- 312CD -- Readme

    Fiecare input al unui task incepe cu numarul taskului,asadar am decis
sa foloseasca functia switch(task), unde task este un string ce retine
numarului taskului, iar fiecare caz apeleaza functia corespunzatoare
taskului si dupa caz afiseaza matricea.(A nu se uita functia break in 
fiecare case, cum am facut la laborator! :( )

    In inceputul functiei main am initializat matricea gameboard cu '.'
acest lucru fiind benefic pentru rezolvarea majoritatii taskurilor.Totodata
aceasta este si 90% rezolvarea pentru task0, ramanand doar de afisat matricea.

    Pentru task1, inputul nu contine secventele bonus, asa dar se va folosi o
citire dedicata in loc de citireInit.Apoi se folosesc functiile citireCuvant 
si adaugare cuvant, dupa case se afiseaza in cadrului lui case1.

    Pentru task2, se face o citire diferita (lipsind secventele bonus,iar
coordonatele nefiind importante). Se face apel la functia adaugarePunctaj,
unde este dedicata o matrice cu punctajele.

    Pentru task3, se folosesc functiile obisnuite de citire citireInit
si citireBoard, pentru a completa tabla de joc. Functia pctBns, calculeaza 
punctajele cu tot cu bonusuri.

    Pentru task4, se citeste matricea in mod obisnuit. Functia cautareCuvant
va cauta primul cuvant ce poate fi adaugat pe tabla, respectand cerinta, iar
cu adaugareCuvant se adauga cuvantul pe tabla. Functia cautareCuvant e destul
de imbarlicata, dar nu am vrut sa fac o functie care sa compare valorile 
pentru ca ar fi primit foarte multi parametri.

    Pentru task5, trebuie prioritizat cuvantul cu punctaj maxim, cu tot cu 
bonusuri. Astfel am declarat o noua functie de cautare, cuvantOptim. Este 
similara dar diferita, si nu am creat alte subfunctii pentru ea din acelasi
motiv ca la cautareCuvant, numarul ridicat de parametrii.

    Pentru task6, ne folosim de functia de cuvantOptim, pentru a gasi un 
cuvant dupa fiecare mutare a playerului 1. Se foloseste functia citireInit,
dar restul citirii este facuta manual, pas cu pas, adaugant in vectorul lista
cuvintele folosite atat de player 1 cat si de player 2. Pentru fiecare apel,
reinitializam coord1, coord2 si max pentru a ne trezi cu valori aleatorii.

    Pentru Readme, am reluat fisierul scrabble.c pentru a-mi aduce aminte
ce am facut la unele taskuri pentru care aproape mi-am dat sufletul sa le 
rezolv. Explicatia pentru Readme este un pamflet si trebuie tratata ca 
atare :)). Multumesc pentru atentie!





