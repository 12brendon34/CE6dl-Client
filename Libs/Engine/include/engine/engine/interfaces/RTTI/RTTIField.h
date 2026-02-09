//
// Created by Brendon on 2/5/2026.
//

#pragma once
#include <cstdint>


#include "engine/Export.h"
#include "engine/Kernel/ttl/String.h"

//ofc also taken from DI
enum class ERTTIType : uint32_t {
    RTTI_TYPE_VOID = 0x0,
    RTTI_TYPE_CHAR = 0x1,
    RTTI_TYPE_UCHAR = 0x2,
    RTTI_TYPE_SHORT = 0x3,
    RTTI_TYPE_USHORT = 0x4,
    RTTI_TYPE_INT = 0x5,
    RTTI_TYPE_UINT = 0x6,
    RTTI_TYPE_INT64 = 0x7,
    RTTI_TYPE_UINT64 = 0x8,
    RTTI_TYPE_FLOAT = 0x9,
    RTTI_TYPE_DOUBLE = 0xA,
    RTTI_TYPE_BOOL = 0xB,
    RTTI_TYPE_STRING = 0xC,
    RTTI_TYPE_VEC2 = 0xD,
    RTTI_TYPE_VEC3 = 0xE,
    RTTI_TYPE_VEC4 = 0xF,
    RTTI_TYPE_MTX__TO_REMOVE__ = 0x10,
    RTTI_TYPE_PTR = 0x11,
    RTTI_TYPE_PTRLIST = 0x12,
    RTTI_TYPE_OBJECT = 0x13,
    RTTI_TYPE_ENUM = 0x14,
    RTTI_TYPE_FLAGS = 0x15,
    RTTI_TYPE_PTRVECTOR = 0x16,
    RTTI_TYPE_RAWPTR = 0x17,
    RTTI_TYPE_RAWPTRLIST = 0x18,
    RTTI_TYPE_RAWPTRVECTOR = 0x19,
    RTTI_TYPE_TAG = 0x1A,
    RTTI_TYPE_TAG_CONTAINER = 0x1B,
    RTTI_TYPE_VECTOR = 0x1C,
    RTTI_TYPE_QUAT = 0x1D,
    RTTI_TYPE_STRINGVECTOR = 0x1E,
    RTTI_TYPE_STRINGENUM = 0x1F,
    RTTI_TYPE_MTX43 = 0x20,
    RTTI_TYPE_MTX44 = 0x21,
    RTTI_TYPE_UNKNOWN = 0xFFFFFFFF,
};

struct ECompressedFieldType {
    enum TYPE {
        None=0,
        Integer64=1,
        UnsignedInteger64=2,
        Integer=3,
        UnsignedInteger=4,
        Short=5,
        UnsignedShrot=6,
        Char=7,
        UnsignedChar=8,
        Bool=9,
        Float=10,
        Vector3=11,
        Vector4=12
    };
};


class ENGINE_API CRTTIField {
    public:
    CRTTIField(CRTTIField const &);
    CRTTIField();
    void AddAdditionalData(char const *);
    void AddAdditionalDataString(char const *);
    void AssignName(char const *,unsigned char);
    bool CmpName(char const *) const;
    static bool EatWhiteChars(char * &);
    char const * GetAdditionalData() const;
    char const * GetCategory() const;
    //void GetClassListFromAdditionalData(ttl::vector<CRTTI const *> &) const;
    char const * GetDescription() const;
    int GetEditFlags() const;
    char const * GetEditorName() const;
    int GetFlags() const;
    char const * GetName() const;
    char const * GetPreviousName() const;
    ERTTIType GetType() const;
    void InitName();
    bool Initialize(char const *,char const *,unsigned char);
    bool IsExpanded() const;
    bool IsPresetFlagSet() const;
    void ReleaseName(unsigned char);
    void SetDescription(char const *);
    void SetExpanded(bool) const;
    void SetPresetFlag(bool) const;
    void UnpackAdditionalDataPacket(char const *);

    virtual ~CRTTIField();
    virtual ttl::string_base<char> const ClampString(char const *) const;
    //virtual bool Copy(CRTTIObject *,CRTTIObject const *) const;
    //virtual bool Exchange(CRTTIObject *,CRTTIObject *) const;
    virtual int GetCompressedFieldType() const;
    virtual void * GetCompressionInfo() const;
    virtual bool GetDataRange(unsigned int *,unsigned int *) const;
    virtual bool IsPrivateObject() const;
    virtual bool ParseInitToken(char,char const *);
    virtual void SetAdditionalData(char const *);

    //I didn't check if this is accurate, taken from DI also
    std::uint8_t            m_InitFlags;
    ttl::string_base<char>  m_Name;
    ERTTIType               m_Type;
    int                     m_Flags;
    int                     m_EditFlags;
    ttl::string_base<char>  m_Category;
    ttl::string_base<char>  m_Description;
    ttl::string_base<char>  m_AdditionalData;
    ttl::string_base<char>  m_PreviousName;
};


template<typename T>
class ENGINE_API CRTTIFieldCompressed : public CRTTIField {
    CRTTIFieldCompressed<T>(const CRTTIFieldCompressed<T>&);
    CRTTIFieldCompressed<T>();
    void SetCompression(ECompressedFieldType::TYPE,char,char);
    void SetCompression(ECompressedFieldType::TYPE,char,char,int);
    void SetVector3Compression(ECompressedFieldType::TYPE,float,float,int,float,float,int,float,float,int);
    void SetVector4Compression(ECompressedFieldType::TYPE,float,float,int,float,float,int,float,float,int,float,float,int);
    virtual ~CRTTIFieldCompressed<T>();
    virtual int GetCompressedFieldType() const;
    virtual void * GetCompressionInfo() const;
};