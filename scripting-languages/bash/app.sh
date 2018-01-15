#!/bin/bash

if [ -z $(command -v gnuplot) ]
then
	echo "Gnuplot is not installed."
  echo "Please run: brew install gnuplot"
  exit
fi

if [ -z $(command -v mktemp) ]
then
	echo "mktemp is not installed."
  exit
fi

function drawPlot {
  GPI="plot.gpi"

  echo "set title 'Currency Statistics'
  unset multiplot
  set xdata time
  set style data lines
  #set term png
  set timefmt '%Y-%m-%d'
  set format x '%b %d'
  set xlabel 'Date'
  set ylabel 'Rate'
  set autoscale y
  "> $GPI

  echo -en "plot \\" >> $GPI
  NUM=1
  for FILE in rates/*.txt; do
    echo -en "\n  '$FILE' using 1:2 title '`basename $FILE .txt`' with lines ls $NUM,\\" >> $GPI
    ((NUM++))
  done

  echo >> $GPI
  sed -i.bak '$s/,\\$//' $GPI
  echo "pause -1;" >> $GPI
  #cat $GPI
  gnuplot $GPI
}

function yearly_statistics {
  wget -q "http://www.nbp.pl/kursy/xml/dir.txt" -O dir.txt
  mkdir -p rates
  > output.txt
  rm rates/*.txt
  cat dir.txt | tr -d "\r" | grep '^a' | sort -k1.6| while read filename
  do
    wget -q -nc "http://www.nbp.pl/kursy/xml/$filename.xml" -O "rates/$filename.xml"
    cat "rates/$filename.xml" | xml2 > tmpfile
    date=$(cat tmpfile| grep -E '/tabela_kursow/data_publikacji'|cut -d= -f 2)
    cat tmpfile | grep -E 'kod_waluty|kurs_sredni'|cut -d= -f 2|sed -e N -e 's/\n/|/' | sort -t "|" -k 1| while read line
    # -e "s/^/$date|/"
    do
      currency="$(echo $line|cut -d'|' -f 1)"
      rate="$(echo $line|cut -d'|' -f 2|sed 's/\,/./')"
      echo -e "$date\t$rate" >> "rates/$currency.txt"
    done
  done
  drawPlot
}

PS3='Please enter your choice: '
options=("Yearly Statistics" "Quit")
select opt in "${options[@]}"
do
    case $opt in
        "Yearly Statistics")
            yearly_statistics
            break
            ;;
        "Quit")
            break
            ;;
        *) echo invalid option;;
    esac
done
