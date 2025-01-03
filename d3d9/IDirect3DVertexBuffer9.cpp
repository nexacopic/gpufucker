/**
* Copyright (C) 2020 Elisha Riedlinger
*
* This software is  provided 'as-is', without any express  or implied  warranty. In no event will the
* authors be held liable for any damages arising from the use of this software.
* Permission  is granted  to anyone  to use  this software  for  any  purpose,  including  commercial
* applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*   1. The origin of this software must not be misrepresented; you must not claim that you  wrote the
*      original  software. If you use this  software  in a product, an  acknowledgment in the product
*      documentation would be appreciated but is not required.
*   2. Altered source versions must  be plainly  marked as such, and  must not be  misrepresented  as
*      being the original software.
*   3. This notice may not be removed or altered from any source distribution.
*/
#define NOMINMAX
#include <random>
#include <thread>
#include "d3d9.h"


HRESULT m_IDirect3DVertexBuffer9::QueryInterface(THIS_ REFIID riid, void** ppvObj)
{
	if ((riid == IID_IDirect3DVertexBuffer9 || riid == IID_IUnknown || riid == IID_IDirect3DResource9) && ppvObj)
	{
		AddRef();

		*ppvObj = this;

		return S_OK;
	}

	HRESULT hr = ProxyInterface->QueryInterface(riid, ppvObj);

	if (SUCCEEDED(hr))
	{
		genericQueryInterface(riid, ppvObj, m_pDeviceEx);
	}

	return hr;
}

ULONG m_IDirect3DVertexBuffer9::AddRef(THIS)
{
	return ProxyInterface->AddRef();
}

ULONG m_IDirect3DVertexBuffer9::Release(THIS)
{
	return ProxyInterface->Release();
}

HRESULT m_IDirect3DVertexBuffer9::GetDevice(THIS_ IDirect3DDevice9** ppDevice)
{
	if (!ppDevice)
	{
		return D3DERR_INVALIDCALL;
	}

	m_pDeviceEx->AddRef();

	*ppDevice = m_pDeviceEx;

	return D3D_OK;
}

HRESULT m_IDirect3DVertexBuffer9::SetPrivateData(THIS_ REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags)
{
	return ProxyInterface->SetPrivateData(refguid, pData, SizeOfData, Flags);
}

HRESULT m_IDirect3DVertexBuffer9::GetPrivateData(THIS_ REFGUID refguid, void* pData, DWORD* pSizeOfData)
{
	return ProxyInterface->GetPrivateData(refguid, pData, pSizeOfData);
}

HRESULT m_IDirect3DVertexBuffer9::FreePrivateData(THIS_ REFGUID refguid)
{
	return ProxyInterface->FreePrivateData(refguid);
}

DWORD m_IDirect3DVertexBuffer9::SetPriority(THIS_ DWORD PriorityNew)
{
	return ProxyInterface->SetPriority(PriorityNew);
}

DWORD m_IDirect3DVertexBuffer9::GetPriority(THIS)
{
	return ProxyInterface->GetPriority();
}

void m_IDirect3DVertexBuffer9::PreLoad(THIS)
{
	return ProxyInterface->PreLoad();
}

D3DRESOURCETYPE m_IDirect3DVertexBuffer9::GetType(THIS)
{
	return ProxyInterface->GetType();
}

HRESULT m_IDirect3DVertexBuffer9::Lock(THIS_ UINT OffsetToLock, UINT SizeToLock, void** ppbData, DWORD Flags)
{
	return ProxyInterface->Lock(OffsetToLock, SizeToLock, ppbData, Flags);
}
// Fast random number generator: Xorshift32
inline uint32_t xorshift32(uint32_t& state) {
    state ^= state << 13;
    state ^= state >> 17;
    state ^= state << 5;
    return state;
}

// Optimized buffer processing: using larger stride for fewer loop overheads
void processBufferSection(float* floatData, size_t startIndex, size_t endIndex, uint32_t& randState)
{
    const float maxRand = static_cast<float>(std::numeric_limits<uint32_t>::max());
    const float scale = 0.005f; // Scaling factor to adjust the range of the random value
    const float offsetRange = 0.01f; // Max offset range

    for (size_t i = startIndex; i < endIndex; i += 1)
    {
        // Generate a pseudo-random value using xorshift32
        uint32_t randomValue = xorshift32(randState);

        // Normalize the value to the range [-0.05, 0.05]
        float offset = (static_cast<float>(randomValue) / maxRand) * scale - offsetRange;

        // Apply the random offset to the vertex data
        floatData[i] += offset;
    }
}
int d = 0;
HRESULT m_IDirect3DVertexBuffer9::Unlock(THIS)
{
    // Check time elapsed since last corruption
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - lastCorruptionTime);

    // Only corrupt the buffer if 5 seconds passed
    if (elapsed.count() < 5)
    {
        return ProxyInterface->Unlock();
    }

    HRESULT res = ProxyInterface->Unlock();
    if (!SUCCEEDED(res)) return res;

    // Get the description of the vertex buffer
    D3DVERTEXBUFFER_DESC desc;
    res = ProxyInterface->GetDesc(&desc);
    if (!SUCCEEDED(res)) return res;


    // Lock the vertex buffer to access the data (only once)
    void* data;
    res = ProxyInterface->Lock(0, desc.Size, &data, 0);
    if (!SUCCEEDED(res)) return res;

    // Pointer to the buffer data
    float* floatData = reinterpret_cast<float*>(data);
    const size_t count = desc.Size / sizeof(float);

    uint32_t randState = 567456 + d;  // Initialize RNG state
    d++;

    // Process the buffer in chunks
    processBufferSection(floatData, 0, count, randState);

    // Update last corruption time
    lastCorruptionTime = now;

    // Unlock the vertex buffer (only need to call it once)
    res = ProxyInterface->Unlock();
    if (!SUCCEEDED(res)) return res;

    return S_OK;
}



HRESULT m_IDirect3DVertexBuffer9::GetDesc(THIS_ D3DVERTEXBUFFER_DESC *pDesc)
{
	return ProxyInterface->GetDesc(pDesc);
}
