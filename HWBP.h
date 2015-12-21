class HardwareBreakpoint
{
public:
	HardwareBreakpoint() {Initialize(); }
	~HardwareBreakpoint() { CloseHandle(Handle); }

public:
	void AddBreakpoint(DWORD Address);
	void SetBreakpoints();
	void RemoveBreakpoints();

private:
	void Initialize();

private:
	HANDLE Handle = INVALID_HANDLE_VALUE;
	CONTEXT ctx;
	CONTEXT ctxOld;
	int Registers = 0;
};