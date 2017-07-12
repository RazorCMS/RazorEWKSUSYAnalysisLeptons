#! /bin/bash

while [[ $# -gt 1 ]]
do
    #echo blash $#
    key="$1"
    #echo $key " " $2
    
    case $key in
	-if|--inputFileDir)
	    inputfiledir="$2"
	    shift #past argument
	    ;;
	-i1|--inputDir1)
	    indir1="$2"
	    shift # past argument
	    ;;
	-i2|--inputDir2)
	    indir2="$2"
	    shift # past argument
	    ;;
	-o|--outputFile)
	    outfile="$2"
	    shift # past argument
	    ;;
	-d|--dataFile)
	    datafile="$2"
	    shift # past argument
	    ;;
	-smh|--smhFile)
	    smhfile="$2"
	    shift # past argument
	    ;;
	-s|--signalFile)
	    sfile="$2"
	    shift # past argument
	    ;;
	-b|--binningFile)
	    bfile="$2"
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


#echo INPUT FILE  = $inputfiledir
#echo OUTFILE PREFIX = $outfile

extra_tag=Summer2017_July10_TChiHZ

for j in $(ls $inputfiledir);
do
    name=`echo $j | awk -F "list_" '{print $2}' | awk -F ".txt" '{print $1}'`
    #echo $name
    #echo ./CreateDataCardCommands" --inputCF="$indir1$name".txt --secondInputCF="$indir2$name".txt --outputFile=MakeDataCards_"$extra_tag$name".sh --dataFile="$datafile" --smhFile="$smhfile" --signalFile="$sfile"/HggRazor_SMS-T2bH_"$name"_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_1pb_weighted.root --sModel="$name"_DataCards_"$extra_tag" --binningFile="$bfile --currentDir=$PWD
    echo ./CreateDataCardCommands" --inputCF="$indir1$name".txt --outputFile=MakeDataCards_"$extra_tag$name".sh --dataFile="$datafile" --smhFile="$smhfile" --signalFile="$sfile"/SMS-TChiHZ_"$name"_1pb_weighted.root --sModel="$name"_DataCards_"$extra_tag" --binningFile="$bfile --currentDir=$PWD
    echo bsub -q 8nh -e  $PWD/err/$name.err -o  $PWD/log/$name.out source MakeDataCards_$extra_tag$name.sh
done


if [[ -n $1 ]]; then
    echo "Last line of file specified as non-opt/last argument:"
    tail -1 $1
fi


