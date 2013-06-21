#include "cjson.h"
#include <stdio.h>
#include <string.h>

cjson* cjson_new(const char* strJson)
{
    cjson* p_json = (cjson*)malloc(sizeof(cjson));
    p_json->root = cJSON_Parse(strJson);
    p_json->child = p_json->root;
    p_json->item = NULL;
    p_json->parse = cjson_parse;
    p_json->obj = cjson_obj;
    p_json->obj_i = cjson_obj_idx;
    p_json->obj_s = cjson_obj_str;

    p_json->sobj = cjson_set_obj;
    p_json->sstr = cjson_set_str;
    p_json->snum = cjson_set_num;
    p_json->sbool = cjson_set_bool;
    p_json->snull = cjson_set_null;

    p_json->sobj_i = cjson_set_obj_idx;
    p_json->sstr_i = cjson_set_str_idx;
    p_json->snum_i = cjson_set_num_idx;
    p_json->sbool_i = cjson_set_bool_idx;
    p_json->snull_i = cjson_set_null_idx;

    return p_json;
}



int cjson_delete(cjson* pJson)
{
    if(pJson)
    {
        
        if(pJson->root)
        {
            cJSON_Delete(pJson->root);
        }
        free(pJson);
        return 1;
    }
    else
    {
        return 0;
    }
}



int cjson_reset(cjson* pJson)
{
    if(pJson)
    {
        pJson->child = pJson->root;
        pJson->item = NULL;
        
        return 1;
    }
    else
    {
        return 0;
    }
}



bbool cjson_parse(cjson* pJson, const char* strJson)
{
    if(pJson)
    {
        pJson->child = NULL;
        
        if(pJson->root)
        {
            cJSON_Delete(pJson->root);
        }
        pJson->root = cJSON_Parse(strJson);
    }
    return 1;
}

cjson* cjson_obj(cjson* pJson, const char* key)
{
    if(pJson)
    {
        if (pJson->item)
            pJson->child = cJSON_GetObjectItem(pJson->item, key);
        else if (pJson->child)
            pJson->child = cJSON_GetObjectItem(pJson->child, key);

        pJson->item = NULL;
        
        return pJson;
    }
    else
    {
        return NULL;
    }
}





cjson* cjson_obj_idx(cjson* pJson, int idx)
{
    if(pJson)
    {
        if(pJson->child)
            pJson->item = cJSON_GetArrayItem(pJson->child, idx);
        pJson->child = pJson->item ? pJson->child : NULL;
        return pJson;
    }
    else
    {
        return NULL;
    }
}



cjson* cjson_set_obj(cjson* pJson, const char* name, cjson* obj)
{
    if(!pJson || !name || !obj)
    {
        return NULL;
    }
    cJSON* lp_dest_json = pJson->item ? pJson->item : pJson->child;
    cJSON* lp_src_json = obj->item ? obj->item : obj->child;

    if(cJSON_GetObjectItem(lp_dest_json, name)!= NULL)
    {
        cJSON_ReplaceItemInObject(lp_dest_json, name, lp_src_json);
    }
    else
    {
        cJSON_AddItemToObject(lp_dest_json, name, lp_src_json);
    }
    free(obj);
    return pJson;
}



cjson* cjson_set_str(cjson* pJson, const char* name, char* str)
{
    if(!pJson || !name || !str)
    {
        return NULL;
    }
    cJSON* lp_dest_json = pJson->item ? pJson->item : pJson->child;
    
    if(cJSON_GetObjectItem(lp_dest_json, name)!= NULL)
    {
        cJSON_ReplaceItemInObject(lp_dest_json, name, cJSON_CreateString(str));
    }
    else
    {
        cJSON_AddItemToObject(lp_dest_json, name, cJSON_CreateString(str));
    }
    
    return pJson;
}





