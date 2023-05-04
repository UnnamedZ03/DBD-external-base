#pragma once
#include "global.h"
#include "ESP.h"
#include <thread>
#include <iostream>
HWND hGameWnd;
HWND hOverlayWnd;
RECT wndRect;

void Update() {
    while (true)
    {
        if (rendering)
        {
            if (GetAsyncKeyState(VK_F1) & 1)
                if (showmenu)
                    esp = !esp;

            if (GetAsyncKeyState(VK_F2) & 1)
                if (showmenu)
                    distanceESp = !distanceESp;

            if (GetAsyncKeyState(VK_F4) & 1)
                if (showmenu)
                    espLine = !espLine;

            if (GetAsyncKeyState(VK_F5) & 1)
                if (showmenu)
                    name = !name;

            if (GetAsyncKeyState(VK_F6) & 1)
                if (showmenu)
                    mate = !mate;

            if (GetAsyncKeyState(VK_UP) & 1)
            {
                if (showmenu)
                    if (distanceMax < 350)
                        distanceMax = distanceMax + 10.f;
            }
            if (GetAsyncKeyState(VK_DOWN) & 1)
            {
                if (showmenu)
                    if (distanceMax > 10)
                        distanceMax = distanceMax - 10.f;
            }

            if (GetAsyncKeyState(VK_LEFT) & 1)
            {
                if (showmenu)
                    if (FOV < 800)
                        FOV = FOV + 1.f;
            }
            if (GetAsyncKeyState(VK_RIGHT) & 1)
            {
                if (showmenu)
                    if (FOV > 10)
                        FOV = FOV - 1.f;
            }
        }
        if (GetAsyncKeyState(VK_INSERT) & 1)
            showmenu = !showmenu;
    }
}

static void render(FOverlay* overlay) {
    while (true) {
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        overlay->begin_scene();
        overlay->clear_scene();
        frame++;
        RenderMenu();
        ESPLoop();
        RenderESP();
        overlay->end_scene();
    }
}

static void _init(FOverlay* overlay) {
    if (!overlay->window_init()) {
        printf("[!] Error init overlay window\n");
        Sleep(5000);
        return;
    }
    else {
        printf("[+] init overlay window\n");

    }

    if (!overlay->init_d2d())
        return;
    std::thread([&]() {  BaseThread2(); }).detach();
    std::thread r(render, overlay);
    std::thread up(Update);

    r.join();
    up.detach();
    overlay->d2d_shutdown();
    return;
}

int main()
{
    DRV::Init();
    std::cout << "[+] Waiting For DBD" << std::endl;
    while (!DBD->Attach("DeadByDaylight-Win64-Shipping.exe"))
    {
        Sleep(20);
    }

    // ###################################################### I was checking to see if everything was okay ###################################################### \\


    process_base = DBD->GetModuleBase();
    std::cout << "[+] Found DBD Base ---> " << "0x" << std::hex << process_base << std::dec << std::endl;

    uWorld = DBD->rpm<uintptr_t>(process_base + offsets::GWorld);
    std::cout << "[+] Found Uworld = " << "0x" << std::hex << uWorld << std::dec << std::endl;

    gameInstance = DBD->rpm<uintptr_t>(uWorld + offsets::OwningGameInstance);
    std::cout << "[+] Found gameInstance = " << "0x" << std::hex << gameInstance << std::dec << std::endl;

    persistentLevel = DBD->rpm<uintptr_t>(uWorld + offsets::PersistentLevel);
    std::cout << "[+] Found persistentLevel = " << "0x" << std::hex << persistentLevel << std::dec << std::endl;

    localPlayerPtr = DBD->rpm<uintptr_t>(gameInstance + offsets::LocalPlayers);
    std::cout << "[+] Found LocalPlayerPtr = " << "0x" << std::hex << localPlayerPtr << std::dec << std::endl;

    localPlayer = DBD->rpm<uintptr_t>(localPlayerPtr);
    std::cout << "[+] Found LocalPlayer = " << "0x" << std::hex << localPlayer << std::dec << std::endl;

    playerController = DBD->rpm<uintptr_t>(localPlayer + offsets::PlayerController);
    std::cout << "[+] Found playerController = " << "0x" << std::hex << playerController << std::dec << std::endl;

    PlayerStateLocalPlayer = DBD->rpm<uintptr_t>(playerController + offsets::PlayerStateLocalPlayer);
    std::cout << "[+] Found PlayerStateLocalPlayer = " << "0x" << std::hex << PlayerStateLocalPlayer << std::dec << std::endl;

    Localpawn = DBD->rpm<uintptr_t>(playerController + offsets::AcknowledgedPawn);
    std::cout << "[+] Found Pawn = " << "0x" << std::hex << Localpawn << std::dec << std::endl;

    cameraManager = DBD->rpm<uintptr_t>(playerController + offsets::PlayerCameraManager);
    std::cout << "[+] Found cameraManager = " << "0x" << std::hex << cameraManager << std::dec << std::endl;

    cameraCache = DBD->rpm<FCameraCacheEntry>(cameraManager + offsets::CameraCachePrivate);
    std::cout << "[+] Found Camera Cache x POV Rotation = " << cameraCache.POV.Rotation.x << std::endl;

    actorsArray = DBD->rpm<uintptr_t>(persistentLevel + offsets::ActorArray);
    std::cout << "[+] Found Actor Array = " << "0x" << std::hex << actorsArray << std::dec << std::endl;

    actorsCount = DBD->rpm<int>(persistentLevel + offsets::ActorCount);
    std::cout << "[+] Found Actor Count = " << actorsCount << std::endl;

    // ###################################################### I was checking to see if everything was okay ###################################################### \\

    RECT desktop;
    const HWND hDesktop = GetDesktopWindow();
    GetWindowRect(hDesktop, &desktop);
    HDC monitor = GetDC(hDesktop);
    int current = GetDeviceCaps(monitor, VERTRES);
    int total = GetDeviceCaps(monitor, DESKTOPVERTRES);
    ScreenCenterX = GetSystemMetrics(SM_CXSCREEN) / 2;
    ScreenCenterY = GetSystemMetrics(SM_CYSCREEN) / 2;
    g_overlay = { 0 };
    _init(g_overlay);
}