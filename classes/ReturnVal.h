#pragma once


#include <sections/Misc.h>

#include <type_traits>
#include <concepts>

/**
 * @file ReturnVal.h
 * 
 * @brief Contains the declaration for Util::ReturnVal<T, Error>
 *		  as well as relevant functions and classes such as Util::FunctionFail<Error>
 */

namespace PashaBibko::Util
{
	#ifndef DOXYGEN_HIDE

	/* Wether functions should check to see if the call is safe or not */
	enum class Result
	{
		Check,
		Force
	};

	/*
	 * Undocumented as it should be mentioned in all functions it is in
	 * and does not need its own section as it is essentially a boolean.
	 */

	#endif // DOXYGEN_HIDE

	/**
	 * @brief Default error class for Uti::ReturnVal.
	 * 
	 * @details Simple error type that just holds an error message.
	 * 			Meant to be used as a temporary error until proper handling is put in place.
	 */
	struct DefaultError
	{
		/**
		 * @brief Default constructor, sets the message to "NO REASON PROVIDED"
		 */
		DefaultError()
			: message("NO REASON PROVIDED") {}

		/**
		 * @brief Provide an error message for the error to carry.
		 * 
		 * @note The class does not have any ownership to the message.
		 *       If the message goes out of scope before access it will cause read-acess violations. 
		 */
		DefaultError(const char* _message)
			: message(_message) {}

		/**
		 * @brief A pointer to a c-string error message, not owned by the class/object.
		 */
		const char* message;
	};

	/**
	 * @brief Class to create when a function fails.
	 * 
	 * @details This class has no functionality and is just used to help distinguish
	 * 			between Function fails and success when using Util::ReturnVal.
	 * 
	 * @tparam Err_Ty The type of the error (cannot be void).
	 */
	template<typename Err_Ty = DefaultError>
	struct FunctionFail final
	{
		/**
		 * @brief Constructor that copies an error and stores it.
		 */
		explicit FunctionFail(Err_Ty _error)
			: error(_error)
		{}

		/**
		 * @brief Constructor that creates the error within the class.
		 * 
		 * @details Constructs the error object within the class instead of
		 * 			copying for higher performance, recommended for large error
		 * 			types. Will only show as a valid function if the parameters
		 * 			passed to the function can be used to construct the error type.
		 * 
		 * @param args The arguments that will be used to create the error object.
		 */
		template<typename... Args>
			requires std::is_constructible_v<Err_Ty, Args...>
		explicit FunctionFail(Args&&... args)
			: error(std::forward<Args>(args)...)
		{}

		/**
		 * @brief The error that the function is returning
		 */
		Err_Ty error;
	};

	/**
	 * @brief Class to return a result from a function that can fail.
	 * 
	 * @tparam Res_Ty The type of the result from the function (if there are no errors).
	 * @tparam Err_Ty The type of the error from the function.
	 * 
	 * @details Instead of throwing exceptions you can use this class as the return type
	 *          of a function to either return the result or the error. This can be especially
	 * 			useful if manually allocating/deallocating memory.
	 * 
	 * 			When you have used it as the return type of a function you do not need to
	 * 			change how you return results. However if you want to return an error out
	 * 			of the function you now do it via: `return Util::FunctionFail<Err_Ty>(args)`.
	 * 
	 * 			After you have returned the result out of a function you can check wether it
	 * 			failed or not using `result.Failed()` or `result.Succeeded()`. Depeding on
	 * 			the result you can then use `result.Result()` or `result.Error()` to get the
	 * 			value passed out of the function.
	 */
	template<typename Res_Ty, typename Err_Ty = DefaultError>
		requires (!std::same_as<Res_Ty, void>) && (!std::same_as<Err_Ty, void>)
	class ReturnVal final
	{
		public:
			/**
			 * @brief Copies the success result.
			 * 
			 * @details Recommended to use the copy-constructor for larger types.
			 */
			explicit ReturnVal(Res_Ty _result)
				: m_Result(_result), m_FunctionFailed(false)
			{}

			/**
			 * @brief Moves the success value.
			 * 
			 * @details Recommended to use for larger types.
			 */
			ReturnVal(Res_Ty&& _result)
				: m_Result(std::move(_result)), m_FunctionFailed(false)
			{}

			/**
			 * @brief Moves the contents of a Util::FunctionFail<Err_Ty> to a Util::ReturnVal.
			 * 
			 * @details Done automatically by the C++ compiler when returning a Util::FunctionFail
			 * 			so does not need to manually be called.
			 */
			ReturnVal(FunctionFail<Err_Ty>&& _error)
				: m_Error(std::move(_error.error)), m_FunctionFailed(true)
			{}

			/* Constructor is not manually called by someone using the library so it is excluded from docs */
			#ifndef DOXYGEN_HIDE

			~ReturnVal()
			{
				/* Makes sure the types deconstructor is called to avoid memory leaks */
				if (m_FunctionFailed)
					m_Error.~Err_Ty();

				else
					m_Result.~Res_Ty();
			}

			#endif

			/**
			 * @brief Returns a const reference to the error.
			 * 
			 * @tparam force Defaults to Result::Check, when set to Result::Force
			 *         the function does not check if the function has failed.
			 * 
			 * @note If checks are enabled and you try to access the error when the function has
			 * 		 succeeded it will trigger a breakpoint and end the program.
			 * 
			 * @warning Using Result::Force when the function may have succeeded can return invalid values.
			 * 			Using these values is undefined-behaviour so it is recommended to only use
			 * 			Result::Force when you are sure the function has failed.
			 */
			template<Result force = Result::Check>
			inline Err_Ty& Error()
			{
				/* Force bypasses checking if the function failed or not */
				if constexpr (force == Result::Check)
				{
					/* Ends the process if the error was tried to access on a sucessful return */
					if (!m_FunctionFailed)
						EndProcess();
				}

				/* Returns a const reference to the error */
				return m_Error;
			}

			/**
			 * @brief Returns a const reference to the result.
			 * 
			 * @tparam force Defaults to Result::Check, when set to Result::Force
			 *         the function does not check if the function has succeeded.
			 * 
			 * @note If checks are enabled and you try to access the result when the function has
			 * 		 failed it will trigger a breakpoint and end the program.
			 * 
			 * @warning Using Result::Force when the function may have failed can return invalid values.
			 * 			Using these values is undefined-behaviour so it is recommended to only use
			 * 			Result::Force when you are sure of the result.
			 */
			template<Result force = Result::Check>
			inline Res_Ty& Result()
			{
				/* Force bypasses checking if the function failed or not */
				if constexpr (force == Result::Check)
				{
					/* Ends the process if the result was tried to access on a failed result */
					if (m_FunctionFailed)
						EndProcess();
				}

				/* Returns a const reference to the result */
				return m_Result;
			}

			/**
			 * @brief Returns whether the function failed or not
			 */
			inline bool Failed() const { return m_FunctionFailed; }

			/**
			 * @brief Returns whether the function suceeded or not
			 */
			inline bool Success() const { return !m_FunctionFailed; }

		private:
			#ifndef DOXYGEN_HIDE

			/* Union to hold either the result or the error */
			union
			{
				Res_Ty m_Result;
				Err_Ty m_Error;
			};

			/*
			 * It appears in Doxygen even though it is within a private block
			 * which is why it is located in a pre-processor block
			 */

			#endif // DOXYGEN_HIDE

			/* Holds wether the function failed or not */
			const bool m_FunctionFailed;
	};
}
