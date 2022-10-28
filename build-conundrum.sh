#!/bin/bash
set -exo pipefail

docker build -t thock/conundrum --build-arg keymap=${keymap:-default:uf2} .
docker run -v $PWD:/qmk_firmware -v $PWD/.build:/qmk_firmware/.build -it thock/conundrum
