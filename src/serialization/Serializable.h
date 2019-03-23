#ifndef _SERIALIZABLE_H
#define _SERIALIZABLE_H

#include <string>

namespace Downpour
{
    class Serializable
    {
        public:
            virtual std::string GetData() const = 0;
            virtual void SetData(const std::string& data) = 0;

    };

    template<typename T>
    struct is_serializable
    {
        constexpr static bool value = std::is_base_of<T, Serializable>::value;
    }
}

#endif