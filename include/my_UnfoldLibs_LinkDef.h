#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ nestedclass    ;  // see http://root.cern.ch/viewvc/trunk/cint/doc/ref.txt
#pragma link C++ nestedtypedef  ;

#pragma link C++ class UNFOLD::FILEIO+;
#pragma link C++ class UNFOLD::HVis+;
#pragma link C++ class UNFOLD::UNFOLD+;
#pragma link C++ class UNCERT::UNCERT+;
#pragma link C++ class UNFOLD:Vis+;

#endif // __CINT__
