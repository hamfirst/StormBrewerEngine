#pragma once

#include "Foundation/Handle/HandleList.h"

class AudioSpec;
class MusicSpec;

using AudioHandle = SpecificHandle<AudioSpec>;
using MusicHandle = SpecificHandle<MusicSpec>;
