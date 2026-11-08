#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")/.." && pwd)"
EMSDK_VERSION="3.1.64"
EMSDK_DIR="${TMPDIR:-/tmp}/digital-duel-emsdk-${EMSDK_VERSION}"

if [[ ! -x "${EMSDK_DIR}/emsdk" ]]; then
    git clone --depth 1 https://github.com/emscripten-core/emsdk.git "${EMSDK_DIR}"
fi

"${EMSDK_DIR}/emsdk" install "${EMSDK_VERSION}"
"${EMSDK_DIR}/emsdk" activate "${EMSDK_VERSION}"
source "${EMSDK_DIR}/emsdk_env.sh"

bash "${ROOT_DIR}/web/build.sh"
