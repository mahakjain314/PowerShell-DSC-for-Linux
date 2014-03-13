/* @migen@ */
#include <MI.h>
#include "L_IndicationC3.h"
#include "impl.h"

static MI_Result MI_CALL _SetIndicationProperties_Impl(
    _In_ void* cfg,
    _Outptr_ MI_Instance** indication)
{
    MI_Result r = MI_RESULT_OK;
    Config* config = (Config*)cfg;
    DEBUG_ASSERT (indication);
    *indication = NULL;
    {
        MI_Boolean match;
        L_IndicationC3* inst;
        MI_Context* context = config->postctx;
        r = MI_Context_NewInstance(context, &L_IndicationC3_rtti, indication);
        CHKMIRESULTRETURN(r, "MI_Context_NewInstance failed");

        L_Indication_SetIndicationProperties(cfg, *indication);
        CHKSETPROPERTY(r, "L_Indication Properties");

        inst = (L_IndicationC3*) (*indication);
        r = L_IndicationC3_Set_message(inst, MI_T("test indication message"));
        CHKSETPROPERTY(r, "message");
        r = L_IndicationC3_Set_id(inst, config->count);
        CHKSETPROPERTY(r, "id");
        r = L_IndicationC3_Set_lcode3(inst, config->count);
        CHKSETPROPERTY(r, "lcode3");

        r = class_TestFilter(config, &inst->__instance, &match);
        if (r == MI_RESULT_OK)
        {
            if (match == MI_FALSE)
            {
                LOGMSG(("Indication does not match filter"));
            }
        }
    }
    return r;
}

static MI_Result MI_CALL _SetIndicationProperties(
    _In_ void* cfg,
    _Outptr_ MI_Instance** indication)
{
    MI_Result r = _SetIndicationProperties_Impl(cfg, indication);
    if (r != MI_RESULT_OK)
    {
        if (*indication)
            MI_Instance_Delete(*indication);
    }
    return r;
}

void MI_CALL L_IndicationC3_Load(
    L_IndicationC3_Self** self,
    MI_Module_Self* selfModule,
    MI_Context* context)
{
    MI_Result r;
    *self = NULL;
    r = class_Load((void**)self, &cfgL_IndicationC3, _SetIndicationProperties);
    MI_PostResult(context, r);
}

void MI_CALL L_IndicationC3_Unload(
    L_IndicationC3_Self* self,
    MI_Context* context)
{
    MI_Result r = class_Unload((void*)self, &cfgL_IndicationC3);
    MI_PostResult(context, r);
}

void MI_CALL L_IndicationC3_EnableIndications(
    L_IndicationC3_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className)
{
    /* TODO: store indicationsContext for posting indication usage */
    /* NOTE:Call one of following functions if and ONLY if encount termination error,
            which will finalize the indicationsContext, 
            and terminate all active subscriptions to current class,
             MI_Context_PostResult
             MI_Context_PostError
             MI_Context_PostCimError
            */
    MI_Result r = class_EnableIndications((void*)self, indicationsContext, &cfgL_IndicationC3, nameSpace, className);
    if (r != MI_RESULT_OK)
        MI_PostResult(indicationsContext, r);
}

void MI_CALL L_IndicationC3_DisableIndications(
    L_IndicationC3_Self* self,
    MI_Context* indicationsContext,
    const MI_Char* nameSpace,
    const MI_Char* className)
{
    MI_Result r = class_DisableIndications((void*)self, indicationsContext, &cfgL_IndicationC3, nameSpace, className);
    MI_PostResult(indicationsContext, r);
}

void MI_CALL L_IndicationC3_Subscribe(
    L_IndicationC3_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    const MI_Filter* filter,
    const MI_Char* bookmark,
    MI_Uint64  subscriptionID,
    void** subscriptionSelf)
{
    /* TODO: store the context for posting indication usage */
    /* NOTE:Call one of following functions if and ONLY if encount termination error,
            which will finalize the context, 
            and Unsubscribe function will not be invoked then,
             MI_Context_PostResult
             MI_Context_PostError
             MI_Context_PostCimError
            */
    MI_Result r = class_Subscribe((void*)self, context, &cfgL_IndicationC3, nameSpace, className, filter, bookmark, subscriptionID, subscriptionSelf);
    if (r != MI_RESULT_OK)
        MI_PostResult(context, r);
}

void MI_CALL L_IndicationC3_Unsubscribe(
    L_IndicationC3_Self* self,
    MI_Context* context,
    const MI_Char* nameSpace,
    const MI_Char* className,
    MI_Uint64  subscriptionID,
    void* subscriptionSelf)
{
    MI_Result r = class_Unsubscribe((void*)self, context, &cfgL_IndicationC3, nameSpace, className, subscriptionID, subscriptionSelf);
    MI_PostResult(context, r);
}

