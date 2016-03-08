/*
 * Copyright (C) 2004, 2005, 2006, 2008 Nikolas Zimmermann <zimmermann@kde.org>
 * Copyright (C) 2004, 2005, 2006 Rob Buis <buis@kde.org>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef SVGCircleElement_h
#define SVGCircleElement_h

#include "SVGAnimatedBoolean.h"
#include "SVGAnimatedLength.h"
#include "SVGExternalResourcesRequired.h"
#include "SVGGraphicsElement.h"

namespace WebCore {

class SVGCircleElement final : public SVGGraphicsElement,
                               public SVGExternalResourcesRequired {
public:
    static PassRefPtr<SVGCircleElement> create(const QualifiedName&, Document&);

private:
    SVGCircleElement(const QualifiedName&, Document&);

    virtual bool isValid() const override { return SVGTests::isValid(); }

    bool isSupportedAttribute(const QualifiedName&);
    virtual void parseAttribute(const QualifiedName&, const AtomicString&) override;
    virtual void svgAttributeChanged(const QualifiedName&) override;

    virtual bool selfHasRelativeLengths() const override { return true; }

    virtual RenderPtr<RenderElement> createElementRenderer(PassRef<RenderStyle>) override;

    BEGIN_DECLARE_ANIMATED_PROPERTIES(SVGCircleElement)
        DECLARE_ANIMATED_LENGTH(Cx, cx)
        DECLARE_ANIMATED_LENGTH(Cy, cy)
        DECLARE_ANIMATED_LENGTH(R, r)
        DECLARE_ANIMATED_BOOLEAN(ExternalResourcesRequired, externalResourcesRequired)
    END_DECLARE_ANIMATED_PROPERTIES
};

NODE_TYPE_CASTS(SVGCircleElement)

} // namespace WebCore

#endif // SVGCircleElement_h
