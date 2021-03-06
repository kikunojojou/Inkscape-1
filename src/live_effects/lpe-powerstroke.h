/** @file
 * @brief PowerStroke LPE effect, see lpe-powerstroke.cpp.
 */
/* Authors:
 *   Johan Engelen <j.b.c.engelen@alumnus.utwente.nl>
 *
 * Copyright (C) 2010-2011 Authors
 *
 * Released under GNU GPL, read the file 'COPYING' for more information
 */

#ifndef INKSCAPE_LPE_POWERSTROKE_H
#define INKSCAPE_LPE_POWERSTROKE_H

#include "live_effects/parameter/enum.h"
#include "live_effects/effect.h"
#include "live_effects/parameter/bool.h"
#include "live_effects/parameter/powerstrokepointarray.h"

namespace Inkscape {
namespace LivePathEffect {

class LPEPowerStroke : public Effect {
public:
    LPEPowerStroke(LivePathEffectObject *lpeobject);
    ~LPEPowerStroke() override;

    
    Geom::PathVector doEffect_path (Geom::PathVector const & path_in) override;
    void doBeforeEffect(SPLPEItem const *lpeItem) override;
    void doOnApply(SPLPEItem const* lpeitem) override;
    void doOnRemove(SPLPEItem const* lpeitem) override;

    // methods called by path-manipulator upon edits
    void adjustForNewPath(Geom::PathVector const & path_in);

    PowerStrokePointArrayParam offset_points;

private:
    BoolParam sort_points;
    EnumParam<unsigned> interpolator_type;
    ScalarParam interpolator_beta;
    ScalarParam scale_width;
    EnumParam<unsigned> start_linecap_type;
    EnumParam<unsigned> linejoin_type;
    ScalarParam miter_limit;
    EnumParam<unsigned> end_linecap_type;
    LPEPowerStroke(const LPEPowerStroke&) = delete;
    LPEPowerStroke& operator=(const LPEPowerStroke&) = delete;
};

} //namespace LivePathEffect
} //namespace Inkscape

#endif

/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0)(case-label . +))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:fileencoding=utf-8:textwidth=99 :
