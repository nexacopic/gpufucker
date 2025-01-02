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

#include "d3d9.h"

Direct3DShaderValidatorCreate9Proc m_pDirect3DShaderValidatorCreate9;
PSGPErrorProc m_pPSGPError;
PSGPSampleTextureProc m_pPSGPSampleTexture;
D3DPERF_BeginEventProc m_pD3DPERF_BeginEvent;
D3DPERF_EndEventProc m_pD3DPERF_EndEvent;
D3DPERF_GetStatusProc m_pD3DPERF_GetStatus;
D3DPERF_QueryRepeatFrameProc m_pD3DPERF_QueryRepeatFrame;
D3DPERF_SetMarkerProc m_pD3DPERF_SetMarker;
D3DPERF_SetOptionsProc m_pD3DPERF_SetOptions;
D3DPERF_SetRegionProc m_pD3DPERF_SetRegion;
DebugSetLevelProc m_pDebugSetLevel;
DebugSetMuteProc m_pDebugSetMute;
Direct3D9EnableMaximizedWindowedModeShimProc m_pDirect3D9EnableMaximizedWindowedModeShim;
Direct3DCreate9Proc m_pDirect3DCreate9;
Direct3DCreate9ExProc m_pDirect3DCreate9Ex;

bool WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	static HMODULE d3d9dll = nullptr;

	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		// Create log window and redirect output to the console
		FreeConsole();
		AllocConsole();
		SetConsoleTitle(TEXT("GPUFUCKER"));

		// Redirect stdout to the new console
		freopen("CONOUT$", "w", stdout); // Redirect stdout to the console

		// Output to console
		printf("[ info ] attached\n");

		// Load DLL
		char path[MAX_PATH];
		GetSystemDirectoryA(path, MAX_PATH);
		strcat_s(path, "\\d3d9.dll");
		printf("[ info ] loading original d3d9 from \"%s\"\n", path);
		d3d9dll = LoadLibraryA(path);

		// Get function addresses and output to console
		printf("[ info ] getting function \"Direct3DShaderValidatorCreate9\"\n");
		m_pDirect3DShaderValidatorCreate9 = (Direct3DShaderValidatorCreate9Proc)GetProcAddress(d3d9dll, "Direct3DShaderValidatorCreate9");
		printf("[ info ] got function \"Direct3DShaderValidatorCreate9\"\n");

		printf("[ info ] getting function \"PSGPError\"\n");
		m_pPSGPError = (PSGPErrorProc)GetProcAddress(d3d9dll, "PSGPError");
		printf("[ info ] got function \"PSGPError\"\n");

		printf("[ info ] getting function \"PSGPSampleTexture\"\n");
		m_pPSGPSampleTexture = (PSGPSampleTextureProc)GetProcAddress(d3d9dll, "PSGPSampleTexture");
		printf("[ info ] got function \"PSGPSampleTexture\"\n");

		printf("[ info ] getting function \"D3DPERF_BeginEvent\"\n");
		m_pD3DPERF_BeginEvent = (D3DPERF_BeginEventProc)GetProcAddress(d3d9dll, "D3DPERF_BeginEvent");
		printf("[ info ] got function \"D3DPERF_BeginEvent\"\n");

		printf("[ info ] getting function \"D3DPERF_EndEvent\"\n");
		m_pD3DPERF_EndEvent = (D3DPERF_EndEventProc)GetProcAddress(d3d9dll, "D3DPERF_EndEvent");
		printf("[ info ] got function \"D3DPERF_EndEvent\"\n");

		printf("[ info ] getting function \"D3DPERF_GetStatus\"\n");
		m_pD3DPERF_GetStatus = (D3DPERF_GetStatusProc)GetProcAddress(d3d9dll, "D3DPERF_GetStatus");
		printf("[ info ] got function \"D3DPERF_GetStatus\"\n");

		printf("[ info ] getting function \"D3DPERF_QueryRepeatFrame\"\n");
		m_pD3DPERF_QueryRepeatFrame = (D3DPERF_QueryRepeatFrameProc)GetProcAddress(d3d9dll, "D3DPERF_QueryRepeatFrame");
		printf("[ info ] got function \"D3DPERF_QueryRepeatFrame\"\n");

		printf("[ info ] getting function \"D3DPERF_SetMarker\"\n");
		m_pD3DPERF_SetMarker = (D3DPERF_SetMarkerProc)GetProcAddress(d3d9dll, "D3DPERF_SetMarker");
		printf("[ info ] got function \"D3DPERF_SetMarker\"\n");

		printf("[ info ] getting function \"D3DPERF_SetOptions\"\n");
		m_pD3DPERF_SetOptions = (D3DPERF_SetOptionsProc)GetProcAddress(d3d9dll, "D3DPERF_SetOptions");
		printf("[ info ] got function \"D3DPERF_SetOptions\"\n");

		printf("[ info ] getting function \"D3DPERF_SetRegion\"\n");
		m_pD3DPERF_SetRegion = (D3DPERF_SetRegionProc)GetProcAddress(d3d9dll, "D3DPERF_SetRegion");
		printf("[ info ] got function \"D3DPERF_SetRegion\"\n");

		printf("[ info ] getting function \"DebugSetLevel\"\n");
		m_pDebugSetLevel = (DebugSetLevelProc)GetProcAddress(d3d9dll, "DebugSetLevel");
		printf("[ info ] got function \"DebugSetLevel\"\n");

		printf("[ info ] getting function \"DebugSetMute\"\n");
		m_pDebugSetMute = (DebugSetMuteProc)GetProcAddress(d3d9dll, "DebugSetMute");
		printf("[ info ] got function \"DebugSetMute\"\n");

		printf("[ info ] getting function \"Direct3D9EnableMaximizedWindowedModeShim\"\n");
		m_pDirect3D9EnableMaximizedWindowedModeShim = (Direct3D9EnableMaximizedWindowedModeShimProc)GetProcAddress(d3d9dll, "Direct3D9EnableMaximizedWindowedModeShim");
		printf("[ info ] got function \"Direct3D9EnableMaximizedWindowedModeShim\"\n");

		printf("[ info ] getting function \"Direct3DCreate9\"\n");
		m_pDirect3DCreate9 = (Direct3DCreate9Proc)GetProcAddress(d3d9dll, "Direct3DCreate9");
		printf("[ info ] got function \"Direct3DCreate9\"\n");

		printf("[ info ] getting function \"Direct3DCreate9Ex\"\n");
		m_pDirect3DCreate9Ex = (Direct3DCreate9ExProc)GetProcAddress(d3d9dll, "Direct3DCreate9Ex");
		printf("[ info ] got function \"Direct3DCreate9Ex\"\n");

		break;

	case DLL_PROCESS_DETACH:
		FreeConsole();
		FreeLibrary(d3d9dll);
		printf("[ info ] DLL detached.\n");
		break;
	}

	return true;
}

