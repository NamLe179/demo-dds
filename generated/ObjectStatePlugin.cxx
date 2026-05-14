
/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ObjectState.idl
using RTI Code Generator (rtiddsgen) version 4.7.0.
The rtiddsgen tool is part of the RTI Connext DDS distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the Code Generator User's Manual.
*/

#include <string.h>

#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif

#ifndef cdr_type_h
#include "cdr/cdr_type.h"
#endif

#ifndef cdr_type_object_h
#include "cdr/cdr_typeObject.h"
#endif

#ifndef cdr_encapsulation_h
#include "cdr/cdr_encapsulation.h"
#endif

#ifndef cdr_stream_h
#include "cdr/cdr_stream.h"
#endif

#include "xcdr/xcdr_interpreter.h"
#include "xcdr/xcdr_stream.h"

#ifndef cdr_log_h
#include "cdr/cdr_log.h"
#endif

#ifndef pres_typePlugin_h
#include "pres/pres_typePlugin.h"
#endif

#include "dds_c/dds_c_typecode_impl.h"

#define RTI_CDR_CURRENT_SUBMODULE RTI_CDR_SUBMODULE_MASK_STREAM

#include <new>

#include "ObjectStatePlugin.h"

namespace ObjectStateMsg {

    /* ----------------------------------------------------------------------------
    *  Type ObjectState
    * -------------------------------------------------------------------------- */

    /* -----------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------- */