cjson* cjson_set_num(cjson* pJson, const char* name, int num)
{
    if(!pJson || !name)
    {
        return NULL;
    }
    cJSON* lp_dest_json = pJson->item ? pJson->item : pJson->child;
    
    if(cJSON_GetObjectItem(lp_dest_json, name)!= NULL)
    {
        cJSON_ReplaceItemInObject(lp_dest_json, name, cJSON_CreateNumber(num));
    }
    else
    {
        cJSON_AddItemToObject(lp_dest_json, name, cJSON_CreateNumber(num));
    }
    
    return pJson;
}

cjson* cjson_set_bool(cjson* pJson, const char* name, bbool b)
{
    if(!pJson || !name)
    {
        return NULL;
    }
    cJSON* lp_dest_json = pJson->item ? pJson->item : pJson->child;
    
    if(cJSON_GetObjectItem(lp_dest_json, name)!= NULL)
    {
        cJSON_ReplaceItemInObject(lp_dest_json, name,  (b ? cJSON_CreateTrue() : cJSON_CreateFalse()) );
    }
    else
    {
        cJSON_AddItemToObject(lp_dest_json, name, (b ? cJSON_CreateTrue() : cJSON_CreateFalse()) );
    }
    
    return pJson;
}



cjson* cjson_set_null(cjson* pJson, const char* name)
{
    if(!pJson || !name)
    {
        return NULL;
    }
    cJSON* lp_dest_json = pJson->item ? pJson->item : pJson->child;
    
    if(cJSON_GetObjectItem(lp_dest_json, name)!= NULL)
    {
        cJSON_ReplaceItemInObject(lp_dest_json, name,  cJSON_CreateNull() );
    }
    else
    {
        cJSON_AddItemToObject(lp_dest_json, name, cJSON_CreateNull() );
    }
    
    return pJson;
}


//////////////////////////////////
//////////////////////////////////
//////////////////////////////////





cjson* cjson_set_obj_idx(cjson* pJson, int idx, cjson* obj)
{
    if(!pJson || !obj)
    {
        return NULL;
    }
    cJSON* lp_dest_json = pJson->item ? pJson->item : pJson->child;
    cJSON* lp_src_json = obj->item ? obj->item : obj->child;
    
    if(cJSON_GetArrayItem(lp_dest_json, idx)!= NULL)
    {
        cJSON_ReplaceItemInArray(lp_dest_json, idx, lp_src_json);
    }
    else
    {
        cJSON_AddItemToArray(lp_dest_json, lp_src_json);
    }
    
    free(obj);
    return pJson;
}



cjson* cjson_set_str_idx(cjson* pJson, int idx, char* str)
{
    if(!pJson || !str)
    {
        return NULL;
    }
    cJSON* lp_dest_json = pJson->item ? pJson->item : pJson->child;
    
    if(cJSON_GetArrayItem(lp_dest_json, idx)!= NULL)
    {
        cJSON_ReplaceItemInArray(lp_dest_json, idx, cJSON_CreateString(str));
    }
    else
    {
        cJSON_AddItemToArray(lp_dest_json, cJSON_CreateString(str));
    }
    
    return pJson;
}





cjson* cjson_set_num_idx(cjson* pJson, int idx, int num)
{
    if(!pJson)
    {
        return NULL;
    }
    cJSON* lp_dest_json = pJson->item ? pJson->item : pJson->child;
    
    if(cJSON_GetArrayItem(lp_dest_json, idx)!= NULL)
    {
        cJSON_ReplaceItemInArray(lp_dest_json, idx, cJSON_CreateNumber(num));
    }
    else
    {
        cJSON_AddItemToArray(lp_dest_json, cJSON_CreateNumber(num));
    }

    
    return pJson;
}

cjson* cjson_set_bool_idx(cjson* pJson, int idx, bbool b)
{
    if(!pJson)
    {
        return NULL;
    }
    cJSON* lp_dest_json = pJson->item ? pJson->item : pJson->child;

    if(cJSON_GetArrayItem(lp_dest_json, idx)!= NULL)
    {
        cJSON_ReplaceItemInArray(lp_dest_json, idx, (b ? cJSON_CreateTrue() : cJSON_CreateFalse()) );
    }
    else
    {
        cJSON_AddItemToArray(lp_dest_json, (b ? cJSON_CreateTrue() : cJSON_CreateFalse()) );
    }

    
    return pJson;
}



