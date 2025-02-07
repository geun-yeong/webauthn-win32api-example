#include <Windows.h>
#include <webauthn.h>
#include <stdio.h>

int main(
	int argc,
	char** argv
)
{
	DWORD WebAuthnApiVersion = 0;

	WebAuthnApiVersion = WebAuthNGetApiVersionNumber();

	printf("WebAuthN API Version = %d\n", WebAuthnApiVersion);

	return 0;
}