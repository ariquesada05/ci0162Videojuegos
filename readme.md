# Froggie Forest

> Froggie Forest es un juego de plataformas 2D donde controlas a una rana aventurera que debe atravesar niveles repletos de enemigos, obstáculos y secretos para rescatar a su familia.

## Características
- Plataformas y exploración en 2D.
- Enemigos con patrones simples y colisiones físicas.
- Varios niveles (level01, level02, level03) con música específica.
- Gestión de assets (sprites, sonidos, mapas TMX).

## Controles
- Movimiento: Flechas izquierda/derecha
- Saltar: Barra espaciadora
- Interactuar / Acción: Tecla `E` (si aplica)
- Pausa / Menú: `Esc`

> Nota: Los controles pueden depender del mapeo del controlador; revisa `scripts` si necesitas personalizarlos.

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
make
./gameEngine
```

Nota: En Windows puede que necesites compilar desde Visual Studio o ajustar el `makefile`.

## Estructura principal del proyecto
- `assets/` — imágenes, fuentes y sonidos.
- `scripts/` — lógica de niveles y comportamiento en Lua.
- `libs/` — dependencias incluidas (glm, sol, tinyxml2, lua headers).
- `src/` — código fuente C++ (gestores, componentes ECS, sistemas).
- `maps/` — archivos TMX de los niveles.

## Contribuir
- Crea una rama con tu cambio: `git checkout -b feat/nombre`.
- Envía un pull request describiendo los cambios.
- Asegúrate de no romper compilación y de incluir assets necesarios.

## Licencia
Indica aquí la licencia elegida (por ejemplo, MIT). Si no hay licencia, especifica cómo quieres que se use el proyecto.

## Créditos
- Autor: (añade tu nombre o alias)
- Recursos gráficos / música: revisar `assets/images` y `assets/sounds` para fuentes y atribuciones.

## Contacto
Si quieres colaborar o reportar bugs, abre un issue en el repositorio o contacta al autor.
