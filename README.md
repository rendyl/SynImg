# rayTRACING
Gamagora 2019 - Ray Tracing

*Ray Tracing C++*

## Fonctionnalités implémentées :
- Affichage de Sphères
- Eclairage direct (Point Lights / Lampes surfaciques)
- Eclairage indirect
- Cornell Box
- Miroirs
- Vitres
- BVH

## Quelques rendus :
### Eclairage Indirect (avec Miroir & Vitre) :
![Render / Indirect Light](/SynImg/Img/Render.png)

### Test du BVH : 
<img src="/SynImg/Img/testBoxZ.png" data-canonical-src="/SynImg/Img/testBoxZ.png" width="299" height="299" /> <img src="/SynImg/Img/testBox.png" data-canonical-src="/SynImg/Img/testBox.png" width="299" height="299" />

### 1000 Sphères avec le BVH :
![1000 Sph / Indirect Light](/SynImg/Img/1000sphpurple.png)
 
## Comparatif avec/sans BVH :

### Sans éclairage indirect :

#### SANS BVH :
Nombre de sphères | Temps d'éxécution | Nombre de tests d'intersection
----------------- | ----------------- | ------------------------------
10 | 6s | 268802711  
50 | 15s | 824666870  
100 | 28s | 1658260659  
1000 | 245s | 4050123043
5000 | 1017s | 65902044150 
10000 | 1531s | 99511761411 
20000 | 2779s | 179748534602 

#### AVEC BVH :
Nombre de sphères | Temps d'éxécution | Nombre de tests d'intersection
----------------- | ----------------- | ------------------------------
10 | 3s | 21193170 
50 | 4s | 40504100 
100 | 5s | 67072736 
1000 | 19s | 334125758 
5000 | 132s | 2394643054 
10000 | 317s | 5477778834 
20000 | 536s | 9007225618 

#### Graphe Comparatif : Nombre d'intersections en fonction du Nombre de sphères
![Nombre d'intersections en fonction du Nombre de sphères](/SynImg/Img/Graphe2.png)


### Avec éclairage indirect :

#### AVEC BVH :
Nombre de sphères | Temps d'éxécution | Nombre de tests d'intersection
----------------- | ----------------- | ------------------------------
10 | 80s | 205660338 
50 | 84s | 295175164 
100 | 97s | 538056776 
1000 | 184s | 2143561292 
5000 | 922s | 15139982976 
10000 | 2578s | 44399352164 
20000 | 3647s | 62759919546 

#### Graphe : Nombre d'intersections en fonction du Nombre de sphères (éclairage indirect)
![Nombre d'intersections en fonction du Nombre de sphères (éclairage indirect)](/SynImg/Img/Graphe1.png)


## En cours :
- Affichage de Mesh
- BVH pour les Mesh
- Sampling pour la camera

*Merci à Guillaume Bouchard pour l'enseignement ! https://github.com/guibou*
