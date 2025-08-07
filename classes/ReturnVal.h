#pragma once

#include <type_traits>

#include <classes/CRef.h>
#include <concepts>

/**
 * @file ReturnVal.h
 * 
 * @brief Contains the declaration for Util::ReturnVal<T, Error>
 *		  as well as relevant functions and classes such as Util::FunctionFail<Error>
 */

namespace PashaBibko::Util
{
	/**
	 * @brief Default error class for Uti::ReturnVal
	 */
	struct DefaultError
	{
		/* Default constructor */
		DefaultError()
			: message("NO REASON PROVIDED") {}

		/* Pass an error message for the error handling to use */
		DefaultError(const char* _message)
			: message(_message) {}

		/* The error message */
		const char* message;
	};

	/**
	 * @brief Class to create when a function fails
	 */
	template<typename Err_Ty = DefaultError>
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

		/* Public to allow for easy access */
		Err_Ty error;
	};

	/**
	 * @brief Class to either return a result or an error type from a function 
	 */
	template<typename Res_Ty, typename Err_Ty = DefaultError>
		requires (!std::same_as<Res_Ty, void>) && (!std::same_as<Err_Ty, void>)
	class ReturnVal
	{
		public:
			/* Copies the sucess result */
			ReturnVal(Res_Ty _result)
				: m_Result(_result), m_FunctionFailed(false)
			{}

			/* Moves the contents of a Util::FunctionFail<Err_Ty> to a Util::ReturnVal */
			ReturnVal(FunctionFail<Err_Ty>&& _error)
				: m_Error(std::move(_error.error)), m_FunctionFailed(true)
			{}

			/* Returns a const reference to the result */
			inline CRef<Res_Ty> Result() const
			{
				return CRef<Res_Ty>(m_Result);
			}

			/* Returns a const reference to the error */
			inline CRef<Err_Ty> Error() const
			{
				return CRef<Err_Ty>(m_Error);
			}

			/* Returns wether the function failed */
			inline bool Failed() const { return m_FunctionFailed; }

			/* Returns wether the function suceeded */
			inline bool Success() const { return !m_FunctionFailed; }

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
