#pragma once
#include "struct.h"
#include "overlay.h"
#include "driver.h"

DRV* DBD = new DRV();

bool esp = false;
bool espLine = false;
bool EnnemiESp = false;
bool distanceESp = false;
bool name = false;
bool mate = false;

bool showmenu = true;
bool rendering = true;
int frame = 0;
FOverlay* g_overlay;

float ScreenCenterX;
float ScreenCenterY;

float FOV = 40;
float distanceMax = 250;

uint64_t process_base = 0;
uint32_t process_id = 0;


