#include "Main.h"

void HardwareBreakpoint::AddBreakpoint(DWORD Address)
{
	switch (Registers)
	{
	case 0:
		ctx.Dr0 = Address;

	default:
		return;
	}
	++Registers;
}

void HardwareBreakpoint::SetBreakpoints()
{
	SetThreadContext(Handle, &ctx);
}

void HardwareBreakpoint::RemoveBreakpoints()
{
	SetThreadContext(Handle, &ctxOld);
}

void HardwareBreakpoint::Initialize()
{
	Handle = GetCurrentThread();

	GetThreadContext(Handle, &ctxOld);

	ZeroMemory(&ctx, sizeof(CONTEXT));
	ctx = { CONTEXT_DEBUG_REGISTERS };
	ctx.Dr7 = 1;
}