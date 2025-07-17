#include "BytePatches.h"

#include "../Core/Core.h"

BytePatch::BytePatch(const char* sModule, const char* sSignature, int iOffset, const char* sPatch)
{
	m_sModule = sModule;
	m_sSignature = sSignature;
	m_iOffset = iOffset;

	auto vPatch = U::Memory.PatternToByte(sPatch);
	m_vPatch = vPatch;
	m_iSize = vPatch.size();
	m_vOriginal.resize(m_iSize);
}

void BytePatch::Write(std::vector<byte>& vBytes)
{
	DWORD flNewProtect, flOldProtect;
	VirtualProtect(m_pAddress, m_iSize, PAGE_EXECUTE_READWRITE, &flNewProtect);
	memcpy(m_pAddress, vBytes.data(), m_iSize);
	VirtualProtect(m_pAddress, m_iSize, flNewProtect, &flOldProtect);
}

bool BytePatch::Initialize()
{
	if (m_bIsPatched)
		return true;

	m_pAddress = LPVOID(U::Memory.FindSignature(m_sModule, m_sSignature));
	if (!m_pAddress)
	{
		U::Core.AppendFailText(std::format("BytePatch::Initialize() failed to initialize:\n  {}\n  {}", m_sModule, m_sSignature).c_str());
		return false;
	}

	m_pAddress = LPVOID(uintptr_t(m_pAddress) + m_iOffset);

	DWORD flNewProtect, flOldProtect;
	VirtualProtect(m_pAddress, m_iSize, PAGE_EXECUTE_READWRITE, &flNewProtect);
	memcpy(m_vOriginal.data(), m_pAddress, m_iSize);
	VirtualProtect(m_pAddress, m_iSize, flNewProtect, &flOldProtect);

	Write(m_vPatch);
	return m_bIsPatched = true;
}

void BytePatch::Unload()
{
	if (!m_bIsPatched)
		return;

	Write(m_vOriginal);
	m_bIsPatched = false;
}

bool CBytePatches::Initialize()
{
	m_vPatches = {
		BytePatch("engine.dll", "0F 82 ? ? ? ? 4A 63 84 2F", 0x0, "90 90 90 90 90 90"), // skybox fix
		//BytePatch("server.dll", "75 ? 44 38 A7 ? ? ? ? 75 ? 41 3B DD", 0x0, "EB"), // listen server speedhack
		BytePatch("vguimatsurface.dll", "66 83 FE ? 0F 84", 0x0, "66 83 FE 00"), // include '&' in text size	
		BytePatch("client.dll", "40 53 48 81 EC ? ? ? ? 0F B7 DA", 0xe8, "A7"), // CStorePage::DoPreviewItem
		BytePatch("client.dll", "73 ? 48 8D 0D ? ? ? ? FF 15 ? ? ? ? 32 C0", 0x0, "EB"), // engine->ClientCmd_Unrestricted( "disconnect" );

		//BytePatch("client.dll", "74 ? 8B 47 ? 8D 4F ? FF 90 ? ? ? ? 5F", 0x0, "EB"), // ResetLatched
     	//BytePatch("client.dll", "74 ? 8B 47 ? 8D 4F ? FF 90 ? ? ? ? 80 BF", 0x0, "EB"), // ResetLatchedAnimating
	    //BytePatch("client.dll", "74 7F 8B 07 8B CF FF 90 ? ? ? ? 8B 4D F8 8B F0 8B 11 FF 92 ? ? ? ? 3B C6 74 64 8B 75 F8 8B CE 6A 39 E8 ? ? ? ? 8B C8 85 C9 74 1D 8B 01 8B 80 ? ? ? ? FF D0 84 C0 74 0F 80 BE", 0x0, "EB"), // CloakedSpyCheckRemoval
	    //BytePatch("client.dll", "FF 86 ? ? ? ? 50 E8 ? ? ? ? 83 C4 04 80 B8 ? ? ? ? ? 74 0A F3 0F 10 15 ? ? ? ? EB 58 F3 0F 2A", 0x0, "90"), // m_nCritSeedRequestsBlock
		//BytePatch("engine.dll", "7B 17 B9 ? ? ? ?", 0x0, "EB"), // AntiDelayedEvents
	};

	for (auto& patch : m_vPatches)
	{
		if (!patch.Initialize())
			m_bFailed = true;
	}

	return !m_bFailed;
}

void CBytePatches::Unload()
{
	for (auto& patch : m_vPatches)
		patch.Unload();
}