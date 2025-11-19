#!/usr/bin/env bash

set -euo pipefail

# --- Config -------------------------------------------------------------------

BUILD_DIR="build"

# --- Runner Cfg -------------------------------------------------------------------

RUNNER_EXE="bin/blackjack_runner.out"
DEALER_SO="bin/libblack_jack_solver_dealer.so"
PLAYER_SO=$(find ./build/players -type f -name "*.so")
DUMP_JSON="out.json"
NDECKS="2"
RESHUFFLE_PCTG="0.5"
NROUNDS="1000"
STARTING_CHIPS="500"
TBL_MIN="5"
TBL_MAX="50"

# ------------------------------------------------------------------------------

cmd="${1:-}"

case "$cmd" in
  build)
    if ! command -v cmake &> /dev/null; then
      echo "Error: cmake not found. Please install CMake."
      exit 1
    fi
    cmake -S . -B "$BUILD_DIR"
    cmake --build "$BUILD_DIR"
    ;;

  debug)
    if ! command -v cmake &> /dev/null; then
      echo "Error: cmake not found. Please install CMake."
      exit 1
    fi
    cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -S . -B "$BUILD_DIR"
    cmake --build "$BUILD_DIR"
    ;;

  test)
    if ! command -v cmake &> /dev/null; then
      echo "Error: cmake not found. Please install CMake."
      exit 1
    fi
    "$RUNNER_EXE" \
    --dealer "$DEALER_SO" \
    --player "$PLAYER_SO" \
    --output "$DUMP_JSON" \
    --ndecks "$NDECKS" \
    --reshuffle "$RESHUFFLE_PCTG" \
    --rounds "$NROUNDS" \
    --starting "$STARTING_CHIPS" \
    --min "$TBL_MIN" \
    --max "$TBL_MAX"
  ;;

  clean)
    rm -rf "$BUILD_DIR"
    ;;

  *)
    echo "Usage: $0 {build|debug|clean|test}"
    exit 1
    ;;
esac

# ------------------------------------------------------------------------------
