#pragma once

#define SHADER_LITERAL(...)            #__VA_ARGS__
#define SHADER_LITERAL_VER(Ver, ...)   "#version " #Ver "\n" #__VA_ARGS__
