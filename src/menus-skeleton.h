#ifndef SEEN_MENUS_SKELETON_H
#define SEEN_MENUS_SKELETON_H

#ifdef __cplusplus
#undef N_
#define N_(x) x
#endif

static char const menus_skeleton[] =
"<inkscape\n"
"  xmlns:sodipodi=\"http://sodipodi.sourceforge.net/DTD/sodipodi-0.dtd\"\n"
"  xmlns:inkscape=\"http://www.inkscape.org/namespaces/inkscape\">\n"
"\n"
"   <submenu name=\"" N_("_File") "\">\n"
"       <verb verb-id=\"FileQuit\" />\n"
"   </submenu>\n"
"</inkscape>\n";

#define MENUS_SKELETON_SIZE (sizeof(menus_skeleton) - 1)


#endif /* !SEEN_MENUS_SKELETON_H */

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
