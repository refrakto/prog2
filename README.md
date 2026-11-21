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

# Desenvolver

Para configurar o seu ambiente de desenvolvimento, tenha:
- WSL (Se estiver no Windows)
- Docker
- Docker Buildx Plugin
- VSCode

> OBS: Para Windows, de preferência, clone o repositório no WSL, instale o Docker e o Buildx no WSL, e clone o repositório dentro do WSL.

1. Clone o repositório.
2. Abra a pasta do repositório no VSCode.
3. Instale a extensão [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) em seu VSCode.
4. Pressione `Ctrl+Shift+P` para abrir a Paleta de Comandos, procure por `Dev Containers: Reabrir no Contêiner` e selecione esse comando.

Espere o Contêiner compilar.

Para compilar para o desenvolvimento, rode no terminal `make run`. Para compilar uma versão finalizada, rode apenas `make`.