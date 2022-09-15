g++ -c client/Client.cpp -o build/Client.o
g++ build/Client.o -o build/Client.exe -lole32 -loleaut32 -luser32

g++ -c server/color/Color.cpp -o build/Color.o
g++ -c server/color/Main.cpp -o build/Main.o
g++ -shared build/Color.o build/Main.o -o build/Color.dll -lole32 -loleaut32 -luser32 -Wl,--kill-at