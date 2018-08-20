/**
 * @file Others.c
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @author Eduardo Vencovsky  (https://github.com/eduvencovsky)
 * @author Guilherme Pinazza  (https://github.com/pinazza)
 *
 * @date 19/08/2018
 *
 * @brief Other functions that don't quite fit in any file are put in here
 *
 */

#include "Core.h"

void final_shutdown(void)
{
	printf("\n\n");
	printf("\n[  OK  ] Stopped target Slices");
	Sleep(50);
	printf("\n[  OK  ] Removed slice User and Session Slice");
	Sleep(50);
	printf("\n[  OK  ] Stopped target Paths");
	Sleep(50);
	printf("\n[  OK  ] Stopped CUPS Scheduler");
	Sleep(50);
	printf("\n[  OK  ] Stopped ACPI Events Check");
	printf("\n[  OK  ] Stopped Forward Password Requests to Wall Directory Watch");
	Sleep(50);
	printf("\n[  OK  ] Stopped Trigger resolvconf update for network DNS");
	Sleep(50);
	printf("\n[  OK  ] Stopped target Sockets");
	Sleep(50);
	printf("\n[  OK  ] Closed UUID daemon activation socket");
	Sleep(50);
	printf("\n[  OK  ] Closed Avahi mDNS/DNS-SD Stack Activation Socket");
	Sleep(50);
	printf("\n[  OK  ] Closed CUPS Scheduler");
	Sleep(50);
	printf("\n[  OK  ] Closed Syslog Socket");
	Sleep(50);
	printf("\n[  OK  ] Closed Socket activation for snappy daemon");
	Sleep(50);
	printf("\n[  OK  ] Closed D-Bus System Message Bus Scoket");
	Sleep(50);
	printf("\n[  OK  ] Stopped target System Initialization");
	Sleep(50);
	printf("\n[  OK  ] Stopped target Encrypted Volumes");
	Sleep(50);
	printf("\n\tStopping Network Time Synchronization...");
	Sleep(50);
	printf("\n[  OK  ] Stopped target swap");
	Sleep(50);
	printf("\n\tDeactivating swap /dev/disk/system...");
	Sleep(50);
	printf("\n\tStopping Load/Save Random Seed...");
	Sleep(50);
	printf("\n\tStopping Update UTMP about System Boot/Shutdown...");
	Sleep(50);
	printf("\n[  OK  ] Stopped Apply Kernel Variables");
	Sleep(50);
	printf("\n[  OK  ] Stopped Load Kernel Modules");
	Sleep(50);
	printf("\n\tStopping Load/Save Screen Backlight Brightness");
	Sleep(50);
	printf("\n[  OK  ] Stopped Load/Save Random Seed");
	Sleep(50);
	printf("\n[  OK  ] Stopped Load/Save Screen Backlight Brightness");
	Sleep(50);
	printf("\n[  OK  ] Stopped Update UTMP about system Boot/Shutdown");
	Sleep(50);
	printf("\n[  OK  ] Deactivated swap /dev/disk/system/sda1");
	Sleep(50);
	printf("\n[  OK  ] Deactivated swap /dev/disk/system/sda2");
	Sleep(50);
	printf("\n[  OK  ] Deactivated swap /dev/disk/system/sda3");
	Sleep(50);
	printf("\n[  OK  ] Deactivated swap /dev/disk/system/sda4");
	Sleep(50);
	printf("\n[  OK  ] Removed slice system-systemd\\x2dbacklight");
	Sleep(50);
	printf("\n[  OK  ] Stopped Network Time Synchronization");
	Sleep(50);
	printf("\n[  OK  ] Stopped Create Volatile Files and Directories");
	Sleep(50);
	printf("\n[  OK  ] Stopped target Local File Systems");
	Sleep(50);
	printf("\n\tUnmounting /run/user/108");
	Sleep(50);
	printf("\n\tUnmounting /run/user/500");
	Sleep(50);
	printf("\n[  OK  ] Unmounted /run/user/108");
	Sleep(50);
	printf("\n[  OK  ] Unmounted /run/user/500");
	Sleep(50);
	printf("\n[  OK  ] Reached target Unmount All Filesystems");
	Sleep(50);
	printf("\n[  OK  ] Stopped target Local File Systems (Pre)");
	Sleep(50);
	printf("\n[  OK  ] Stopped Remount Root and Kernel File Systems");
	Sleep(50);
	printf("\n[  OK  ] Stopped Create Static Device Nodes in /dev");
	Sleep(50);
	printf("\n[  OK  ] Reached target Shutdown");
}