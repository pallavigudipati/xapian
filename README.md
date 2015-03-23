Enhancing Xapian
=================
Modules added for auto-completion and auto-expansion of queries.
Also added design patterns to make further development easier in these areas.

About Xapian
============
Xapian is split into several modules, which are held in sub-directories of
the directory containing this file.  The core code and documentation is in
the xapian-core module.

If you're new to hacking on Xapian, you should probably start by reading the
xapian-core/HACKING file.  If you're new to Xapian entirely, you should
probably read the xapian-core/README file, or you can find further information
on our website at http://xapian.org/

See the section "Building from git" in xapian-core/HACKING for details
on getting started.

Experimental: we have support for building an Ubuntu VM using Vagrant
and VirtualBox. `vagrant up` will start the process, although it can
currently take a long time to download and install all the relevant
packages. See "Using a Vagrant-driven Ubuntu virtual machine" in
xapian-core/HACKING for details.
