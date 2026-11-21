#!/usr/bin/env bash

docker buildx build -f .dockerfiles/Dockerfile.build --output type=local,dest=. .