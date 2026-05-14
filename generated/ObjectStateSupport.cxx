
/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ObjectState.idl
using RTI Code Generator (rtiddsgen) version 4.7.0.
The rtiddsgen tool is part of the RTI Connext DDS distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the Code Generator User's Manual.
*/

#include "ObjectStateSupport.h"
#include "ObjectStatePlugin.h"

#ifndef dds_c_log_impl_h              
#include "dds_c/dds_c_log_impl.h"                                
#endif        

namespace ObjectStateMsg {

    /* ========================================================================= */
    /**
    <<IMPLEMENTATION>>

    Defines:   TData,
    TDataWriter,
    TDataReader,
    TTypeSupport

    Configure and implement 'ObjectState' support classes.

    Note: Only the #defined classes get defined
    */

    /* ----------------------------------------------------------------- */
    /* DDSDataWriter
    */

    /**
    <<IMPLEMENTATION >>

    Defines:   TDataWriter, TData
    */

    /* Requires */
    #define TTYPENAME   ObjectStateTYPENAME

    /* Defines */
    #define TDataWriter ObjectStateDataWriter
    #define TData       ::ObjectStateMsg::ObjectState

    #define RTI_ENABLE_TDATAWRITER_DATA_CONSTRUCTOR_METHODS
    #include "dds_cpp/generic/dds_cpp_data_TDataWriter.gen"
    #undef RTI_ENABLE_TDATAWRITER_DATA_CONSTRUCTOR_METHODS

    #undef TDataWriter
    #undef TData

    #undef TTYPENAME

    /* ----------------------------------------------------------------- */
    /* DDSDataReader
    */

    /**
    <<IMPLEMENTATION >>

    Defines:   TDataReader, TDataSeq, TData
    */

    /* Requires */
    #define TTYPENAME   ObjectStateTYPENAME

    /* Defines */
    #define TDataReader ObjectStateDataReader
    #define TDataSeq    ObjectStateSeq
    #define TData       ::ObjectStateMsg::ObjectState

    #define RTI_ENABLE_TDATAREADER_DATA_CONSISTENCY_CHECK_METHOD
    #include "dds_cpp/generic/dds_cpp_data_TDataReader.gen"
    #undef RTI_ENABLE_TDATAREADER_DATA_CONSISTENCY_CHECK_METHOD

    #undef TDataReader
    #undef TDataSeq
    #undef TData

    #undef TTYPENAME

    /* ----------------------------------------------------------------- */
    /* TypeSupport

    <<IMPLEMENTATION >>

    Requires:  TTYPENAME,
    TPlugin_new
    TPlugin_delete
    Defines:   TTypeSupport, TData, TDataReader, TDataWriter
    */

    /* Requires */
    #define TTYPENAME    ObjectStateTYPENAME
    #define TPlugin_new  ::ObjectStateMsg::ObjectStatePlugin_new
    #define TPlugin_delete  ::ObjectStateMsg::ObjectStatePlugin_delete

    /* Defines */
    #define TTypeSupport ObjectStateTypeSupport
    #define TData        ::ObjectStateMsg::ObjectState
    #define TDataReader  ObjectStateDataReader
    #define TDataWriter  ObjectStateDataWriter
    #define TGENERATE_SER_CODE
    #ifndef NDDS_STANDALONE_TYPE
    #define TGENERATE_TYPECODE
    #endif

    #include "dds_cpp/generic/dds_cpp_data_TTypeSupport.gen"

    #undef TTypeSupport
    #undef TData
    #undef TDataReader
    #undef TDataWriter
    #ifndef NDDS_STANDALONE_TYPE
    #undef TGENERATE_TYPECODE
    #endif
    #undef TGENERATE_SER_CODE
    #undef TTYPENAME
    #undef TPlugin_new
    #undef TPlugin_delete

} /* namespace ObjectStateMsg  */
