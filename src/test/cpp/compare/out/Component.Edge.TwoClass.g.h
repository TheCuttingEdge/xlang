﻿// WARNING: Please don't edit this file. It was generated by C++/WinRT v2.0.000000.0
#pragma once
#include "winrt/Component.Edge.h"
namespace winrt::Component::Edge::implementation
{
    template <typename D, typename... I>
    struct WINRT_EBO TwoClass_base : implements<D, Component::Edge::ITwoClass, I...>
    {
        using base_type = TwoClass_base;
        using class_type = Component::Edge::TwoClass;
        using implements_type = typename TwoClass_base::implements_type;
        using implements_type::implements_type;
        
        operator impl::producer_ref<class_type> const() const noexcept
        {
            return { to_abi<default_interface<class_type>>(this) };
        }

        hstring GetRuntimeClassName() const
        {
            return L"Component.Edge.TwoClass";
        }
    };
}
namespace winrt::Component::Edge::factory_implementation
{
    template <typename D, typename T, typename... I>
    struct WINRT_EBO TwoClassT : implements<D, Windows::Foundation::IActivationFactory, Component::Edge::ITwoClassFactory, Component::Edge::ITwoClassStatics, I...>
    {
        using instance_type = Component::Edge::TwoClass;

        hstring GetRuntimeClassName() const
        {
            return L"Component.Edge.TwoClass";
        }
        Component::Edge::TwoClass CreateInstance(int32_t a, int32_t b)
        {
            return make<T>(a, b);
        }
        void StaticMethod(int32_t a, int32_t b)
        {
            return T::StaticMethod(a, b);
        }
        [[noreturn]] Windows::Foundation::IInspectable ActivateInstance() const
        {
            throw hresult_not_implemented();
        }
    };
}

#if defined(WINRT_FORCE_INCLUDE_TWOCLASS_XAML_G_H) || __has_include("Component.Edge.TwoClass.xaml.g.h")
#include "Component.Edge.TwoClass.xaml.g.h"
#else

namespace winrt::Component::Edge::implementation
{
    template <typename D, typename... I>
    using TwoClassT = TwoClass_base<D, I...>;
}

#endif
