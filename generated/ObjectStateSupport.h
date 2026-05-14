
/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ObjectState.idl
using RTI Code Generator (rtiddsgen) version 4.7.0.
The rtiddsgen tool is part of the RTI Connext DDS distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the Code Generator User's Manual.
*/

#ifndef ObjectStateSupport_1035534872_h
#define ObjectStateSupport_1035534872_h

/* Uses */
#include "ObjectState.h"

#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)

class __declspec(dllimport) DDSTypeSupport;
class __declspec(dllimport) DDSDataWriter;
class __declspec(dllimport) DDSDataReader;

#endif

namespace ObjectStateMsg {
    /* ========================================================================= */
    /**
    Uses:     T

    Defines:  TTypeSupport, TDataWriter, TDataReader

    Organized using the well-documented "Generics Pattern" for
    implementing generics in C and C++.
    */

    #if defined(NDDS_USER_DLL_EXPORT) && defined(RTI_WIN32)
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    #if !defined(RTI_WIN32) && defined(NDDS_USER_SYMBOL_EXPORT)
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __attribute__((visibility("default")))
    #endif

    DDS_TYPESUPPORT_CPP(
        ObjectStateTypeSupport, 
        ObjectState);

    #define RTI_ENABLE_TDATAWRITER_DATA_CONSTRUCTOR_METHODS
    DDS_DATAWRITER_WITH_DATA_CONSTRUCTOR_METHODS_CPP(ObjectStateDataWriter, ObjectState);
    #undef RTI_ENABLE_TDATAWRITER_DATA_CONSTRUCTOR_METHODS
    #define RTI_ENABLE_TDATAREADER_DATA_CONSISTENCY_CHECK_METHOD
    DDS_DATAREADER_W_DATA_CONSISTENCY_CHECK(ObjectStateDataReader, ObjectStateSeq, ObjectState);
    #undef RTI_ENABLE_TDATAREADER_DATA_CONSISTENCY_CHECK_METHOD

    #if defined(NDDS_USER_DLL_EXPORT) || defined(NDDS_USER_SYMBOL_EXPORT)
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
} /* namespace ObjectStateMsg  */

#endif  /* ObjectStateSupport_1035534872_h */
