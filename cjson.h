
#ifndef cjson__H_
#define cjson__H_

#include "cJSON.h"
#define JSON_TYPE_BOOL     1
#define JSON_TYPE_NUM      2
#define JSON_TYPE_STRING   3
#define JSON_TYPE_ARRAY    4
typedef struct st_cjson cjson;
typedef unsigned short bbool;
typedef bbool (*fn_str) (cjson* this, const char*);
typedef cjson* (*fn_objson) (cjson* this, const char*);
typedef cjson* (*fn_objson_idx) (cjson* this, int idx);

typedef cjson* (*fn_set_objson) (cjson* this, const char*, cjson* obj);

typedef cjson* (*fn_set_strjson) (cjson* this, const char*, char* str);

typedef cjson* (*fn_set_numjson) (cjson* this, const char*, int num);

typedef cjson* (*fn_set_booljson) (cjson* this, const char*, bbool b);

typedef cjson* (*fn_set_nulljson) (cjson* this, const char*);



typedef cjson* (*fn_set_objson_i) (cjson* this, int idx, cjson* obj);

typedef cjson* (*fn_set_strjson_i) (cjson* this, int idx, char* str);

typedef cjson* (*fn_set_numjson_i) (cjson* this, int idx, int num);

typedef cjson* (*fn_set_booljson_i) (cjson* this, int idx, bbool b);

typedef cjson* (*fn_set_nulljson_i) (cjson* this, int idx );


typedef char* (*fn_objson_str) (cjson* this);

struct st_cjson
{
    
    cJSON* root;
    cJSON* child;
    cJSON* item;
    fn_str parse;
    
    fn_objson obj;
    fn_objson_idx obj_i;
    
    fn_set_objson sobj;
    fn_set_strjson sstr;
    fn_set_numjson snum;
    fn_set_booljson sbool;
    fn_set_nulljson snull;

    fn_set_objson_i sobj_i;
    fn_set_strjson_i sstr_i;
    fn_set_numjson_i snum_i;
    fn_set_booljson_i sbool_i;
    fn_set_nulljson_i snull_i;

    
    fn_objson_str obj_s;
};

#define CJSON_MEMBER_POS(n) ( ((cjson*)(0))->(n) )

cjson* cjson_new(const char* strJson);

int cjson_delete(cjson* pJson);

int cjson_reset(cjson* pJson);

bbool cjson_parse(cjson* pJson, const char* strJson);

cjson* cjson_obj(cjson* pJson, const char* key);

cjson* cjson_obj_idx(cjson* pJson, int idx);



cjson* cjson_set_obj(cjson* pJson, const char* name, cjson* obj);

cjson* cjson_set_str(cjson* pJson, const char* name, char* str);


cjson* cjson_set_num(cjson* pJson, const char* name, int num);

cjson* cjson_set_bool(cjson* pJson, const char* name, bbool b);

cjson* cjson_set_null(cjson* pJson, const char* name);


cjson* cjson_set_obj_idx(cjson* pJson, int idx, cjson* obj);

cjson* cjson_set_str_idx(cjson* pJson, int idx, char* str);


cjson* cjson_set_num_idx(cjson* pJson, int idx, int num);

cjson* cjson_set_bool_idx(cjson* pJson, int idx, bbool b);

cjson* cjson_set_null_idx(cjson* pJson, int idx );



char* cjson_obj_str(cjson* pJson);

#endif /* SPDJSON_H_ */
