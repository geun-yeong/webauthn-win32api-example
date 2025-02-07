# WebAuthN Win32API Examples

This repository contains example projects demonstrating how to use the WebAuthN Win32 API.

These projects use Windows SDK 10.0.26100 and were built with Visual Studio Community 2022 (v17.3.6).

Project details:

- **WebAuthN API Version**

  Displays the version of the WebAuthN API installed on your Windows system.

- **WebAuthN Credential List**

  Displays a list of WebAuthN credentials stored on your Windows system.

  The list corresponds to the passkey list, which can also be viewed in *Windows Settings > Accounts > Passkeys*.

Note:

- You should add 'webauthn.lib' to *Project Properties > Configuration Properties > Linker > Input > Additional Dependencies*

  ![webauthn_lib_added](https://github.com/user-attachments/assets/50248b86-24b4-4387-8050-12198eb2d602)

---

Anyone is free to use this code anytime, anywhere.