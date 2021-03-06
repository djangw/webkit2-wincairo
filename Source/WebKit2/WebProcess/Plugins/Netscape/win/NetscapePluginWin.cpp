/*
 * Copyright (C) 2010 Apple Inc. All rights reserved.
 * Copyright (C) 2010 University of Szeged
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "NetscapePlugin.h"

#if ENABLE(NETSCAPE_PLUGIN_API)

#include "PluginController.h"
#include "WebEvent.h"
#include <WebCore/GraphicsContext.h>
#include <WebCore/NotImplemented.h>

using namespace WebCore;

namespace WebKit {

void NetscapePlugin::platformPreInitialize()
{
    notImplemented();
}

bool NetscapePlugin::platformPostInitialize()
{
    notImplemented();
    return true;
}

void NetscapePlugin::platformDestroy()
{
    notImplemented();
}

bool NetscapePlugin::platformInvalidate(const IntRect&)
{
    notImplemented();
    return false;
}

void NetscapePlugin::platformGeometryDidChange()
{
    notImplemented();
}

void NetscapePlugin::platformVisibilityDidChange()
{
    notImplemented();
}

void NetscapePlugin::platformPaint(GraphicsContext* context, const IntRect& dirtyRect, bool /*isSnapshot*/)
{
    notImplemented();
}

bool NetscapePlugin::platformHandleMouseEvent(const WebMouseEvent& event)
{
    notImplemented();
    return false;
}

bool NetscapePlugin::platformHandleWheelEvent(const WebWheelEvent& event)
{
    notImplemented();
    return false;
}

void NetscapePlugin::platformSetFocus(bool focusIn)
{
    notImplemented();
}

bool NetscapePlugin::wantsPluginRelativeNPWindowCoordinates()
{
    notImplemented();
    return true;
}

bool NetscapePlugin::platformHandleMouseEnterEvent(const WebMouseEvent& event)
{
    notImplemented();
    return false;
}

bool NetscapePlugin::platformHandleMouseLeaveEvent(const WebMouseEvent& event)
{
    notImplemented();
    return false;
}

bool NetscapePlugin::platformHandleKeyboardEvent(const WebKeyboardEvent& event)
{
    notImplemented();
    return false;
}

} // namespace WebKit

#endif // PLUGIN_ARCHITECTURE(X11) && ENABLE(NETSCAPE_PLUGIN_API)
