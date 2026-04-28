/**
* @file Core.cpp.
* @brief The Core Class Implementation.
* @author Spices.
*/

#include "Pchheader.h"

#ifdef NP_PLATFORM_WINDOWS

#include "Core.h"

namespace Neptune::Direct3D12 {

	namespace {
	
		HandleResultDelegate::Handler s_Handler;   // @brief HandleResultDelegate::Handler instance.
	}

	void HandleResultDelegate::SetHandler(const Handler& fn)
	{
        NEPTUNE_PROFILE_ZONE

		s_Handler = fn;
	}

	const HandleResultDelegate::Handler& HandleResultDelegate::GetHandler()
	{
        NEPTUNE_PROFILE_ZONE

		return s_Handler;
	}

	void HandleResult(HRESULT result)
	{
        NEPTUNE_PROFILE_ZONE

		if (!FAILED(result)) return;

		const char* label = "";
		switch (result)
		{
			case D3D12_ERROR_ADAPTER_NOT_FOUND:                          label = "Cached PSO was created on a different adapter and cannot be reused";                       break;
			case D3D12_ERROR_DRIVER_VERSION_MISMATCH:                    label = "Cached PSO was created on a different driver version and cannot be reused";                break;
			case D3D12_ERROR_INVALID_REDIST:                             label = "Invalid Redist";                                                                           break;
			case E_FAIL:												 label = "Generic failure";                                                                          break;
			case E_INVALIDARG:											 label = "Invalid parameter passed to function";                                                     break;
			case E_OUTOFMEMORY:                                          label = "Out of Memory";                                                                            break;
			case E_NOTIMPL:                                              label = "Method not implemented for the given parameter combination";                               break;
			case E_ACCESSDENIED:                                         label = "Access denied";                                                                            break;
			case E_NOINTERFACE:                                          label = "No such interface supported";                                                              break;
			case DXGI_ERROR_INVALID_CALL:                                label = "Invalid method call";                                                                      break;
			case DXGI_ERROR_WAS_STILL_DRAWING:                           label = "Previous operation is still drawing";                                                      break;
			case DXGI_ERROR_DEVICE_REMOVED:                              label = "Device was removed";                                                                       break;
			case DXGI_ERROR_DEVICE_RESET:                                label = "Device was reset due to invalid command or hang";                                          break;
			case DXGI_ERROR_DRIVER_INTERNAL_ERROR:                       label = "Driver internal error occurred";                                                           break;
			case DXGI_ERROR_UNSUPPORTED:                                 label = "Operation not supported by the device or driver";                                          break;
			case DXGI_ERROR_SDK_COMPONENT_MISSING:                       label = "Debug layer requires 'Graphics Tools' optional feature. Install via Windows Settings";     break;
			case DXGI_ERROR_FRAME_STATISTICS_DISJOINT:                   label = "Frame statistics are disjoint from previous queries";                                      break;
			case DXGI_ERROR_NONEXCLUSIVE:                                label = "Could not acquire fullscreen exclusive mode";                                              break;
			case DXGI_ERROR_NOT_CURRENTLY_AVAILABLE:                     label = "Resource or operation not currently available";                                            break;
			case DXGI_ERROR_NOT_FOUND:									 label = "Requested object or resource not found";                                                   break;
			case DXGI_ERROR_WAIT_TIMEOUT:                                label = "Wait operation timed out";                                                                 break;
			default:                                                     label = "Unknown Error";                                                                            break;
		}

		std::stringstream ss;
		ss << "Direct3D12 Error: [ " << label << " ]";

        NEPTUNE_CORE_ERROR(ss.str())
	}
}

#endif