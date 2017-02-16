//
// Created by Lewis on 2017/2/14.
//

#ifndef ELFBOX_MESSAGEVARIANT_H
#define ELFBOX_MESSAGEVARIANT_H

#include <string>
#include <sstream>
#include <unordered_map>
#include <common/IObject.h>
#include <common/Context.h>

namespace elfbox
{
namespace common
{
namespace detail
{
const std::string NoValue = "NoValue";

template <typename T>
T lexical_cast(const std::string& str)
{
    T var;
    std::istringstream iss;
    iss.str(str);
    iss >> var;
    // TODO: deal with any error bits that may have been set on the stream
    return var;
}

class MessageVariant
{
public:
    MessageVariant(): value_(NoValue) {}
    virtual ~MessageVariant() = default;

    template <class T>
    MessageVariant(T value)
    {
        setValue(value);
    }

    MessageVariant(const MessageVariant& other)
    {
        value_ = other.value_;
    }

    MessageVariant(MessageVariant&& other)
    {
        value_ = std::move(other.value_);
    }

    template <class T>
    void setValue (T value)
    {
        value_ = std::to_string(value);
    }

    template <class T>
    T getValue ()
    {
        return lexical_cast<T>(value_);
    }

    template <class T>
    MessageVariant& operator =(T rhs)
    {
        setValue(rhs);
    }

    MessageVariant& operator =(const MessageVariant& other)
    {
        value_ = other.value_;
    }

    template <class T>
    operator T()
    {
        return getValue<T>();
    }

private:
    std::string value_;
};

template <>
inline void MessageVariant::setValue<std::string>(std::string value)
{
    value_ = value;
}
template <>
inline std::string MessageVariant::getValue<std::string>()
{
    return value_;
}

}
}
}

#endif //ELFBOX_MESSAGEVARIANT_H
