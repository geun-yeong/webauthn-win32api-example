#include <Windows.h>
#include <webauthn.h>
#include <stdio.h>

void hexdump(
	const unsigned char* data,
	unsigned long length) 
{
	unsigned long offset = 0;

	while (offset < length)
	{
		printf("%08x  ", offset);

		for (int i = 0; i < 16; i++)
		{
			if (offset + i < length)
			{
				printf("%02x ", data[offset + i]);
			}
			else {
				printf("   ");
			}
		}

		printf(" |");
		for (int i = 0; i < 16; i++)
		{
			if (offset + i < length)
			{
				unsigned char ch = data[offset + i];
				printf("%c", isprint(ch) ? ch : '.');
			}
		}
		printf("|\n");

		offset += 16;
	}
}

int main(
	int argc,
	char** argv
)
{
	DWORD WebAuthnHresult = S_OK;
	WEBAUTHN_GET_CREDENTIALS_OPTIONS WebAuthnGetCredOpts = { 0, };
	PWEBAUTHN_CREDENTIAL_DETAILS_LIST pWebAuthnCredList = NULL;

	WebAuthnGetCredOpts.dwVersion = \
		WEBAUTHN_GET_CREDENTIALS_OPTIONS_CURRENT_VERSION;
	WebAuthnGetCredOpts.pwszRpId = NULL; // can be null
	WebAuthnGetCredOpts.bBrowserInPrivateMode = FALSE;

	WebAuthnHresult = WebAuthNGetPlatformCredentialList(
		&WebAuthnGetCredOpts,
		&pWebAuthnCredList
	);

	if /* error occurred */ (WebAuthnHresult != S_OK)
	{
		fprintf(
			stderr,
			"[!] WebAuthNGetPlatformCredentialList occurred an error(HRESULT = %08x)",
			WebAuthnHresult
		);

		return WebAuthnHresult;
	}
	else if /* error occurred */ (!pWebAuthnCredList)
	{
		fprintf(
			stderr,
			"[!] WebAuthNGetPlatformCredentialList returned a null"
		);

		return E_POINTER;
	}

	/* success */
	puts("[*] WebAuthNGetPlatformCredentialList was success to be invoked\n");

	for (DWORD i = 0; i < pWebAuthnCredList->cCredentialDetails; i++)
	{
		PWEBAUTHN_CREDENTIAL_DETAILS pWebAuthnCred = \
			pWebAuthnCredList->ppCredentialDetails[i];

		printf("[+] Passkey corresponding to %S was found! \n", pWebAuthnCred->pRpInformation->pwszId);

		puts("<Relying Party>");
		printf(
			" %S (Displayed: %S)\n",
			pWebAuthnCred->pRpInformation->pwszId,
			pWebAuthnCred->pRpInformation->pwszName
		);

		puts("<User>");
		printf(
			" %S (Displayed: %S)\n",
			pWebAuthnCred->pUserInformation->pwszName,
			pWebAuthnCred->pUserInformation->pwszDisplayName
		);

		puts("<Credential ID>");
		hexdump(
			pWebAuthnCred->pbCredentialID,
			pWebAuthnCred->cbCredentialID
		);

		puts("");
	}

	return 0;
}