cjson* cjson_set_null_idx(cjson* pJson, int idx)
{
    if(!pJson)
    {
        return NULL;
    }
    
    cJSON* lp_dest_json = pJson->item ? pJson->item : pJson->child;
    
    if(cJSON_GetArrayItem(lp_dest_json, idx)!= NULL)
    {
        cJSON_ReplaceItemInArray(lp_dest_json, idx, cJSON_CreateNull() );
    }
    else
    {
        cJSON_AddItemToArray(lp_dest_json, cJSON_CreateNull() );
    }
    
    
    return pJson;
}








char* cjson_obj_str(cjson* pJson)
{

    if(pJson==NULL || pJson->child == NULL)
    {
        //throw runtime_error("json字符串格式错误");
        return calloc(1,1);
    }
    char* lp_str_ret = NULL;
    cJSON* lp_json_ret = pJson->item ? pJson->item : pJson->child;
    switch (lp_json_ret->type) {
    case cJSON_False:
        lp_str_ret = strdup("false");
        break;
    case cJSON_True:
        lp_str_ret = strdup("true");
        break;
    case cJSON_NULL:
        lp_str_ret =  strdup("null");
        break;
    case cJSON_Number:
        lp_str_ret = cJSON_Print(lp_json_ret);
        break;
    case cJSON_String:
        lp_str_ret = strdup(lp_json_ret->valuestring);
        break;
    case cJSON_Array:
    case cJSON_Object:
        lp_str_ret = cJSON_Print(lp_json_ret);
        break;
    }

    return lp_str_ret;

    
}





int main()
{
    const char* p = "{\"op\":\"ADDTAG\",\"org\":\"xian\",\"fieldId\":\"READ\", \"age\":{\"num1\":\"11111\", \"num2\":\"22222\",\"tagId\":[\"0\", \"1\", 2, \"3\"], \"num3\":[{\"aaa\":\"1111\", \"num3\":[{\"aaa\":\"1111\" }] }]} }";
    cjson* pjson = cjson_new(p);
    
    {
//       cjson* lp_new_json = cjson_new("{\"name\":\"bf\"}");
        /* pjson->sobj(pjson, "name", lp_new_json); */
        /* pjson->sstr(pjson, "ape", "apeadmin"); */
        /* pjson->snum(pjson, "num", 100); */
        /* pjson->sbool(pjson, "bool", 10); */
        /* pjson->sbool(pjson, "bool2", 0); */
//        pjson->obj(pjson, "age")->sstr_i(pjson, "age", 1, "555555");
        pjson->obj(pjson, "age")->obj(pjson, "tagId")->snum_i(pjson, 6, 100);
        cjson_reset(pjson);

//        pjson->snull(pjson, "null1");
        //      pjson->snull(pjson, "age");
        char* content = pjson->obj_s(pjson);
//    char* content =pjson->obj(pjson, "age")->obj(pjson, "num1")->obj_s(pjson);
        if(content)
        {
            printf("%s\n", content);
            free(content);
        }
        cjson_reset(pjson);
    }
    
    {
        char* content =pjson->obj(pjson, "age")->obj(pjson, "num3")->obj_i(pjson, 0)->obj(pjson, "num3")->obj_i(pjson, 0)->obj(pjson, "aaa")->obj_s(pjson);
//    char* content =pjson->obj(pjson, "age")->obj(pjson, "num1")->obj_s(pjson);
        if(content)
        {
            printf("%s\n", content);
            free(content);
        }
        cjson_reset(pjson);
    }

    {
        char* content =pjson->obj(pjson, "age")->obj(pjson, "tagId")->obj_i(pjson, 2)->obj_s(pjson);
//    char* content =pjson->obj(pjson, "age")->obj(pjson, "num1")->obj_s(pjson);
        if(content)
        {
            printf("%s\n", content);
            free(content);
        }
        cjson_reset(pjson);
    }

    cjson_delete(pjson);
//    free(pjson);
    return 0;
}
