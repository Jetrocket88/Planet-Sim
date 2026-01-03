gcc main.c -Wall -Wextra -O2 \
-I "C:\Users\harry\SDL\x86_64-w64-mingw32\include" \
-I "C:\Users\harry\SDL\SDL_Fonts\include" \
-L "C:\Users\harry\SDL\x86_64-w64-mingw32\lib" \
-L "C:\Users\harry\SDL\SDL_Fonts\lib" \
-lSDL3_ttf \
-lSDL3 \
-o gravity_simulator.exe;
./gravity_simulator.exe
