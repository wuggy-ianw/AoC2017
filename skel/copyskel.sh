#!/bin/bash
set -e

dayname=$1
destdir="../day$dayname"
mkdir -p $destdir

for i in `ls *.in`
do
    destfile=`basename $i .in`
    destfile=${destfile//\$DAYNAME/$dayname}
    cat $i | sed "s/\$DAYNAME/$dayname/g" > $destdir/$destfile
done
