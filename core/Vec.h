#pragma once

#include <cstddef>

#include <core/Log.h>

/**
 * @file Vec.h
 * 
 * @brief Contains the defenition of Vec<Len, Ty> with operator overloads
 *        for mathmatical expressions.
 */

namespace PashaBibko::Util
{
    /* Excludes the internal namespace from the documentation */
    #ifndef DOXYGEN_HIDE

    namespace Internal
    {
        /* General layout of a Vec<T> with just an array of x length */
        template<std::size_t len, typename Ty, typename Enable = void>
        struct VecMembers
        {
            Ty data[len];

            template<typename... Args> VecMembers(Args&&... args) : data{ std::forward<Args>(args)... } {}
        };

        /* Provides aliases of [X, Y] to indecies of [0, 1] to the array when of length 2 */
        template<std::size_t len, typename Ty>
        struct VecMembers<len, Ty, std::enable_if_t<(len == 2)>>
        {
            union
            {
                struct { Ty x, y; };
                Ty data[2];
            };

            template<typename... Args> VecMembers(Args&&... args) : data{ std::forward<Args>(args)... } {}

            CREATE_CUSTOM_LOG_ITERATOR_FUNCTION
            {
                if (index = 0)
                    os << "x";

                else
                    os << "y";
            }
        };

        /* Provides aliases of [X, Y, Z] and [R, G, B] to indecies of [0, 1, 2] to the array when of length 3 */
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

            CREATE_CUSTOM_LOG_ITERATOR_FUNCTION
            {
                if (index == 0)
                    os << "x";

                else if (index == 1)
                    os << "y";

                else
                    os << "z";
            }
        };

        /* Provides aliases of [X, Y, Z, Z] and [R, G, B, A] to indecies of [0, 1, 2, 3] to the array when of length 4 */
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

