#include <game/gt.hpp>
#include <utils/memory.hpp>

#include <string>
#include <stdexcept>
#include <windows.h>

typedef NTSTATUS(_stdcall* _ZwQueryInformationProcess)(
	HANDLE ProcessHandle,
	DWORD ProcessInformationClass,
	PVOID ProcessInformation,
	ULONG ProcessInformationLength,
	PULONG ReturnLength
	);

typedef NTSTATUS(_stdcall* _ZwQuerySystemInformation)(
	DWORD SystemInformationClass,
	PVOID SystemInformation,
	ULONG SystemInformationLength,
	PULONG ReturnLength
	);

typedef NTSTATUS(_stdcall* _ZwQueryObject)(
	HANDLE ObjectHandle,
	DWORD ObjectInformationClass,
	PVOID ObjectInformation,
	ULONG ObjectInformationLength,
	PULONG ReturnLength
	);

typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR Buffer;
} UNICODE_STRING, * PUNICODE_STRING;

typedef struct _OBJECT_NAME_INFORMATION {
	UNICODE_STRING Name;
} OBJECT_NAME_INFORMATION, * POBJECT_NAME_INFORMATION;

typedef struct _SYSTEM_HANDLE {
	DWORD ProcessId;
	BYTE ObjectTypeNumber;
	BYTE Flags;
	USHORT Handle;
	PVOID Object;
	ACCESS_MASK GrantedAccess;
} SYSTEM_HANDLE, * PSYSTEM_HANDLE;

typedef struct _SYSTEM_HANDLE_INFORMATION {
	DWORD HandleCount;
	SYSTEM_HANDLE Handles[1];
} SYSTEM_HANDLE_INFORMATION, * PSYSTEM_HANDLE_INFORMATION;

typedef struct _PROCESS_BASIC_INFORMATION {
	PVOID Reserved1;
	PVOID PebBaseAddress;
	PVOID Reserved2[2];
	ULONG_PTR UniqueProcessId;
	PVOID Reserved3;
} PROCESS_BASIC_INFORMATION, * PPROCESS_BASIC_INFORMATION;

void gt::close_mutexes() {
	std::uintptr_t mutex_check = memory::find_pattern("0f 84 ? ? ? ? 48 8b c8 ff 15");

	if (mutex_check == 0)
		throw std::runtime_error("mutex check pattern not found");

	if (!memory::patch_bytes(mutex_check, "90 90 90 90 90 90"))
		throw std::runtime_error("failed to patch mutex check");


	HMODULE ntdll = LoadLibraryA("ntdll.dll");
	_ZwQueryInformationProcess ZwQueryInformationProcess = (_ZwQueryInformationProcess)GetProcAddress(ntdll, "ZwQueryInformationProcess");
	_ZwQuerySystemInformation ZwQuerySystemInformation = (_ZwQuerySystemInformation)GetProcAddress(ntdll, "ZwQuerySystemInformation");
	_ZwQueryObject ZwQueryObject = (_ZwQueryObject)GetProcAddress(ntdll, "ZwQueryObject");

	DWORD process_id;
	GetWindowThreadProcessId(gt::hwnd, &process_id);
	HANDLE process_handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, process_id);

	PROCESS_BASIC_INFORMATION pbi;
	ULONG size = 0;
	ZwQueryInformationProcess(process_handle, 0, &pbi, sizeof(pbi), &size);

	// get system handle information
	SYSTEM_HANDLE_INFORMATION* pshi = nullptr;
	ULONG pshi_size = 0;
	ULONG bytes_needed = 0;
	do {
		pshi_size += 0x10000;
		pshi = (SYSTEM_HANDLE_INFORMATION*)std::realloc(pshi, pshi_size);
		std::memset(pshi, 0, pshi_size);
		ZwQuerySystemInformation(16, pshi, pshi_size, &bytes_needed);
	} while (bytes_needed >= pshi_size);

	for (DWORD i = 0; i < pshi->HandleCount; ++i) {
		const auto& handle = pshi->Handles[i];

		if (handle.ProcessId != process_id) // check if it's in gt process
			continue;

		if (handle.ObjectTypeNumber != 17 && handle.ObjectTypeNumber != 20) // check if it's the mutex type
			continue;

		// get name information
		POBJECT_NAME_INFORMATION poni = nullptr;
		ULONG poni_size = 0;
		ZwQueryObject((HANDLE)pshi->Handles, 1, poni, poni_size, &bytes_needed);
		do {
			poni_size += 0x1000;
			poni = (POBJECT_NAME_INFORMATION)std::realloc(poni, poni_size);
			std::memset(poni, 0, poni_size);
			ZwQueryObject((HANDLE)handle.Handle, 1, poni, poni_size, &bytes_needed);
		} while (bytes_needed >= poni_size);

		// if it's "Growtopia" mutex, close it
		if (poni->Name.Buffer != nullptr) 
			if (std::wstring{ poni->Name.Buffer }.ends_with(L"BaseNamedObjects\\Growtopia")) 
				CloseHandle((HANDLE)handle.Handle);

		std::free(poni);
	}

	std::free(pshi);
	CloseHandle(process_handle);
}
