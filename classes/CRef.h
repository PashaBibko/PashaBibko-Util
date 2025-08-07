#pragma once

namespace PashaBibko::Util
{
	template<typename Ty>
	class CRef
	{
		public:
			CRef(const Ty& _ref)
				: m_Ref(_ref)
			{}

			operator const Ty& () const { return m_Ref; }

		private:
			const Ty& m_Ref;
	};

	template<>
	class CRef<void>
	{
		public:
			CRef() = default;

			operator void() const { return; }
	};
}
