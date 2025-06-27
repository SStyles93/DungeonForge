#pragma once

#ifndef PXP_EXPORTS
#define PXP_DF_API __declspec(dllexport)
#else
#define PXP_DF_API __declspec(dllimport)
#endif