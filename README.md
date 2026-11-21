# Compilar jogo

## 1. (Recomendado) Compilar com Docker Buildx

> Esse método compila os binários para Windows e Linux.

Requisitos:
- Docker instalado,
- Docker Buildx Plugin instalado.

Se estiver no Windows, clique no arquivo `build.cmd`. Se o Docker no Windows falhar, o script tenta executar o mesmo comando pelo WSL (com Docker configurado nele).
Se estiver no WSL ou no Linux, rode `./build.sh`

## 2. Compilar pelo Make
> Apenas compila os binários do seu sistema.

Requisitos: 
- ter a biblioteca raylib instalada no seu sistema.
- Utilizar MSYS2 ou Linux.


Em seu terminal, rode `make`. Os binários resultantes estarão na pasta `saida`.

# Desenvolver

## Iniciando Ambiente de Desenvolvimento

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

## Estrutura do Repositório

- .devcontainer, .dockerfiles, .vscode: configurações do ambiente de desenvolvimento.
- build: diretório de cache de compilação.
- saida: diretório dos executáveis compilados.
- src: diretório do código-fonte.

### Como estruturar o código?

Exceto a `main.c`, todo arquivo `*.c` tem seu devido `*.h` localizado na mesma pasta. \
Nenhum código pode importar diretamente os arquivos `*.c`, somente `*.h`. \
Todo código deve estar dentro de src, ou dentro de qualquer pasta criada dentro de src.
