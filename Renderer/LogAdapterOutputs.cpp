#include "D3Base.h"
#include <windowsx.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include "Utilities.h"

void D3Base::LogAdapterOutputs(IDXGIAdapter* adapter) const
{
	UINT i = 0;
	IDXGIOutput* output = nullptr;
	while (adapter->EnumOutputs(i, &output) != DXGI_ERROR_NOT_FOUND)
	{
		DXGI_OUTPUT_DESC desc;
		output->GetDesc(&desc);

		std::wstring text = L"***Output: ";
		text += desc.DeviceName;
		text += L"\n";
		OutputDebugString(text.c_str());

		LogOutputDisplayModes(output, mBackBufferFormat);

		ReleaseCom(output);

		++i;
	}
}