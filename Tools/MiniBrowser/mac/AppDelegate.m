/*
 * Copyright (C) 2010 Apple Inc. All rights reserved.
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

#import "AppDelegate.h"

#import "SettingsController.h"
#import "WK1BrowserWindowController.h"
#import "WK2BrowserWindowController.h"
#import <WebKit/WebHistory.h>
#import <WebKit/WebKit2.h>

enum {
    WebKit1NewWindowTag = 1,
    WebKit2NewWindowTag = 2
};

@implementation BrowserAppDelegate

- (id)init
{
    self = [super init];
    if (self) {
        _browserWindowControllers = [[NSMutableSet alloc] init];
    }

    return self;
}

- (void)awakeFromNib
{
    NSMenuItem *item = [[NSMenuItem alloc] init];
    [item setSubmenu:[[SettingsController shared] menu]];
    [[NSApp mainMenu] insertItem:[item autorelease] atIndex:[[NSApp mainMenu] indexOfItemWithTitle:@"Debug"]];
}

- (IBAction)newWindow:(id)sender
{
    BrowserWindowController *controller = nil;

    BOOL useWebKit2 = NO;

    if (![sender respondsToSelector:@selector(tag)])
        useWebKit2 = [SettingsController shared].useWebKit2ByDefault;
    else
        useWebKit2 = [sender tag] == WebKit2NewWindowTag;
    
    if (!useWebKit2)
        controller = [[WK1BrowserWindowController alloc] initWithWindowNibName:@"BrowserWindow"];
#if WK_API_ENABLED
    else
        controller = [[WK2BrowserWindowController alloc] initWithWindowNibName:@"BrowserWindow"];
#endif
    if (!controller)
        return;

    [[controller window] makeKeyAndOrderFront:sender];
    [_browserWindowControllers addObject:controller];
    
    [controller loadURLString:[SettingsController shared].defaultURL];
}

- (void)browserWindowWillClose:(NSWindow *)window
{
    [_browserWindowControllers removeObject:window.windowController];
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    WebHistory *webHistory = [[WebHistory alloc] init];
    [WebHistory setOptionalSharedHistory:webHistory];
    [webHistory release];

    [self _updateNewWindowKeyEquivalents];

    [self newWindow:self];
}

- (void)applicationWillTerminate:(NSNotification *)notification
{
    for (BrowserWindowController* controller in _browserWindowControllers)
        [controller applicationTerminating];
}

- (BrowserWindowController *)frontmostBrowserWindowController
{
    for (NSWindow* window in [NSApp windows]) {
        id delegate = [window delegate];

        if (![delegate isKindOfClass:[BrowserWindowController class]])
            continue;

        BrowserWindowController *controller = (BrowserWindowController *)delegate;
        assert([_browserWindowControllers containsObject:controller]);
        return controller;
    }

    return nil;
}

- (IBAction)openDocument:(id)sender
{
    BrowserWindowController *browserWindowController = [self frontmostBrowserWindowController];

    if (browserWindowController) {
        NSOpenPanel *openPanel = [[NSOpenPanel openPanel] retain];
        [openPanel beginSheetModalForWindow:browserWindowController.window completionHandler:^(NSInteger result) {
            if (result != NSOKButton)
                return;

            NSURL *url = [openPanel.URLs objectAtIndex:0];
            [browserWindowController loadURLString:[url absoluteString]];
        }];
        return;
    }

    NSOpenPanel *openPanel = [NSOpenPanel openPanel];
    [openPanel beginWithCompletionHandler:^(NSInteger result) {
        if (result != NSOKButton)
            return;

        BrowserWindowController *newBrowserWindowController = [[WK1BrowserWindowController alloc] initWithWindowNibName:@"BrowserWindow"];
        [newBrowserWindowController.window makeKeyAndOrderFront:self];

        NSURL *url = [openPanel.URLs objectAtIndex:0];
        [newBrowserWindowController loadURLString:[url absoluteString]];
    }];
}

- (void)didChangeSettings
{
    [self _updateNewWindowKeyEquivalents];

    // Let all of the BrowserWindowControllers know that a setting changed, so they can attempt to dynamically update.
    for (BrowserWindowController<BrowserController> *browserWindowController in _browserWindowControllers)
        [browserWindowController didChangeSettings];
}

- (void)_updateNewWindowKeyEquivalents
{
    if ([[SettingsController shared] useWebKit2ByDefault]) {
        [_newWebKit1WindowItem setKeyEquivalentModifierMask:NSCommandKeyMask | NSAlternateKeyMask];
        [_newWebKit2WindowItem setKeyEquivalentModifierMask:NSCommandKeyMask];
    } else {
        [_newWebKit1WindowItem setKeyEquivalentModifierMask:NSCommandKeyMask];
        [_newWebKit2WindowItem setKeyEquivalentModifierMask:NSCommandKeyMask | NSAlternateKeyMask];
    }
}

@end
