echo "[Параметры сборки]"
read -p "Файл: " name
read -p "Число потоков: " n
echo -e
mpic++ $name -o main.out
mpiexec -n $n ./main.out
rm main.out