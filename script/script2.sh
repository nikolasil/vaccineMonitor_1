#! /bin/bash

virusFile=$1
counrtyFile=$2
num=$3
duplicates=$4

declare -a arrCountries;
declare -a arrViruses;
declare -a arrId;

# check length arguments
# kena arxeia
# pinakes me -A gia idia onomata epitheta

while IFS= read -r line; do
    arrCountries+=("$line")
done < $counrtyFile

while IFS= read -r line; do
    arrViruses+=("$line")
done < $virusFile

lengthOfCountries=${#arrCountries[@]}
lengthOfViruses=${#arrViruses[@]}

for (( i=0; i<$num; i++ )) do
    lengthOfarrId=${#arrId[@]}
    id=0
    if [ $duplicates -eq 1 ]    
    then
        if [ $lengthOfarrId -eq 0 ]
        then
            id=$((1 + $RANDOM % 9999))
        else
            possibility=4
            if [ $((1 + $RANDOM % 10)) -lt $possibility ]
            then
                indexarrId=$((0 + $RANDOM % $lengthOfarrId))
                id=${arrId[indexarrId]}
                if [ $((1 + $RANDOM % 10)) -lt $possibility ]
                then
                    id=${arrId[lengthOfarrId-1]}
                fi
            fi
            
        fi
    fi

    if [ $id -eq 0 ]
    then
        flag=1
        while [ $flag -ne 0 ]
        do
            id=$((1 + $RANDOM % 9999))
            flag=0
            for (( j=0; j<$lengthOfarrId; j++ )) do
                if [ ${arrId[j]} -eq $id ]
                then
                    flag=1
                    break
                fi
            done
        done
    fi

    lengthOfFirstName=$((3 + $RANDOM % 12))
    lengthOfLastName=$((3 + $RANDOM % 12))
    indexCountry=$((0 + $RANDOM % $lengthOfCountries))

    age=$((1 + $RANDOM % 120))
    firstName=$(head -3 /dev/urandom | tr -cd '[:alpha:]' | cut -c -$lengthOfFirstName)
    lastName=$(head -3 /dev/urandom | tr -cd '[:alpha:]' | cut -c -$lengthOfLastName)
    
    indexVirus=$((0 + $RANDOM % $lengthOfViruses))

    date="$((1 + RANDOM % 30))-$((1 + RANDOM % 12))-$((1950 + RANDOM % 70))"

    if [ $(($RANDOM % 2)) -eq 1 ]
    then
        status='YES'
        echo $id $firstName $lastName ${arrCountries[indexCountry]} $age ${arrViruses[indexVirus]} $status  $date >> ../citizenRecords/inputFile.txt
    else
        status='NO'
        echo $id $firstName $lastName ${arrCountries[indexCountry]} $age ${arrViruses[indexVirus]} $status  >> ../citizenRecords/inputFile.txt
    fi
    
    arrId+=("$id")
done