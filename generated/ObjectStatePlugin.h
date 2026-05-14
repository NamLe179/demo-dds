

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ObjectState.idl
using RTI Code Generator (rtiddsgen) version 4.7.0.
The rtiddsgen tool is part of the RTI Connext DDS distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the Code Generator User's Manual.
*/

#ifndef ObjectStatePlugin_1035534872_h
#define ObjectStatePlugin_1035534872_h

#include "ObjectState.h"

struct RTICdrStream;

#ifndef pres_typePlugin_h
#include "pres/pres_typePlugin.h"
#endif

#if defined(NDDS_USER_DLL_EXPORT) && defined(RTI_WIN32)
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#if !defined(RTI_WIN32) && defined(NDDS_USER_SYMBOL_EXPORT)
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __attribute__((visibility("default")))
#endif

namespace ObjectStateMsg {

    /* The type used to store keys for instances of type struct
    * AnotherSimple.
    *
    * By default, this type is struct ObjectState
    * itself. However, if for some reason this choice is not practical for your
    * system (e.g. if sizeof(struct ObjectState)
    * is very large), you may redefine this typedef in terms of another type of
    * your choosing. HOWEVER, if you define the KeyHolder type to be something
    * other than struct AnotherSimple, the
    * following restriction applies: the key of struct
    * ObjectState must consist of a
    * single field of your redefined KeyHolder type and that field must be the
    * first field in struct ObjectState.
    */
    typedef  class ObjectState ObjectStateKeyHolder;

    #define ObjectStatePlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 

    #define ObjectStatePlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define ObjectStatePlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define ObjectStatePlugin_get_key PRESTypePluginDefaultEndpointData_getKey 
    #define ObjectStatePlugin_return_key PRESTypePluginDefaultEndpointData_returnKey

    #define ObjectStatePlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define ObjectStatePlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern ObjectState*
    ObjectStatePluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern ObjectState*
    ObjectStatePluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern ObjectState*
    ObjectStatePluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    ObjectStatePluginSupport_copy_data(
        ObjectState *out,
        const ObjectState *in);

    NDDSUSERDllExport extern void 
    ObjectStatePluginSupport_destroy_data_w_params(
        ObjectState *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    ObjectStatePluginSupport_destroy_data_ex(
        ObjectState *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    ObjectStatePluginSupport_destroy_data(
        ObjectState *sample);

    NDDSUSERDllExport extern void 
    ObjectStatePluginSupport_print_data(
        const ObjectState *sample,
        const char *desc,
        unsigned int indent);

    NDDSUSERDllExport extern ObjectState*
    ObjectStatePluginSupport_create_key_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern ObjectState*
    ObjectStatePluginSupport_create_key(void);

    NDDSUSERDllExport extern void 
    ObjectStatePluginSupport_destroy_key_ex(
        ObjectStateKeyHolder *key,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    ObjectStatePluginSupport_destroy_key(
        ObjectStateKeyHolder *key);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    ObjectStatePlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    ObjectStatePlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    ObjectStatePlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    ObjectStatePlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    ObjectStatePlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        ObjectState *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    ObjectStatePlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        ObjectState *out,
        const ObjectState *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    ObjectStatePlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const ObjectState *sample); 

    NDDSUSERDllExport extern RTIBool
    ObjectStatePlugin_serialize_to_cdr_buffer_ex(
        char *buffer,
        unsigned int *length,
        const ObjectState *sample,
        DDS_DataRepresentationId_t representation);

    NDDSUSERDllExport extern RTIBool
    ObjectStatePlugin_deserialize_from_cdr_buffer(
        ObjectState *sample,
        const char * buffer,
        unsigned int length);    
    #if !defined (NDDS_STANDALONE_TYPE)
    NDDSUSERDllExport extern DDS_ReturnCode_t
    ObjectStatePlugin_data_to_string(
        const ObjectState *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    
    #endif

    NDDSUSERDllExport extern unsigned int 
    ObjectStatePlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    ObjectStatePlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    ObjectStatePlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    ObjectStatePlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    ObjectStatePlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        ObjectState ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *cdrStream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    ObjectStatePlugin_instance_to_key(
        PRESTypePluginEndpointData endpoint_data,
        ObjectStateKeyHolder *key, 
        const ObjectState *instance);

    NDDSUSERDllExport extern RTIBool 
    ObjectStatePlugin_key_to_instance(
        PRESTypePluginEndpointData endpoint_data,
        ObjectState *instance, 
        const ObjectStateKeyHolder *key);

    NDDSUSERDllExport extern RTIBool 
    ObjectStatePlugin_serialized_sample_to_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *cdrStream, 
        DDS_KeyHash_t *keyhash,
        RTIBool deserialize_encapsulation,
        void *endpoint_plugin_qos); 

    NDDSUSERDllExport extern
    struct RTIXCdrInterpreterPrograms * ObjectStatePlugin_get_programs(void);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    ObjectStatePlugin_new(void);

    NDDSUSERDllExport extern void
    ObjectStatePlugin_delete(struct PRESTypePlugin *);

} /* namespace ObjectStateMsg  */

#if defined(NDDS_USER_DLL_EXPORT) || defined(NDDS_USER_SYMBOL_EXPORT)
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* ObjectStatePlugin_1035534872_h */
