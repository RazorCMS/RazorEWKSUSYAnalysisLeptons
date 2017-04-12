#! /bin/bash
source ~/.bash_login

while [[ $# -gt 1 ]]
do
    echo blash $#
    key="$1"
    echo $key " " $2
    
    case $key in
	-i|--inputList)
	    inlist="$2"
	    shift # past argument
	    ;;
	-o|--outputFile)
	    outfile="$2"
	    shift # past argument
	    ;;
	-l|--lumi)
	    lumi="$2"
	    shift # past argument
	    ;;
	-a|--analysisTag)
	    anTag="$2"
	    shift # past argument
	    ;;
	-s|--signalType)
	    sigType="$2"
	    shift # past argument
	    ;;
	-b|--binningFile)
	    bFile="$2"
	    shift # past argument
	    ;;
	--default)
	    DEFAULT=YES
	    ;;
	*)
            # unknown option
	    ;;
    esac
    shift # past argument or value
done


echo INPUT FILE  = $inlist
echo OUTFILE PREFIX = $outfile

categories=( highpt hzbb highres lowres )

for j in $(ls $inlist);
do
    for i in "${categories[@]}";
    do
	echo ./GetHggRazorSystematicsQuadratureFaster --inputList=$inlist/$j --category=$i --outputFile=$outfile"_"$i".txt" --lumi=$lumi --analysisTag=$anTag --binningFile=$bFile --signalType=$sigType
	./GetHggRazorSystematicsQuadratureFaster --inputList=$inlist/$j --category=$i --outputFile=$outfile"_"$i".txt" --lumi=$lumi --analysisTag=$anTag --binningFile=$bFile --signalType=$sigType
    done
    #echo $outfile"_"${categories[0]}".txt" $outfile"_"${categories[1]}".txt" $outfile"_"${categories[2]}".txt" $outfile"_"${categories[3]}".txt"
    #echo $outfile"_AllCategories_"$j
    cat $outfile"_"${categories[0]}".txt" $outfile"_"${categories[1]}".txt" $outfile"_"${categories[2]}".txt" $outfile"_"${categories[3]}".txt" > $outfile"_AllCategories_"$j
done


if [[ -n $1 ]]; then
    echo "Last line of file specified as non-opt/last argument:"
    tail -1 $1
fi


