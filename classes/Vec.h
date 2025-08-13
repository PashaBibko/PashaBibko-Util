#pragma once

#include <type_traits>
#include <utility>
#include <cstddef>

namespace PashaBibko::Util
{
    namespace Internal
    {
        template<std::size_t len, typename Ty, typename Enable = void>
        struct VecMembers
        {
            Ty data[len];

            template<typename... Args> VecMembers(Args&&... args) : data{ std::forward<Args>(args)... } {}
        };

        template<std::size_t len, typename Ty>
        struct VecMembers<len, Ty, std::enable_if_t<(len == 2)>>
        {
            union
            {
                struct { Ty x, y; };
                Ty data[2];
            };

            template<typename... Args> VecMembers(Args&&... args) : data{ std::forward<Args>(args)... } {}
        };

        template<std::size_t len, typename Ty>
        struct VecMembers<len, Ty, std::enable_if_t<(len == 3)>>
        {
            union
            {
                struct { Ty x, y, z; };
                struct { Ty r, g, b; };
                Ty data[3];
            };

            template<typename... Args> VecMembers(Args&&... args) : data{ std::forward<Args>(args)... } {}
        };

        template<std::size_t len, typename Ty>
        struct VecMembers<len, Ty, std::enable_if_t<(len == 4)>>
        {
            union
            {
                struct { Ty x, y, z, w; };
                struct { Ty r, g, b, a; };
                Ty data[4];
            };

            template<typename... Args> VecMembers(Args&&... args) : data{ std::forward<Args>(args)... } {}
        };

        template<typename Ty, typename... Args>
        concept AllSameType = (std::is_same_v<Ty, Args> && ...);

        template<typename LhsTy, typename RhsTy>
        concept CanAdd = requires(LhsTy lhs, RhsTy rhs)
        {
            { lhs + rhs } -> std::same_as<decltype(lhs + rhs)>;
        };

        template<typename LhsTy, typename RhsTy>
        using AddResultT = decltype(std::declval<LhsTy>() + std::declval<RhsTy>());

        template<typename LhsTy, typename RhsTy>
        concept CanSub = requires(LhsTy lhs, RhsTy rhs)
        {
            { lhs - rhs } -> std::same_as<decltype(lhs - rhs)>;
        };

        template<typename LhsTy, typename RhsTy>
        using SubResultT = decltype(std::declval<LhsTy>() + std::declval<RhsTy>());

        template<typename LhsTy, typename RhsTy>
        concept CanMul = requires(LhsTy lhs, RhsTy rhs)
        {
            { lhs * rhs } -> std::same_as<decltype(lhs * rhs)>;
        };

        template<typename LhsTy, typename RhsTy>
        using MulResultT = decltype(std::declval<LhsTy>() * std::declval<RhsTy>());

        template<typename LhsTy, typename RhsTy>
        concept CanDiv = requires(LhsTy lhs, RhsTy rhs)
        {
            { lhs / rhs } -> std::same_as<decltype(lhs + rhs)>;
        };

        template<typename LhsTy, typename RhsTy>
        using DivResultT = decltype(std::declval<LhsTy>() / std::declval<RhsTy>());

        template<typename LhsTy, typename RhsTy>
        concept CanEqualityCheck = requires(LhsTy lhs, RhsTy rhs)
        {
            { lhs == rhs } -> std::convertible_to<bool>;
            { lhs != rhs } -> std::convertible_to<bool>;
        };
    }

    template<std::size_t len, typename Ty>
        requires (len != 0 && len != 1)
    struct Vec : public Internal::VecMembers<len, Ty>
    {
        Vec()
        {
            for (std::size_t index = 0; index < len; index++)
                this->data[index] = Ty{};
        }

        explicit Vec(const Ty& value)
        {
            for (std::size_t index = 0; index < len; index++)
                this->data[index] = value;
        }

        template<typename... Args>
            requires Internal::AllSameType<Ty, Args...> && (sizeof...(Args) == len)
        explicit Vec(Args&&... args) : Internal::VecMembers<len, Ty>(std::forward<Args>(args)...) {}

        Ty& operator[](std::size_t index) { return this->data[index]; }
        const Ty& operator[](std::size_t index) const { return this->data[index]; }

        Ty* begin() noexcept { return this->data; }
        const Ty* begin() const noexcept { return this->data; }
        const Ty* cbegin() const noexcept { return this->data; }

        Ty* end() { return this->data + len; }
        const Ty* end() const noexcept { return this->data + len; }
        const Ty* cend() const noexcept { return this->data + len; }

