/*
 * Authors:
 *   Ted Gould <ted@gould.cx>
 *
 * Copyright (C) 2007 Authors
 *
 * Released under GNU GPL v2+, read the file 'COPYING' for more information
 */

#include <list>

#include "main-cmdlineact.h"

#include "desktop.h"
#include "document.h"
#include "file.h"
#include "inkscape.h"
#include "selection.h"
#include "verbs.h"

#include "helper/action.h"

#include "ui/view/view.h"

#include <glibmm/i18n.h>

namespace Inkscape {

std::list <CmdLineAction *> CmdLineAction::_list;

CmdLineAction::CmdLineAction (bool isVerb, gchar const * arg) : _isVerb(isVerb), _arg(nullptr) {
    if (arg != nullptr) {
        _arg = g_strdup(arg);
    }

    _list.insert(_list.end(), this);

    return;
}

CmdLineAction::~CmdLineAction () {
    if (_arg != nullptr) {
        g_free(_arg);
    }
}

bool
CmdLineAction::isExtended() {
    return false;
}

void
CmdLineAction::doItX (ActionContext const & context)
{
    (void)context;
    printf("CmdLineAction::doItX() %s\n", _arg);
}

void
CmdLineAction::doIt (ActionContext const & context) {
    //printf("Doing: %s\n", _arg);
    if (_isVerb) {
        if (isExtended()) {
            doItX(context);
            return;
        }

        Inkscape::Verb * verb = Inkscape::Verb::getbyid(_arg);
        if (verb == nullptr) {
            printf(_("Unable to find verb ID '%s' specified on the command line.\n"), _arg);
            return;
        }
        SPAction * action = verb->get_action(context);
        sp_action_perform(action, nullptr);
    } else {
        if (context.getDocument() == nullptr || context.getSelection() == nullptr) { return; }

        SPDocument * doc = context.getDocument();
        SPObject * obj = doc->getObjectById(_arg);
        if (obj == nullptr) {
            printf(_("Unable to find node ID: '%s'\n"), _arg);
            return;
        }

        Inkscape::Selection * selection = context.getSelection();
        selection->add(obj);
    }
    return;
}

bool
CmdLineAction::doList (ActionContext const & context) {
    bool hasActions = !_list.empty();
    for (std::list<CmdLineAction *>::iterator i = _list.begin(); i != _list.end(); ++i) {
        CmdLineAction * entry = *i;
        entry->doIt(context);
    }
    return hasActions;
}

bool
CmdLineAction::idle () {
    std::list<SPDesktop *> desktops;
    INKSCAPE.get_all_desktops(desktops);

    // We're going to assume one desktop per document, because no one
    // should have had time to make more at this point.
    for (std::list<SPDesktop *>::iterator i = desktops.begin();
            i != desktops.end(); ++i) {
        SPDesktop * desktop = *i;
        //Inkscape::UI::View::View * view = dynamic_cast<Inkscape::UI::View::View *>(desktop);    
        doList(ActionContext(desktop));
    }
    return false;
}

} // Inkscape

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
