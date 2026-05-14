

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ObjectState.idl 
using RTI Code Generator (rtiddsgen) version 4.7.0.
The rtiddsgen tool is part of the RTI Connext DDS distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the Code Generator User's Manual.
*/

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#ifndef dds_c_log_impl_h              
#include "dds_c/dds_c_log_impl.h"                                
#endif 

#ifndef dds_c_log_infrastructure_h
#include "dds_c/dds_c_infrastructure_impl.h"       
#endif 

#ifndef cdr_type_h
#include "cdr/cdr_type.h"
#endif    

#include "osapi/osapi_atomic.h"
#else
#include "ndds_standalone_type.h"
#endif

#include "ObjectState.h"

#ifndef NDDS_STANDALONE_TYPE
#include "ObjectStatePlugin.h"
#endif

#include <new>

namespace ObjectStateMsg {

    /* ========================================================================= */
    const char *ObjectStateTYPENAME = "ObjectStateMsg::ObjectState";

    #ifndef NDDS_STANDALONE_TYPE

    DDS_TypeCode * ObjectState_get_typecode(void)
    {
        static RTI_ATOMIC(RTIBool) is_initialized;

        static DDS_TypeCode_Member ObjectState_g_tc_members[11]=
        {

            {
                (char *)"frame_id",/* Member name */
                {
                    0,/* Representation ID */
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                RTICdrTypeCodeAnnotations_INITIALIZER
            }, 
            {
                (char *)"timestamp_ns",/* Member name */
                {
                    1,/* Representation ID */
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                RTICdrTypeCodeAnnotations_INITIALIZER
            }, 
            {
                (char *)"object_id",/* Member name */
                {
                    2,/* Representation ID */
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_KEY_MEMBER , /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                RTICdrTypeCodeAnnotations_INITIALIZER
            }, 
            {
                (char *)"pos_x",/* Member name */
                {
                    3,/* Representation ID */
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                RTICdrTypeCodeAnnotations_INITIALIZER
            }, 
            {
                (char *)"pos_y",/* Member name */
                {
                    4,/* Representation ID */
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                RTICdrTypeCodeAnnotations_INITIALIZER
            }, 
            {
                (char *)"pos_z",/* Member name */
                {
                    5,/* Representation ID */
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                RTICdrTypeCodeAnnotations_INITIALIZER
            }, 
            {
                (char *)"vel_x",/* Member name */
                {
                    6,/* Representation ID */
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                RTICdrTypeCodeAnnotations_INITIALIZER
            }, 
            {
                (char *)"vel_y",/* Member name */
                {
                    7,/* Representation ID */
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                RTICdrTypeCodeAnnotations_INITIALIZER
            }, 
            {
                (char *)"vel_z",/* Member name */
                {
                    8,/* Representation ID */
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                RTICdrTypeCodeAnnotations_INITIALIZER
            }, 
            {
                (char *)"heading",/* Member name */
                {
                    9,/* Representation ID */
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                RTICdrTypeCodeAnnotations_INITIALIZER
            }, 
            {
                (char *)"status",/* Member name */
                {
                    10,/* Representation ID */
                    DDS_BOOLEAN_FALSE,/* Is a pointer? */
                    -1, /* Bitfield bits */
                    NULL/* Member type code is assigned later */
                },
                0, /* Ignored */
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
                DDS_PUBLIC_MEMBER,/* Member visibility */
                RTICdrTypeCodeAnnotations_INITIALIZER
            }
        };

        static DDS_TypeCode ObjectState_g_tc =
        {{
                DDS_TK_STRUCT| DDS_TK_FINAL_EXTENSIBILITY, /* Kind */
                DDS_BOOLEAN_FALSE, /* Ignored */
                -1, /*Ignored*/
                (char *)"ObjectStateMsg::ObjectState", /* Name */
                NULL, /* Ignored */ 
                0, /* Ignored */
                0, /* Ignored */
                NULL, /* Ignored */
                11, /* Number of members */
                ObjectState_g_tc_members, /* Members */
                DDS_VM_NONE, /* Ignored */
                RTICdrTypeCodeAnnotations_INITIALIZER,
                DDS_BOOLEAN_TRUE, /* _isCopyable */
                NULL, /* _sampleAccessInfo: assigned later */
                NULL /* _typePlugin: assigned later */
            }}; /* Type code for ObjectState*/

        if (RTIOsapiAtomic_load32(&is_initialized, RTI_OSAPI_ATOMIC_MEMORY_ORDER_ACQUIRE)) {
            return &ObjectState_g_tc;
        }

        ObjectState_g_tc._data._annotations._allowedDataRepresentationMask = 5;

        ObjectState_g_tc_members[0]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_ulonglong_w_new;
        ObjectState_g_tc_members[1]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_longlong_w_new;
        ObjectState_g_tc_members[2]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_long_w_new;
        ObjectState_g_tc_members[3]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float_w_new;
        ObjectState_g_tc_members[4]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float_w_new;
        ObjectState_g_tc_members[5]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float_w_new;
        ObjectState_g_tc_members[6]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float_w_new;
        ObjectState_g_tc_members[7]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float_w_new;
        ObjectState_g_tc_members[8]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float_w_new;
        ObjectState_g_tc_members[9]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_float_w_new;
        ObjectState_g_tc_members[10]._representation._typeCode =  (RTICdrTypeCode *)&DDS_g_tc_octet_w_new;

        /* Initialize the values for member annotations. */
        ObjectState_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_ULONGLONG;
        ObjectState_g_tc_members[0]._annotations._defaultValue._u.ulong_long_value = 0ull;
        ObjectState_g_tc_members[0]._annotations._minValue._d = RTI_XCDR_TK_ULONGLONG;
        ObjectState_g_tc_members[0]._annotations._minValue._u.ulong_long_value = RTIXCdrUnsignedLongLong_MIN;
        ObjectState_g_tc_members[0]._annotations._maxValue._d = RTI_XCDR_TK_ULONGLONG;
        ObjectState_g_tc_members[0]._annotations._maxValue._u.ulong_long_value = RTIXCdrUnsignedLongLong_MAX;
        ObjectState_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_LONGLONG;
        ObjectState_g_tc_members[1]._annotations._defaultValue._u.long_long_value = 0ll;
        ObjectState_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_LONGLONG;
        ObjectState_g_tc_members[1]._annotations._minValue._u.long_long_value = RTIXCdrLongLong_MIN;
        ObjectState_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_LONGLONG;
        ObjectState_g_tc_members[1]._annotations._maxValue._u.long_long_value = RTIXCdrLongLong_MAX;
        ObjectState_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
        ObjectState_g_tc_members[2]._annotations._defaultValue._u.long_value = 0;
        ObjectState_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_LONG;
        ObjectState_g_tc_members[2]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
        ObjectState_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
        ObjectState_g_tc_members[2]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;
        ObjectState_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
        ObjectState_g_tc_members[3]._annotations._defaultValue._u.float_value = 0.0f;
        ObjectState_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
        ObjectState_g_tc_members[3]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
        ObjectState_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
        ObjectState_g_tc_members[3]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
        ObjectState_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
        ObjectState_g_tc_members[4]._annotations._defaultValue._u.float_value = 0.0f;
        ObjectState_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
        ObjectState_g_tc_members[4]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
        ObjectState_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
        ObjectState_g_tc_members[4]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
        ObjectState_g_tc_members[5]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
        ObjectState_g_tc_members[5]._annotations._defaultValue._u.float_value = 0.0f;
        ObjectState_g_tc_members[5]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
        ObjectState_g_tc_members[5]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
        ObjectState_g_tc_members[5]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
        ObjectState_g_tc_members[5]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
        ObjectState_g_tc_members[6]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
        ObjectState_g_tc_members[6]._annotations._defaultValue._u.float_value = 0.0f;
        ObjectState_g_tc_members[6]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
        ObjectState_g_tc_members[6]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
        ObjectState_g_tc_members[6]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
        ObjectState_g_tc_members[6]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
        ObjectState_g_tc_members[7]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
        ObjectState_g_tc_members[7]._annotations._defaultValue._u.float_value = 0.0f;
        ObjectState_g_tc_members[7]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
        ObjectState_g_tc_members[7]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
        ObjectState_g_tc_members[7]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
        ObjectState_g_tc_members[7]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
        ObjectState_g_tc_members[8]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
        ObjectState_g_tc_members[8]._annotations._defaultValue._u.float_value = 0.0f;
        ObjectState_g_tc_members[8]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
        ObjectState_g_tc_members[8]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
        ObjectState_g_tc_members[8]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
        ObjectState_g_tc_members[8]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
        ObjectState_g_tc_members[9]._annotations._defaultValue._d = RTI_XCDR_TK_FLOAT;
        ObjectState_g_tc_members[9]._annotations._defaultValue._u.float_value = 0.0f;
        ObjectState_g_tc_members[9]._annotations._minValue._d = RTI_XCDR_TK_FLOAT;
        ObjectState_g_tc_members[9]._annotations._minValue._u.float_value = RTIXCdrFloat_MIN;
        ObjectState_g_tc_members[9]._annotations._maxValue._d = RTI_XCDR_TK_FLOAT;
        ObjectState_g_tc_members[9]._annotations._maxValue._u.float_value = RTIXCdrFloat_MAX;
        ObjectState_g_tc_members[10]._annotations._defaultValue._d = RTI_XCDR_TK_OCTET;
        ObjectState_g_tc_members[10]._annotations._defaultValue._u.octet_value = 0;
        ObjectState_g_tc_members[10]._annotations._minValue._d = RTI_XCDR_TK_OCTET;
        ObjectState_g_tc_members[10]._annotations._minValue._u.octet_value = RTIXCdrOctet_MIN;
        ObjectState_g_tc_members[10]._annotations._maxValue._d = RTI_XCDR_TK_OCTET;
        ObjectState_g_tc_members[10]._annotations._maxValue._u.octet_value = RTIXCdrOctet_MAX;

        ObjectState_g_tc._data._sampleAccessInfo =
        ObjectState_get_sample_access_info();
        ObjectState_g_tc._data._typePlugin =
        ObjectState_get_type_plugin_info();

        RTIOsapiAtomic_store32(
            &is_initialized,
            RTI_TRUE,
            RTI_OSAPI_ATOMIC_MEMORY_ORDER_RELEASE);

        return &ObjectState_g_tc;
    }

    #define TSeq ObjectStateSeq
    #define T ObjectState
    #include "dds_cpp/generic/dds_cpp_data_TInterpreterSupport.gen"
    #undef T
    #undef TSeq

    RTIXCdrSampleAccessInfo *ObjectState_get_sample_seq_access_info()
    {
        static RTIXCdrSampleAccessInfo ObjectState_g_seqSampleAccessInfo = {
            RTI_XCDR_TYPE_BINDING_CPP, \
            {sizeof(ObjectStateSeq),0,0,0}, \
            RTI_XCDR_FALSE, \
            DDS_Sequence_get_member_value_pointer, \
            ObjectStateSeq_set_member_element_count, \
            NULL, \
            NULL, \
            NULL \
        };

        return &ObjectState_g_seqSampleAccessInfo;
    }

    RTIXCdrSampleAccessInfo *ObjectState_get_sample_access_info()
    {
        static RTI_ATOMIC(RTIBool) is_initialized;

        ::ObjectStateMsg::ObjectState *sample;

        static RTIXCdrMemberAccessInfo ObjectState_g_memberAccessInfos[11] =
        {RTIXCdrMemberAccessInfo_INITIALIZER};

        static RTIXCdrSampleAccessInfo ObjectState_g_sampleAccessInfo =
        RTIXCdrSampleAccessInfo_INITIALIZER;

        if (RTIOsapiAtomic_load32(
            &is_initialized,
            RTI_OSAPI_ATOMIC_MEMORY_ORDER_ACQUIRE)) {
            return (RTIXCdrSampleAccessInfo*) &ObjectState_g_sampleAccessInfo;
        }

        RTIXCdrHeap_allocateStruct(
            &sample,
            ::ObjectStateMsg::ObjectState);
        if (sample == NULL) {
            return NULL;
        }

        ObjectState_g_memberAccessInfos[0].bindingMemberValueOffset[0] =
        (RTIXCdrUnsignedLong) ((char *)&sample->frame_id - (char *)sample);

        ObjectState_g_memberAccessInfos[1].bindingMemberValueOffset[0] =
        (RTIXCdrUnsignedLong) ((char *)&sample->timestamp_ns - (char *)sample);

        ObjectState_g_memberAccessInfos[2].bindingMemberValueOffset[0] =
        (RTIXCdrUnsignedLong) ((char *)&sample->object_id - (char *)sample);

        ObjectState_g_memberAccessInfos[3].bindingMemberValueOffset[0] =
        (RTIXCdrUnsignedLong) ((char *)&sample->pos_x - (char *)sample);

        ObjectState_g_memberAccessInfos[4].bindingMemberValueOffset[0] =
        (RTIXCdrUnsignedLong) ((char *)&sample->pos_y - (char *)sample);

        ObjectState_g_memberAccessInfos[5].bindingMemberValueOffset[0] =
        (RTIXCdrUnsignedLong) ((char *)&sample->pos_z - (char *)sample);

        ObjectState_g_memberAccessInfos[6].bindingMemberValueOffset[0] =
        (RTIXCdrUnsignedLong) ((char *)&sample->vel_x - (char *)sample);

        ObjectState_g_memberAccessInfos[7].bindingMemberValueOffset[0] =
        (RTIXCdrUnsignedLong) ((char *)&sample->vel_y - (char *)sample);

        ObjectState_g_memberAccessInfos[8].bindingMemberValueOffset[0] =
        (RTIXCdrUnsignedLong) ((char *)&sample->vel_z - (char *)sample);

        ObjectState_g_memberAccessInfos[9].bindingMemberValueOffset[0] =
        (RTIXCdrUnsignedLong) ((char *)&sample->heading - (char *)sample);

        ObjectState_g_memberAccessInfos[10].bindingMemberValueOffset[0] =
        (RTIXCdrUnsignedLong) ((char *)&sample->status - (char *)sample);

        ObjectState_g_sampleAccessInfo.memberAccessInfos =
        ObjectState_g_memberAccessInfos;

        {
            size_t candidateTypeSize = sizeof(ObjectState);

            if (candidateTypeSize > RTIXCdrLong_MAX) {
                ObjectState_g_sampleAccessInfo.typeSize[0] =
                RTIXCdrLong_MAX;
            } else {
                ObjectState_g_sampleAccessInfo.typeSize[0] =
                (RTIXCdrUnsignedLong) candidateTypeSize;
            }
        }

        ObjectState_g_sampleAccessInfo.useGetMemberValueOnlyWithRef =
        RTI_XCDR_TRUE;

        ObjectState_g_sampleAccessInfo.getMemberValuePointerFcn =
        ObjectState_get_member_value_pointer;

        ObjectState_g_sampleAccessInfo.languageBinding =
        RTI_XCDR_TYPE_BINDING_CPP ;

        RTIXCdrHeap_freeStruct(sample);
        RTIOsapiAtomic_store32(
            &is_initialized,
            RTI_TRUE,
            RTI_OSAPI_ATOMIC_MEMORY_ORDER_RELEASE);
        return (RTIXCdrSampleAccessInfo*) &ObjectState_g_sampleAccessInfo;
    }
    RTIXCdrTypePlugin *ObjectState_get_type_plugin_info()
    {
        static RTIXCdrTypePlugin ObjectState_g_typePlugin =
        {
            NULL, /* serialize */
            NULL, /* serialize_key */
            NULL, /* deserialize_sample */
            NULL, /* deserialize_key_sample */
            NULL, /* skip */
            NULL, /* get_serialized_sample_size */
            NULL, /* get_serialized_sample_max_size_ex */
            NULL, /* get_serialized_key_max_size_ex */
            NULL, /* get_serialized_sample_min_size */
            NULL, /* serialized_sample_to_key */
            (RTIXCdrTypePluginInitializeSampleFunction)
            ::ObjectStateMsg::ObjectState_initialize_ex,
            NULL,
            (RTIXCdrTypePluginFinalizeSampleFunction)
            ::ObjectStateMsg::ObjectState_finalize_w_return,
            NULL,
            NULL
        };

        return &ObjectState_g_typePlugin;
    }
    #endif

    RTIBool ObjectState_initialize(
        ObjectState* sample)
    {
        return ::ObjectStateMsg::ObjectState_initialize_ex(
            sample, 
            RTI_TRUE, 
            RTI_TRUE);
    }
    RTIBool ObjectState_initialize_w_params(
        ObjectState *sample,
        const struct DDS_TypeAllocationParams_t *allocParams)
    {

        if (sample == NULL) {
            return RTI_FALSE;
        }
        if (allocParams == NULL) {
            return RTI_FALSE;
        }

        sample->frame_id = 0ull;

        sample->timestamp_ns = 0ll;

        sample->object_id = 0;

        sample->pos_x = 0.0f;

        sample->pos_y = 0.0f;

        sample->pos_z = 0.0f;

        sample->vel_x = 0.0f;

        sample->vel_y = 0.0f;

        sample->vel_z = 0.0f;

        sample->heading = 0.0f;

        sample->status = 0;

        return RTI_TRUE;
    }
    RTIBool ObjectState_initialize_ex(
        ObjectState *sample,
        RTIBool allocatePointers, 
        RTIBool allocateMemory)
    {

        struct DDS_TypeAllocationParams_t allocParams =
        DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

        allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
        allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

        return ::ObjectStateMsg::ObjectState_initialize_w_params(
            sample,
            &allocParams);
    }

    RTIBool ObjectState_finalize_w_return(
        ObjectState* sample)
    {
        ::ObjectStateMsg::ObjectState_finalize_ex(sample, RTI_TRUE);

        return RTI_TRUE;
    }

    void ObjectState_finalize(
        ObjectState* sample)
    {  
        ::ObjectStateMsg::ObjectState_finalize_ex(
            sample, 
            RTI_TRUE);
    }

    void ObjectState_finalize_ex(
        ObjectState *sample,
        RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParams =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

        if (sample==NULL) {
            return;
        } 

        deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

        ::ObjectStateMsg::ObjectState_finalize_w_params(
            sample,
            &deallocParams);
    }

    void ObjectState_finalize_w_params(
        ObjectState *sample,
        const struct DDS_TypeDeallocationParams_t *deallocParams)
    {
        if (sample==NULL) {
            return;
        }

        if (deallocParams == NULL) {
            return;
        }

    }

    void ObjectState_finalize_optional_members(
        ObjectState* sample, RTIBool deletePointers)
    {
        struct DDS_TypeDeallocationParams_t deallocParamsTmp =
        DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
        struct DDS_TypeDeallocationParams_t * deallocParams =
        &deallocParamsTmp;

        if (sample==NULL) {
            return;
        } 
        RTIOsapiUtility_unusedParameter(deallocParams);

        deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
        deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

    }

    RTIBool ObjectState_copy(
        ObjectState* dst,
        const ObjectState* src)
    {
        try {

            if (dst == NULL || src == NULL) {
                return RTI_FALSE;
            }

            if (!RTICdrType_copyUnsignedLongLong (
                &dst->frame_id, 
                &src->frame_id)) { 
                return RTI_FALSE;
            }
            if (!RTICdrType_copyLongLong (
                &dst->timestamp_ns, 
                &src->timestamp_ns)) { 
                return RTI_FALSE;
            }
            if (!RTICdrType_copyLong (
                &dst->object_id, 
                &src->object_id)) { 
                return RTI_FALSE;
            }
            if (!RTICdrType_copyFloat (
                &dst->pos_x, 
                &src->pos_x)) { 
                return RTI_FALSE;
            }
            if (!RTICdrType_copyFloat (
                &dst->pos_y, 
                &src->pos_y)) { 
                return RTI_FALSE;
            }
            if (!RTICdrType_copyFloat (
                &dst->pos_z, 
                &src->pos_z)) { 
                return RTI_FALSE;
            }
            if (!RTICdrType_copyFloat (
                &dst->vel_x, 
                &src->vel_x)) { 
                return RTI_FALSE;
            }
            if (!RTICdrType_copyFloat (
                &dst->vel_y, 
                &src->vel_y)) { 
                return RTI_FALSE;
            }
            if (!RTICdrType_copyFloat (
                &dst->vel_z, 
                &src->vel_z)) { 
                return RTI_FALSE;
            }
            if (!RTICdrType_copyFloat (
                &dst->heading, 
                &src->heading)) { 
                return RTI_FALSE;
            }
            if (!RTICdrType_copyOctet (
                &dst->status, 
                &src->status)) { 
                return RTI_FALSE;
            }

            return RTI_TRUE;
        } catch (const std::bad_alloc&) {
            return RTI_FALSE;
        }
    }

    /**
    * <<IMPLEMENTATION>>
    *
    * Defines:  TSeq, T
    *
    * Configure and implement 'ObjectState' sequence class.
    */
    #define T ObjectState
    #define TSeq ObjectStateSeq

    #define T_initialize_w_params ::ObjectStateMsg::ObjectState_initialize_w_params

    #define T_finalize_w_params   ::ObjectStateMsg::ObjectState_finalize_w_params
    #define T_copy       ::ObjectStateMsg::ObjectState_copy

    #ifndef NDDS_STANDALONE_TYPE
    #include "dds_c/generic/dds_c_sequence_TSeq.gen"
    #include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
    #else
    #include "dds_c_sequence_TSeq.gen"
    #include "dds_cpp_sequence_TSeq.gen"
    #endif

    #undef T_copy
    #undef T_finalize_w_params

    #undef T_initialize_w_params

    #undef TSeq
    #undef T

} /* namespace ObjectStateMsg  */

#ifndef NDDS_STANDALONE_TYPE
namespace rti { 
    namespace xcdr {
        const RTIXCdrTypeCode * type_code< ::ObjectStateMsg::ObjectState>::get() 
        {
            return (const RTIXCdrTypeCode *) ::ObjectStateMsg::ObjectState_get_typecode();
        }

    } 
}
#endif
