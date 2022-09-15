@rem Компиляция
g++ -c manager/Manager.cpp -o build/Manager.o
g++ -c component/Component.cpp -o build/Component.o
g++ -shared build/Manager.o -o build/Manager.dll
g++ -shared build/Component.o -o build/Component.dll
g++ client/Client.cpp -o build/Main.exe

@rem Регистрация компонента
regsvr32 build/Component.dll

@rem Удаление компонента из реестра
@rem regsvr32 /u build/Component.dll