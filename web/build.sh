#!/usr/bin/env bash
set -eu

ROOT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
OUTPUT_DIR="${ROOT_DIR}/build/web"

if ! command -v emcc >/dev/null 2>&1; then
    printf '%s\n' "emcc was not found. Install and activate the Emscripten SDK, then try again." >&2
    exit 1
fi

export EM_CACHE="${EM_CACHE:-${HOME}/.cache/emscripten}"
mkdir -p "${EM_CACHE}"
PACKAGE_EMSCRIPTEN_CONFIG="/usr/share/emscripten/.emscripten"
if [ -z "${EM_CONFIG:-}" ] && [ -f "${PACKAGE_EMSCRIPTEN_CONFIG}" ] && grep -q '^FROZEN_CACHE = True' "${PACKAGE_EMSCRIPTEN_CONFIG}"; then
    # Ubuntu freezes its system cache, so use an equivalent config for the writable user cache.
    EM_CONFIG="${EM_CACHE}/emscripten.config"
    sed 's/^FROZEN_CACHE = True/FROZEN_CACHE = False/' "${PACKAGE_EMSCRIPTEN_CONFIG}" > "${EM_CONFIG}"
    export EM_CONFIG
fi

mkdir -p "${OUTPUT_DIR}"
mkdir -p "${OUTPUT_DIR}/assets/images" "${OUTPUT_DIR}/fonts"
cp "${ROOT_DIR}/assets/images/sky.png" "${ROOT_DIR}/assets/images/clouds.png" "${OUTPUT_DIR}/assets/images/"
cp "${ROOT_DIR}/web/fonts/PressStart2P-Regular.ttf" "${ROOT_DIR}/web/fonts/OFL.txt" "${OUTPUT_DIR}/fonts/"
cd "${ROOT_DIR}"

emcc \
    src/main.c src/menu.c src/game.c util/util.c \
    -o "${OUTPUT_DIR}/index.html" \
    --shell-file web/shell.html \
    --preload-file assets/images@assets/images \
    -sUSE_SDL=2 \
    -sUSE_SDL_IMAGE=2 \
    -sSDL2_IMAGE_FORMATS='["png","jpg"]' \
    -sALLOW_MEMORY_GROWTH=1 \
    -lm

printf 'Browser build created at %s\n' "${OUTPUT_DIR}"
