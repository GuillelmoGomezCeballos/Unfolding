#!/bin/sh

if [ $# != 1 ]; then
echo 'TOO FEW PARAMATERS'
exit
fi

if [ $1 == 'LL' ]; then
  ./runAllUnfold.sh 0 0 LL >& outputs_logs/log_runAllUnfold00LL &
  ./runAllUnfold.sh 2 0 LL >& outputs_logs/log_runAllUnfold20LL &
  ./runAllUnfold.sh 1 0 LL >& outputs_logs/log_runAllUnfold10LL &
  ./runAllUnfold.sh 1 1 LL >& outputs_logs/log_runAllUnfold11LL &
  ./runAllUnfold.sh 1 2 LL >& outputs_logs/log_runAllUnfold12LL &
  ./runAllUnfold.sh 1 3 LL >& outputs_logs/log_runAllUnfold13LL &
  ./runAllUnfold.sh 1 4 LL >& outputs_logs/log_runAllUnfold14LL &
  exit;
fi

./runAllUnfold.sh 0 0 0 >& outputs_logs/log_runAllUnfold000 &  
./runAllUnfold.sh 2 0 0 >& outputs_logs/log_runAllUnfold200 &  
./runAllUnfold.sh 1 0 0 >& outputs_logs/log_runAllUnfold100 &  
./runAllUnfold.sh 1 1 0 >& outputs_logs/log_runAllUnfold110 &  
./runAllUnfold.sh 1 2 0 >& outputs_logs/log_runAllUnfold120 &  
./runAllUnfold.sh 1 3 0 >& outputs_logs/log_runAllUnfold130 &  
./runAllUnfold.sh 1 4 0 >& outputs_logs/log_runAllUnfold140 &  

