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

class DataContainer
{
public:
    DataContainer(): value_(NoValue) {}
    virtual ~DataContainer() = default;

    template <class T>
    DataContainer(T value)
    {
        setValue(value);
    }

    DataContainer(const DataContainer& other)
    {
        value_ = other.value_;
    }

    DataContainer(DataContainer&& other)
    {
        printf("DataContainer rvalues\n");
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
    DataContainer& operator =(T rhs)
    {
        setValue(rhs);
        return *this;
    }

    DataContainer& operator =(const DataContainer& other)
    {
        value_ = other.value_;
        return *this;
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
inline void DataContainer::setValue<std::string>(std::string value)
{
    value_ = std::move(value);
}
template <>
inline std::string DataContainer::getValue<std::string>()
{
    return value_;
}

}
}
}

#endif //ELFBOX_MESSAGEVARIANT_H
