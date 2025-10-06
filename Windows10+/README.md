# Windows 10+

Compilar trompo3 e inercial3 en Windows 10+ es un proceso delicado.
Siga cuidadosamente las instrucciones.

## Requisitos

### MSYS2

Descargar MSYS2 desde el sitio oficial:
→[MSYS2](https://www.msys2.org/)

Hay que eligir la versión según el sistema que se use, generalmente msys2-x86_64 para procesadores Intel y msys2-arm64 para procesadores ARM.  Los archivos tienen en su nombre una fecha que cambia conforme se va actualizando MSYS2.

Una vez descargado el instalador, hay que ejecutarlo y seguir los pasos (acepte la configuración predeterminada).  En la última ventana de diálogo se pregunta si se quiere ejecutar MSYS2, preferentmente no hacerlo.

### MUY IMPORTANTE
Abrir MSYS2 (buscar "MSYS2 MinGW 64-bit" en el menú de Windows).

### Actualizar los paquetes 
Ejecutar en la terminal de MSYS2:
```console
 pacman -Syu
```
Si MSYS2 pide cerrar la terminal, hay que hacerlo y volver a abrirla para continuar.

### Actualizar el resto de paquetes:

```console
 pacman -Su
```

### Instalar el compilador, bibliotecas y herramientas.

Instalar g++ (compilador C/C++) y make:

```console
 pacman -S --needed base-devel mingw-w64-x86_64-gcc mingw-w64-x86_64-make
```

Instalar OpenGL y FreeGLUT
OpenGL ya viene incluido en Windows pero se necesitan las bibliotecas de GLEW y FreeGLUT:

```console
pacman -S mingw-w64-x86_64-freeglut mingw-w64-x86_64-glew
```

###Descarga y descompresión de los programas 

Descargar el archivo MovimientoDelCuerpoRigido-main.zip de GitHub.com

Para descomprimirlo, hay que dar clic con el botón derecho sobre el archivo descargado, 
en el menú que se exhibe hay que elegir EXTRAER/EXTRACT

En este punto hay que ubicar los archivos extraídos.  Supondremos que la descarga se hizo por el 
usuario USUARIO en el disco C: en el subdirectorio de Descargas.  En la terminal de
MSYS2 hay que dar la instrucción:

```console
cd /c/Users/USUARIO/Descargas/MovimientoDelCuerpoRigido-main/Windows10+
```
En caso de que se haya descargado el programa por el usuario USAURIO en el disco E: en la 
carpeta Movimiento, la instrucción anterior sería entonces:
```console
cd /e/Users/USAURIO/Movimiento/MovimientoDelCuerpoRigido-main/Windows10+
```

### Compilación

Para compilar los programas basta dar la instrucción
```console
make
```
en la terminal de MSYS2 después de haberse ubicado el directorio de los programas fuente.
La compilación generará dos programas ejecutables:  trompo3.exe e inercial.exe


### Ejecución

