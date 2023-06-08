//
// By Emma Gouné on 04/06/2023.
// 2d convolution, max pooling and sobel filters
// The convolution.c file contains all the filter methods
// and the sobel.c file contains the pbm methods/
//



Pour ce projet j'utilise Clions comme IDE.

Pour la convolution 2D j'utilise un kernel tel que: 
----------------- Kernel -----------------
0.000000 -1.000000 0.000000
-1.000000 5.000000 -1.000000
0.000000 -1.000000 0.000000
Aussi appelé matrice de convolution d'amélioration de netteté.

La matrice de test est :
----------------- Image -----------------
1.000000 2.000000 3.000000 4.000000
5.000000 6.000000 7.000000 8.000000
9.000000 10.000000 11.000000 12.000000
13.000000 14.000000 15.000000 16.000000

Résultats:
----------------- Convolution -----------------
23.000000 14.000000 11.000000 11.000000 14.000000 17.000000
14.000000 2.000000 1.000000 1.000000 2.000000 9.000000
11.000000 1.000000 0.000000 0.000000 1.000000 6.000000
11.000000 1.000000 0.000000 0.000000 1.000000 5.000000
14.000000 2.000000 1.000000 1.000000 2.000000 7.000000
23.000000 14.000000 11.000000 11.000000 13.000000 16.000000
----------------- Max Pooling 2x2 -----------------
6.000000 8.000000
14.000000 16.000000


Enfin, pour la detection des contours j'ai décidé d'implémenter un filtre de Sobel et de travailler avec des image PGM. 
Le test de detection de contours est effectuée sur une petite matrice 13x13 changée en pgm file.

-

