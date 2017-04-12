#! /bin/bash

./GetHggRazorSystematicsQuadrature --inputList=$1 --category=highpt > $2
./GetHggRazorSystematicsQuadrature --inputList=$1 --category=hzbb >> $2
./GetHggRazorSystematicsQuadrature --inputList=$1 --category=highres >> $2
./GetHggRazorSystematicsQuadrature --inputList=$1 --category=lowres >> $2
