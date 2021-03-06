/*
 * Copyright (C) 2014 Daewoong Jang (daewoong.jang@navercorp.com)
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "PluginProcessMainWin.h"

#if ENABLE(NETSCAPE_PLUGIN_API)

#include "Logging.h"
#include "NetscapePlugin.h"
#include "PluginProcess.h"
#include "WebKit2Initialize.h"
#include <wtf/RunLoop.h>

using namespace WebCore;

namespace WebKit {

WK_EXPORT int PluginProcessMainWin(int argc, char* argv[])
{
    ASSERT_UNUSED(argc, argc == 3);

    InitializeWebKit2();

    HANDLE socket = reinterpret_cast<HANDLE>(atoi(argv[1]));

    WebKit::ChildProcessInitializationParameters parameters;
    parameters.connectionIdentifier = socket;
    parameters.extraInitializationData.add("plugin-path", argv[2]);

    WebKit::PluginProcess::shared().initialize(parameters);

    RunLoop::run();

    return 0;
}

} // namespace WebKit

#endif
