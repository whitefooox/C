g++ -c client/Client.cpp -o build/Client.o
g++ build/Client.o -o build/Client.exe

g++ -c server/color/Color.cpp -o build/Color.o
g++ -shared build/Color.o -o build/Color.dll

g++ -c server/colorReverse/ColorReverse.cpp -o build/ColorReverse.o
g++ -shared build/ColorReverse.o -o build/ColorReverse.dll

g++ -c manager/Manager.cpp -o build/Manager.o
g++ -shared build/Manager.o -o build/Manager.dll

regsvr32 build/Color.dll
regsvr32 build/ColorReverse.dll