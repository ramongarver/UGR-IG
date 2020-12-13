# Práctica 3 - Informática Gráfica
## Modos de visualización:
- 1 -- Puntos
- 2 -- Líneas
- 3 -- Sólido
- 4 -- Sólido Ajedrez

## Objetos visualizables:
- Z -- ROTACION
- X -- PIRAMIDE
- C -- CUBO
- V -- CONO
- B -- CILINDRO
- N -- ESFERA
- M -- ROTACION
- , -- OBJETO_PLY
- . -- ROTACION PLY
- R -- ROBOT
- T -- TANQUE

### Objeto TANQUE:
Debemos estar visualizando el objeto TANQUE (tecla T).
- F1 -- Subir el cañón del tanque
- F2 -- Bajar el cañón del tanque
- F3 -- Girar torreta a la izquierda
- F4 -- Girar torreta a la derecha

### Objeto ROBOT:
Debemos estar visualizando el objeto ROBOT (tecla R).

Como existen muchos grados de libertad y ocuparían muchas teclas, he decidido definir una tecla para cambiar el lado del robot que se mueve. Por defecto, se mueve el lado derecho del cuerpo. Si se quiere cambiar de lado de cuerpo es necesario pulsar una tecla:
- Y -- Cambiar el lado del cuerpo que se mueve
En función del lado del cuerpo que se mueva:
- F1 -- Mover pierna completa hacia atrás
- F2 -- Mover pierna completa hacia delante
- F3 -- Mover parte inferior de la pierna hacia atrás
- F4 -- Mover parte inferior de la pierna hacia delante
- F5 -- Mover brazp completo hacia atrás
- F6 -- Mover brazo completo hacia delante
- F7 -- Mover brazo completo hacia fuera
- F8 -- Mover brazo completo hacia dentro
- F9 -- Mover antrezado hacia abajo
- F10 -- Mover antebrazo hacia arriba
- F11 -- Mover cara hacia la izquierda
- F12 -- Mover cara hacia la derecha

#### Animación:
- A -- Activar/Desactivar animación
- S -- Aumentar la velocidad de la animación
- D -- Disminuir la velocidad de la animación

### Articulaciones:
- W -- Aumentar la velocidad del movimiento las articulaciones
- E -- Disminuir la velocidad del movimiento las articulaciones

## Compilación y ejecución
Para compilar el proyecto:
- ``make``
Para ejecutar el proyecto:
- ``./practica3 beethoven``
Para limpiar los archivos del proyecto:
- ``make clean``