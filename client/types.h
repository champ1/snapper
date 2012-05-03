/*
 * Copyright (c) 2012 Novell, Inc.
 *
 * All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as published
 * by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, contact Novell, Inc.
 *
 * To contact Novell about this file by physical or electronic mail, you may
 * find current contact information at www.novell.com.
 */


#include <string>
#include <list>
#include <map>

using std::string;
using std::list;
using std::map;

#include "dbus/DBusConnection.h"
#include "dbus/DBusMessage.h"


struct XConfigInfo
{
    string config_name;
    string subvolume;
};


enum XSnapshotType { XSINGLE, XPRE, XPOST };


struct XSnapshot
{
    XSnapshotType getType() const { return type; }

    unsigned int getNum() const { return num; }
    bool isCurrent() const { return num == 0; }

    time_t getDate() const { return date; }

    unsigned int getPreNum() const { return pre_num; }

    string getDescription() const { return description; }

    string getCleanup() const { return cleanup; }

    map<string, string> getUserdata() const { return userdata; }

    XSnapshotType type;
    unsigned int num;
    time_t date;
    unsigned int pre_num;
    string description;
    string cleanup;
    map<string, string> userdata;
};


struct XSnapshots
{
    typedef list<XSnapshot>::const_iterator const_iterator;

    const_iterator begin() const { return entries.begin(); }

    const_iterator end() const { return entries.end(); }

    const_iterator findPost(const_iterator pre) const;

    list<XSnapshot> entries;
};


struct XFile
{
    string status;
    string name;
    bool undo;
};


struct XUndo
{
    string name;
    bool undo;
};


struct XUndoStatistic
{
    bool empty() const;

    unsigned int numCreate;
    unsigned int numModify;
    unsigned int numDelete;
};


namespace DBus
{

    template <> struct TypeInfo<XSnapshot> { static const char* signature; };
    template <> struct TypeInfo<XConfigInfo> { static const char* signature; };
    template <> struct TypeInfo<XFile> { static const char* signature; };
    template <> struct TypeInfo<XUndo> { static const char* signature; };

    Hihi& operator>>(Hihi& hihi, XConfigInfo& data);
    Hihi& operator>>(Hihi& hihi, XSnapshotType& data);
    Hihi& operator>>(Hihi& hihi, XSnapshot& data);
    Hihi& operator>>(Hihi& hihi, XFile& data);

    Hoho& operator<<(Hoho& hoho, XSnapshotType data);
    Hoho& operator<<(Hoho& hoho, const XUndo& data);

};

