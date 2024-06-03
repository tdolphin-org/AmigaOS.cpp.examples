//
// AmigaOS CPP Examples
//
// (c) 2023-2024 TDolphin
//

//
// AmiSSL scope (amisslmaster.library & amissl & bsdscoket)
// opens & init on constructor, closes on destructor
// throws exception if library is already open or on error opening library
//

#include "AmiSSLScope.hpp"

#include <stdexcept>

#include <proto/amissl.h>
#include <proto/amisslmaster.h>
#include <proto/exec.h>

struct Library *AmiSSLBase = nullptr;

AmiSSLScope::AmiSSLScope()
{
    if (AmiSSLBase != nullptr)
    {
        std::string error = (std::string) __PRETTY_FUNCTION__ + " AmiSSL already open!";
        throw std::runtime_error(error);
    }

    if (!(AmiSSLBase = OpenAmiSSL()))
    {
        std::string error = (std::string) __PRETTY_FUNCTION__ + " failed to open AmiSSL";
        throw std::runtime_error(error);
    }

    if (InitAmiSSL(AmiSSL_ErrNoPtr, (unsigned long)&errno, AmiSSL_SocketBase, (unsigned long)mBSDSocketBaseScope.get(), TAG_DONE) != 0)
    {
        CloseAmiSSL();
        AmiSSLBase = nullptr;

        std::string error = (std::string) __PRETTY_FUNCTION__ + " failed to initialize AmiSSL!";
        throw std::runtime_error(error);
    }
}

AmiSSLScope::~AmiSSLScope()
{
    if (AmiSSLBase != nullptr)
    {
        CloseAmiSSL();
        AmiSSLBase = nullptr;
    }
}

Library *AmiSSLScope::get() const
{
    return AmiSSLBase;
}
