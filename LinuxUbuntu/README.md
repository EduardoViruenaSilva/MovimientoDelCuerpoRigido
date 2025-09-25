En un sistema Linux/Ubunto 22.04 o posterior, hay que instalar el comilardor gcc, make y la biblioteca:
libfreeglut3-dev

En una terminal:

```console
sudo pkg update
sudo apt install g++
sudo apt install make
sudo apt install freeglut3-dev
```



Luego, para compilar los programas, hay que descargarlos en un subdirectorio y dar la instrucción:
```console
make
```

Para ejecutar:

Movimiento del cuerpo rígido visto desde el sistema de referencia:
```console
./trompo3
```

Movimiento del cuerpo rígido con el sistema de referencia montado en el cuerpo mismo.
```console
./inercial3
```
