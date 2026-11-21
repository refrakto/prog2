# Compilar jogo

## 1. (Recomendado) Compilar com Docker Buildx

> Requisito:
> - Docker instalado,
> - Docker Buildx Plugin instalado.
>>
> Esse método compila os binários para Windows e Linux.

Se estiver no Windows, clique no arquivo `build.cmd`. Se o Docker no Windows falhar, o script tenta executar o mesmo comando pelo WSL (com Docker configurado nele).
Se estiver no WSL ou no Linux, rode `./build.sh`

## 2. Compilar pelo Make

> Requisito: 
> - ter a biblioteca raylib instalada no seu sistema.
> - Utilizar MSYS2 ou Linux.
>
>Apenas compila os binários do seu sistema.

Em seu terminal, rode `make`. Os binários resultantes estarão na pasta `saida`.