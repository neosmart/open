#include "stdafx.h"

template <typename T>
int main(int argc, T argv);

int _main()
{
	auto cmdline = GetCommandLine();
	int argc = -1;
	auto argv = CommandLineToArgvW(cmdline, &argc);

	auto array = new TCHAR *[argc];
	for (int i = 0; i < argc; ++i)
	{
		array[i] = argv[i];
	}

	ExitProcess(main(argc, argv));
}

template <typename T>
int main(int argc, T argv)
{
	//Prevent blurry error dialogs
	SetProcessDPIAware();

	//Disable WOW64 redirection so we can use a single binary on both x86 and x64
	PVOID oldState;
	Wow64DisableWow64FsRedirection(&oldState);

	if (argc == 1)
	{
		return -1;
	}

	SHELLEXECUTEINFO sexi{};
	sexi.cbSize = sizeof(sexi);
	sexi.lpFile = argv[1];
	//sexi.lpVerb = _T("open"); //does not trigger an "Open With" dialog
	sexi.lpVerb = nullptr; //this will trigger an "Open With" dialog for unknown file types
	sexi.nShow = SW_NORMAL; //because we are running hidden, this is required
	
	if (ShellExecuteEx(&sexi))
	{
		return 0;
	}
	return GetLastError();
}