HRESULT WINAPI Direct3DShaderValidatorCreate9()
{
	if (!m_pDirect3DShaderValidatorCreate9)
	{
		return E_FAIL;
	}

	return m_pDirect3DShaderValidatorCreate9();
}

HRESULT WINAPI PSGPError()
{
	if (!m_pPSGPError)
	{
		return E_FAIL;
	}

	return m_pPSGPError();
}

HRESULT WINAPI PSGPSampleTexture()
{
	if (!m_pPSGPSampleTexture)
	{
		return E_FAIL;
	}

	return m_pPSGPSampleTexture();
}

int WINAPI D3DPERF_BeginEvent(D3DCOLOR col, LPCWSTR wszName)
{
	if (!m_pD3DPERF_BeginEvent)
	{
		return NULL;
	}

	return m_pD3DPERF_BeginEvent(col, wszName);
}

int WINAPI D3DPERF_EndEvent()
{
	if (!m_pD3DPERF_EndEvent)
	{
		return NULL;
	}

	return m_pD3DPERF_EndEvent();
}

DWORD WINAPI D3DPERF_GetStatus()
{
	if (!m_pD3DPERF_GetStatus)
	{
		return NULL;
	}

	return m_pD3DPERF_GetStatus();
}

BOOL WINAPI D3DPERF_QueryRepeatFrame()
{
	if (!m_pD3DPERF_QueryRepeatFrame)
	{
		return FALSE;
	}

	return m_pD3DPERF_QueryRepeatFrame();
}

void WINAPI D3DPERF_SetMarker(D3DCOLOR col, LPCWSTR wszName)
{
	if (!m_pD3DPERF_SetMarker)
	{
		return;
	}

	return m_pD3DPERF_SetMarker(col, wszName);
}

void WINAPI D3DPERF_SetOptions(DWORD dwOptions)
{
	if (!m_pD3DPERF_SetOptions)
	{
		return;
	}

	return m_pD3DPERF_SetOptions(dwOptions);
}

void WINAPI D3DPERF_SetRegion(D3DCOLOR col, LPCWSTR wszName)
{
	if (!m_pD3DPERF_SetRegion)
	{
		return;
	}

	return m_pD3DPERF_SetRegion(col, wszName);
}

HRESULT WINAPI DebugSetLevel(DWORD dw1)
{
	if (!m_pDebugSetLevel)
	{
		return E_FAIL;
	}

	return m_pDebugSetLevel(dw1);
}

void WINAPI DebugSetMute()
{
	if (!m_pDebugSetMute)
	{
		return;
	}

	return m_pDebugSetMute();
}

int WINAPI Direct3D9EnableMaximizedWindowedModeShim(BOOL mEnable)
{
	return m_pDirect3D9EnableMaximizedWindowedModeShim(mEnable);
}

IDirect3D9 *WINAPI Direct3DCreate9(UINT SDKVersion)
{
	if (!m_pDirect3DCreate9)
	{
		return nullptr;
	}

	IDirect3D9 *pD3D9 = m_pDirect3DCreate9(SDKVersion);

	if (pD3D9)
	{
		return new m_IDirect3D9Ex((IDirect3D9Ex*)pD3D9, IID_IDirect3D9);
	}

	return nullptr;
}

HRESULT WINAPI Direct3DCreate9Ex(UINT SDKVersion, IDirect3D9Ex **ppD3D)
{
	if (!m_pDirect3DCreate9Ex)
	{
		return E_FAIL;
	}

	HRESULT hr = m_pDirect3DCreate9Ex(SDKVersion, ppD3D);

	if (SUCCEEDED(hr) && ppD3D)
	{
		*ppD3D = new m_IDirect3D9Ex(*ppD3D, IID_IDirect3D9Ex);
	}

	return hr;
}
