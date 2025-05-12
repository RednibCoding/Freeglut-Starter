@echo off
gcc main.c -Wall -std=c99 ^
-Ldeps/libs/freeglut -Ideps/include ^
-lfreeglut_static -DFREEGLUT_STATIC ^
-lwinmm -lopengl32 -lgdi32 -lglu32 ^
-mwindows -o main.exe
