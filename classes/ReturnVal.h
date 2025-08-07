#pragma once

#include <type_traits>

/**
 * @file ReturnVal.h
 * @brief Contains the declaration for Util::ReturnVal<T, Error>
 *		  as well as relevant functions and classes such as Util::FunctionFail<Error>
 */

namespace PashaBibko::Util
{
	/**
	 * @brief Class to create when a function fails
	 */
	template<typename Err_Ty>
	struct FunctionFail
	{
		/* Copies an error to within the class */
		explicit FunctionFail(Err_Ty _error)
			: error(_error)
		{}

		/* Constructs the error object with the object creation */
		template<typename... Args>
			requires std::is_constructible_v<Err_Ty, Args...>
		explicit FunctionFail(Args&&... args)
			: error(std::forward<Args>(args)...)
		{}

		/* Public to allow for easy access but marked const to avoid accidental changes */
		const Err_Ty error;
	};

	/**
	 * @brief Class to either return a result or an error type from a function 
	 */
	template<typename Res_Ty, typename Err_Ty>
	class ReturnVal
	{
		public:
			/* Copies the sucess result */
			ReturnVal(const Res_Ty& _result)
				: m_Result(_result), m_FunctionFailed(false)
			{}

			/* Moves the contents of a Util::FunctionFail<Err_Ty> to a Util::ReturnVal */
			ReturnVal(FunctionFail<Err_Ty>&& _error)
				: m_Error(std::move(_error.error)), m_FunctionFailed(true)
			{}

		private:
			/* Union to hold either the result or the error */
			union
			{
				Res_Ty m_Result;
				Err_Ty m_Error;
			};

			/* Holds wether the function failed or not */
			const bool m_FunctionFailed;
	};
}
