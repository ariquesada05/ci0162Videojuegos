Creación de Videojuegos - Froggie Forest

> Froggie Forest es un juego de plataformas 2D donde controlas Rannie, una rana aventurera que debe atravesar niveles repletos de enemigos, obstáculos y secretos para rescatar a su familia.

## Características
- Plataformas y exploración en 2D.
- Enemigos con patrones simples y colisiones físicas.
- Varios niveles (level01, level02, level03) con música específica.
- Gestión de assets (sprites, sonidos, mapas TMX).

## Controles
- Movimiento: Flechas izquierda/derecha
- Saltar: Z
- Atacar: X 
- Pausa / Menú: `Esc`


## Cómo jugar
1. Inicia el juego.
2. Supera plataformas, evita o derrota enemigos.
3. Recoge objetos y busca la salida del nivel.
4. Avanza por los niveles hasta completar la historia.

## Requisitos
- Compilador C++ (soporta C++17 o superior recomendado).
- Dependencias: `SDL2` (u otras librerías multimedia usadas por el proyecto). Revisa el `makefile` y la carpeta `libs/` para detalles.

## Instalación y ejecución (rápida)
1. Clona el repositorio.
2. Revisa y satisface las dependencias nativas (`SDL2`, `lua`, etc.).
3. Desde la raíz del proyecto ejecuta:


```
make clean; make; make run
```

## Estructura principal del proyecto
- `assets/` — imágenes, fuentes y sonidos.
- `scripts/` — lógica de niveles y comportamiento en Lua.
- `libs/` — dependencias incluidas (glm, sol, tinyxml2, lua headers).
- `src/` — código fuente C++ (gestores, componentes ECS, sistemas).
- `maps/` — archivos TMX de los niveles.


## Instalación de bibliotecas
```
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev lua5.3 liblua5.3-dev
```
