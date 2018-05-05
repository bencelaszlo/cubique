# cubique
![Cubique logo](/media/cubique_logo_full.png)
Számítógépi grafika féléves feladat.

## A feladat
3 dimenziós grafikát használó program fejlesztése OpenGL + GLUT (C) / SDL2 (C++) könyvtárak használatával.

A feladat [bővebb leírása](http://uni-miskolc.hu/~matip/grafika/).

## A megoldás
Egy 3 dimenziós, számítógépes építőjáték, mozgatható kockákkal.

### Alapvető kritériumok
- [x] kamerakezelés: egérrel és billentyűzettel navigálható a program
- [x] 3 dimenziós objektumok, külön fájlból (a __res__ jegyzékben)
- [x] animáció, mozgatás: a kockák mozgathatóak a 3 dimenziós térben a billentyűzet használatával
- [x] textúrák: a kockákra textúrák vannak helyezve
- [x] fények: a __+__ és __-__ billentyűkkel növelhető, illetve csökkenthető a fényerő
- [x] súgó: az __F1__ gomb megnyomásával megjeleníthető/elrejthető egy menü, ami információt ad a programról, valamint annak kezelési módjáról, lehetőségeiről

### További megvalósított lehetőségek:
- [x] ködhatás
- [x] áttetsző kockák
- [x] ütközésvizsgálat a kockák között
- [x] mentés/betöltés külső fájlból
