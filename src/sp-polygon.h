#ifndef __SP_POLYGON_H__
#define __SP_POLYGON_H__

/*
 * SVG <polygon> implementation
 *
 * Authors:
 *   Lauris Kaplinski <lauris@kaplinski.com>
 *
 * Copyright (C) 1999-2002 Lauris Kaplinski
 * Copyright (C) 2000-2001 Ximian, Inc.
 *
 * Released under GNU GPL, read the file 'COPYING' for more information
 */

#include "sp-shape.h"

#define SP_TYPE_POLYGON (sp_polygon_get_type ())
#define SP_POLYGON(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), SP_TYPE_POLYGON, SPPolygon))
#define SP_POLYGON_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), SP_TYPE_POLYGON, SPPolygonClass))
#define SP_IS_POLYGON(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), SP_TYPE_POLYGON))
#define SP_IS_POLYGON_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), SP_TYPE_POLYGON))

class CPolygon;

class SPPolygon : public SPShape {
public:
	CPolygon* cpolygon;
};

struct SPPolygonClass {
	SPShapeClass parent_class;
};


class CPolygon : public CShape {
public:
	CPolygon(SPPolygon* polygon);
	virtual ~CPolygon();

	virtual void build(SPDocument *document, Inkscape::XML::Node *repr);
	virtual Inkscape::XML::Node* write(Inkscape::XML::Document *xml_doc, Inkscape::XML::Node *repr, guint flags);
	virtual void set(unsigned int key, gchar const* value);
	virtual gchar* description();

protected:
	SPPolygon* sppolygon;
};


GType sp_polygon_get_type (void);

// made 'public' so that SPCurve can set it as friend:
void sp_polygon_set(SPObject *object, unsigned int key, const gchar *value);

#endif
