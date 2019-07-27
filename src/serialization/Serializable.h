#ifndef _SERIALIZABLE_H
#define _SERIALIZABLE_H

#include <charconv>
#include <exception>
#include <string>
#include <string_view>
#include <type_traits>

#include "BaseTypes.h"

namespace Downpour
{
    class Serializable
    {
        public:
            virtual std::string GetData() const = 0;
            virtual void SetData(const std::string_view& data) = 0;
    };

    template<typename T>
    struct is_serializable
    {
        constexpr static bool value = std::is_base_of<T, Serializable>::value;
    };

    struct DeserializeException: public std::exception
    {
        std::string badStr;
        std::string attemptedType;
        std::string failReason;

        virtual const char* what() const throw()
        {
            return "Failed to deserialize";
        }
    };

    std::string Serialize(const Serializable& s);
    std::string Serialize(bool s);
    std::string Serialize(char s);
    std::string Serialize(short s);
    std::string Serialize(int s);
    std::string Serialize(long s);
    std::string Serialize(long long s);
    std::string Serialize(Types::byte s);
    std::string Serialize(Types::index_t s);
    std::string Serialize(Types::id_t s);
    std::string Serialize(const std::string_view& s);

    template<typename T>
    T Deserialize(const std::string_view& str) 
    {
        static_assert(is_serializable<T>::value, "Type given to Deserialize was not serializable");
        static_assert(std::is_default_constructible<T>::value, "Type given to Deserialize must be default constructable");
        static_assert)
        T deserialized;
        deserialized.SetData(str)
        return deserialized;
    }

    template<>
    bool Deserialize<bool>(const std::string_view& str) 
    {
        if(str == "true") return true;
        if(str == "false") return false;

        DeserializeException e;
        e.badStr = str;
        e.attemptedType = "bool";
        e.failReason = "Expected \"true\" or \"false\"";
        throw e;
    }

    template<>
    char Deserialize<char>(const std::string_view& str) 
    {
        if(str.length == 1) return str[0];

        DeserializeException e;
        e.badStr = str;
        e.attemptedType = "char";
        e.failReason = "Given input was not a single character";
        throw e;
    }

#define DeserializeSpecializationForNumericType(numtype)                                                        \
    template<>                                                                                                  \
    numtype Deserialize<numtype>(const std::string_view& str)                                                   \
    {                                                                                                           \
        numtype value;                                                                                          \
        auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.length(), value);                         \
        if(ec == std::errc()) return value;                                                                     \
                                                                                                                \
        DeserializeException e;                                                                                 \
        e.badStr = str;                                                                                         \
        e.attemptedType = #numtype ;                                                                            \
        if(ec == std::errc::invalid_argument) e.failReason = "String not a valid " #numtype;                    \
        else if(ec == std::errc::result_out_of_range) e.failReason = "Parsed value out of range of " #numtype;  \
        else e.failReason = "Failed to parse " #numtype;                                                        \
        throw e;                                                                                                \
    }                                                                                                           

    DeserializeSpecializationForNumericType(Types::byte);
    DeserializeSpecializationForNumericType(Types::index_t);
    DeserializeSpecializationForNumericType(Types::id_t);
    DeserializeSpecializationForNumericType(int16_t);
    DeserializeSpecializationForNumericType(uint16_t);
    DeserializeSpecializationForNumericType(int32_t);
    DeserializeSpecializationForNumericType(uint32_t);
    DeserializeSpecializationForNumericType(int64_t);
    DeserializeSpecializationForNumericType(uint64_t);
    DeserializeSpecializationForNumericType(float);
    DeserializeSpecializationForNumericType(double);

}

#endif