    ObjectState*
    ObjectStatePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params)
    {
        ObjectState *sample = NULL;

        if (alloc_params == NULL) {
            return NULL;
        } else if(!alloc_params->allocate_memory) {
            RTICdrLog_exception(&RTI_CDR_LOG_TYPE_OBJECT_NOT_ASSIGNABLE_ss,
            "alloc_params->allocate_memory","false");
            return NULL;
        }

        sample = new (std::nothrow) ObjectState();
        if (sample == NULL) {
            return NULL;
        }

        if (!::ObjectStateMsg::ObjectState_initialize_w_params(sample,alloc_params)) {
            struct DDS_TypeDeallocationParams_t deallocParams =
            DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
            deallocParams.delete_pointers = alloc_params->allocate_pointers;
            deallocParams.delete_optional_members = alloc_params->allocate_pointers;
            /* Coverity reports a possible uninit_use_in_call that will happen if the
            allocation fails. But if the allocation fails then sample == null and
            the method will return before reach this point.*/
            /* Coverity reports a possible overwrite_var on the members of the sample.
            It is a false positive since all the pointers are freed before assigning
            null to them. */
            /* coverity[uninit_use_in_call : FALSE] */
            /* coverity[overwrite_var : FALSE] */
            ::ObjectStateMsg::ObjectState_finalize_w_params(sample, &deallocParams);
            /* Coverity reports a possible leaked_storage on the sample members when
            freeing sample. It is a false positive since all the members' memory
            is freed in the call "::ObjectStateMsg::ObjectState_finalize_ex" */
            /* coverity[leaked_storage : FALSE] */
            delete  sample;
            sample=NULL;
        }
        return sample;
    }

    ObjectState *
    ObjectStatePluginSupport_create_data_ex(RTIBool allocate_pointers)
    {
        ObjectState *sample = NULL;

        sample = new (std::nothrow) ObjectState();

        if(sample == NULL) {
            return NULL;
        }

        /* coverity[example_checked : FALSE] */
        if (!::ObjectStateMsg::ObjectState_initialize_ex(sample,allocate_pointers, RTI_TRUE)) {
            /* Coverity reports a possible uninit_use_in_call that will happen if the
            new fails. But if new fails then sample == null and the method will
            return before reach this point. */
            /* Coverity reports a possible overwrite_var on the members of the sample.
            It is a false positive since all the pointers are freed before assigning
            null to them. */
            /* coverity[uninit_use_in_call : FALSE] */
            /* coverity[overwrite_var : FALSE] */
            ::ObjectStateMsg::ObjectState_finalize_ex(sample, RTI_TRUE);
            /* Coverity reports a possible leaked_storage on the sample members when
            freeing sample. It is a false positive since all the members' memory
            is freed in the call "::ObjectStateMsg::ObjectState_finalize_ex" */
            /* coverity[leaked_storage : FALSE] */
            delete  sample;
            sample=NULL;
        }

        return sample;
    }

    void *
    ObjectStatePluginSupport_create_dataI(void)
    {
        return ::ObjectStateMsg::ObjectStatePluginSupport_create_data_ex(RTI_TRUE);
    }

    ObjectState *
    ObjectStatePluginSupport_create_data(void)
    {
        return (ObjectState *) ObjectStatePluginSupport_create_dataI();
    }

    void
    ObjectStatePluginSupport_destroy_data_w_params(
        ObjectState *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params) {
        ::ObjectStateMsg::ObjectState_finalize_w_params(sample,dealloc_params);

        delete  sample;
    }

    void
    ObjectStatePluginSupport_destroy_data_ex(
        ObjectState *sample,RTIBool deallocate_pointers) {
        ::ObjectStateMsg::ObjectState_finalize_ex(sample,deallocate_pointers);

        delete  sample;
    }

    void
    ObjectStatePluginSupport_destroy_data(
        ObjectState *sample) {

        ::ObjectStateMsg::ObjectStatePluginSupport_destroy_data_ex(sample,RTI_TRUE);

    }

    void
    ObjectStatePluginSupport_destroy_dataI(
        void *sample)
    {
        ::ObjectStateMsg::ObjectStatePluginSupport_destroy_data((ObjectState *) sample);
    }

    RTIBool
    ObjectStatePluginSupport_copy_data(
        ObjectState *dst,
        const ObjectState *src)
    {
        return ::ObjectStateMsg::ObjectState_copy(dst,(const ObjectState*) src);
    }

    void
    ObjectStatePluginSupport_print_data(
        const ObjectState *sample,
        const char *desc,
        unsigned int indent_level)
    {

        RTICdrType_printIndent(indent_level);

        if (desc != NULL) {
            RTILogParamString_printPlain("%s:\n", desc);
        } else {
            RTILogParamString_printPlain("\n");
        }

        if (sample == NULL) {
            RTILogParamString_printPlain("NULL\n");
            return;
        }

        RTICdrType_printUnsignedLongLong(
            &sample->frame_id,
            "frame_id",
            RTIOsapiUtility_uInt32Plus1(indent_level));

        RTICdrType_printLongLong(
            &sample->timestamp_ns,
            "timestamp_ns",
            RTIOsapiUtility_uInt32Plus1(indent_level));

        RTICdrType_printLong(
            &sample->object_id,
            "object_id",
            RTIOsapiUtility_uInt32Plus1(indent_level));

        RTICdrType_printFloat(
            &sample->pos_x,
            "pos_x",
            RTIOsapiUtility_uInt32Plus1(indent_level));

        RTICdrType_printFloat(
            &sample->pos_y,
            "pos_y",
            RTIOsapiUtility_uInt32Plus1(indent_level));

        RTICdrType_printFloat(
            &sample->pos_z,
            "pos_z",
            RTIOsapiUtility_uInt32Plus1(indent_level));

        RTICdrType_printFloat(
            &sample->vel_x,
            "vel_x",
            RTIOsapiUtility_uInt32Plus1(indent_level));

        RTICdrType_printFloat(
            &sample->vel_y,
            "vel_y",
            RTIOsapiUtility_uInt32Plus1(indent_level));

        RTICdrType_printFloat(
            &sample->vel_z,
            "vel_z",
            RTIOsapiUtility_uInt32Plus1(indent_level));

        RTICdrType_printFloat(
            &sample->heading,
            "heading",
            RTIOsapiUtility_uInt32Plus1(indent_level));

        RTICdrType_printOctet(
            &sample->status,
            "status",
            RTIOsapiUtility_uInt32Plus1(indent_level));

    }

    ObjectState *
    ObjectStatePluginSupport_create_key_ex(RTIBool allocate_pointers){
        ObjectState *key = NULL;

        key = new (std::nothrow) ObjectStateKeyHolder();

        ::ObjectStateMsg::ObjectState_initialize_ex(key,allocate_pointers, RTI_TRUE);

        return key;
    }

    void *
    ObjectStatePluginSupport_create_keyI(void)
    {
        return ::ObjectStateMsg::ObjectStatePluginSupport_create_key_ex(RTI_TRUE);
    }

    ObjectState *
    ObjectStatePluginSupport_create_key(void)
    {
        return (ObjectState *) ObjectStatePluginSupport_create_keyI();
    }

    void
    ObjectStatePluginSupport_destroy_key_ex(
        ObjectStateKeyHolder *key,RTIBool deallocate_pointers)
    {
        ::ObjectStateMsg::ObjectState_finalize_ex(key,deallocate_pointers);

        delete  key;
    }

    void
    ObjectStatePluginSupport_destroy_key(
        ObjectStateKeyHolder *key) {

        ::ObjectStateMsg::ObjectStatePluginSupport_destroy_key_ex(key,RTI_TRUE);

    }

    void
    ObjectStatePluginSupport_destroy_keyI(
        void *key)
    {
        ::ObjectStateMsg::ObjectStatePluginSupport_destroy_key((ObjectStateKeyHolder *) key);
    }

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    PRESTypePluginParticipantData
    ObjectStatePlugin_on_participant_attached(
        void *registration_data,
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration,
        void *container_plugin_context,
        RTICdrTypeCode *type_code)
    {
        struct RTIXCdrInterpreterPrograms *programs = NULL;
        struct RTIXCdrInterpreterProgramsGenProperty programProperty =
        RTIXCdrInterpreterProgramsGenProperty_INITIALIZER;
        struct PRESTypePluginDefaultParticipantData *pd = NULL;

        RTIOsapiUtility_unusedParameter(registration_data);
        RTIOsapiUtility_unusedParameter(participant_info);
        RTIOsapiUtility_unusedParameter(top_level_registration);
        RTIOsapiUtility_unusedParameter(container_plugin_context);
        RTIOsapiUtility_unusedParameter(type_code);

        if (!RTIXCdrXTypesComplianceMask_verifyGeneratedXTypesMask(0x0000018C)) {
            return NULL;
        }

        pd = (struct PRESTypePluginDefaultParticipantData *)
        PRESTypePluginDefaultParticipantData_new(participant_info);

        programProperty.generateV1Encapsulation = RTI_XCDR_TRUE;
        programProperty.generateV2Encapsulation = RTI_XCDR_TRUE;

        programProperty.resolveAlias = RTI_XCDR_TRUE;
        programProperty.inlineStruct = RTI_XCDR_TRUE;
        programProperty.optimizeEnum = RTI_XCDR_TRUE;
        programProperty.unboundedSize = RTIXCdrLong_MAX;

        programs = DDS_TypeCodeFactory_assert_programs_in_global_list(
            DDS_TypeCodeFactory_get_instance(),
            ObjectState_get_typecode(),
            &programProperty,
            RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN);
        if (programs == NULL) {
            PRESTypePluginDefaultParticipantData_delete(
                (PRESTypePluginParticipantData) pd);
            return NULL;
        }

        pd->programs = programs;
        return (PRESTypePluginParticipantData)pd;
    }

    void
    ObjectStatePlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data)
    {
        if (participant_data != NULL) {
            struct PRESTypePluginDefaultParticipantData *pd =
            (struct PRESTypePluginDefaultParticipantData *)participant_data;

            if (pd->programs != NULL) {
                DDS_TypeCodeFactory_remove_programs_from_global_list(
                    DDS_TypeCodeFactory_get_instance(),
                    pd->programs);
                pd->programs = NULL;
            }
            PRESTypePluginDefaultParticipantData_delete(participant_data);
        }
    }

    PRESTypePluginEndpointData
    ObjectStatePlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration,
        void *containerPluginContext)
    {
        PRESTypePluginEndpointData epd = NULL;
        unsigned int serializedSampleMaxSize = 0;

        unsigned int serializedKeyMaxSize = 0;
        unsigned int serializedKeyMaxSizeV2 = 0;

        RTIOsapiUtility_unusedParameter(top_level_registration);
        RTIOsapiUtility_unusedParameter(containerPluginContext);

        if (participant_data == NULL) {
            return NULL;
        }

        epd = PRESTypePluginDefaultEndpointData_new(
            participant_data,
            endpoint_info,
            ::ObjectStateMsg::ObjectStatePluginSupport_create_dataI,
            ::ObjectStateMsg::ObjectStatePluginSupport_destroy_dataI,
            ::ObjectStateMsg::ObjectStatePluginSupport_create_keyI ,            ::ObjectStateMsg::ObjectStatePluginSupport_destroy_keyI);

        if (epd == NULL) {
            return NULL;
        }

        serializedKeyMaxSize =  ::ObjectStateMsg::ObjectStatePlugin_get_serialized_key_max_size(
            epd,RTI_FALSE,RTI_CDR_ENCAPSULATION_ID_CDR_BE,0);
        serializedKeyMaxSizeV2 =  ObjectStatePlugin_get_serialized_key_max_size_for_keyhash(
            epd,
            RTI_CDR_ENCAPSULATION_ID_CDR2_BE,
            0);

        if(!PRESTypePluginDefaultEndpointData_createMD5StreamWithInfo(
            epd,
            endpoint_info,
            serializedKeyMaxSize,
            serializedKeyMaxSizeV2))
        {
            PRESTypePluginDefaultEndpointData_delete(epd);
            return NULL;
        }

        if (endpoint_info->endpointKind == PRES_TYPEPLUGIN_ENDPOINT_WRITER) {
            serializedSampleMaxSize = ::ObjectStateMsg::ObjectStatePlugin_get_serialized_sample_max_size(
                epd,RTI_FALSE,RTI_CDR_ENCAPSULATION_ID_CDR_BE,0);
            PRESTypePluginDefaultEndpointData_setMaxSizeSerializedSample(epd, serializedSampleMaxSize);

            if (PRESTypePluginDefaultEndpointData_createWriterPool(
                epd,
                endpoint_info,
                (PRESTypePluginGetSerializedSampleMaxSizeFunction)
                ::ObjectStateMsg::ObjectStatePlugin_get_serialized_sample_max_size, epd,
                (PRESTypePluginGetSerializedSampleSizeFunction)
                PRESTypePlugin_interpretedGetSerializedSampleSize,
                epd) == RTI_FALSE) {
                PRESTypePluginDefaultEndpointData_delete(epd);
                return NULL;
            }
        }

        return epd;
    }

    void
    ObjectStatePlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data)
    {
        PRESTypePluginDefaultEndpointData_delete(endpoint_data);
    }

    void
    ObjectStatePlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        ObjectState *sample,
        void *handle)
    {
        ObjectState_finalize_optional_members(sample, RTI_TRUE);

        PRESTypePluginDefaultEndpointData_returnSample(
            endpoint_data, sample, handle);
    }

    void ObjectStatePlugin_finalize_optional_members(
        PRESTypePluginEndpointData endpoint_data,
        ObjectState* sample,
        RTIBool deletePointers)
    {
        RTIOsapiUtility_unusedParameter(endpoint_data);
        ObjectState_finalize_optional_members(
            sample, deletePointers);
    }

    RTIBool
    ObjectStatePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        ObjectState *dst,
        const ObjectState *src)
    {
        RTIOsapiUtility_unusedParameter(endpoint_data);
        return ::ObjectStateMsg::ObjectStatePluginSupport_copy_data(dst,src);
    }

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */
    unsigned int
    ObjectStatePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    RTIBool
    ObjectStatePlugin_serialize_to_cdr_buffer_ex(
        char *buffer,
        unsigned int *length,
        const ObjectState *sample,
        DDS_DataRepresentationId_t representation)
    {
        RTIEncapsulationId encapsulationId = RTI_CDR_ENCAPSULATION_ID_INVALID;
        struct RTICdrStream cdrStream;
        struct PRESTypePluginDefaultEndpointData epd;
        RTIBool result;
        struct PRESTypePluginDefaultParticipantData pd;
        struct RTIXCdrTypePluginProgramContext defaultProgramContext =
        RTIXCdrTypePluginProgramContext_INTIALIZER;
        struct PRESTypePlugin plugin;

        if (length == NULL) {
            return RTI_FALSE;
        }

        RTIOsapiMemory_zero(&epd, sizeof(struct PRESTypePluginDefaultEndpointData));
        epd.programContext = defaultProgramContext;
        epd._participantData = &pd;
        epd.typePlugin = &plugin;
        epd.programContext.endpointPluginData = &epd;
        plugin.typeCode = (struct RTICdrTypeCode *)
        ObjectState_get_typecode();
        pd.programs = ObjectStatePlugin_get_programs();
        if (pd.programs == NULL) {
            return RTI_FALSE;
        }

        encapsulationId = DDS_TypeCode_get_native_encapsulation(
            (DDS_TypeCode *) plugin.typeCode,
            representation);
        if (encapsulationId == RTI_CDR_ENCAPSULATION_ID_INVALID) {
            return RTI_FALSE;
        }

        epd._maxSizeSerializedSample =
        ObjectStatePlugin_get_serialized_sample_max_size(
            (PRESTypePluginEndpointData)&epd,
            RTI_TRUE,
            encapsulationId,
            0);

        if (buffer == NULL) {
            *length =
            PRESTypePlugin_interpretedGetSerializedSampleSize(
                (PRESTypePluginEndpointData)&epd,
                RTI_TRUE,
                encapsulationId,
                0,
                sample);

            if (*length == 0) {
                return RTI_FALSE;
            }

            return RTI_TRUE;
        }

        RTICdrStream_init(&cdrStream);
        RTICdrStream_set(&cdrStream, (char *)buffer, *length);

        result = PRESTypePlugin_interpretedSerialize(
            (PRESTypePluginEndpointData)&epd,
            sample,
            &cdrStream,
            RTI_TRUE,
            encapsulationId,
            RTI_TRUE,
            NULL);

        *length = (unsigned int) RTICdrStream_getCurrentPositionOffset(&cdrStream);
        return result;
    }

    RTIBool
    ObjectStatePlugin_serialize_to_cdr_buffer(
        char *buffer,
        unsigned int *length,
        const ObjectState *sample)
    {
        return ObjectStatePlugin_serialize_to_cdr_buffer_ex(
            buffer,
            length,
            sample,
            DDS_AUTO_DATA_REPRESENTATION);
    }

    RTIBool
    ObjectStatePlugin_deserialize_from_cdr_buffer(
        ObjectState *sample,
        const char * buffer,
        unsigned int length)
    {
        struct RTICdrStream cdrStream;
        struct PRESTypePluginDefaultEndpointData epd;
        struct RTIXCdrTypePluginProgramContext defaultProgramContext =
        RTIXCdrTypePluginProgramContext_INTIALIZER;
        struct PRESTypePluginDefaultParticipantData pd;
        struct PRESTypePlugin plugin;

        epd.programContext = defaultProgramContext;
        epd._participantData = &pd;
        epd.typePlugin = &plugin;
        epd.programContext.endpointPluginData = &epd;
        plugin.typeCode = (struct RTICdrTypeCode *)
        ObjectState_get_typecode();
        pd.programs = ObjectStatePlugin_get_programs();
        if (pd.programs == NULL) {
            return RTI_FALSE;
        }
        RTIXCdrSampleAssignabilityProperty_setFromGlobalComplianceMask(
            &epd._assignabilityProperty);

        RTICdrStream_init(&cdrStream);
        RTICdrStream_set(&cdrStream, (char *)buffer, length);

        ObjectState_finalize_optional_members(sample, RTI_TRUE);
        return PRESTypePlugin_interpretedDeserialize(
            (PRESTypePluginEndpointData)&epd, sample,
            &cdrStream, RTI_TRUE, RTI_TRUE,
            NULL);
    }

    #if !defined(NDDS_STANDALONE_TYPE)
    DDS_ReturnCode_t
    ObjectStatePlugin_data_to_string(
        const ObjectState *sample,
        char *_str,
        DDS_UnsignedLong *str_size,
        const struct DDS_PrintFormatProperty *property)
    {
        DDS_DynamicData *data = NULL;
        char *buffer = NULL;
        unsigned int length = 0;
        struct DDS_PrintFormat printFormat;
        DDS_ReturnCode_t retCode = DDS_RETCODE_ERROR;

        if (sample == NULL) {
            return DDS_RETCODE_BAD_PARAMETER;
        }

        if (str_size == NULL) {
            return DDS_RETCODE_BAD_PARAMETER;
        }

        if (property == NULL) {
            return DDS_RETCODE_BAD_PARAMETER;
        }
        if (!ObjectStatePlugin_serialize_to_cdr_buffer(
            NULL,
            &length,
            sample)) {
            return DDS_RETCODE_ERROR;
        }

        RTIOsapiHeap_allocateBuffer(&buffer, length, RTI_OSAPI_ALIGNMENT_DEFAULT);
        if (buffer == NULL) {
            return DDS_RETCODE_ERROR;
        }

        if (!ObjectStatePlugin_serialize_to_cdr_buffer(
            buffer,
            &length,
            sample)) {
            RTIOsapiHeap_freeBuffer(buffer);
            return DDS_RETCODE_ERROR;
        }
        data = DDS_DynamicData_new(
            ObjectState_get_typecode(),
            &DDS_DYNAMIC_DATA_PROPERTY_DEFAULT);
        if (data == NULL) {
            RTIOsapiHeap_freeBuffer(buffer);
            return DDS_RETCODE_ERROR;
        }

        retCode = DDS_DynamicData_from_cdr_buffer(data, buffer, length);
        if (retCode != DDS_RETCODE_OK) {
            RTIOsapiHeap_freeBuffer(buffer);
            DDS_DynamicData_delete(data);
            return retCode;
        }

        retCode = DDS_PrintFormatProperty_to_print_format(
            property,
            &printFormat);
        if (retCode != DDS_RETCODE_OK) {
            RTIOsapiHeap_freeBuffer(buffer);
            DDS_DynamicData_delete(data);
            return retCode;
        }

        retCode = DDS_DynamicDataFormatter_to_string_w_format(
            data,
            _str,
            str_size,
            &printFormat);
        if (retCode != DDS_RETCODE_OK) {
            RTIOsapiHeap_freeBuffer(buffer);
            DDS_DynamicData_delete(data);
            return retCode;
        }

        RTIOsapiHeap_freeBuffer(buffer);
        DDS_DynamicData_delete(data);
        return DDS_RETCODE_OK;
    }
    #endif

    unsigned int
    ObjectStatePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;

        size = PRESTypePlugin_interpretedGetSerializedSampleMaxSize(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);

        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */

    PRESTypePluginKeyKind
    ObjectStatePlugin_get_key_kind(void)
    {
        return PRES_TYPEPLUGIN_USER_KEY;
    }

    RTIBool ObjectStatePlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        ObjectState **sample,
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos)
    {
        RTIBool result;
        RTIOsapiUtility_unusedParameter(drop_sample);
        /*  Depending on the type and the flags used in rtiddsgen, coverity may detect
        that sample is always null. Since the case is very dependant on
        the IDL/XML and the configuration we keep the check for safety.
        */
        result= PRESTypePlugin_interpretedDeserializeKey(
            endpoint_data,
            /* coverity[check_after_deref] */
            (sample != NULL) ? *sample : NULL,
            cdrStream,
            deserialize_encapsulation,
            deserialize_key,
            endpoint_plugin_qos);
        return result;

    }

    unsigned int
    ObjectStatePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;
        size = PRESTypePlugin_interpretedGetSerializedKeyMaxSize(
            endpoint_data,&overflow,include_encapsulation,encapsulation_id,current_alignment);
        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    unsigned int
    ObjectStatePlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment)
    {
        unsigned int size;
        RTIBool overflow = RTI_FALSE;
        size = PRESTypePlugin_interpretedGetSerializedKeyMaxSizeForKeyhash(
            endpoint_data,
            &overflow,
            encapsulation_id,
            current_alignment);
        if (overflow) {
            size = RTI_CDR_MAX_SERIALIZED_SIZE;
        }

        return size;
    }

    RTIBool 
    ObjectStatePlugin_instance_to_key(
        PRESTypePluginEndpointData endpoint_data,
        ObjectStateKeyHolder *dst, 
        const ObjectState *src)
    {
        RTIOsapiUtility_unusedParameter(endpoint_data);   

        if (!RTICdrType_copyLong (
            &dst->object_id, 
            &src->object_id)) { 
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    RTIBool 
    ObjectStatePlugin_key_to_instance(
        PRESTypePluginEndpointData endpoint_data,
        ObjectState *dst, const
        ObjectStateKeyHolder *src)
    {
        RTIOsapiUtility_unusedParameter(endpoint_data);   
        if (!RTICdrType_copyLong (
            &dst->object_id, 
            &src->object_id)) { 
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    RTIBool 
    ObjectStatePlugin_serialized_sample_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *cdrStream, 
        DDS_KeyHash_t *keyhash,
        RTIBool deserialize_encapsulation,
        void *endpoint_plugin_qos) 
    {   
        ObjectState * sample = NULL;
        sample = (ObjectState *)
        PRESTypePluginDefaultEndpointData_getTempSample(endpoint_data);
        if (sample == NULL) {
            return RTI_FALSE;
        }

        if (!PRESTypePlugin_interpretedSerializedSampleToKey(
            endpoint_data,
            sample,
            cdrStream, 
            deserialize_encapsulation, 
            RTI_TRUE,
            endpoint_plugin_qos)) {
            return RTI_FALSE;
        }
        if (!PRESTypePlugin_interpretedInstanceToKeyHash(
            endpoint_data, 
            keyhash, 
            sample,
            RTICdrStream_getEncapsulationKind(cdrStream))) {
            return RTI_FALSE;
        }
        return RTI_TRUE;
    }

    struct RTIXCdrInterpreterPrograms * ObjectStatePlugin_get_programs(void)
    {
        if (!RTIXCdrXTypesComplianceMask_verifyGeneratedXTypesMask(0x0000018C)) {
            return NULL;
        }
        return ::rti::xcdr::get_cdr_serialization_programs<
        ObjectState,
        true, true, true>();
    }

    /* ------------------------------------------------------------------------
    * Plug-in Installation Methods
    * ------------------------------------------------------------------------ */
    struct PRESTypePlugin *ObjectStatePlugin_new(void)
    {
        struct PRESTypePlugin *plugin = NULL;
        const struct PRESTypePluginVersion PLUGIN_VERSION =
        PRES_TYPE_PLUGIN_VERSION_2_0;

        RTIOsapiHeap_allocateStructure(
            &plugin, struct PRESTypePlugin);

        if (plugin == NULL) {
            return NULL;
        }

        plugin->version = PLUGIN_VERSION;

        /* set up parent's function pointers */
        plugin->onParticipantAttached =
        (PRESTypePluginOnParticipantAttachedCallback)
        ::ObjectStateMsg::ObjectStatePlugin_on_participant_attached;
        plugin->onParticipantDetached =
        (PRESTypePluginOnParticipantDetachedCallback)
        ::ObjectStateMsg::ObjectStatePlugin_on_participant_detached;
        plugin->onEndpointAttached =
        (PRESTypePluginOnEndpointAttachedCallback)
        ::ObjectStateMsg::ObjectStatePlugin_on_endpoint_attached;
        plugin->onEndpointDetached =
        (PRESTypePluginOnEndpointDetachedCallback)
        ::ObjectStateMsg::ObjectStatePlugin_on_endpoint_detached;

        plugin->copySampleFnc =
        (PRESTypePluginCopySampleFunction)
        ::ObjectStateMsg::ObjectStatePlugin_copy_sample;
        plugin->createSampleFnc =
        (PRESTypePluginCreateSampleFunction)
        ObjectStatePlugin_create_sample;
        plugin->destroySampleFnc =
        (PRESTypePluginDestroySampleFunction)
        ObjectStatePlugin_destroy_sample;
        plugin->finalizeOptionalMembersFnc =
        (PRESTypePluginFinalizeOptionalMembersFunction)
        ObjectStatePlugin_finalize_optional_members;

        plugin->serializeFnc =
        (PRESTypePluginSerializeFunction) PRESTypePlugin_interpretedSerialize;
        plugin->deserializeFnc =
        (PRESTypePluginDeserializeFunction) PRESTypePlugin_interpretedDeserializeWithAlloc;
        plugin->getSerializedSampleMaxSizeFnc =
        (PRESTypePluginGetSerializedSampleMaxSizeFunction)
        ::ObjectStateMsg::ObjectStatePlugin_get_serialized_sample_max_size;
        plugin->getSerializedSampleMinSizeFnc =
        (PRESTypePluginGetSerializedSampleMinSizeFunction)
        PRESTypePlugin_interpretedGetSerializedSampleMinSize;
        plugin->getDeserializedSampleMaxSizeFnc = NULL;
        plugin->getSampleFnc =
        (PRESTypePluginGetSampleFunction)
        ObjectStatePlugin_get_sample;
        plugin->returnSampleFnc =
        (PRESTypePluginReturnSampleFunction)
        ObjectStatePlugin_return_sample;
        plugin->getKeyKindFnc =
        (PRESTypePluginGetKeyKindFunction)
        ::ObjectStateMsg::ObjectStatePlugin_get_key_kind;

        plugin->getSerializedKeyMaxSizeFnc =
        (PRESTypePluginGetSerializedKeyMaxSizeFunction)
        ::ObjectStateMsg::ObjectStatePlugin_get_serialized_key_max_size;
        plugin->serializeKeyFnc =
        (PRESTypePluginSerializeKeyFunction)
        PRESTypePlugin_interpretedSerializeKey;
        plugin->deserializeKeyFnc =
        (PRESTypePluginDeserializeKeyFunction)
        ::ObjectStateMsg::ObjectStatePlugin_deserialize_key;
        plugin->deserializeKeySampleFnc =
        (PRESTypePluginDeserializeKeySampleFunction)
        PRESTypePlugin_interpretedDeserializeKey;

        plugin-> instanceToKeyHashFnc =
        (PRESTypePluginInstanceToKeyHashFunction)
        PRESTypePlugin_interpretedInstanceToKeyHash;
        plugin->serializedSampleToKeyHashFnc =
        (PRESTypePluginSerializedSampleToKeyHashFunction)
        ::ObjectStateMsg::ObjectStatePlugin_serialized_sample_to_keyhash;

        plugin->getKeyFnc =
        (PRESTypePluginGetKeyFunction)
        ObjectStatePlugin_get_key;
        plugin->returnKeyFnc =
        (PRESTypePluginReturnKeyFunction)
        ObjectStatePlugin_return_key;

        plugin->instanceToKeyFnc =
        (PRESTypePluginInstanceToKeyFunction)
        ::ObjectStateMsg::ObjectStatePlugin_instance_to_key;
        plugin->keyToInstanceFnc =
        (PRESTypePluginKeyToInstanceFunction)
        ::ObjectStateMsg::ObjectStatePlugin_key_to_instance;
        plugin->serializedKeyToKeyHashFnc = NULL; /* Not supported yet */
        #ifdef NDDS_STANDALONE_TYPE
        plugin->typeCode = NULL;
        #else
        plugin->typeCode =  (struct RTICdrTypeCode *)::ObjectStateMsg::ObjectState_get_typecode();
        #endif
        plugin->languageKind = PRES_TYPEPLUGIN_CPP_LANG;

        /* Serialized buffer */
        plugin->getBuffer =
        (PRESTypePluginGetBufferFunction)
        ObjectStatePlugin_get_buffer;
        plugin->returnBuffer =
        (PRESTypePluginReturnBufferFunction)
        ObjectStatePlugin_return_buffer;
        plugin->getBufferWithParams = NULL;
        plugin->returnBufferWithParams = NULL;
        plugin->getSerializedSampleSizeFnc =
        (PRESTypePluginGetSerializedSampleSizeFunction)
        PRESTypePlugin_interpretedGetSerializedSampleSize;

        plugin->getWriterLoanedSampleFnc = NULL;
        plugin->returnWriterLoanedSampleFnc = NULL;
        plugin->returnWriterLoanedSampleFromCookieFnc = NULL;
        plugin->validateWriterLoanedSampleFnc = NULL;
        plugin->setWriterLoanedSampleSerializedStateFnc = NULL;

        plugin->endpointTypeName = ObjectStateTYPENAME;
        plugin->isMetpType = RTI_FALSE;
        plugin->isRecursiveType = RTI_FALSE;
        return plugin;
    }

    void
    ObjectStatePlugin_delete(struct PRESTypePlugin *plugin)
    {
        RTIOsapiHeap_freeStructure(plugin);
    }
} /* namespace ObjectStateMsg  */
#undef RTI_CDR_CURRENT_SUBMODULE
