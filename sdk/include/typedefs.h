/*
 * PROJECT:     FiveOS SDK
 * LICENSE:     GPL-2.0+ (https://spdx.org/licenses/GPL-2.0+)
 * PURPOSE:     Type definitions and useful macros
 * COPYRIGHT:   Copyright 2021 Scott Maday <coldasdryice1@gmail.com>
 *              Copyright 2007 Hervé Poussineau (hpoussin@reactos.org)
 *              Copyright 2007 Colin Finck (colin@reactos.org)
 */

#pragma once

#include <assert.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>

/* Function attributes for GCC */
#if !defined(_MSC_VER) && !defined(__fastcall)
#define __fastcall __attribute__((fastcall))
#endif
#if !defined(_MSC_VER) && !defined(__cdecl)
#define __cdecl __attribute__((cdecl))
#endif
#if !defined(_MSC_VER) && !defined(__stdcall)
#define __stdcall __attribute__((stdcall))
#endif

/* Basic definitions */
#define UNIMPLEMENTED { printf("%s unimplemented\n", __FUNCTION__); exit(1); }
#define UNIMPLEMENTED_ONCE { printf("%s unimplemented\n", __FUNCTION__); exit(1); }
#define ASSERT(x) assert(x)
#define ASSERTMSG(m, x) assert(x)
#define DPRINT if (0) printf
#define DPRINT1 printf

#define NTAPI
#define WINAPI

#define IN
#define OUT
#define OPTIONAL

#define FALSE 0
#define TRUE  1

#define ANYSIZE_ARRAY 1

/* Basic types
   Emulate a LLP64 memory model using a LP64 compiler */
typedef void VOID, *PVOID, *LPVOID;
typedef char CHAR, CCHAR, *PCHAR, *PSTR, *LPSTR;
typedef const char *PCSTR, *LPCSTR;
typedef unsigned char UCHAR, *PUCHAR, BYTE, *LPBYTE, BOOLEAN, *PBOOLEAN;
typedef uint8_t UINT8;
typedef int16_t SHORT, *PSHORT;
typedef uint16_t USHORT, *PUSHORT, WORD, *PWORD, *LPWORD, WCHAR, *PWCHAR, *PWSTR, *LPWSTR, UINT16;
typedef const uint16_t *PCWSTR, *LPCWSTR;
typedef int32_t INT, LONG, *PLONG, *LPLONG, BOOL, WINBOOL, INT32;
typedef uint32_t UINT, *PUINT, *LPUINT, ULONG, *PULONG, DWORD, *PDWORD, *LPDWORD, UINT32;
#if defined(_LP64)
typedef int64_t LONG_PTR, *PLONG_PTR, INT_PTR, *PINT_PTR;
typedef uint64_t ULONG_PTR, DWORD_PTR, *PULONG_PTR, UINT_PTR, *PUINT_PTR;
#else
typedef int32_t LONG_PTR, *PLONG_PTR, INT_PTR, *PINT_PTR;
typedef uint32_t ULONG_PTR, DWORD_PTR, *PULONG_PTR, UINT_PTR, *PUINT_PTR;
#endif
typedef uint64_t ULONG64, DWORD64, *PDWORD64, UINT64, ULONGLONG;
typedef int64_t LONGLONG, LONG64, INT64;
typedef float FLOAT;
typedef double DOUBLE;

/* Derived types */
typedef PVOID HANDLE;
#ifndef _HAVE_HKEY
typedef HANDLE HKEY, *PHKEY;
#endif
typedef HANDLE HMODULE, HINSTANCE;
typedef INT NTSTATUS, POOL_TYPE;
typedef LONG HRESULT;
typedef ULONG_PTR SIZE_T, *PSIZE_T;
typedef WORD LANGID;

#define MAXUSHORT USHRT_MAX

/* Widely used structures */

#ifndef _HAVE_RTL_BITMAP
typedef struct _RTL_BITMAP
{
    ULONG  SizeOfBitMap;
    PULONG  Buffer;
} RTL_BITMAP, *PRTL_BITMAP;

typedef struct _RTL_BITMAP_RUN
{
    ULONG StartingIndex;
    ULONG NumberOfBits;
} RTL_BITMAP_RUN, *PRTL_BITMAP_RUN;
#endif

#ifndef _HAVE_LARGE_INTEGER
typedef union _LARGE_INTEGER
{
    struct
    {
        ULONG LowPart;
        LONG HighPart;
    };
    struct
    {
        ULONG LowPart;
        LONG HighPart;
    } u;
    LONGLONG QuadPart;
} LARGE_INTEGER, *PLARGE_INTEGER;
#endif

#ifndef _HAVE_LIST_ENTRY
typedef struct _LIST_ENTRY
{
    struct _LIST_ENTRY *Flink;
    struct _LIST_ENTRY *Blink;
} LIST_ENTRY,*PLIST_ENTRY;
#endif

#ifndef _HAVE_ANSI_STRING
typedef struct _ANSI_STRING
{
    USHORT Length;
    USHORT MaximumLength;
    PSTR   Buffer;
} ANSI_STRING, *PANSI_STRING;

typedef struct _UNICODE_STRING
{
    USHORT Length;
    USHORT MaximumLength;
    PWSTR  Buffer;
} UNICODE_STRING, *PUNICODE_STRING;
#endif

#ifndef _HAVE_ANSI_STRING
typedef const UNICODE_STRING *PCUNICODE_STRING;
#endif

/* Widely used macros */
#define LOBYTE(w)               ((BYTE)(w))
#define HIBYTE(w)               ((BYTE)(((WORD)(w)>>8)&0xFF))
#define LOWORD(l)               ((WORD)((DWORD_PTR)(l)))
#define HIWORD(l)               ((WORD)(((DWORD_PTR)(l)>>16)&0xFFFF))
#define MAKEWORD(a,b)           ((WORD)(((BYTE)(a))|(((WORD)((BYTE)(b)))<<8)))
#define MAKELONG(a,b)           ((LONG)(((WORD)(a))|(((DWORD)((WORD)(b)))<<16)))

#define MAXULONG 0xFFFFFFFF

#define NT_SUCCESS(x)           ((x)>=0)
#if !defined(__GNUC__)
#define FIELD_OFFSET(t,f)       ((LONG)(LONG_PTR)&(((t*) 0)->f))
#else
#define FIELD_OFFSET(t,f)       ((LONG)__builtin_offsetof(t,f))
#endif
#define RTL_CONSTANT_STRING(s)  { sizeof(s)-sizeof((s)[0]), sizeof(s), s }
#define CONTAINING_RECORD(address, type, field)  ((type *)(((ULONG_PTR)address) - (ULONG_PTR)(&(((type *)0)->field))))

#define RtlZeroMemory(Destination, Length)            memset(Destination, 0, Length)
#define RtlCopyMemory(Destination, Source, Length)    memcpy(Destination, Source, Length)
#define RtlMoveMemory(Destination, Source, Length)    memmove(Destination, Source, Length)

#define MAKELANGID(p,s)         ((((WORD)(s))<<10)|(WORD)(p))
#define PRIMARYLANGID(l)        ((WORD)(l)&0x3ff)
#define SUBLANGID(l)            ((WORD)(l)>>10)
#define SUBLANG_NEUTRAL         0x00
