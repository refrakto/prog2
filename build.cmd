@echo off

docker buildx build -f .dockerfiles/Dockerfile.build --output type=local,dest=.
if not errorlevel 1 exit /b 0

echo Docker falhou no Windows. Tentando executar pelo WSL...
where wsl.exe >nul 2>&1
if errorlevel 1 (
    echo WSL nao encontrado. Nao foi possivel repetir o comando.
    exit /b 1
)

wsl.exe --cd "%CD%" --exec docker buildx build -f .dockerfiles/Dockerfile.build --output type=local,dest=.
exit /b %ERRORLEVEL%