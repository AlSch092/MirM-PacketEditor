# MirM-PacketEditor
LUA Scripter + 'Internal' Packet Editor for Mir:M  

## Includes:  
- Outbound & Inbound packet logging  
- Packet Sending  
- LUA Scripting

## How to use:
We are proxying the 'xAudio2_9redist.dll' sound library file by creating our own version, and replacing it in the game's file structure. Our module will be auto-loaded at game startup, and their anticheat mechanisms (Uncheater for UE4) will not detect this DLL since it's whitelisted as a game library. Ensure to rename the original file to "XAudio2_9redist_REAL.dll" and the compiled DLL to "XAudio2_9redist.dll".

![Alt text](pwr_score.PNG?raw=true "Sample")   
