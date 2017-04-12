# Setup Correctly

cd include

make clean;make

cd ..

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PWD/include

make clean;make

