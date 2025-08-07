#pragma once

/**
 * @file CRef.h
 * 
 * @brief Contains util classes for using constant references.
 */

namespace PashaBibko::Util
{
	/**
	 * @brief Wrapper for `const Ty&`
	 * 
	 * @details There is no difference between using this and a const reference
	 * 			apart unless you are working in a context where the type (Ty)
	 * 			may be void as CRef has a template specialisation for void.
	 * 
	 * @tparam Ty The type that is being held excluding the const reference.
	 * 
	 * @par Example:
	 * @code
	 * #include <iostream>
	 * #include <string>
	 * 
	 * // A function that takes a CRef<T> and prints its value
	 * template<typename T>
	 * void PrintValue(CRef<T> value)
	 * {
	 *     std::cout << "Value: " << value << '\\n';
	 * }
	 * 
	 * // A specialization for void, where nothing is printed
	 * void PrintValue(CRef<void>)
	 * {
	 *     std::cout << "Void reference - nothing to print.\\n";
	 * }
	 * 
	 * int main()
	 * {
	 *     int num = 42;
	 *     std::string text = "Hello, world!";
	 * 
	 *     // Using CRef with int and string
	 *     CRef<int> intRef(num);
	 *     CRef<std::string> stringRef(text);
	 * 
	 *     PrintValue(intRef);        // Output: Value: 42
	 *     PrintValue(stringRef);     // Output: Value: Hello, world!
	 * 
	 *     // Using CRef<void>
	 *     CRef<void> voidRef;
	 *     PrintValue(voidRef);       // Output: Void reference - nothing to print.
	 * 
	 *     return 0;
	 * }
	 * @endcode
	 */
	template<typename Ty>
	class CRef
	{
		public:
			/**
			 * @brief Construct a new CRef object with the given reference
			 */
			CRef(const Ty& _ref)
				: m_Ref(_ref)
			{}

			/**
			 * @brief Allows use of the class like a normal reference
			 */
			operator const Ty& () const { return m_Ref; }

		private:
			const Ty& m_Ref;
	};

	/**
	 * @brief Template specialisation for CRef<void>
	 * 
	 * @details Instead of returning a reference to void (which is illegal in C++)
	 * 			the operator overload is set to just return void. For more information
	 * 			see Util::Cref.
	 */
	template<>
	class CRef<void>
	{
		public:
			/**
			 * @brief Construct a new CRef object
			 */
			CRef() = default;

			/**
			 * @brief Allows the class to be treated as void
			 */
			operator void() const { return; }
	};
}
