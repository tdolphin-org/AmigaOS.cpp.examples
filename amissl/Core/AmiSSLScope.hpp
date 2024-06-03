//
// AmigaOS CPP Examples
//
// (c) 2023-2024 TDolphin
//

#include "AmiSSLMasterBaseScope.hpp"
#include "../../bsdsocket/Core/BSDSocketBaseScope.hpp"

class AmiSSLScope
{
    BSDSocketBaseScope mBSDSocketBaseScope;
    AmiSSLMasterBaseScope mAmiSSLMasterBaseScope;

  public:
    AmiSSLScope();
    ~AmiSSLScope();

    Library *get() const;
};
