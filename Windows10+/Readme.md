# Windows 10+

Compilar trompo3 e inercial3 en Windows 10+ es un proceso delicado.
Siga cuidadosamente las instrucciones.

## Paso 1: Instalar MSYS2

Descargar MSYS2 desde el sitio oficial:
→[MSYS2](https://www.msys2.org/)

Hay que eligir la versión según el sistema que se use, generalmente msys2-x86_64 para procesadores Intel y msys2-arm64 para procesadores ARM.  Los archivos tienen en su nombre una fecha que cambia conforme se va actualizando MSYS2.

Una vez descargado el instalador, hay que ejecutarlo y seguir los pasos (acepte la configuración predeterminada).  En la última ventana de diálogo se pregunta si se quiere ejecutar MSYS2, preferentmente no hacerlo.

## MUY IMPORTANTE
Abrir MSYS2 (buscar "MSYS2 MinGW 64-bit" en el menú de Windows).


Actualizar los paquetes (ejecutar en la terminal de MSYS2):
```console
 pacman -Syu
```
Si pide cerrar la terminal, hay que hacerlo y volver a abrirla para continuar.

Actualizar el resto de paquetes:

```console
 pacman -Su
```

## Paso 2: Instalar herramientas de compilación
Instalar GCC (compilador) y make:

```console
 pacman -S --needed base-devel mingw-w64-x86_64-gcc mingw-w64-x86_64-make
```

## Paso 3: Instalar OpenGL y FreeGLUT
OpenGL ya viene incluido en Windows, pero se necesitan las bibliotecas de desarrollo y FreeGLUT:

```console
pacman -S mingw-w64-x86_64-freeglut mingw-w64-x86_64-glew
```
## Paso 4: Instalar herramientas adicionales

```console
pacman -s unzip
```
## Paso 5: Descargar los programas fuente.

```console 
wget https://michelle.esfm.ipn.mx/eduardo.viruena/DrPina/DrPina.zip
```

## Paso 6: Descomprimir el archivo zip

```console
unzip DrPina.zip
```

## Paso 7. Compilar para obtener inercial3.exe y trompo3.exe

```console
cd DrPina/win
make
```
## Paso 8:  Llevar los ejecutables a un directorio adecuado.

Supondremos que USUARIO es el nombre de la cuenta de Windows en la que se está trabajando y 
que dicha cuenta está en el disco C, si no es así hay que sustituir "c"  por la letra del 
disco en donde se encuentre la cuenta de USUARIO.

```console
 mkdir /c/Users/USUARIO/Documentos/DrPina
 cp *.exe /c/Users/USUARIO/Documentos/DrPina
```
