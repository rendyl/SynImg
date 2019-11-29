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

### SANS BVH :
Nombre Spheres | Temps d'éxécution | Nb Tests Intersection
-------------- | ----------------- | ---------------------
10 | 6s | 268802711  
50 | 15s | 824666870  
100 | 28s | 1658260659  
1000 | 245s | 4050123043
5000 | 1017s | 65902044150 
10000 | 1531s | 99511761411 
20000 | 2779s | 179748534602 

### AVEC BVH :
Nombre Spheres | Temps d'éxécution | Nb Tests Intersection
-------------- | ----------------- | ---------------------
10 |  | 2 
50 | 1 | 2 
100 | 1 | 2 
1000 | 1 | 2 
5000 | 1 | 2 
10000 | 1 | 2 
20000 | 1 | 2 
 
## En cours :
- Affichage de Mesh
- BVH pour les Mesh
- Sampling pour la camera

*Merci à Guillaume Bouchard pour l'enseignement ! https://github.com/guibou*
