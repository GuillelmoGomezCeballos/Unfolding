#!/bin/bash

for value in {0..3}
do
  root -l -q -b makeUnrolling.C+'('${value}', "Tot")'
  root -l -q -b makeUnrolling.C+'('${value}', "Pt")'
  root -l -q -b makeUnrolling.C+'('${value}', "Rap")'
  root -l -q -b makeUnrolling.C+'('${value}', "PhiStar")'
  root -l -q -b makeUnrolling.C+'('${value}', "PtRap0")'
  root -l -q -b makeUnrolling.C+'('${value}', "PtRap1")'
  root -l -q -b makeUnrolling.C+'('${value}', "PtRap2")'
  root -l -q -b makeUnrolling.C+'('${value}', "PtRap3")'
  root -l -q -b makeUnrolling.C+'('${value}', "PtRap4")'
done
