# OS-Directory-Manager

## Important TO-DOs:

* Remove all directories inside /home directory if a user is deleted including root folders (currently directories are deleted by name)
* Change global id as users are loaded from file

## Functions

### Directory related functions

* mkdir X
* cd \[X, ..]
* rmdir X (non-empty)
* pwd
* ls

### User related functions

* adduser U
* deluser U
* lock U
* unlock U
* id U (shows User info)
* logout (back to login screen)

### System related functions

* help (shows help menu)
* poweroff
* date (shows date)
* time (shows time)
* copyright (shows team's copyright)
* echo (prints parameter)

## Functioning

* Only root may use user-related functions
* Home directory for each user
* Save state to a file (and then read)
