template <DWORD GKey, DWORD GLength>
class GString
{
public:
	char String[GLength];

public:
	GString(const char* Str);
	~GString() { ZeroMemory(&String, sizeof(String)); }
};

template <DWORD GKey, DWORD GLength>
GString<GKey, GLength>::GString(const char* Str)
{
	for (int i = 0; i < (int)GLength; ++i)
	{
		BYTE _Xor = ((i + 1) * GLength) % 256;
		String[i] = (char)(GKey ^ (Str[i] - _Xor));
	}

	String[GLength] = 0;
}