#!/bin/bash
set -exo pipefail

# Check if $keymap is set, and if it is not, set $keymap to $1,
# this will make it so you can either supply $keymap as a
# command line argument, or as a variable.
if [ -z "$keymap" ]; then
    keymap="$1"
fi

# If $RUNTIME is not set, check if podman or docker exists on the machine,
# and set $RUNTIME to the container runtime that is found.
# If none are found, error out.
if [ -z "$RUNTIME" ]; then
    if command -v podman >/dev/null 2>&1; then
        RUNTIME="podman"
    elif command -v docker >/dev/null 2>&1; then
        RUNTIME="docker"
    else
        echo "Error: no compatible container runtime found."
        echo "Either podman or docker are required"
        echo "See https://podman.io/getting-started/installation"
        echo "or https://docs.docker.com/install/#supported-platforms"
        echo "for installation instructions."
        exit 2
    fi
fi

"$RUNTIME" build -t thock/conundrum --build-arg keymap=${keymap:-default:uf2} .
"$RUNTIME" run -v $PWD:/qmk_firmware -v $PWD/.build:/qmk_firmware/.build -it thock/conundrum
