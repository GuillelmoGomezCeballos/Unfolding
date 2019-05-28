{
  gROOT->Macro("../macros/CPlot.cc+");
  gROOT->Macro("../macros/MitStyleRemix.cc+");  
  gInterpreter->ProcessLine(".! ps |grep root.exe");
  
}
