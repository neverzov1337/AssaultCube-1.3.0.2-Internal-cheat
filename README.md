# AssaultCube-1.3.0.2-Internal-cheat
This is a cheat that hooks game commands, allowing you to create your own custom commands

Example: 

    if (strcmp(text, "rapid") == 0) {
        isRapid = !isRapid;
        return print_original("Rapid has been enabled", "", "");
    }

Change value in memory:

    if (isRapid == true) {
            *(int*)(*localplayer + 0x158) = 0;
            *(int*)(*localplayer + 0x160) = 0;
            *(int*)(*localplayer + 0x164) = 0;
    }

List of commands:

    /rapid
    /health
    /ammo
    /armor

