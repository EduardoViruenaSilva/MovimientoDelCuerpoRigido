## Requisitos

En un sistema Linux/Ubunto 22.04 o posterior, hay que instalar 

unzip, para descomprimir los programas
gcc, el compilador C/C++.
freeglut3-dev, una biblioteca que es requisito para compilar los programas.
make, para automarizar el proceso de compilación.

La forma más sencilla de instalarlos es abrir una terminal (ctrl-alt-T):

```console
sudo pkg update
sudo apt install unzip 
sudo apt install g++
sudo apt install make
sudo apt install glut3-dev
```

## Descargar los programas

Descargar el archivo MovimientoDelCuerpoRigido-main.zip de GitHub.com y descomprimirlos:
```console
unzip MovimientoDelCuerpoRigido-main.zip
cd MovimientoDelCuerpoRigido-main.zip
cd LinuxUbuntu
```

## Compilación

Para compilar los programas, hay que descargarlos en un subdirectorio y dar la instrucción:
```console
make
```

## Ejecución

Movimiento del cuerpo rígido visto desde el sistema inercial:
```console
./inercial3
```

Movimiento del cuerpo rígido con el sistema de referencia montado en el cuerpo mismo:
```console
./trompo3
```
