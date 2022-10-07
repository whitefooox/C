clear
echo "[Параметры сборки]"
read -p "Файл: " name
read -p "Число потоков: " n
mpic++ $name -o main.out
echo "Собрано [*]"
echo -e
mpiexec -n $n ./main.out
rm main.out