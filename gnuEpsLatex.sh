#!/bin/gnuplot -c
#input picName
picName=ARG1
#logName="'/dev/null'"
set term epslatex color standalone size 6,5
set output "tmp.tex"

# your code (in default just a command test)
test

set output
!latex tmp.tex
!dvips -o @picName.eps tmp.dvi
!xelatex tmp.tex
!cp tmp.pdf @picName.pdf
!rm tmp*
