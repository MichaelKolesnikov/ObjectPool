# ObjectPool
## Installation
```bash
sudo apt install g++ build-essential cmake clang git -y
git clone https://github.com/MichaelKolesnikov/ObjectPool.git
mkdir ObjectPool/build
cd ObjectPool/build
cmake ..
make
sudo make install
sudo ldconfig
```
## Installation google-tests
```bash
sudo apt install libgtest-dev googletest
cd /usr/src/gtest
sudo cmake -Bbuild
sudo cmake --build build
sudo cp ./build/lib/libgtest* /usr/lib
```
## Uninstalling
```bash
sudo rm /usr/local/include/ObjectPool.h
sudo ldconfig
```