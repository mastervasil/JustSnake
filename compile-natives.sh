#!/bin/bash
set -e
cd /Users/vasil/projects/JustSnake/JustSnake/build/classes/debug
javah -d /Users/vasil/projects/JustSnake/JustSnake/src/main/jni ru.vasil.justsnake.renderer.NativeRenderer
cd /Users/vasil/projects/JustSnake/JustSnake/src/main
~/android-ndk-r9c/ndk-build
