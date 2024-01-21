#pragma once

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include "framework.h"
#include <windowsx.h>
#include <dxgi1_4.h>
#include <wrl.h>
#include <d3d12.h>

class D3Base
{
public:
	D3Base(HWND hWnd, int clientWidth, int clientHeight);
	virtual ~D3Base();

protected:
	void CreateCommandObjects();
	void CreateSwapChain();
	void FlushCommandQueue();
	void CreateRtvAndDsvDescriptorHeaps();

	void OnResize();

	void LogAdapters() const;
	void LogAdapterOutputs(IDXGIAdapter* adapter) const;
	void LogOutputDisplayModes(IDXGIOutput* output, DXGI_FORMAT format) const;

protected:
	HWND mHwnd;
	int mClientWidth;
	int mClientHeight;

	// Multisampling support
	bool m4xMsaaEnabled = false;
	UINT m4xMsaaQuality = 0;

	Microsoft::WRL::ComPtr<IDXGIFactory4> mDxgiFactory;
	Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
	Microsoft::WRL::ComPtr<ID3D12Device> mD3Device;

	// CPU/GPU synchronization
	Microsoft::WRL::ComPtr<ID3D12Fence> mFence;
	UINT64 mCurrentFence = 0;

	// Command list stuff
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> mCommandQueue;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> mDirectCmdListAlloc;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> mCommandList;

	// Swap chain
	static const int SwapChainBufferCount = 2;
	int mCurrBackBuffer = 0;
	Microsoft::WRL::ComPtr<ID3D12Resource> mSwapChainBuffer[SwapChainBufferCount];
	Microsoft::WRL::ComPtr<ID3D12Resource> mDepthStencilBuffer;

	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mRtvHeap;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mDsvHeap;

	D3D12_VIEWPORT	mScreenViewport;
	D3D12_RECT	mScissorRect;

	UINT mRtvDescriptorSize = 0;
	UINT mDsvDescriptorSize = 0;
	UINT mCbvSrvUavDescriptorSize = 0;

	D3D_DRIVER_TYPE D3D_DRIVER_TYPE_HARDWARE;
	DXGI_FORMAT mBackBufferFormat = DXGI_FORMAT_R8G8B8A8_UNORM;
	DXGI_FORMAT mDepthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
};

