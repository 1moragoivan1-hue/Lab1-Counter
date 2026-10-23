#!/bin/bash

# Stop if the build or executable fails.
set -e

if [ "$#" -lt 2 ]; then
    echo "Usage: ./run.sh <task_number> <module_name> [arguments...]"
    echo "Example: ./run.sh 1 counter"
    exit 1
fi

TASK_NUM=$1
MODULE_NAME=$2
shift 2

TARGET="task${TASK_NUM}_${MODULE_NAME}"
TASK_FOLDER="./build/task${TASK_NUM}"

mkdir -p "$TASK_FOLDER"
# Build the executable.
cmake --build build --target "$TARGET"

# Run inside the task's build folder so the VCD is written there.
cd "$TASK_FOLDER"
"./${TARGET}" "$@"

# Open the generated waveform.
gtkwave "${MODULE_NAME}.vcd"

