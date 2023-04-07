# Sistem de supraveghere - Proiect POO
<hr>
Tema: Sistem de supraveghere

Clase:
- CustomString
  - clasa utilitara pentru string handling
  - supraincarca operatorii de copiere si mutare
- Camera
  - cuprinde un nume si o adresa (CustomString)
  - cuprinde 2 getteri si 2 setteri
  - supraincarca operatorii de citire si afisare
  - supraincarca operatorii de copiere
- Stocare
  - Clasa simuleaza un spatiu de stocare cu proprietatile: spatiu(GB), viteza read/write(mb/s) si cat % este plin spatiul de stocare
  - cuprinde 3 getteri si 3 setteri
- Server
  - Liste dinamice pentru Camere si Spatii de stocare
  - supraincarca operatorii de citire si afisare
  - supraincarca operatorii de copiere si mutare
  - implica logica de business:
    - adaugarea/stergerea camerelor dupa index, nume sau adresa
    - adaugarea/stergerea spatiilor de stocare
    - calcularea timpului ramas pana spatiul se umple cu inregistrari
Aplicatia poate sa citeasca o serie de camere si spatii de stocare si sa le atribuie dinamic unui server. Acesta poate adauga sau sterge aceste obiecte si poate calcula timpul ramas pana spatiul de stocare se umple.