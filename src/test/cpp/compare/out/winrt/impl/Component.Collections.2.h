﻿// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.000000.0
#pragma once
#include "winrt/impl/Component.Collections.1.h"
namespace winrt::Component::Collections
{
    struct Class
    {
        Class() = delete;
        static Windows::Foundation::Collections::IIterable<hstring> Iterable();
        static Windows::Foundation::Collections::IVectorView<hstring> VectorView();
        static Windows::Foundation::Collections::IVector<hstring> Vector();
        static Windows::Foundation::Collections::IIterable<Windows::Foundation::Collections::IKeyValuePair<hstring, int32_t>> IterablePair();
        static Windows::Foundation::Collections::IMapView<hstring, int32_t> MapView();
        static Windows::Foundation::Collections::IMap<hstring, int32_t> Map();
    };
}
