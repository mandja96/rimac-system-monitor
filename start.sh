mkdir -p build
cd build/

app="SystemMonitor"

qmake ../SystemMonitor/"$app".pro
  
make
rm *.o

echo "Build done!"
echo "$app is starting now..."
./SystemMonitor
