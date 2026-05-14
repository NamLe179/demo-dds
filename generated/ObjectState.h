

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ObjectState.idl
using RTI Code Generator (rtiddsgen) version 4.7.0.
The rtiddsgen tool is part of the RTI Connext DDS distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the Code Generator User's Manual.
*/

#ifndef ObjectState_1035534872_h
#define ObjectState_1035534872_h

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#include "rti/xcdr/Interpreter.hpp"
#include "cdr/cdr_typeCode.h"
#else
#include "ndds_standalone_type.h"
#endif

namespace ObjectStateMsg {

    extern const char *ObjectStateTYPENAME;

    struct ObjectStateSeq;
    #ifndef NDDS_STANDALONE_TYPE
    class ObjectStateTypeSupport;
    class ObjectStateDataWriter;
    class ObjectStateDataReader;
    #endif
    class ObjectState 
    {
      public:
        typedef struct ObjectStateSeq Seq;
        #ifndef NDDS_STANDALONE_TYPE
        typedef ObjectStateTypeSupport TypeSupport;
        typedef ObjectStateDataWriter DataWriter;
        typedef ObjectStateDataReader DataReader;
        #endif

        DDS_UnsignedLongLong frame_id;
        DDS_LongLong timestamp_ns;
        DDS_Long object_id;
        DDS_Float pos_x;
        DDS_Float pos_y;
        DDS_Float pos_z;
        DDS_Float vel_x;
        DDS_Float vel_y;
        DDS_Float vel_z;
        DDS_Float heading;
        DDS_Octet status;

    };
    #if defined(NDDS_USER_DLL_EXPORT) && defined(RTI_WIN32)
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __declspec(dllexport)
    #endif

    #if !defined(RTI_WIN32) && defined(NDDS_USER_SYMBOL_EXPORT)
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport __attribute__((visibility("default")))
    #endif

    #ifndef NDDS_STANDALONE_TYPE
    NDDSUSERDllExport DDS_TypeCode * ObjectState_get_typecode(void); /* Type code */
    NDDSUSERDllExport RTIXCdrTypePlugin *ObjectState_get_type_plugin_info(void);
    NDDSUSERDllExport RTIXCdrSampleAccessInfo *ObjectState_get_sample_access_info(void);
    NDDSUSERDllExport RTIXCdrSampleAccessInfo *ObjectState_get_sample_seq_access_info(void);
    #endif

    DDS_SEQUENCE(ObjectStateSeq, ObjectState);

    NDDSUSERDllExport
    RTIBool ObjectState_initialize(
        ObjectState* self);

    NDDSUSERDllExport
    RTIBool ObjectState_initialize_ex(
        ObjectState* self,RTIBool allocatePointers,RTIBool allocateMemory);

    NDDSUSERDllExport
    RTIBool ObjectState_initialize_w_params(
        ObjectState* self,
        const struct DDS_TypeAllocationParams_t * allocParams);  

    NDDSUSERDllExport
    RTIBool ObjectState_finalize_w_return(
        ObjectState* self);

    NDDSUSERDllExport
    void ObjectState_finalize(
        ObjectState* self);

    NDDSUSERDllExport
    void ObjectState_finalize_ex(
        ObjectState* self,RTIBool deletePointers);

    NDDSUSERDllExport
    void ObjectState_finalize_w_params(
        ObjectState* self,
        const struct DDS_TypeDeallocationParams_t * deallocParams);

    NDDSUSERDllExport
    void ObjectState_finalize_optional_members(
        ObjectState* self, RTIBool deletePointers);  

    NDDSUSERDllExport
    RTIBool ObjectState_copy(
        ObjectState* dst,
        const ObjectState* src);

    #if defined(NDDS_USER_DLL_EXPORT) || defined(NDDS_USER_SYMBOL_EXPORT)
    #undef NDDSUSERDllExport
    #define NDDSUSERDllExport
    #endif
} /* namespace ObjectStateMsg  */

#ifndef NDDS_STANDALONE_TYPE
namespace rti { 
    namespace xcdr {
        template <>
        struct type_code< ::ObjectStateMsg::ObjectState> {
            static const RTIXCdrTypeCode * get();
        };

    } 
}

#endif

#endif /* ObjectState */
