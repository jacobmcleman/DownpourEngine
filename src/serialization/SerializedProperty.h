#ifndef _SERIALIZEDPROPERTY_H
#define _SERIALIZEDPROPERTY_H

#include <unordered_set>
#include <type_traits>

#include "Serializable.h"
#include "../utils/Property.h"

namespace Downpour
{
    class SerializedObject; 

    class SerializedPropertyBase : public Serializable
    {
    public:
        SerializedPropertyBase(
            const std::string& name,
            SerializedObject* owner);

        std::string GetName() const;
        void SetName(const std::string& name);
    };

    template<typename T>
    class SerializedProperty : public SerializedPropertyBase
    {
        static_assert(is_serializable<T>::value, "Type in Serialized Property must be Serializable");

        public:
            virtual std::string GetData() const;
            virtual void SetData(const std::string& data);

        private:
            T data_;
    };

    class SerializedObject : public Serializable
    {   
        public:

            

        private:
            std::unordered_set<SerializedPropertyBase*> members;
    };
        
}

#endif