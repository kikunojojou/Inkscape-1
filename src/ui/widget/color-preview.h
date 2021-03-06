#ifndef SEEN_COLOR_PREVIEW_H
#define SEEN_COLOR_PREVIEW_H
/*
 * Authors:
 *   Lauris Kaplinski <lauris@kaplinski.com>
 *   Ralf Stephan <ralf@ark.in-berlin.de>
 *
 * Copyright (C) 2001-2005 Authors
 * Copyright (C) 2001 Ximian, Inc.
 *
 * Released under GNU GPL, read the file 'COPYING' for more information
 */

#include <gtkmm/widget.h>

namespace Inkscape {
namespace UI {
namespace Widget {

/**
 * A simple color preview widget, mainly used within a picker button.
 */
class ColorPreview : public Gtk::Widget {
public:
    ColorPreview (guint32 rgba);
    void setRgba32 (guint32 rgba);
    GdkPixbuf* toPixbuf (int width, int height);

protected:
    void on_size_allocate (Gtk::Allocation &all) override;

    void get_preferred_height_vfunc(int& minimum_height, int& natural_height) const override;
    void get_preferred_height_for_width_vfunc(int width, int& minimum_height, int& natural_height) const override;
    void get_preferred_width_vfunc(int& minimum_width, int& natural_width) const override;
    void get_preferred_width_for_height_vfunc(int height, int& minimum_width, int& natural_width) const override;
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

    guint32 _rgba;
};

} // namespace Widget
} // namespace UI
} // namespace Inkscape

#endif // SEEN_COLOR_PREVIEW_H

/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0)(case-label . +))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4 :
