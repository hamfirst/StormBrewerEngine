
#pragma once

static const char * g_ProjectZones[] = {
    "us-west2-a",
    "australia-southeast1-b",
    "asia-east2-c",
    "northamerica-northeast1-a",
    "europe-west2-b",
    "europe-west3-c",
    "asia-south1-c"
};

static const char * g_ProjectZoneUrls[] = {
  "http://35.236.45.25/ping",
  "http://35.189.6.113/ping",
  "http://35.220.162.209/ping",
  "http://35.203.57.164/ping",
  "http://35.189.67.146/ping",
  "http://35.198.78.172/ping",
  "http://35.200.186.152/ping"
};

static const int kNumProjectZones = sizeof(g_ProjectZones) / sizeof(g_ProjectZones[0]);
