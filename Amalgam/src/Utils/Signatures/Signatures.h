#pragma once
#include "../Feature/Feature.h"
#include <cstdint>
#include <vector>

class CSignature
{
private:
	uintptr_t m_dwVal;
	const char* m_pszDLLName;
	const char* m_pszSignature;
	int m_nOffset;
	const char* m_pszName;

public:
	CSignature(const char* sDLLName, const char* sSignature, int nOffset, const char* sName);

	bool Initialize();

	inline uintptr_t operator()()
	{
		return m_dwVal;
	}

	template <typename T>
	inline T As()
	{
		return reinterpret_cast<T>(m_dwVal);
	}

	template <typename T, typename... Args> 
	inline T Call(Args... args) const
	{
		return reinterpret_cast<T(__fastcall*)(Args...)>(m_dwVal)(args...);
	}

	template <typename T>
	inline T Offset(const int iOffset)
	{
		if (m_dwVal)
			m_dwVal += iOffset;

		return *this;
	}

	template <typename T>
	inline T Deref(int iCount = 1)
	{
		uintptr_t m_pOut = m_dwVal;

		while (m_pOut && iCount > 0)
		{
			m_pOut = *reinterpret_cast<T>(m_pOut);

			if (!m_pOut)
				return m_dwVal;

			iCount--;
		}

		m_dwVal = m_pOut;
		return *this;
	}

	template <typename T>
	inline T FixRip(const int iOffset = 1)
	{
		if (m_dwVal && iOffset)
		{
			uintptr_t m_pBase = m_dwVal + iOffset;
			auto m_pRipAddress = *reinterpret_cast<T>(m_pBase);
			m_pBase += 4 + m_pRipAddress;
			m_dwVal = m_pBase;
		}

		return *this;
	}
};

#define MAKE_SIGNATURE(name, dll, sig, offset) namespace S { inline CSignature name(dll, sig, offset, #name); }

class CSignatures
{
private:
	std::vector<CSignature*> m_vSignatures = {};
	bool m_bFailed = false;

public:
	bool Initialize();

	inline void AddSignature(CSignature* pSignature)
	{
		m_vSignatures.push_back(pSignature);
	}
};

ADD_FEATURE_CUSTOM(CSignatures, Signatures, U);

#define SIGNATURE(name, type, sig, ...) inline type name() \
{ \
	return S::sig##_##name.Call<type>(##__VA_ARGS__); \
}

#define SIGNATURE_ARGS(name, type, sig, args, ...) inline type name##args \
{ \
	return S::sig##_##name.Call<type>(##__VA_ARGS__); \
}