        template<typename OtherTy>
            requires Internal::CanAdd<Ty, OtherTy> && std::is_same_v<Ty, Internal::AddResultT<Ty, OtherTy>>
        Vec& operator+= (const Vec<len, OtherTy>& other)
        {
            for (std::size_t index = 0; index < len; index++)
                this->data[index] += other[index];

            return *this;
        }

        template<typename OtherTy>
            requires Internal::CanSub<Ty, OtherTy> && std::is_same_v<Ty, Internal::SubResultT<Ty, OtherTy>>
        Vec& operator-= (const Vec<len, OtherTy>& other)
        {
            for (std::size_t index = 0; index < len; index++)
                this->data[index] += other[index];

            return *this;
        }

        template<typename OtherTy>
            requires Internal::CanMul<Ty, OtherTy> && std::is_same_v<Ty, Internal::MulResultT<Ty, OtherTy>>
        Vec& operator*= (const Vec<len, OtherTy>& other)
        {
            for (std::size_t index = 0; index < len; index++)
                this->data[index] += other[index];

            return *this;
        }

        template<typename OtherTy>
            requires Internal::CanDiv<Ty, OtherTy> && std::is_same_v<Ty, Internal::DivResultT<Ty, OtherTy>>
        Vec& operator/= (const Vec<len, OtherTy>& other)
        {
            for (std::size_t index = 0; index < len; index++)
                this->data[index] += other[index];

            return *this;
        }
    };

    template<std::size_t len, typename LhsTy, typename RhsTy, typename ResTy = Internal::AddResultT<LhsTy, RhsTy>>
        requires Internal::CanAdd<LhsTy, RhsTy>
    Vec<len, ResTy> operator+ (const Vec<len, LhsTy>& lhs, const Vec<len, RhsTy>& rhs)
    {
        return [&]<std::size_t... index>(std::index_sequence<index...>) { return Vec<len, ResTy>{ (lhs[index] + rhs[index])... }; } (std::make_index_sequence<len>{});
    }

    template<std::size_t len, typename LhsTy, typename RhsTy, typename ResTy = Internal::SubResultT<LhsTy, RhsTy>>
        requires Internal::CanSub<LhsTy, RhsTy>
    Vec<len, ResTy> operator- (const Vec<len, LhsTy>& lhs, const Vec<len, RhsTy>& rhs)
    {
        return [&]<std::size_t... index>(std::index_sequence<index...>) { return Vec<len, ResTy>{ (lhs[index] - rhs[index])... }; } (std::make_index_sequence<len>{});
    }

    template<std::size_t len, typename LhsTy, typename RhsTy, typename ResTy = Internal::MulResultT<LhsTy, RhsTy>>
        requires Internal::CanMul<LhsTy, RhsTy>
    Vec<len, ResTy> operator* (const Vec<len, LhsTy>& lhs, const Vec<len, RhsTy>& rhs)
    {
        return [&]<std::size_t... index>(std::index_sequence<index...>) { return Vec<len, ResTy>{ (lhs[index] * rhs[index])... }; } (std::make_index_sequence<len>{});
    }

    template<std::size_t len, typename LhsTy, typename RhsTy, typename ResTy = Internal::SubResultT<LhsTy, RhsTy>>
        requires Internal::CanDiv<LhsTy, RhsTy>
    Vec<len, ResTy> operator/ (const Vec<len, LhsTy>& lhs, const Vec<len, RhsTy>& rhs)
    {
        return [&]<std::size_t... index>(std::index_sequence<index...>) { return Vec<len, ResTy>{ (lhs[index] / rhs[index])... }; } (std::make_index_sequence<len>{});
    }

    template<std::size_t len, typename LhsTy, typename RhsTy>
        requires Internal::CanEqualityCheck<LhsTy, RhsTy>
    bool operator== (const Vec<len, LhsTy>& lhs, const Vec<len, RhsTy>& rhs)
    {
        for (std::size_t index = 0; index < len; index++)
        {
            if (lhs[index] != rhs[index])
                return false;
        }

        return true;
    }

    template<std::size_t len, typename LhsTy, typename RhsTy>
        requires Internal::CanEqualityCheck<LhsTy, RhsTy>
    bool operator!= (const Vec<len, LhsTy>& lhs, const Vec<len, RhsTy>& rhs)
    {
        for (size_t index = 0; index < len; index++)
        {
            if (lhs[index] == rhs[index])
                return false;
        }

        return true;
    }
}
