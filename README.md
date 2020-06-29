# Introduction
This dll file allows you to interact with ```steam_api.dll``` in the game that made using RPG Maker VX Ace.

To use a Steam Overlay, it has to use a OpenGL/DirectX Renderer(Device) in your game. 
But a default RPG Maker VX Ace is used the Windows GDI, so it doesn't have a hardware acceleration.

To implemention it properly, you need to replace your main executable binary as <a href="https://forums.rpgmakerweb.com/index.php?threads/rgd-directx-implementation-of-rgss3.95228/">[RGD] DirectX implementation of RGSS3</a>

Before using this dll, you need to change a file called ```pch.cpp``` and compile it.

```c++
void InitWithSteamAPI() 
{
	// k_uAppIdInvalid must change as your own app id
	if (SteamAPI_RestartAppIfNecessary(k_uAppIdInvalid))
	{
		return;
	}

	// ...

}

```

after compiling it, you have to download a new binary for binding steam at <a href="https://github.com/biud436/SteamBind">SteamBind</a>