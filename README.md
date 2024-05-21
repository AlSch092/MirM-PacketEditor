# MirM-PacketEditor
LUA Scripter + 'Internal' Packet Editor for Mir:M  

## Includes:  
- Outbound & Inbound packet logging  
- Packet Sending  
- LUA Scripting

## How to use:
We are proxying the 'xAudio2_9.dll' sound library file by creating our own version, and replacing it in the game's file structure. Our module will be auto-loaded at game startup, and their anticheat mechanisms (Uncheater for UE4) will not detect this DLL since it's whitelisted as a game library.

![Alt text](pwr_score.PNG?raw=true "Sample")   
