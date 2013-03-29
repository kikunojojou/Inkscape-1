#ifndef SEEN_SP_CLIPPATH_H
#define SEEN_SP_CLIPPATH_H

/*
 * SVG <clipPath> implementation
 *
 * Authors:
 *   Lauris Kaplinski <lauris@kaplinski.com>
 *   Abhishek Sharma
 *   Jon A. Cruz <jon@joncruz.org>
 *
 * Copyright (C) 2001-2002 authors
 * Copyright (C) 2001 Ximian, Inc.
 *
 * Released under GNU GPL, read the file 'COPYING' for more information
 */

#define SP_TYPE_CLIPPATH (sp_clippath_get_type())
#define SP_CLIPPATH(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), SP_TYPE_CLIPPATH, SPClipPath))
#define SP_CLIPPATH_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST((klass), SP_TYPE_CLIPPATH, SPClipPathClass))
#define SP_IS_CLIPPATH(obj) (G_TYPE_CHECK_INSTANCE_TYPE((obj), SP_TYPE_CLIPPATH))
#define SP_IS_CLIPPATH_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE((klass), SP_TYPE_CLIPPATH))

struct SPClipPathView;

#include "sp-object-group.h"
#include "uri-references.h"
#include "xml/node.h"

GType sp_clippath_get_type() G_GNUC_CONST;

namespace Inkscape {

class Drawing;
class DrawingItem;

} // namespace Inkscape

class CClipPath;

class SPClipPath : public SPObjectGroup {
public:
	CClipPath* cclippath;

    class Reference;

    unsigned int clipPathUnits_set : 1;
    unsigned int clipPathUnits : 1;

    SPClipPathView *display;
    static const gchar *create(GSList *reprs, SPDocument *document, Geom::Affine const* applyTransform);
    static GType sp_clippath_get_type(void);

    Inkscape::DrawingItem *show(Inkscape::Drawing &drawing, unsigned int key);
    void hide(unsigned int key);

    void setBBox(unsigned int key, Geom::OptRect const &bbox);
    Geom::OptRect geometricBounds(Geom::Affine const &transform);

private:
    friend class SPClipPathClass;
};

class SPClipPathClass {
public:
    SPObjectGroupClass parent_class;

private:
    friend class SPClipPath;
};


class CClipPath : public CObjectGroup {
public:
	CClipPath(SPClipPath* clippath);
	virtual ~CClipPath();

	virtual void build(SPDocument* doc, Inkscape::XML::Node* repr);
	virtual void release();

	virtual void child_added(Inkscape::XML::Node* child, Inkscape::XML::Node* ref);

	virtual void set(unsigned int key, const gchar* value);

	virtual void update(SPCtx* ctx, unsigned int flags);
	virtual void modified(unsigned int flags);

	virtual Inkscape::XML::Node* write(Inkscape::XML::Document* doc, Inkscape::XML::Node* repr, guint flags);

protected:
	SPClipPath* spclippath;
};


class SPClipPathReference : public Inkscape::URIReference {
public:
    SPClipPathReference(SPObject *obj) : URIReference(obj) {}
    SPClipPath *getObject() const {
        return static_cast<SPClipPath *>(URIReference::getObject());
    }

protected:
    /**
     * If the owner element of this reference (the element with <... clippath="...">)
     * is a child of the clippath it refers to, return false.
     * \return false if obj is not a clippath or if obj is a parent of this
     *         reference's owner element.  True otherwise.
     */
    virtual bool _acceptObject(SPObject *obj) const {
        if (!SP_IS_CLIPPATH(obj)) {
            return false;
        }
        SPObject * const owner = this->getOwner();
        if (obj->isAncestorOf(owner)) {
            //XML Tree being used directly here while it shouldn't be...
            Inkscape::XML::Node * const owner_repr = owner->getRepr();
            //XML Tree being used directly here while it shouldn't be...
            Inkscape::XML::Node * const obj_repr = obj->getRepr();
            gchar const * owner_name = NULL;
            gchar const * owner_clippath = NULL;
            gchar const * obj_name = NULL;
            gchar const * obj_id = NULL;
            if (owner_repr != NULL) {
                owner_name = owner_repr->name();
                owner_clippath = owner_repr->attribute("clippath");
            }
            if (obj_repr != NULL) {
                obj_name = obj_repr->name();
                obj_id = obj_repr->attribute("id");
            }
            g_warning("Ignoring recursive clippath reference "
                      "<%s clippath=\"%s\"> in <%s id=\"%s\">",
                      owner_name, owner_clippath,
                      obj_name, obj_id);
            return false;
        }
        return true;
    }
};

#endif // SEEN_SP_CLIPPATH_H

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
