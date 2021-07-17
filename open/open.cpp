#include "stdafx.h"

template <typename T>
int main(int argc, T argv);

int _main()
{
	auto cmdline = GetCommandLine();
	int argc = -1;
	auto argv = CommandLineToArgvW(cmdline, &argc);

	ExitProcess(main(argc, argv));
}

template <typename T>
int main(int argc, T argv)
{
	// Prevent blurry error dialogs
	SetProcessDPIAware();

	// Disable WOW64 redirection so we can use a single binary on both x86 and x64
	PVOID oldState;
	Wow64DisableWow64FsRedirection(&oldState);

	if (argc == 1)
	{
		return -1;
	}

    // For WSL support, replace backslashes with forward slashes and replace /mnt/x with X:
	for (int i = 1; i < argc; ++i)
	{
		auto prefixLen = wcslen(L"/mnt/");
		auto arg = argv[i];
		if (wcslen(arg) > (prefixLen + 2) &&
			wcsncmp(arg, L"/mnt/", prefixLen) == 0 &&
			isalpha(arg[prefixLen]) &&
			arg[prefixLen + 1] == L'/') {
			// Treat this as an absolute path to a Windows drive mounted under WSL
			auto letter = arg[prefixLen];
			arg[prefixLen] = L':';
			arg[prefixLen - 1] = letter;
			arg = argv[i] = arg + prefixLen - 1;
		}
		auto ptr = arg;
		while (ptr = wcschr(ptr, L'/'))
		{
			*ptr = '\\';
		}
	}

	SHELLEXECUTEINFO sexi{};
	sexi.cbSize = sizeof(sexi);
	sexi.lpFile = argv[1];
	// This does not trigger an "Open With" dialog for unknown file types:
	//sexi.lpVerb = _T("open");
	// Whereas this will trigger an "Open With" dialog for unknown file types:
	sexi.lpVerb = nullptr;
	sexi.nShow = SW_NORMAL; // because we are running hidden, this is required
	if (argc > 2) {
		sexi.lpParameters = argv[2];
	}

	if (ShellExecuteEx(&sexi))
	{
		return 0;
	}
	return GetLastError();
}
