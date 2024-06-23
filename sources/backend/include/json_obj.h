#ifndef __JSON_OBJ_H
#define __JSON_OBJ_H

#include <stdint.h>

namespace utility
{
    enum class ObjType : int32_t
    {
        Boolean = 0,
        Int32,
        Int64,
        Double,
        String,
        Array,
        Object
    };
    
    class IJsonObj
    {
    public:
        virtual ~IJsonObj() = default;

        virtual int32_t Init(ObjType eType) = 0;
        virtual int32_t InitFromBuffer(const char *lpBuffer) = 0;
        virtual int32_t InitFromFile(const char *lpFileName) = 0;

        virtual const char *GetJsonStr(bool bPretty = false) = 0;

        virtual int32_t AddBool(const char *lpName, bool bValue) = 0;
        virtual int32_t AddInt32(const char *lpName, int32_t nValue) = 0;
        virtual int32_t AddInt64(const char *lpName, int64_t nValue) = 0;
        virtual int32_t AddDouble(const char *lpName, double dValue) = 0;
        virtual int32_t AddString(const char *lpName, const char *lpValue) = 0;
        virtual IJsonObj *AddArray(const char *lpName) = 0;
        virtual IJsonObj *AddObject(const char *lpName) = 0;

        virtual int32_t GetBool(const char *lpName, bool bDefaultValue = false) = 0;
        virtual int32_t GetInt32(const char *lpName, int32_t nDefaultValue = 0) = 0;
        virtual int32_t GetInt64(const char *lpName, int64_t nDefaultValue = 0) = 0;
        virtual int32_t GetDouble(const char *lpName, double dDefaultValue = 0.0) = 0;
        virtual const char *GetString(const char *lpName, const char *lpDefaultValue = nullptr) = 0;
        virtual IJsonObj *GetArray(const char *lpName) = 0;
        virtual IJsonObj *GetObject(const char *lpName) = 0;
    };
};

#ifdef __cplusplus
extern "C"
{
#endif

    utility::IJsonObj *NewJsonObject();

    void DeleteJsonObject(utility::IJsonObj *lpJsonObj);

#ifdef __cplusplus
}
#endif

#endif //__JSON_OBJ_H