            CREATE_CUSTOM_LOG_ITERATOR_FUNCTION
            {
                if (index == 0)
                    os << "x";

                else if (index == 1)
                    os << "y";

                else if (index == 2)
                    os << "z";

                else
                    os << "w";
            }
        };

        /* Checks all types within a variadic template are the same */
        template<typename Ty, typename... Args> concept AllSameType = (std::is_same_v<Ty, Args> && ...);

        /* Checks types can be added together */
        template<typename LhsTy, typename RhsTy>
        concept CanAdd = requires(LhsTy lhs, RhsTy rhs)
        {
            { lhs + rhs } -> std::same_as<decltype(lhs + rhs)>;
        };

        /* The result type when two types are added to each other */
        template<typename LhsTy, typename RhsTy>
        using AddResultT = decltype(std::declval<LhsTy>() + std::declval<RhsTy>());

        /* Checks two types can be subtracted from each other */
        template<typename LhsTy, typename RhsTy>
        concept CanSub = requires(LhsTy lhs, RhsTy rhs)
        {
            { lhs - rhs } -> std::same_as<decltype(lhs - rhs)>;
        };

        /* The result type when two types are subtracted from each other */
        template<typename LhsTy, typename RhsTy>
        using SubResultT = decltype(std::declval<LhsTy>() + std::declval<RhsTy>());

        /* Checks two types can be multipled together */
        template<typename LhsTy, typename RhsTy>
        concept CanMul = requires(LhsTy lhs, RhsTy rhs)
        {
            { lhs * rhs } -> std::same_as<decltype(lhs * rhs)>;
        };

        /* The result type when two types are multiplied to each other */
        template<typename LhsTy, typename RhsTy>
        using MulResultT = decltype(std::declval<LhsTy>() * std::declval<RhsTy>());

        /* Checks two types can be divided from each other */
        template<typename LhsTy, typename RhsTy>
        concept CanDiv = requires(LhsTy lhs, RhsTy rhs)
        {
            { lhs / rhs } -> std::same_as<decltype(lhs + rhs)>;
        };

        /* The result type when two types are divided from each other */
        template<typename LhsTy, typename RhsTy>
        using DivResultT = decltype(std::declval<LhsTy>() / std::declval<RhsTy>());

        /* Checks the types can be compared equally */
        template<typename LhsTy, typename RhsTy>
        concept CanEqualityCheck = requires(LhsTy lhs, RhsTy rhs)
        {
            { lhs == rhs } -> std::convertible_to<bool>;
            { lhs != rhs } -> std::convertible_to<bool>;
        };
    }

    #endif // DOXYGEN_HIDE

    /**
     * @brief Mathmatical vector class.
     * 
     * @tparam len The length of the array, cannot be 0 or 1.
     * @tparam Ty The type that the vector contains must be copyable.
     * 
     * @details The `Vec` class is a fixed-size, strongly-typed mathematical vector implementation
     *          that supports compile-time size checking and type constraints. It is designed for 
     *          mathematical operations and performance-critical applications where a fixed size 
     *          and no dynamic memory allocation are desired.
     * 
     *          For convenience whilst using there are also multiple
     *          typedefs for easier recognition of common Vec types.
     *          For vectors between size of 2 and 4 you are able to
     *          write Vec2<Ty> / Vec3<Ty> / Vec4<Ty> where Ty is the
     *          type that you want the vector to contain. If no type
     *          is provided it will default to float.
     * 
     *          Combined with this, there are also typedefs of these
     *          lengths with the types. Below are the Vec2 types but
     *          the number can be changed to work with Vec3 and Vec4.
     *          - short         = Vec2s
     *          - int           = Vec2i
     *          - unsigned int  = Vec2u
     *          - long          = Vec2l
     *          - double        = Vec2d
     * 
     *          For further convenience vectors between the lengths of
     *          2 and 4 allow access to their members via letters:
     *          - x = data[0]
     *          - y = data[1]
     *          - z = data[2]
     *          - w = data[3]
     * 
     *          If you are working with colours you are also able to use
     *          those letters (only available on Vec3 and Vec4):
     *          - r = data[0]
     *          - g = data[1]
     *          - b = data[2]
     *          - a = data[3]
     * 
     *          Letters are only availble if the vector is already that long,
     *          for example: Vec2 only has access to x and y as it is only
     *          2 elements long.
     * 
     *          Example usage:
     * @code
     * #include <iostream>
     * 
     * int main()
     * {
     *     // Create a 3D vector with all elements default-initialized to 0
     *     Vec3 a;
     * 
     *     // Create a vector where all elements are set to 5.0f
     *     Vec3 b(5.0f);
     * 
     *     // Create a vector from individual values
     *     Vec3 c(1.0f, 2.0f, 3.0f);
     * 
     *     // Access and modify an element
     *     c.x = 10.0f;
     * 
     *     // Iterate over vector elements
     *     for (float value : c)
     *     {
     *         std::cout << value << " ";
     *     }
     *     std::cout << "\n";
     * 
     *     // Add two vectors
     *     c += b; // element-wise addition
     * 
     *     // Print result
     *     for (float value : c)
     *     {
     *         std::cout << value << " ";
     *     }
     *     std::cout << "\n";
     * 
     *     return 0;
     * }
     * @endcode
     */
    template<std::size_t len, typename Ty>
        requires (len != 0 && len != 1) && std::is_copy_constructible_v<Ty>
    struct Vec : public Internal::VecMembers<len, Ty>
    {
        /**
         * @brief Default constructor which default constructs all items.
         * 
         * @details Will only be available if Ty has a default constructor
         *          to avoid compile-time errors.
         */
        template<typename = std::enable_if_t<std::is_default_constructible_v<Ty>>>
        Vec()
        {
            for (std::size_t index = 0; index < len; index++)
                this->data[index] = Ty{};
        }

        /**
         * @brief Constructor to create each item in the vector with a given value.
         * 
         * @param value The value that will be copied to all values within the vector.
         */
        explicit Vec(const Ty& value)
        {
            for (std::size_t index = 0; index < len; index++)
                this->data[index] = value;
        }

        /**
         * @brief Creates a vector with a given value for each item.
         * 
         * @param args The arguments that will be copied to the contents of the vector.
         * 
         * @details Requires all arguments to be the same type as Ty and have the same
         *          length as the array or will have a compile-time error.
         */
        template<typename... Args> requires Internal::AllSameType<Ty, Args...> && (sizeof...(Args) == len)
        explicit Vec(Args&&... args) : Internal::VecMembers<len, Ty>(std::forward<Args>(args)...) {}

        /**
         * @brief Returns a reference to the item at that index.
         * 
         * @param index The index that it will find the item of.
         * 
         * @warning The function does not check if the index is within
         *          the bounds of the vector. Accessing elements not
         *          within the bounds is classified as UB.
         */
        Ty& operator[](std::size_t index) { return this->data[index]; }

        /**
         * @brief Returns a pointer to the beginning of the array.
         * 
         * @details Used by C++ to allow the data type to be iterated
         *          over by a range for loop.
         */
        Ty* begin() noexcept { return this->data; }

        /**
         * @brief Returns a pointer to the end of the vector.
         * 
         * @details Used by C++ to allow the data type to be iterated
         *          over by a range for loop.
         */
        Ty* end() { return this->data + len; }

        /* Hides const versions of functions as they do not need to be documented twice */
        #ifndef DOXYGEN_HIDE

        const Ty& operator[](std::size_t index) const { return this->data[index]; }

        const Ty* begin() const noexcept { return this->data; }
        const Ty* cbegin() const noexcept { return this->data; }

        const Ty* end() const noexcept { return this->data + len; }
        const Ty* cend() const noexcept { return this->data + len; }

        #endif // DOXYGEN_HIDE

        /**
         * @brief Adds another vector of the same size to itself.
         * 
         * @details Requires OtherTy to be able to be added to Ty,
         *          otherwise it will not compile and the result type
         *          to be the same as Ty.
         */
        template<typename OtherTy>
            requires Internal::CanAdd<Ty, OtherTy> && std::is_same_v<Ty, Internal::AddResultT<Ty, OtherTy>>
        Vec& operator+= (const Vec<len, OtherTy>& other)
        {
            for (std::size_t index = 0; index < len; index++)
                this->data[index] += other[index];

            return *this;
        }

        /**
         * @brief Adds a single item of to each of the vectors elements.
         * 
         * @details Requires OtherTy to be able to be added to Ty,
         *          otherwise it will not compile and the result type
         *          to be the same as Ty.
         */
        template<typename OtherTy>
            requires Internal::CanAdd<Ty, OtherTy> && std::is_same_v<Ty, Internal::AddResultT<Ty, OtherTy>>
        Vec& operator+= (const OtherTy& other)
        {
            for (std::size_t index = 0; index < len; index++)
                this->data[index] += other;

            return *this;
        }

        /**
         * @brief Subtracts another vector of the same size to itself.
         * 
         * @details Requires OtherTy to be able to be subtracted from Ty,
         *          otherwise it will not compile and the result type
         *          to be the same as Ty.
         */
        template<typename OtherTy>
            requires Internal::CanSub<Ty, OtherTy> && std::is_same_v<Ty, Internal::SubResultT<Ty, OtherTy>>
        Vec& operator-= (const Vec<len, OtherTy>& other)
        {
            for (std::size_t index = 0; index < len; index++)
                this->data[index] -= other[index];

            return *this;
        }

        /**
         * @brief Subtracts a single item to each of the vectors elements.
         * 
         * @details Requires OtherTy to be able to be subtracted from Ty,
         *          otherwise it will not compile and the result type
         *          to be the same as Ty.
         */
        template<typename OtherTy>
            requires Internal::CanSub<Ty, OtherTy> && std::is_same_v<Ty, Internal::SubResultT<Ty, OtherTy>>
        Vec& operator-= (const OtherTy& other)
        {
            for (std::size_t index = 0; index < len; index++)
                this->data[index] -= other;

            return *this;
        }

        /**
         * @brief Multiplies another vector of the same size to itself.
         * 
         * @details Requires Ty to be able to be multipled by OtherTy,
         *          otherwise it will not compile and the result type
         *          to be the same as Ty.
         */
        template<typename OtherTy>
            requires Internal::CanMul<Ty, OtherTy> && std::is_same_v<Ty, Internal::MulResultT<Ty, OtherTy>>
        Vec& operator*= (const Vec<len, OtherTy>& other)
        {
            for (std::size_t index = 0; index < len; index++)
                this->data[index] *= other[index];

            return *this;
        }

        /**
         * @brief Multiplies a single item to each of the vectors elements.
         * 
         * @details Requires Ty to be able to be multipled by OtherTy,
         *          otherwise it will not compile and the result type
         *          to be the same as Ty.
         */
        template<typename OtherTy>
            requires Internal::CanMul<Ty, OtherTy> && std::is_same_v<Ty, Internal::MulResultT<Ty, OtherTy>>
        Vec& operator*= (const OtherTy& other)
        {
            for (std::size_t index = 0; index < len; index++)
                this->data[index] *= other;

            return *this;
        }

        /**
         * @brief Divides another vector of the same size to itself.
         * 
         * @details Requires Ty to be able to be divided by OtherTy,
         *          otherwise it will not compile and the result type
         *          to be the same as Ty.
         */
        template<typename OtherTy>
            requires Internal::CanDiv<Ty, OtherTy> && std::is_same_v<Ty, Internal::DivResultT<Ty, OtherTy>>
        Vec& operator/= (const Vec<len, OtherTy>& other)
        {
            for (std::size_t index = 0; index < len; index++)
                this->data[index] /= other[index];

            return *this;
        }

        /**
         * @brief Divides a single item to each of the vectors elements.
         * 
         * @details Requires Ty to be able to be divided by OtherTy,
         *          otherwise it will not compile and the result type
         *          to be the same as Ty.
         */
        template<typename OtherTy>
            requires Internal::CanDiv<Ty, OtherTy> && std::is_same_v<Ty, Internal::DivResultT<Ty, OtherTy>>
        Vec& operator/= (const OtherTy& other)
        {
            for (std::size_t index = 0; index < len; index++)
                this->data[index] /= other;

            return *this;
        }
    };

    /**
     * @brief Adds two vectors together.
     * 
     * @details Requires the two types contained in the vector to
     *          be able to be added together. The result type will
     *          also be the same type as when they are normally
     *          added together.
     */
    template<std::size_t len, typename LhsTy, typename RhsTy, typename ResTy = Internal::AddResultT<LhsTy, RhsTy>>
        requires Internal::CanAdd<LhsTy, RhsTy>
    Vec<len, ResTy> operator+ (const Vec<len, LhsTy>& lhs, const Vec<len, RhsTy>& rhs)
    {
        return [&]<std::size_t... index>(std::index_sequence<index...>) { return Vec<len, ResTy>{ (lhs[index] + rhs[index])... }; } (std::make_index_sequence<len>{});
    }

    /**
     * @brief Adds a single item to each element of the vector.
     * 
     * @details Requires the two types contained in the vector to
     *          be able to be added together. The result type will
     *          also be the same type as when they are normally
     *          added together.
     */
    template<std::size_t len, typename LhsTy, typename RhsTy, typename ResTy = Internal::AddResultT<LhsTy, RhsTy>>
        requires Internal::CanAdd<LhsTy, RhsTy>
    Vec<len, ResTy> operator+ (const Vec<len, LhsTy>& lhs, const RhsTy& rhs)
    {
        return [&]<std::size_t... index>(std::index_sequence<index...>) { return Vec<len, ResTy>{ (lhs[index] + rhs)... }; } (std::make_index_sequence<len>{});
    }

    /**
     * @brief Adds a single item to each element of the vector.
     * 
     * @details Requires the two types contained in the vector to
     *          be able to be added together. The result type will
     *          also be the same type as when they are normally
     *          added together.
     */
    template<std::size_t len, typename LhsTy, typename RhsTy, typename ResTy = Internal::AddResultT<LhsTy, RhsTy>>
        requires Internal::CanAdd<LhsTy, RhsTy>
    Vec<len, ResTy> operator+ (const LhsTy& lhs, const Vec<len, RhsTy>& rhs)
    {
        return [&]<std::size_t... index>(std::index_sequence<index...>) { return Vec<len, ResTy>{ (lhs + rhs[index])... }; } (std::make_index_sequence<len>{});
    }

    /**
     * @brief Subtracts the right vector by the left vector.
     * 
     * @details Requires the two types contained in the vector to
     *          be able to be subtracted from each other The result type will
     *          also be the same type as when they are normally subtracted.
     */
    template<std::size_t len, typename LhsTy, typename RhsTy, typename ResTy = Internal::SubResultT<LhsTy, RhsTy>>
        requires Internal::CanSub<LhsTy, RhsTy>
    Vec<len, ResTy> operator- (const Vec<len, LhsTy>& lhs, const Vec<len, RhsTy>& rhs)
    {
        return [&]<std::size_t... index>(std::index_sequence<index...>) { return Vec<len, ResTy>{ (lhs[index] - rhs[index])... }; } (std::make_index_sequence<len>{});
    }

    /**
     * @brief Subtracts an item from each element in a vector.
     * 
     * @details Requires the two types contained in the vector to
     *          be able to be subtracted from each other The result type will
     *          also be the same type as when they are normally subtracted.
     */
    template<std::size_t len, typename LhsTy, typename RhsTy, typename ResTy = Internal::SubResultT<LhsTy, RhsTy>>
        requires Internal::CanSub<LhsTy, RhsTy>
    Vec<len, ResTy> operator- (const Vec<len, LhsTy>& lhs, const RhsTy& rhs)
    {
        return [&]<std::size_t... index>(std::index_sequence<index...>) { return Vec<len, ResTy>{ (lhs[index] - rhs)... }; } (std::make_index_sequence<len>{});
    }

    /**
     * @brief Multiplies two vectors together.
     * 
     * @details Requires the two types contained in the vector to
     *          be able to be multiplied together. The result type will
     *          also be the same type as when they are normally
     *          multiplied together.
     */
    template<std::size_t len, typename LhsTy, typename RhsTy, typename ResTy = Internal::MulResultT<LhsTy, RhsTy>>
        requires Internal::CanMul<LhsTy, RhsTy>
    Vec<len, ResTy> operator* (const Vec<len, LhsTy>& lhs, const Vec<len, RhsTy>& rhs)
    {
        return [&]<std::size_t... index>(std::index_sequence<index...>) { return Vec<len, ResTy>{ (lhs[index] * rhs[index])... }; } (std::make_index_sequence<len>{});
    }

    /**
     * @brief Multiplies an item with each element in a vector.
     * 
     * @details Requires the two types contained in the vector to
     *          be able to be multiplied together. The result type will
     *          also be the same type as when they are normally
     *          multiplied together.
     */
    template<std::size_t len, typename LhsTy, typename RhsTy, typename ResTy = Internal::MulResultT<LhsTy, RhsTy>>
        requires Internal::CanMul<LhsTy, RhsTy>
    Vec<len, ResTy> operator* (const Vec<len, LhsTy>& lhs, const RhsTy& rhs)
    {
        return [&]<std::size_t... index>(std::index_sequence<index...>) { return Vec<len, ResTy>{ (lhs[index] * rhs)... }; } (std::make_index_sequence<len>{});
    }

    /**
     * @brief Multiplies an item with each element in a vector.
     * 
     * @details Requires the two types contained in the vector to
     *          be able to be multiplied together. The result type will
     *          also be the same type as when they are normally
     *          multiplied together.
     */
    template<std::size_t len, typename LhsTy, typename RhsTy, typename ResTy = Internal::MulResultT<LhsTy, RhsTy>>
        requires Internal::CanMul<LhsTy, RhsTy>
    Vec<len, ResTy> operator* (const LhsTy& lhs, const Vec<len, RhsTy>& rhs)
    {
        return [&]<std::size_t... index>(std::index_sequence<index...>) { return Vec<len, ResTy>{ (lhs * rhs[index])... }; } (std::make_index_sequence<len>{});
    }

    /**
     * @brief Divides the left vector by the right vector.
     * 
     * @details Requires the two types contained in the vector to
     *          be able to be divided from each other. The result type will
     *          also be the same type as when they are normally
     *          divided together.
     */
    template<std::size_t len, typename LhsTy, typename RhsTy, typename ResTy = Internal::SubResultT<LhsTy, RhsTy>>
        requires Internal::CanDiv<LhsTy, RhsTy>
    Vec<len, ResTy> operator/ (const Vec<len, LhsTy>& lhs, const Vec<len, RhsTy>& rhs)
    {
        return [&]<std::size_t... index>(std::index_sequence<index...>) { return Vec<len, ResTy>{ (lhs[index] / rhs[index])... }; } (std::make_index_sequence<len>{});
    }

    /**
     * @brief Divides each element in the vector by a single item.
     * 
     * @details Requires the two types contained in the vector to
     *          be able to be divided from each other. The result type will
     *          also be the same type as when they are normally
     *          divided together.
     */
    template<std::size_t len, typename LhsTy, typename RhsTy, typename ResTy = Internal::SubResultT<LhsTy, RhsTy>>
        requires Internal::CanDiv<LhsTy, RhsTy>
    Vec<len, ResTy> operator/ (const Vec<len, LhsTy>& lhs, const RhsTy& rhs)
    {
        return [&]<std::size_t... index>(std::index_sequence<index...>) { return Vec<len, ResTy>{ (lhs[index] / rhs)... }; } (std::make_index_sequence<len>{});
    }

    /**
     * @brief Checks if two vectors are equal.
     * 
     * @details Requires both the == and != operators to
     *          be available for both types.
     */
    template<std::size_t len, typename LhsTy, typename RhsTy>
        requires Internal::CanEqualityCheck<LhsTy, RhsTy>
    bool operator== (const Vec<len, LhsTy>& lhs, const Vec<len, RhsTy>& rhs)
    {
        /* Loops over the vector if it is considered to be long and returns early for invalid results */
        if constexpr (len > 4)
        {
            for (std::size_t index = 0; index < len; index++)
            {
                if (lhs[index] != rhs[index])
                    return false;
            }

            return true;
        }

        /* For short vectors the branching is less efficent so it is instead stored in a tracker with loop unravelling */
        else
        {
            bool allEqual = true;

            for (std::size_t index = 0; index < len; index++)
                allEqual = allEqual && (lhs[index] == rhs[index]);

            return allEqual;
        }
    }

    /**
     * @brief Checks if two vectors are not equal.
     * 
     * @details Requires both the == and != operators to
     *          be available for both types.
     */
    template<std::size_t len, typename LhsTy, typename RhsTy>
        requires Internal::CanEqualityCheck<LhsTy, RhsTy>
    bool operator!= (const Vec<len, LhsTy>& lhs, const Vec<len, RhsTy>& rhs)
    {
        return !(lhs == rhs);
    }

    /* Hides using aliases to avoid uneccesary bloat in doxygen documentation */
    /* The types are mentoined in the description of Vec<len, T>              */
    #ifndef DOXYGEN_HIDE

    template<typename Ty = float>
    using Vec2 = Vec<2, Ty>;

    template<typename Ty = float>
    using Vec3 = Vec<3, Ty>;

    template<typename Ty = float>
    using Vec4 = Vec<4, Ty>;

    using Vec2s = Vec3<short>;
    using Vec2i = Vec3<int>;
    using Vec2u = Vec3<unsigned int>;
    using Vec2l = Vec3<long>;
    using Vec2d = Vec3<double>;

    using Vec3s = Vec3<short>;
    using Vec3i = Vec3<int>;
    using Vec3u = Vec3<unsigned int>;
    using Vec3l = Vec3<long>;
    using Vec3d = Vec3<double>;

    using Vec3s = Vec3<short>;
    using Vec3i = Vec3<int>;
    using Vec3u = Vec3<unsigned int>;
    using Vec3l = Vec3<long>;
    using Vec3d = Vec3<double>;

    #endif // DOXYGEN_HIDE
}
