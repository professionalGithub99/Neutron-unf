// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME myUnfoldlibs_Dict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "FILEIO.h"
#include "UNFOLD.h"
#include "UNCERT.h"
#include "HVis.h"
#include "Vis.h"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static TClass *UNFOLDcLcLFILEIO_Dictionary();
   static void UNFOLDcLcLFILEIO_TClassManip(TClass*);
   static void *new_UNFOLDcLcLFILEIO(void *p = 0);
   static void *newArray_UNFOLDcLcLFILEIO(Long_t size, void *p);
   static void delete_UNFOLDcLcLFILEIO(void *p);
   static void deleteArray_UNFOLDcLcLFILEIO(void *p);
   static void destruct_UNFOLDcLcLFILEIO(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::UNFOLD::FILEIO*)
   {
      ::UNFOLD::FILEIO *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::UNFOLD::FILEIO));
      static ::ROOT::TGenericClassInfo 
         instance("UNFOLD::FILEIO", "FILEIO.h", 19,
                  typeid(::UNFOLD::FILEIO), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &UNFOLDcLcLFILEIO_Dictionary, isa_proxy, 4,
                  sizeof(::UNFOLD::FILEIO) );
      instance.SetNew(&new_UNFOLDcLcLFILEIO);
      instance.SetNewArray(&newArray_UNFOLDcLcLFILEIO);
      instance.SetDelete(&delete_UNFOLDcLcLFILEIO);
      instance.SetDeleteArray(&deleteArray_UNFOLDcLcLFILEIO);
      instance.SetDestructor(&destruct_UNFOLDcLcLFILEIO);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::UNFOLD::FILEIO*)
   {
      return GenerateInitInstanceLocal((::UNFOLD::FILEIO*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::UNFOLD::FILEIO*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *UNFOLDcLcLFILEIO_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::UNFOLD::FILEIO*)0x0)->GetClass();
      UNFOLDcLcLFILEIO_TClassManip(theClass);
   return theClass;
   }

   static void UNFOLDcLcLFILEIO_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *UNFOLDcLcLUNFOLD_Dictionary();
   static void UNFOLDcLcLUNFOLD_TClassManip(TClass*);
   static void delete_UNFOLDcLcLUNFOLD(void *p);
   static void deleteArray_UNFOLDcLcLUNFOLD(void *p);
   static void destruct_UNFOLDcLcLUNFOLD(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::UNFOLD::UNFOLD*)
   {
      ::UNFOLD::UNFOLD *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::UNFOLD::UNFOLD));
      static ::ROOT::TGenericClassInfo 
         instance("UNFOLD::UNFOLD", "UNFOLD.h", 22,
                  typeid(::UNFOLD::UNFOLD), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &UNFOLDcLcLUNFOLD_Dictionary, isa_proxy, 4,
                  sizeof(::UNFOLD::UNFOLD) );
      instance.SetDelete(&delete_UNFOLDcLcLUNFOLD);
      instance.SetDeleteArray(&deleteArray_UNFOLDcLcLUNFOLD);
      instance.SetDestructor(&destruct_UNFOLDcLcLUNFOLD);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::UNFOLD::UNFOLD*)
   {
      return GenerateInitInstanceLocal((::UNFOLD::UNFOLD*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::UNFOLD::UNFOLD*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *UNFOLDcLcLUNFOLD_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::UNFOLD::UNFOLD*)0x0)->GetClass();
      UNFOLDcLcLUNFOLD_TClassManip(theClass);
   return theClass;
   }

   static void UNFOLDcLcLUNFOLD_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *UNCERTcLcLUNCERT_Dictionary();
   static void UNCERTcLcLUNCERT_TClassManip(TClass*);
   static void delete_UNCERTcLcLUNCERT(void *p);
   static void deleteArray_UNCERTcLcLUNCERT(void *p);
   static void destruct_UNCERTcLcLUNCERT(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::UNCERT::UNCERT*)
   {
      ::UNCERT::UNCERT *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::UNCERT::UNCERT));
      static ::ROOT::TGenericClassInfo 
         instance("UNCERT::UNCERT", "UNCERT.h", 20,
                  typeid(::UNCERT::UNCERT), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &UNCERTcLcLUNCERT_Dictionary, isa_proxy, 4,
                  sizeof(::UNCERT::UNCERT) );
      instance.SetDelete(&delete_UNCERTcLcLUNCERT);
      instance.SetDeleteArray(&deleteArray_UNCERTcLcLUNCERT);
      instance.SetDestructor(&destruct_UNCERTcLcLUNCERT);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::UNCERT::UNCERT*)
   {
      return GenerateInitInstanceLocal((::UNCERT::UNCERT*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::UNCERT::UNCERT*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *UNCERTcLcLUNCERT_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::UNCERT::UNCERT*)0x0)->GetClass();
      UNCERTcLcLUNCERT_TClassManip(theClass);
   return theClass;
   }

   static void UNCERTcLcLUNCERT_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   static TClass *UNFOLDcLcLHVis_Dictionary();
   static void UNFOLDcLcLHVis_TClassManip(TClass*);
   static void *new_UNFOLDcLcLHVis(void *p = 0);
   static void *newArray_UNFOLDcLcLHVis(Long_t size, void *p);
   static void delete_UNFOLDcLcLHVis(void *p);
   static void deleteArray_UNFOLDcLcLHVis(void *p);
   static void destruct_UNFOLDcLcLHVis(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::UNFOLD::HVis*)
   {
      ::UNFOLD::HVis *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(::UNFOLD::HVis));
      static ::ROOT::TGenericClassInfo 
         instance("UNFOLD::HVis", "HVis.h", 24,
                  typeid(::UNFOLD::HVis), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &UNFOLDcLcLHVis_Dictionary, isa_proxy, 4,
                  sizeof(::UNFOLD::HVis) );
      instance.SetNew(&new_UNFOLDcLcLHVis);
      instance.SetNewArray(&newArray_UNFOLDcLcLHVis);
      instance.SetDelete(&delete_UNFOLDcLcLHVis);
      instance.SetDeleteArray(&deleteArray_UNFOLDcLcLHVis);
      instance.SetDestructor(&destruct_UNFOLDcLcLHVis);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::UNFOLD::HVis*)
   {
      return GenerateInitInstanceLocal((::UNFOLD::HVis*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::UNFOLD::HVis*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *UNFOLDcLcLHVis_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const ::UNFOLD::HVis*)0x0)->GetClass();
      UNFOLDcLcLHVis_TClassManip(theClass);
   return theClass;
   }

   static void UNFOLDcLcLHVis_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_UNFOLDcLcLFILEIO(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::UNFOLD::FILEIO : new ::UNFOLD::FILEIO;
   }
   static void *newArray_UNFOLDcLcLFILEIO(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::UNFOLD::FILEIO[nElements] : new ::UNFOLD::FILEIO[nElements];
   }
   // Wrapper around operator delete
   static void delete_UNFOLDcLcLFILEIO(void *p) {
      delete ((::UNFOLD::FILEIO*)p);
   }
   static void deleteArray_UNFOLDcLcLFILEIO(void *p) {
      delete [] ((::UNFOLD::FILEIO*)p);
   }
   static void destruct_UNFOLDcLcLFILEIO(void *p) {
      typedef ::UNFOLD::FILEIO current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::UNFOLD::FILEIO

namespace ROOT {
   // Wrapper around operator delete
   static void delete_UNFOLDcLcLUNFOLD(void *p) {
      delete ((::UNFOLD::UNFOLD*)p);
   }
   static void deleteArray_UNFOLDcLcLUNFOLD(void *p) {
      delete [] ((::UNFOLD::UNFOLD*)p);
   }
   static void destruct_UNFOLDcLcLUNFOLD(void *p) {
      typedef ::UNFOLD::UNFOLD current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::UNFOLD::UNFOLD

namespace ROOT {
   // Wrapper around operator delete
   static void delete_UNCERTcLcLUNCERT(void *p) {
      delete ((::UNCERT::UNCERT*)p);
   }
   static void deleteArray_UNCERTcLcLUNCERT(void *p) {
      delete [] ((::UNCERT::UNCERT*)p);
   }
   static void destruct_UNCERTcLcLUNCERT(void *p) {
      typedef ::UNCERT::UNCERT current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::UNCERT::UNCERT

namespace ROOT {
   // Wrappers around operator new
   static void *new_UNFOLDcLcLHVis(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::UNFOLD::HVis : new ::UNFOLD::HVis;
   }
   static void *newArray_UNFOLDcLcLHVis(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) ::UNFOLD::HVis[nElements] : new ::UNFOLD::HVis[nElements];
   }
   // Wrapper around operator delete
   static void delete_UNFOLDcLcLHVis(void *p) {
      delete ((::UNFOLD::HVis*)p);
   }
   static void deleteArray_UNFOLDcLcLHVis(void *p) {
      delete [] ((::UNFOLD::HVis*)p);
   }
   static void destruct_UNFOLDcLcLHVis(void *p) {
      typedef ::UNFOLD::HVis current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::UNFOLD::HVis

namespace ROOT {
   static TClass *vectorlEfloatgR_Dictionary();
   static void vectorlEfloatgR_TClassManip(TClass*);
   static void *new_vectorlEfloatgR(void *p = 0);
   static void *newArray_vectorlEfloatgR(Long_t size, void *p);
   static void delete_vectorlEfloatgR(void *p);
   static void deleteArray_vectorlEfloatgR(void *p);
   static void destruct_vectorlEfloatgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<float>*)
   {
      vector<float> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<float>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<float>", -2, "vector", 386,
                  typeid(vector<float>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEfloatgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<float>) );
      instance.SetNew(&new_vectorlEfloatgR);
      instance.SetNewArray(&newArray_vectorlEfloatgR);
      instance.SetDelete(&delete_vectorlEfloatgR);
      instance.SetDeleteArray(&deleteArray_vectorlEfloatgR);
      instance.SetDestructor(&destruct_vectorlEfloatgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<float> >()));

      ::ROOT::AddClassAlternate("vector<float>","std::vector<float, std::allocator<float> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<float>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEfloatgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<float>*)0x0)->GetClass();
      vectorlEfloatgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEfloatgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEfloatgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<float> : new vector<float>;
   }
   static void *newArray_vectorlEfloatgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<float>[nElements] : new vector<float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEfloatgR(void *p) {
      delete ((vector<float>*)p);
   }
   static void deleteArray_vectorlEfloatgR(void *p) {
      delete [] ((vector<float>*)p);
   }
   static void destruct_vectorlEfloatgR(void *p) {
      typedef vector<float> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<float>

namespace ROOT {
   static TClass *vectorlEdoublegR_Dictionary();
   static void vectorlEdoublegR_TClassManip(TClass*);
   static void *new_vectorlEdoublegR(void *p = 0);
   static void *newArray_vectorlEdoublegR(Long_t size, void *p);
   static void delete_vectorlEdoublegR(void *p);
   static void deleteArray_vectorlEdoublegR(void *p);
   static void destruct_vectorlEdoublegR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<double>*)
   {
      vector<double> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<double>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<double>", -2, "vector", 386,
                  typeid(vector<double>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEdoublegR_Dictionary, isa_proxy, 0,
                  sizeof(vector<double>) );
      instance.SetNew(&new_vectorlEdoublegR);
      instance.SetNewArray(&newArray_vectorlEdoublegR);
      instance.SetDelete(&delete_vectorlEdoublegR);
      instance.SetDeleteArray(&deleteArray_vectorlEdoublegR);
      instance.SetDestructor(&destruct_vectorlEdoublegR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<double> >()));

      ::ROOT::AddClassAlternate("vector<double>","std::vector<double, std::allocator<double> >");
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const vector<double>*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEdoublegR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<double>*)0x0)->GetClass();
      vectorlEdoublegR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEdoublegR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEdoublegR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double> : new vector<double>;
   }
   static void *newArray_vectorlEdoublegR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<double>[nElements] : new vector<double>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEdoublegR(void *p) {
      delete ((vector<double>*)p);
   }
   static void deleteArray_vectorlEdoublegR(void *p) {
      delete [] ((vector<double>*)p);
   }
   static void destruct_vectorlEdoublegR(void *p) {
      typedef vector<double> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<double>

namespace {
  void TriggerDictionaryInitialization_libmyUnfoldlibs_Dict_Impl() {
    static const char* headers[] = {
"FILEIO.h",
"UNFOLD.h",
"UNCERT.h",
"HVis.h",
"Vis.h",
0
    };
    static const char* includePaths[] = {
"/home/wadermane/forschoo/research/root_install/include",
"/home/wadermane/forschoo/research/RESC_REAL/include",
"/home/wadermane/forschoo/research/RESC_REAL/EigenLib",
"/",
"/home/wadermane/forschoo/research/RESC_REAL",
"/home/wadermane/forschoo/research/root_install/include/",
"/home/wadermane/forschoo/research/RESC_REAL/build/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "libmyUnfoldlibs_Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
namespace UNFOLD{class __attribute__((annotate("$clingAutoload$FILEIO.h")))  FILEIO;}
namespace UNFOLD{class __attribute__((annotate("$clingAutoload$UNFOLD.h")))  UNFOLD;}
namespace UNCERT{class __attribute__((annotate("$clingAutoload$UNCERT.h")))  UNCERT;}
namespace UNFOLD{class __attribute__((annotate("$clingAutoload$HVis.h")))  HVis;}
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "libmyUnfoldlibs_Dict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "FILEIO.h"
#include "UNFOLD.h"
#include "UNCERT.h"
#include "HVis.h"
#include "Vis.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"UNCERT::UNCERT", payloadCode, "@",
"UNFOLD::FILEIO", payloadCode, "@",
"UNFOLD::HVis", payloadCode, "@",
"UNFOLD::UNFOLD", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("libmyUnfoldlibs_Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_libmyUnfoldlibs_Dict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_libmyUnfoldlibs_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_libmyUnfoldlibs_Dict() {
  TriggerDictionaryInitialization_libmyUnfoldlibs_Dict_Impl();
}
